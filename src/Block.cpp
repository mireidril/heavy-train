#include "Block.hpp"


/*Block Constructor */

Block::Block (int sizeX, b2World * world) 
{
	m_sizeX= sizeX;
	//Sprite * m_sprite;
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -30.0f);
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	m_body = world->CreateBody(&groundBodyDef);

	//SDL_Rect * posSol = new SDL_Rect;
	//posSol->x = 0.0;
	//posSol->y = 30 + 249/2 + 20;

}

/*
 * Block construction
 */
void Block::constructGround()
{
	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(800.0f, 10.0f);

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&groundBox, 0.0f);
}
