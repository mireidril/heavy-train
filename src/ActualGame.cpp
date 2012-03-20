#include "ActualGame.hpp"

double PhysicalObject::fixedTimestepAccumulatorRatio;

/*
 * ActualGame Constructor
 */
ActualGame::ActualGame(unsigned int level, unsigned int island)
: m_lastPosXTrain (INFINITE)
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
	m_timeStep = 1.0f / 60.0f;
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
	m_train->updatePosition();
	scroll();
	m_actualLevel->render(screen, w, h);
	m_train->drawSprite(screen,w,h);

	fooDrawInstance->SetFlags( b2Draw::e_shapeBit );
	//Affichage des formes physiques pour Debug
	m_world->DrawDebugData();
}

void ActualGame::scroll()
{
	//Récupération de la dernière position du train
	b2Vec2 currentPos = m_train->getBodyPosition();
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
}

void ActualGame::clearAllSmoothAngleAndPosition()
{
	m_actualLevel->clearAllSmoothAngleAndPosition();
	m_train->clearAllSmoothAngleAndPosition();
}

void ActualGame::checkKeyboardEvent(const SDL_KeyboardEvent *event)
{
	m_train->keyboard(event);
}


//Update durant le jeu !!!
void ActualGame::updateStarDustScore(){
	m_starDustScore += m_starsPoint;
}
void ActualGame::updateObstacleScore(){
	//m_obstacleScore= ;
}
//Update a la gare !!!
void ActualGame::updatePassengerScore(){
	//il faut implementer getNbPassenger
	m_passengerScore+=(m_nbPassengerPoint*m_train->getNbPassengers());
}
void ActualGame::updateTimeScore(){

}
void ActualGame::updateSatisfactionScore(){

}
void ActualGame::updateTotalScore(){
	m_totalScore += m_starDustScore;
	m_totalScore += m_passengerScore;
	m_totalScore += m_timeScore;
	m_totalScore += m_satisfactionScore;
	m_totalScore += m_obstacleScore;
}