#include "ActualGame.hpp"

double PhysicalObject::fixedTimestepAccumulatorRatio;

/*
 * ActualGame Constructor
 */
ActualGame::ActualGame()
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

	m_actualLevel= new Level();
	/* Test pour tracer le premier bloc du level actuel*/
	Block * actualBlock =  m_actualLevel->getBlock(0);
	actualBlock->build(m_world);
	/* test pour tracer le train */
	m_train = new Train();
	m_train->build(m_world);

	//TEST Création d'un passager
	Passenger *p = new Passenger(5.0f, 30.0f);

	fooDrawInstance = new DebugDraw;
	m_world->SetDebugDraw( fooDrawInstance );
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
 * ActualGame run: est appelé dans le game Engine: update le world et dessine les éléments
 */
void ActualGame::run(SDL_Surface * screen, int w, int h)
{
	//Actualise la simulation
	runSimulation();
	
	//Dessine le niveau & le train
	m_actualLevel->render(screen, w, h);
	m_train->drawSprite(screen,w,h);

	fooDrawInstance->SetFlags( b2Draw::e_shapeBit );
	//Affichage des formes physiques pour Debug
	m_world->DrawDebugData();	
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


