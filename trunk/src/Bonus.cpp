#include "Bonus.hpp"

Bonus::Bonus(BonusType type, int posX, int posY)
: PhysicalObject()
, m_type(type)
, m_isUsed(false)
{
	m_posX = posX*40/WINDOWS_W;
	m_posY = posY*30/WINDOWS_H;

	//Sprite
	switch(type){
		case STAR_DUST:
			m_sprite = new Sprite("../img/bonus/star_dust.png",  posX-75, posY);
			break;
		case ACCELERATOR:
			m_sprite = new Sprite("../img/bonus/anneau.png",  posX-75, posY);
			std::cout<<"ACCELERATOR"<<std::endl;
			break;
	}
	std::cout<<"BUILD BONUS"<<std::endl;
	build(PhysicalObject::m_world);
}

void Bonus::scroll(const int & x)
{
	m_sprite->setPositionX(m_sprite->getPositionX()+x);
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
		miWidth = 1.5f;
		miHeight = 1.0f;
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

void Bonus::setIsUsed(bool b)
{
	m_isUsed = b;
}

BonusType  Bonus::getType()
{
	return m_type;
}

void Bonus::draw(SDL_Surface * screen, const int & width, const int & height){
	if( !m_isUsed || m_type == ACCELERATOR){
		b2Vec2 bodyPos = m_body->GetPosition();
		double x = bodyPos.x;
		double y = bodyPos.y;
		m_sprite->convertMetersToPixels(&x, &y,  width,  height);
		if( m_type == ACCELERATOR )
			m_sprite->setPositionY( y -90);
		else
			m_sprite->setPositionY( y-50);
		m_sprite->draw(screen,  width,  height);
	}
}