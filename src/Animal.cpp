#include "Animal.hpp"


Animal::Animal(const char * type, int x, int y)
:PhysicalObject()
{
	m_posX = x*40/1024;
	m_posY = y*30/768;
	m_type = type;
	m_die = false;
	m_tchou = false;

	//sprite animal
	int sizeX, sizeY;
	//taille de l'animal

	if (strcmp(type,"tatou")==0)
	{
		sizeX = 150; sizeY = 53;
		m_sprite = new Sprite("../img/animaux/tatou1.png",  x-40, y,  sizeX, sizeY);
		for (int i=2; i<8; i++) {
			 std::ostringstream oss;
			 oss << i;
			std::string s1 = "../img/animaux/tatou"; 
			std::string s2 = ".png"; 
			std::string s3 = s1 + oss.str() +s2;
			m_sprite->addImage(s3.c_str());
		}
	}
	else if (strcmp(type,"coyote")==0)
	{
		sizeX = 150; sizeY = 53;
		m_sprite = new Sprite("../img/animaux/coyote.png",  x-40, y,  sizeX, sizeY);
	}
	else {
		sizeX = 150; sizeY = 53;
		m_sprite = new Sprite("../img/animaux/vache.png",  x-40, y, sizeX, sizeY);
	}


}
Animal::~Animal() 
{
	delete m_sprite;
}

void Animal::build(b2World * world){
	//Création de la boite contenant l'animal
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(m_posX, m_posY);//position initial de l'animal
	b2PolygonShape bodyShape;
	b2Vec2 vertices[4];
	vertices[0].Set(-1.0f, -1.f);
	vertices[1].Set(1.0f, -1.f);
	vertices[2].Set(1.0f, 1.f);
	vertices[3].Set(-1.0f, 1.f);
	bodyShape.Set(vertices, 4);//corpds de l'animal

	m_body = world->CreateBody(&bd);
	m_body->CreateFixture(&bodyShape, 0.1f);
}

void Animal::scroll(int x){

	m_sprite->setPositionX(m_sprite->getPositionX()+x);
}

bool Animal::isDie() {
	return m_die;
}

void Animal::draw(SDL_Surface * screen, const int & width, const int & height){
	
	b2Vec2 bodyPos = m_body->GetPosition();
	double angle = m_body->GetAngle();
	double angledegrees = angle*180/M_PI;
	double x = bodyPos.x;
	double y = bodyPos.y;
	if (m_tchou == true || abs(x - m_posX)>0.01){
		
		if (m_sprite->animate()) {
			m_sprite->draw(screen,  width,  height);
		}
		else {
			die();
		}
		
	}
	else{
		m_sprite->convertMetersToPixels(&x, &y,  width,  height);
		m_sprite->setPositionY( y-40);
		m_sprite->setAngle (angle);
		m_sprite->draw(screen,  width,  height);
		
	}

}

void Animal::die(){
	//animation
	m_die = true;
	std::cout << "collision" << std::endl;
}


/*
 * Animal keyboard
 */
void Animal::keyboard( const SDL_KeyboardEvent *event)
{
	
	switch ( (event->keysym).sym)
	{
	case SDLK_SPACE:
		m_tchou = true;
		
		
		break;
	default:
		break;
	}
}
