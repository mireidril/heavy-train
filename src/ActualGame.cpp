#include "ActualGame.hpp"
#include "GameEngine.hpp"

double PhysicalObject::fixedTimestepAccumulatorRatio;

/*
 * ActualGame Constructor
 */
ActualGame::ActualGame(unsigned int level, unsigned int island)
: m_lastPosXTrain (INFINITE)
, m_actualBlock(0)
, m_actualTime(NULL)
, m_timer(NULL)
, m_train(NULL)
, m_totalScore(0)
, m_gameOver(false)
, m_lastStation(0)
, m_passengerScore(0)
, m_timeScore(0)
, m_satisfactionScore(0)
, m_starDustScore(0)
, m_obstacleScore(0)
, m_gameWon(false)
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
	m_passengerScore = 0;
	m_totalScore = 0;
	m_timeScore = 0;

	//Charges les images de l'interface
	m_font =  TTF_OpenFont("../fonts/GOTHIC.TTF", 24);
	m_interfaceImages.push_back(new Sprite("../img/interface/fond.png", 0, 0, 1024, 160) );
	m_interfaceImages.push_back(new Sprite("../img/interface/time.png", 0, 5, 200, 48) );
	m_interfaceImages.push_back(new Sprite("../img/interface/passengers.png", 230, 5, 200, 50) );
	m_interfaceImages.push_back(new Sprite("../img/interface/speed.png", 520, 5, 200, 50) );
	m_interfaceImages.push_back(new Sprite("../img/interface/score.png", 800, 5, 200, 58) );
	m_interfaceImages.push_back(new Sprite("../img/interface/next.png", 0, 70, 200, 50) );
	m_interfaceImages.push_back(new Sprite("../img/interface/time_left.png", 350, 70, 100, 36) );
}
ActualGame::~ActualGame()
{
	delete m_actualLevel;
	TTF_CloseFont(m_font);

	if(m_timer) delete m_timer;
	if(m_actualTime) delete m_actualTime;

	for(unsigned int i = 0; i < m_interfaceImages.size(); ++i)
	{
		delete m_interfaceImages[i];
	}

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
void ActualGame::run(GameEngine * gameEngine, SDL_Surface * screen, int w, int h)
{
	if(m_actualLevel->getNbBlocks() == 0)
	{
		gameEngine->changeScreen(GAME, TITLE, -1, -1);
		return;
	}

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
	if(!m_gameOver && !m_gameWon)
	{
		runSimulation();
	
		//Dessine le niveau & le train
		updateActualBlock();
		scroll();

		m_actualLevel->render(screen, w, h, this, m_world);
		drawInterface(screen, w, h);
		m_train->drawSprite(screen, w, h);
		m_actualLevel->drawTunnels(screen, w, h, this, m_world);

		//fooDrawInstance->SetFlags( b2Draw::e_shapeBit );
		//Affichage des formes physiques pour Debug
		m_world->DrawDebugData();

		checkVictoryConditions();
	}
	else if(m_gameOver)
	{
		gameEngine->changeScreen(GAME, GAMEOVER, -1, -1);
		//gameEngine->changeScreen(GAME, ENDGAME, m_actualLevel->getLevelNum(), m_actualLevel->getIslandNum()); //pour des tests plus rapides
	}
	else if(m_gameWon)
	{
		gameEngine->changeScreen(GAME, ENDGAME, m_actualLevel->getLevelNum(), m_actualLevel->getIslandNum());
	}
}

void ActualGame::teleportTrainToLastStation()
{
	m_gameOver = false;
	double x = m_actualLevel->getBlock(m_lastStation)->getPosX();
	Sprite::convertPixelsToMeters(&x, NULL, WINDOWS_W, WINDOWS_H);
	//TODO déplacer le body du train à la dernière station passée
}

void ActualGame::drawInterface(SDL_Surface * screen, const int & w, const int & h)
{
	for(unsigned int i = 0; i < m_interfaceImages.size(); ++i)
	{
		if(m_interfaceImages[i])
			m_interfaceImages[i]->draw(screen, w, h);
	}
	
	//Dessine les textes
	std::stringstream ss;
	SDL_Surface * surf;
	SDL_Color black = {0, 0, 0};
	SDL_Rect pos;

	//Time
	if(m_actualTime != NULL)
	{
		ss << m_actualTime->getHours() << ":" << m_actualTime->getMinutes() << ":" << m_actualTime->getSeconds();
	}
	else
	{
		ss << "00:00:00";
	}
	surf = TTF_RenderText_Blended(m_font, ss.str().c_str(), black);
	pos.x = 75; pos.y = 25;
	SDL_BlitSurface(surf, NULL, screen, &pos);
	ss.str(std::string());

	//Passengers
	if(m_train != NULL)
	{
		ss << m_train->getNbPassengers() << "/" << m_train->getMaxCapacity();
	}
	else
	{
		ss << "00/00";
	}
	surf = TTF_RenderText_Blended(m_font, ss.str().c_str(), black);
	pos.x = 300; pos.y = 25;
	SDL_BlitSurface(surf, NULL, screen, &pos);
	ss.str(std::string());

	//Speed
	if(m_train != NULL)
	{
		int velocity = abs( m_train->getBody(0)->GetLinearVelocity().x * 60 * 60 / 1000.0 );
		ss << velocity << " km/h";
	}
	else
	{
		ss << "00 km/h";
	}
	surf = TTF_RenderText_Blended(m_font, ss.str().c_str(), black);
	pos.x = 590; pos.y = 25;
	SDL_BlitSurface(surf, NULL, screen, &pos);
	ss.str(std::string());

	//Score
	int nbChiffre = m_totalScore; 
	ss << m_totalScore << " pts";
	surf = TTF_RenderText_Blended(m_font, ss.str().c_str(), black);
	pos.x = 880; pos.y = 25;
	SDL_BlitSurface(surf, NULL, screen, &pos);
	ss.str(std::string());

	//Next Stop
	/*if( getNextStation() != NULL)
	{
		ss << m_actualTime->getHours() << ":" << m_actualTime->getMinutes() << ":" << m_actualTime->getSeconds();
	}
	else
	{
		ss << "00:00:00";
	}
	surf = TTF_RenderText_Blended(m_font, ss.str().c_str(), black);
	pos.x = 75; pos.y = 150;
	SDL_BlitSurface(surf, NULL, screen, &pos);
	ss.str(std::string());*/

	//Timer
	if( m_timer != NULL)
	{
		ss << m_timer->getMinutes() << ":" << m_timer->getSeconds();
	}
	else
	{
		ss << "00:00";
	}
	surf = TTF_RenderText_Blended(m_font, ss.str().c_str(), black);
	pos.x = 435; pos.y = 90;
	SDL_BlitSurface(surf, NULL, screen, &pos);
	ss.str(std::string());
}

void ActualGame::updateActualBlock()
{
	double headLocoX = m_train->getLocoBodyPosition().x;

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

		if(m_actualLevel->getBlock(m_actualBlock)->getType() == STATION && m_actualBlock > m_lastStation)
		{
			m_lastStation = m_actualBlock;
		}

		//Pour vérifier l'entrée en gare
		if( !m_train->getIsAtStation() && actualBlock->getType() == STATION && !m_train->getBody(0)->IsAwake() )
		{
			trainAtStation();
		}
		else if( m_train->getIsAtStation() &&  m_train->getBody(0)->IsAwake() )
		{
			trainLeavingStation();
		}
	}
}

