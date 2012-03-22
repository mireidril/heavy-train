#include "ActualGame.hpp"

double PhysicalObject::fixedTimestepAccumulatorRatio;

/*
 * ActualGame Constructor
 */
ActualGame::ActualGame(unsigned int level, unsigned int island)
: m_lastPosXTrain (INFINITE)
, m_actualBlock(0)
{
	std::cout << "Actual Game" << std::endl;
	b2Vec2 gravity(0.0f, -10.0f);
	// Construct a world object, which will hold and simulate the rigid bodies.
	m_world = new b2World(gravity);
	PhysicalObject::m_world = m_world;
	// Pour caler la simulation avec le framerate
	fixedTimestepAccumulator = 0;
	fixedTimestepAccumulatorRatio = 0;
	m_world->SetAutoClearForces (false);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	m_timeStep = 1.0f / 30.0f;
	m_velocityIterations = 6;
	m_positionIterations = 2;

	//Charge le niveau
	m_actualLevel= new Level(m_world, level, island);

	/* test pour tracer le train */
	m_train = new Train();
	m_train->build(m_world);

	fooDrawInstance = new DebugDraw;
	uint32 flags = 0;
	flags += 1			* b2Draw::e_shapeBit;
	flags += 1			* b2Draw::e_jointBit;
	flags += 0		* b2Draw::e_aabbBit;
	flags += 0				* b2Draw::e_centerOfMassBit;
	fooDrawInstance->SetFlags(flags);
	m_world->SetDebugDraw( fooDrawInstance );

	m_starDustScore = 0;
	m_obstacleScore = 0;
	m_animalsFactor = -1.5;
	m_satisfactionScore = 0;
}
ActualGame::~ActualGame()
{
	delete m_actualLevel;
	delete m_train;
	delete fooDrawInstance;
	//supprimer m_world
	b2Body * body = m_world->GetBodyList();
	while(body != NULL)
	{
		m_world->DestroyBody(body);
		body = m_world->GetBodyList();
	}
}

/*
 * ActualGame run: est appele dans le game Engine: update le world et dessine les elements
 */
void ActualGame::run(SDL_Surface * screen, int w, int h)
{

	//Calcule FPS
	static double current_time = 0;
	static double last_time = 0;
	static int n = 0;
	static int fps = n;

	n++;
	current_time = SDL_GetTicks () / 1000.0;

	if ((current_time - last_time) >= 1.0)
    {
		// nombre de frames par seconde
		fps = n;
		n = 0;
		last_time = current_time;
    }
	//std::cout<<"FPS : "<<fps<<std::endl;

	//Actualise la simulation
	runSimulation();
	
	//Dessine le niveau & le train
	updateActualBlock();
	scroll();

	m_actualLevel->render(screen, w, h, this, m_world);

	m_train->drawSprite(screen,w,h);

	fooDrawInstance->SetFlags( b2Draw::e_shapeBit );
	//Affichage des formes physiques pour Debug
	m_world->DrawDebugData();
}

void ActualGame::updateActualBlock()
{
	double headLocoX = m_train->getLocoBodyPosition().x /*+ m_train->getBodySize().x*/;

	Block * actualBlock = m_actualLevel->getBlock(m_actualBlock);
	if(actualBlock != NULL)
	{
		double posX = actualBlock->getPosInMeters();
		double endPosX = actualBlock->getEndBlockPosInMeters();
		if(headLocoX > endPosX )
		{
			if(m_actualBlock + 1 < m_actualLevel->getNbBlocks() )
				m_actualBlock++;
		}
		else if(headLocoX < posX )
		{
			if(m_actualBlock - 1 >= 0 )
				m_actualBlock--;
		}
	}
}

void ActualGame::scroll()
{
	//Récupération de la dernière position du train
 	b2Vec2 currentPos = m_train->getLocoBodyPosition();
	if( m_lastPosXTrain != INFINITE )
	{
		double x = m_lastPosXTrain - currentPos.x;
		Sprite::convertMetersToPixels(&x, NULL, WINDOWS_W, WINDOWS_H);

		m_actualLevel->scrollLevel(x);
	}
	m_lastPosXTrain = currentPos.x;
}

void ActualGame::runSimulation()
{
	//Pour caler la simulation physique avec le framerate
	float dt = (float) SDL_GetTicks()/1000.f;
	const int MAX_STEPS = 5;
 
	fixedTimestepAccumulator += dt;
	const int nSteps = static_cast<int> ( std::floor (fixedTimestepAccumulator / m_timeStep) );
	if (nSteps > 0)
	{
		fixedTimestepAccumulator -= nSteps * m_timeStep;
	}
	assert("Accumulator must have a value lesser than the fixed time step" && fixedTimestepAccumulator < m_timeStep + FLT_EPSILON);
	fixedTimestepAccumulatorRatio = fixedTimestepAccumulator / m_timeStep;
	PhysicalObject::fixedTimestepAccumulatorRatio = fixedTimestepAccumulatorRatio;
 
	const int nStepsClamped = std::min (nSteps, MAX_STEPS);
	for (int i = 0; i < nStepsClamped; ++ i)
	{
		clearAllSmoothAngleAndPosition();
		m_world->Step (m_timeStep, m_velocityIterations, m_positionIterations);
	}
 
	m_world->ClearForces();

	smoothAllBodyPositions();
}

