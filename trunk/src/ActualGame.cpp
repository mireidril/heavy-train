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


	m_actualLevel= new Level();
	Block * actualBlock =  m_actualLevel->getBlock(0);
	b2Body * bodyBlock = actualBlock->getBody();
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -30.0f);
	bodyBlock = m_world->CreateBody(&groundBodyDef);
	actualBlock->setBody(bodyBlock);
	actualBlock->build();

	

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


