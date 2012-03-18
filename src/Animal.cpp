#include "Animal.hpp"


Animal::Animal(int type)
:PhysicalObject()
{
	m_posX = 0;
	m_posY = 0;
	m_typeAnimal= type;

	//sprite animal
	SDL_Rect * pos = new SDL_Rect;	
	pos->x = 0; pos->y = 0; 
	//taille de l'animal
	SDL_Rect * size = new SDL_Rect;
	if (m_typeAnimal==0){
		size->x = 150; size->y = 53;
		m_sprite = new Sprite("../img/animaux/tatou.png",  pos,  size);
	}
	else {
		size->x = 150; size->y = 53;
		m_sprite = new Sprite("../img/animaux/tatou.png",  pos,  size);
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
	
	double x2 = m_posX*1024/40;
	m_sprite->setPositionX(x2+x);
}

void Animal::draw(SDL_Surface * screen, const int & width, const int & height){
	b2Vec2 bodyPos = m_body->GetPosition();
	
	double angle = m_body->GetAngle();
	double angledegrees = angle*180/M_PI;
	double x = bodyPos.x;
	double y = bodyPos.y;
	//std::cout << x <<std::endl;
	m_sprite->convertMetersToPixels(&x, &y,  width,  height);
	m_sprite->setPositionY( y);
	m_sprite->draw(screen,  width,  height);
}


void Animal::setPosY(int y){
	m_posY = y;
}
