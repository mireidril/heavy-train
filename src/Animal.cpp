#include "Animal.hpp"


Animal::Animal(const char * type, int x, int y)
:PhysicalObject()
{
	m_posX = x*40/1024;
	m_posY = y*30/768;
	m_type = type;
	m_die = false;

	//sprite animal
	int sizeX, sizeY;
	//taille de l'animal

	if (strcmp(type,"tatou")==0)
	{
		sizeX = 150; sizeY = 53;
		m_sprite = new Sprite("../img/animaux/tatou.png",  x-40, y,  sizeX, sizeY);
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

	std::cout << "posX" << m_posX << std::endl;

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
	if (abs(x - m_posX)<2){
		m_sprite->convertMetersToPixels(&x, &y,  width,  height);
		m_sprite->setPositionY( y);
		m_sprite->setAngle (angle);
		m_sprite->draw(screen,  width,  height);
	}
	else {
		die();
	}
}

void Animal::die(){
	//animation
	m_die = true;
	std::cout << "collision" << std::endl;
}
