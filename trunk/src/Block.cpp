#include "Block.hpp"


/*
 * Block Constructor
 * sizeX and sizeY are dimension of the image in pixel 
 */

Block::Block(BlockType type, int sizeX, SDL_Rect * pos)
{
	switch(type)
	{
		case GROUND :
			break;
		case PRECIPICE :
			break;
		case STATION :
			break;
		case TUNNEL :
			break;
		default:
			m_sizeX = sizeX;
			break;

	}

	m_sprite = new Sprite("../img/ground.png",  pos,  NULL);
	
}

Block::~Block() 
{
	delete m_sprite;
	//supprimer le body
}


b2Body * Block::getBody() 
{
	return m_body;
} 

void Block::setBody(b2Body * body) 
{
	m_body = body;
} 


void Block::draw(SDL_Surface * screen, const int & width, const int & height)
{
	/*b2Vec2 bodyPos = m_body->GetPosition();
	SDL_Rect * pos = new SDL_Rect;
	double x = bodyPos.x;
	double y = bodyPos.y;
	
	Sprite::convertMetersToPixels(x, y, width, height);

	pos->x =  x;
	pos->y = y + bodyPos.y;

	m_sprite->setPosition(pos);
	m_sprite->draw(screen, width, height);

	delete pos;*/
}

/*
 * Block construction
 */
void Block::build(b2World * world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);// a changer ensuite avec les bonne valeurs
	m_body = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	double sizeX = m_sizeX;
	double sizeY = 10;
	Sprite::convertPixelsToMeters( sizeX, sizeY, 1024, 768);
	groundBox.SetAsBox(40, 0.1);

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&groundBox, 0.0f);
}