void ActualGame::clearAllSmoothAngleAndPosition()
{	
	b2Vec2 smoothedPosition_, previousPosition_;
	double smoothedAngle_, previousAngle_;
	for(int i = 0; i < m_train->getPhysicalObjects().size(); ++i)
	{
		b2Body * b = m_train->getPhysicalObjects()[i]->getBody();
		smoothedPosition_ = previousPosition_ = b->GetPosition ();
		smoothedAngle_ = previousAngle_ = b->GetAngle ();
		m_train->getPhysicalObjects()[i]->updatePositions(smoothedPosition_, smoothedAngle_);
		m_train->getPhysicalObjects()[i]->updatePreviousPositions(smoothedPosition_, smoothedAngle_);
	}

	for(int i = 0; i < m_train->getWagons().size(); ++i)
	{
		Wagon * w = m_train->getWagons()[i];
		for(int j = 0; j < w->getPhysicalObjects().size(); ++j)
		{
			b2Body * b = w->getPhysicalObjects()[j]->getBody();
			smoothedPosition_ = previousPosition_ = b->GetPosition ();
			smoothedAngle_ = previousAngle_ = b->GetAngle ();
			w->getPhysicalObjects()[j]->updatePositions(smoothedPosition_, smoothedAngle_);
			w->getPhysicalObjects()[j]->updatePreviousPositions(smoothedPosition_, smoothedAngle_);
		}
	}
}

void ActualGame::smoothAllBodyPositions()
{
	const float oneMinusRatio = 1.f - fixedTimestepAccumulatorRatio;
 
	b2Vec2 smoothedPosition_;
	double smoothedAngle_;
	for(int i = 0; i < m_train->getPhysicalObjects().size(); ++i)
	{
		b2Body * b = m_train->getPhysicalObjects()[i]->getBody();
		b2Vec2 smoothedPosition_ = fixedTimestepAccumulatorRatio * b->GetPosition () + oneMinusRatio * m_train->getPhysicalObjects()[i]->getPreviousPosition();
		double smoothedAngle_ = fixedTimestepAccumulatorRatio* b->GetAngle () + oneMinusRatio * m_train->getPhysicalObjects()[i]->getPreviousAngle();
		m_train->getPhysicalObjects()[i]->updatePositions(smoothedPosition_, smoothedAngle_);
	}

	for(int i = 0; i < m_train->getWagons().size(); ++i)
	{
		Wagon * w = m_train->getWagons()[i];
		for(int j = 0; j < w->getPhysicalObjects().size(); ++j)
		{
			b2Body * b = w->getPhysicalObjects()[j]->getBody();
			smoothedPosition_ = fixedTimestepAccumulatorRatio * b->GetPosition () + oneMinusRatio * w->getPhysicalObjects()[j]->getPreviousPosition();
			smoothedAngle_ = fixedTimestepAccumulatorRatio* b->GetAngle () + oneMinusRatio * w->getPhysicalObjects()[j]->getPreviousAngle();
			w->getPhysicalObjects()[j]->updatePositions(smoothedPosition_, smoothedAngle_);
		}
	}
}

void ActualGame::checkKeyboardEvent(const SDL_KeyboardEvent *event)
{
	m_train->keyboard(event);
	if (m_actualLevel->getBlock(m_actualBlock)){	
		m_actualLevel->getBlock(m_actualBlock)->keyboard(event);
	}
	if (m_actualLevel->getBlock(m_actualBlock+1)){
		m_actualLevel->getBlock(m_actualBlock+1)->keyboard(event);
	}
}


//Update durant le jeu !!!
void ActualGame::updateStarDustScore()
{
	m_starDustScore += m_starsPoint;
}
void ActualGame::updateObstacleScore()
{
	//s'augmente a chaque collision avec un animal => compte le nombre d'animal shoutés
	m_obstacleScore++;
	std::cout << m_obstacleScore <<std::endl;
}
//Update a la gare !!!
void ActualGame::updatePassengerScore()
{
	m_passengerScore+=(m_nbPassengerPoint*m_train->getNbPassengers());
}
void ActualGame::updateTimeScore()
{
	/*Time * temps = new Time(0,0,0);
	Time * tempsAvance = new Time(0, 10,0);
	if(m_timer < temps) // >10 en retard
	{
		for(int i = 0 ; i < abs(m_timer->getMinutes()) ; i++)
		{
			m_timeScore -= m_timePoint;
		}
	}else if(m_timer > temps && m_timer <= tempsAvance) // >10 en avance
	{
		m_timeScore += m_onTimeInfTenPoint;
	}else if(m_timer > tempsAvance) // <10 en avance
	{
		m_timeScore += m_timePoint;
	}else //a l'heure
	{
		m_timeScore += m_onTimePoint;
	}*/
}
void ActualGame::updateSatisfactionScore()
{
	m_satisfactionScore += m_obstacleScore * m_animalsFactor;
	//point quand on rate une station
	/*if()
		m_satisfactionScore += m_missStationPoint;
	//checkLaPosition du trin et met a jour score
	if(m_trains->checkPositionStation() == true)
	{
		m_satisfactionScore += m_stopStationPoint;
	}else
	{
		m_satisfactionScore -= m_stopStationPoint;
	}
	*/
	/*//check la mauvaise conduite en fonction de mshaken
	if(m_shaken > ____)
	{
		m_satisfactionScore +=( m_drivePoint*15);
	}else if(m_shaken > ____  && m_skahen < ___)
	{
		m_satisfactionScore +=( m_drivePoint*10);
	}else if(m_shaken > 0  && m_skahen < ___)
	{
		m_satisfactionScore +=( m_drivePoint*5);
	}

	*/
	//satisfaction en fonction du nombre de passager arrivé a destination
	m_satisfactionScore += m_train->getNbPassengers()*200;
}
void ActualGame::updateTotalScore()
{
	m_totalScore += m_starDustScore;
	m_totalScore += m_passengerScore;
	m_totalScore += m_timeScore;
	m_totalScore += m_satisfactionScore;
}
Train * ActualGame::getTrain()
{
	return m_train;
}