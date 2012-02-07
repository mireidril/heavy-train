#include "ActualGame.hpp"

/*
 * ActualGame Constructor
 */
ActualGame::ActualGame()
{
	//box2D
	b2Vec2 gravity(0.0f, -10.0f);
	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);


}

/*
 * ActualGame Destructor
 */
ActualGame::~ActualGame()
{
	//destruct world
}

/*
 * ActualGame
 */
void ActualGame::constructGround()
{
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -30.0f);
	//SDL_Rect * posSol = new SDL_Rect;
	//posSol->x = 0.0;
	//posSol->y = 30 + 249/2 + 20;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(800.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void ActualGame::checkCollisions()
{
	
}


