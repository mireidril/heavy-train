#include "Animal.hpp"


Animal::Animal()
:PhysicalObject()
{
	m_posX = 0;
	m_posY = 0;

	//sprite animal
	SDL_Rect * pos = new SDL_Rect;
	pos->x = m_posX; pos->y = m_posY; 
	//taille de l'animal
	SDL_Rect * size = new SDL_Rect;
	size->x = 150; size->y = 53;
	m_sprite = new Sprite("../img/animaux/tatou.png",  pos,  size);

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

void Animal::setType(const char * type){
	int L = strlen(type);
	memcpy (m_type, type, L*sizeof(char));
}
void Animal::setPosX(int x){
	m_posX = x;
}
void Animal::setPosY(int y){
	m_posY = y;
}
