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



void Train::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	b2Vec2 bodyPos = m_body->GetPosition();
	SDL_Rect * pos = new SDL_Rect;
	//largeur de l'écran : 1024 = 40 metres
	//hauteur de l'écran : 768 = ??? metres a voir pour l'instant j'ai mis 100
	pos->x = width * bodyPos.x / 40;
	pos->y = - height * bodyPos.y / 100;  
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
	bodyDef.position.Set(0.0f, 0.f);
	m_body = world->CreateBody(&bodyDef);
	// Define the ground box shape.
	b2PolygonShape dynamicBox;
	// The extents are the half-widths of the box.
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&fixtureDef);

}