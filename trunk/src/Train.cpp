#include "Train.hpp"


/*
 * Train Constructor 
 */

Train::Train () 
{
	SDL_Rect * pos = new SDL_Rect;
	pos->x = 10*1024/40;//the initial position in px
	pos->y = 20*768/30; 
	SDL_Rect * size = new SDL_Rect;
	size->x = 396;
	size->y = 165; 
	m_sprite = new Sprite("../img/trainvache.png",  pos,  size);
	
}

Train::~Train () 
{
	delete m_sprite;
	//suppr bodies, + sounds
}

b2Body * Train::getBody() 
{
	return m_body;
} 

void Train::setBody(b2Body * body) 
{
	m_body = body;
} 


/*
 * draw the train on the screen
 */
void Train::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	b2Vec2 bodyPos = m_body->GetPosition();
	SDL_Rect * pos = new SDL_Rect;
  
	//std::cout << bodyPos.y << std::endl;
	double x = bodyPos.x;
	double y = bodyPos.y;
	m_sprite->convertToPixel(x,y,width, height);
	pos->x =  x;
	pos->y = y;
	m_sprite->setPosition(pos);
	m_sprite->draw(screen, width, height);
}

/*
 * Train construction
 */

void Train::build(b2World * world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(10.0f, 20.0f);//initial position in meter
	m_body = world->CreateBody(&bodyDef);
	// Define the ground box shape.
	b2PolygonShape dynamicBox;
	// The extents are the half-widths of the box.
	dynamicBox.SetAsBox(m_sprite->getSizeX()*40/1024, m_sprite->getSizeY()*30/768);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 3.0f;
	fixtureDef.friction = 0.3f;
	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&fixtureDef);

}
