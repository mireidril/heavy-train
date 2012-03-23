#include "PhysicalObject.hpp"



PhysicalObject::PhysicalObject()
: m_smoothedPosition(INFINITE, INFINITE)
, m_previousPosition(INFINITE, INFINITE)
, m_previousAngle(INFINITE)
, m_smoothedAngle(INFINITE)
{
	m_sprite = NULL;
	m_body = NULL;
}

PhysicalObject::PhysicalObject(Sprite * s)
{
	m_sprite = s;
}

PhysicalObject::~PhysicalObject()
{
	delete m_sprite;
	PhysicalObject::m_world->DestroyBody(getBody());
}

b2Body * PhysicalObject::getBody()
{
	return m_body;
}

void PhysicalObject::setBody(b2Body * body)
{
	m_body = body;
	m_smoothedPosition = m_previousPosition = m_body->GetPosition();
	m_previousAngle = m_body->GetAngle();
}

Sprite * PhysicalObject::getSprite(){
	return m_sprite;
}

void PhysicalObject::updatePositions(b2Vec2 pos, double angle)
{
	m_smoothedPosition = pos;
	m_smoothedAngle = angle;
}

void PhysicalObject::updatePreviousPositions(b2Vec2 pos, double angle)
{
	m_previousPosition = pos;
	m_previousAngle = angle;
}

b2Vec2 PhysicalObject::getPosition()
{
	return m_smoothedPosition;
}

double PhysicalObject::getAngle()
{
	return m_smoothedAngle;
}

b2Vec2 PhysicalObject::getPreviousPosition()
{
	return m_previousPosition;
}

double PhysicalObject::getPreviousAngle()
{
	return m_previousAngle;
}