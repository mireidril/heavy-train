#include "ActualGame.hpp"

/*
 * ActualGame Constructor
 */
ActualGame::ActualGame()
{
	//box2D
	b2Vec2 gravity(0.0f, -10.0f);
	// Construct a world object, which will hold and simulate the rigid bodies.
	m_world = new b2World(gravity);


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


