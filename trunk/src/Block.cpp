#include "Block.hpp"


/*
 * Block Constructor 
 */

Block::Block (int sizeX) 
{
	m_sizeX = sizeX;
	SDL_Rect * pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 80; 
	SDL_Rect * size = new SDL_Rect;
	size->x = 50;
	size->y = 50; 
	m_sprite = new Sprite("../img/sol.bmp",  pos,  size);
	
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
	//largeur de l'écran : 1024 = 40 metres
	//hauteur de l'écran : 768 = ??? metres a voir pour l'instant j'ai mis 100
	pos->x = (float) (width * bodyPos.x) / 40;
	pos->y = (float) (- height * bodyPos.y) / 100;
	m_sprite->setPosition(pos);
	m_sprite->draw(screen, width, height);
}

/*
 * Block construction
 */
void Block::build(b2World * world)
{

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -80.0f);// a changer ensuite avec les bonne valeurs
	m_body = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&groundBox, 0.0f);
}
