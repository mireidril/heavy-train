#include "Animal.hpp"


Animal::Animal(int type, int x, int y)
:PhysicalObject()
{
	m_posX = x;
	m_posY = y;
	m_typeAnimal= type;
	m_die = false;

	//sprite animal
	int xp = x*1024/40; int yp = y*768/30;
	int sizeX = 150, sizeY = 53;
	//taille de l'animal
	if (m_typeAnimal==0){
		sizeX = 150; sizeY = 53;
		m_sprite = new Sprite("../img/animaux/tatou.png",  xp-40, yp,  sizeX, sizeY);
	}
	else {
		sizeX = 150; sizeY = 53;
		m_sprite = new Sprite("../img/animaux/tatou.png",  xp-40, yp, sizeX, sizeY);
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
	bd.position.Set(m_posX, m_posY);//position initial train

	b2PolygonShape bodyShape;
	b2Vec2 vertices[4];
	vertices[0].Set(-1.0f, -1.f);
	vertices[1].Set(1.0f, -1.f);
	vertices[2].Set(1.0f, 1.f);
	vertices[3].Set(-1.0f, 1.f);
	bodyShape.Set(vertices, 4);//locomotive

	m_body = world->CreateBody(&bd);
	m_body->CreateFixture(&bodyShape, 0.1f);
}
/*
void Animal::setType(const char * type){
	int L = strlen(type);
	memcpy (m_type, type, L*sizeof(char));
}*/
void Animal::setPosX(int x){
	m_posX = x;
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
	if (x == m_posX){
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


void Animal::setPosY(int y){
	m_posY = y;
}
