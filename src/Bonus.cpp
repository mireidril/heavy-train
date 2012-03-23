#include "Bonus.hpp"

Bonus::Bonus(BonusType type, int posX, int posY)
: PhysicalObject()
, m_type(type)
, m_used(false)
{
	m_posX = posX*40/WINDOWS_W;
	m_posY = posY*30/WINDOWS_H;

	int sizeX, sizeY;
	//Sprite
	switch(type){
		case STAR_DUST:
			sizeX = 200; sizeY = 400;
			m_sprite = new Sprite("../img/bonus/anneau.png",  posX-75, posY,  sizeX, sizeY);
			break;
		case ACCELERATOR:
			sizeX = 200; sizeY = 400;
			m_sprite = new Sprite("../img/bonus/anneau.png",  posX-75, posY,  sizeX, sizeY);
			break;
	}
	build(PhysicalObject::m_world);
}



Bonus::~Bonus() 
{
	
}

void Bonus::build(b2World * world)
{
	//Création de la boite contenant le bonus
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(m_posX, m_posY);//position initiale du bonus
	b2PolygonShape bodyShape;
	float height = 0.5f;
	float width = 0.5f;
	b2Vec2 vertices[4];
	vertices[0].Set(-height, -width);
	vertices[1].Set(height, -width);
	vertices[2].Set(height, width);
	vertices[3].Set(-height, width);
	bodyShape.Set(vertices, 4);

	m_body = world->CreateBody(&bd);
	m_body->CreateFixture(&bodyShape, 0.1f);
}