#include "ActualGame.hpp"

/*
 * ActualGame Constructor
 */
ActualGame::ActualGame()
{
	std::cout << "Actual Game" << std::endl;
	//box2D
	b2Vec2 gravity(0.0f, -10.0f);
	// Construct a world object, which will hold and simulate the rigid bodies.
	m_world = new b2World(gravity);
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 m_timeStep = 1.0f / 60.0f;
	int32 m_velocityIterations = 6;
	int32 m_positionIterations = 2;


	m_actualLevel= new Level();
	/* Test pour tracer le premier bloc du level actuel*/
	Block * actualBlock =  m_actualLevel->getBlock(0);
	actualBlock->build(m_world);
	/* test pour tracer le train */
	m_train = new Train();
	m_train->build(m_world);

	

}

/*
 * ActualGame run: est appelé dans le game Engine: update le world et dessine les éléments
 */
void ActualGame::run(SDL_Surface * screen, int w, int h){

	m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
	m_actualLevel->drawBlocks( screen, w, h);
	m_train->draw(screen,w,h);

}

/*
 * ActualGame Destructor
 */
ActualGame::~ActualGame()
{
	//destruct world
}



void ActualGame::checkCollisions()
{
	
}


