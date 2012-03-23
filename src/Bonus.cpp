#include "Bonus.hpp"

Bonus::Bonus(BonusType type, int posX, int posY)
: PhysicalObject()
, m_type(type)
, m_isUsed(false)
{
	m_posX = posX*40/WINDOWS_W;
	m_posY = posY*30/WINDOWS_H;

	int sizeX, sizeY;
	//Sprite
	switch(type){
		case STAR_DUST:
			sizeX = 250; sizeY = 120;
			m_sprite = new Sprite("../img/bonus/star_dust.png",  posX-75, posY,  sizeX, sizeY);
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
	float miWidth, miHeight;
	switch(m_type){
	case STAR_DUST:
		miWidth = .5f;
		miHeight = .5f;
		break;
	case ACCELERATOR:
		miWidth = .5f;
		miHeight = 2.5f;
		break;
	}
	
	b2Vec2 vertices[4];
	vertices[0].Set(-miWidth, -miHeight);
	vertices[1].Set(miWidth, -miHeight);
	vertices[2].Set(miWidth, miHeight);
	vertices[3].Set(-miWidth, miHeight);
	bodyShape.Set(vertices, 4);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bodyShape;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = OBSTACLE_SENSOR;
	fixtureDef.filter.maskBits = TRAIN; // Collision qu'avec le train
	m_body = world->CreateBody(&bd);
	m_body->CreateFixture(&fixtureDef);
	m_body->SetGravityScale(0); // Il vole !

	m_body->SetUserData(this);
}

bool Bonus::isUsed()
{
	return m_isUsed;
}
