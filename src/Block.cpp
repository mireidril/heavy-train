#include "Block.hpp"


/*
 * Block Constructor
 * sizeX and sizeY are dimension of the image in pixel 
 */

Block::Block (int sizeX, int sizeY,  const int & width, const int & height) 
{

	m_size = new SDL_Rect;
	m_size->x = sizeX*40/width;//dimension in meter
	m_size->y = sizeY*30/height; 

	SDL_Rect * m_sizeScaled = new SDL_Rect;
	m_sizeScaled->x = sizeX;
	m_sizeScaled->y = sizeY; 

	SDL_Rect * pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 768-m_sizeScaled->y; 

	m_sprite = new Sprite("../img/ground.png",  pos,  m_sizeScaled);
	
}

Block::~Block () 
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
	b2Vec2 bodyPos = m_body->GetPosition();
	SDL_Rect * pos = new SDL_Rect;
	double x = bodyPos.x;
	double y = m_size->y + bodyPos.y;
	
	m_sprite->convertToPixel(x,y,width,height);

	pos->x =  x;
	pos->y = y + bodyPos.y;

	m_sprite->setPosition(pos);
	m_sprite->draw(screen, width, height);
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
	groundBox.SetAsBox(m_size->x, m_size->y);

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&groundBox, 0.0f);
}
