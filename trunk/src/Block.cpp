#include "Block.hpp"


/*Block Constructor */

Block::Block (int sizeX) 
{
	m_sizeX= sizeX;
	//b2Body * m_body;
}


b2Body * Block::getBody() {
	return m_body;
} 

void Block::setBody(b2Body * body) {
	m_body = body;
} 

/*
 * Block construction
 */
void Block::build()
{
	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(800.0f, 10.0f);

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&groundBox, 0.0f);
}
