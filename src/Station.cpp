#include "Station.hpp"
#include "Level.hpp"

Station::Station(int sizeX, int id, Level * l)
:Block(STATION, sizeX, id, l, -1), hasStoppedBefore(false)
{

}

int Station::build(b2World * world)
{
	hasStoppedBefore = false;
	//On suppose que la taille de la gare est supérieure à zéro
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); //Position à changer plus tard
	m_body = world->CreateBody(&groundBodyDef);

	if(m_sizeX < m_sizeXMinStation)
		m_sizeX = m_sizeXMinStation;

	b2EdgeShape shape;
	//Attention aux blocs mitoyens : y'a t-il besoin de mettre shape.m_hasVertex0 et shape.m_hasVertex3 ?
	double x1 = m_posX, y1 = m_y;
	double x2 = m_posX + m_sizeX, y2 = m_y;
	Sprite::convertPixelsToMeters(&x1, &y1, WINDOWS_W, WINDOWS_H);
	Sprite::convertPixelsToMeters(&x2, &y2, WINDOWS_W, WINDOWS_H);
	b2Vec2 p1((float32) x1, (float32) y1);
	b2Vec2 p2((float32) x2, (float32) y2);
	shape.Set(p1, p2);
	m_body->CreateFixture(&shape, 0);
	
	//On mets des murs aux bords du niveau
	if(m_id == 0)
	{
		b2EdgeShape leftLevel;
		double x = 0; double y = 0;
		double x_ = 0; double y_ = WINDOWS_H;
		Sprite::convertPixelsToMeters(&x, &y, WINDOWS_W, WINDOWS_H);
		Sprite::convertPixelsToMeters(&x_, &y_, WINDOWS_W, WINDOWS_H);
		b2Vec2 p((float32) x, (float32) y);
		b2Vec2 p_((float32) x_, (float32) y_);
		leftLevel.Set(p, p_);
		m_body->CreateFixture(&leftLevel, 0);
	}
	if(m_id == m_level->getNbBlocks() - 1)
	{
		b2EdgeShape leftLevel;
		double x = m_posX + m_sizeX; double y = 0;
		double x_ = m_posX + m_sizeX; double y_ = WINDOWS_H;
		Sprite::convertPixelsToMeters(&x, &y, WINDOWS_W, WINDOWS_H);
		Sprite::convertPixelsToMeters(&x_, &y_, WINDOWS_W, WINDOWS_H);
		b2Vec2 p((float32) x, (float32) y);
		b2Vec2 p_((float32) x_, (float32) y_);
		leftLevel.Set(p, p_);
		m_body->CreateFixture(&leftLevel, 0);
	}

	createImage();

	initPassengers();

	return m_sizeX;
}

void Station::setTime(int h, int m)
{
	m_theoricalArrivalTime = new Time(h, m, 0);
}
void Station::setLeaving(int leave)
{
	m_nbLeavingPassengers = leave;
}
void Station::setEnter(int enter)
{
	m_nbEnteringPassengers = enter;
}

void Station::initPassengers()
{
	Passenger *p ;
	for(int i = 0; i< m_nbEnteringPassengers; i++ )
	{
		float x = rand()% (m_sizeX-5);
		//std::cout<<"float rand :"<<x<<" \tm_posX + x = "<<m_posX+x<<std::endl;
		p = new Passenger(m_posX + x, 0.0f);
		m_passengers.push_back(p);
	}
}

int Station::getNbEnteringPassengers()
{
	return m_nbEnteringPassengers;
}

int Station::getNbLeavingPassengers()
{
	return m_nbLeavingPassengers;
}

bool Station::getHasStoppedBefore()
{
	return hasStoppedBefore;
}

void Station::setHasStoppedBefore(bool b)
{
	hasStoppedBefore = b;
}

