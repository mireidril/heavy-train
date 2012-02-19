#include "Train.hpp"


/*
 * Train Constructor 
 */

Train::Train () 
{
	SDL_Rect * pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 0; 
	SDL_Rect * size = new SDL_Rect;
	size->x = 10;
	size->y = 10; 
	m_sprite = new Sprite("../img/test.bmp",  pos,  size);
	
}

b2Body * Train::getBody() 
{
	return m_body;
} 

void Train::setBody(b2Body * body) 
{
	m_body = body;
} 



void Train::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	m_sprite->draw(screen, width, height);
}

/*
 * Train construction
 */

void Train::build(b2World * world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	m_body = world->CreateBody(&bodyDef);
	// Define the ground box shape.
	b2PolygonShape groundBox;
	// The extents are the half-widths of the box.
	groundBox.SetAsBox(8.0f, 10.0f);
	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&groundBox, 0.0f);

	//std::cout <<  m_body->GetPosition().y << std::endl;
}


void Train::draw(SDL_Surface * screen, int w, int h)
{	
	b2Vec2 bodyPos = m_body->GetPosition();
	//std::cout << bodyPos.y << std::endl;
	SDL_Rect * pos = new SDL_Rect;
	pos->x = bodyPos.x/30 ;
	pos->y = bodyPos.y/30 ; 
	m_sprite->setPosition(pos);
	m_sprite->draw(screen, w, h);
}