void ActualGame::trainAtStation()
{
	m_train->setIsAtStation(true);
	Station* station = (Station*) m_actualLevel->getBlock(m_actualBlock);

	//Si premier arrêt : les passagers descendent et on compte les points
	if( !station->getHasStoppedBefore() )
	{
		std::cout<<"Train at station ! Entering passengers : "<<station->getNbEnteringPassengers()<<" Leaving passengers : "<<station->getNbLeavingPassengers()<<std::endl;
		station->setHasStoppedBefore(true);
		
		//updateTimeScore();
		updatePassengerScore();
		updateSatisfactionScore();
		updateTotalScore();

		m_train->takeOffPassengers(station);
		
		updateSatisfactionScore();
		updateTotalScore();

		//Les passagers montent
		m_train->takeInPassengers(station);

		
	}
	
	std::cout<<"Number of passangers : "<<m_train->getNbPassengers()<<std::endl;
}

void ActualGame::trainLeavingStation()
{
	std::cout<<"\tTrain leaving station !"<<std::endl;
	m_train->setIsAtStation(false);
}


void ActualGame::scroll()
{
	//Récupération de la dernière position du train
 	b2Vec2 currentPos = m_train->getLocoBodyPosition();
	//Récupération de la position du dernier bloc
	Block * b = m_actualLevel->getBlock(m_actualLevel->getNbBlocks() - 1);
	if(b)
	{
		double lastBlockPosX = b->getPosX() + b->getSizeX();
		if(lastBlockPosX < WINDOWS_W)
		{
			std::cout<<"lol"<<std::endl;
		}
		else if( m_lastPosXTrain != INFINITE )
		{
			double x = m_lastPosXTrain - currentPos.x;
			Sprite::convertMetersToPixels(&x, NULL, WINDOWS_W, WINDOWS_H);

			m_actualLevel->scrollLevel(x);
		}
		m_lastPosXTrain = currentPos.x;
	}
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

void ActualGame::checkVictoryConditions()
{
	if(m_train->getBody(0)->GetPosition().y < 0)
	{
		m_gameOver = true;
	}

	//Si un wagon est coincé sous le sol : TODO

	//Condition de victoire
	if(m_actualBlock == (m_actualLevel->getNbBlocks() - 1) && m_train->getNbPassengers() == 0)
	{
		m_gameWon = true;
	}

	if(m_train->checkiIfTrainIsReturned())
	{
		m_gameOver = true;
	}

}

void ActualGame::checkKeyboardEvent(GameEngine* g, const SDL_KeyboardEvent *event)
{
	m_train->keyboard(g, event);
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
	std::cout << "obstacle SCORE : " << m_obstacleScore <<std::endl;
}
//Update a la gare !!!
void ActualGame::updatePassengerScore()
{
	m_passengerScore+=(m_nbPassengerPoint*m_train->getNbPassengers());
	std::cout << "PASSENGER SCORE : " << m_passengerScore <<std::endl;
	std::cout << "*m_train->getNbPassengers() : " << m_train->getNbPassengers() <<std::endl;
}
void ActualGame::updateTimeScore()
{
	Time * temps = new Time(0,0,0);
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
	}
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