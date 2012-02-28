#include "ActualGame.hpp"

/*
 * ActualGame Constructor
 */
ActualGame::ActualGame()
{
	std::cout << "Actual Game" << std::endl;

	b2Vec2 gravity(0.0f, -10.0f);
	// Construct a world object, which will hold and simulate the rigid bodies.
	m_world = new b2World(gravity);
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

	fooDrawInstance = new DebugDraw;
	m_world->SetDebugDraw( fooDrawInstance );
}
ActualGame::~ActualGame()
{
	delete m_actualLevel;
	delete m_train;
	delete fooDrawInstance;
	//supprimer m_world
}


/*
 * ActualGame run: est appelé dans le game Engine: update le world et dessine les éléments
 */
void ActualGame::run(SDL_Surface * screen, int w, int h){

	fooDrawInstance->SetFlags( b2Draw::e_shapeBit );
	m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
	m_world->DrawDebugData();

	m_actualLevel->drawBlocks(screen, w, h);
	m_train->drawSprite(screen,w,h);
}

void ActualGame::checkCollisions()
{
	
}

void ActualGame::checkKeyboardEvent(const SDL_KeyboardEvent *event)
{
	switch(event->keysym.sym)
	{
		default:
			break;
	}
}


