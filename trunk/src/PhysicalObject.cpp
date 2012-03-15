#include "PhysicalObject.hpp"

PhysicalObject::PhysicalObject()
: m_smoothedPosition(0, 0)
, m_previousPosition(0, 0)
{
	m_sprite = NULL;
}

PhysicalObject::PhysicalObject(Sprite * s)
{
	m_sprite = s;
}

PhysicalObject::~PhysicalObject()
{
	delete m_sprite;
}

b2Body * PhysicalObject::getBody(){
	return m_body;
}

void PhysicalObject::setBody(b2Body * body){
	m_body = body;
	m_smoothedPosition = m_previousPosition = m_body->GetPosition();
	m_previousAngle = m_body->GetAngle();
}

Sprite * PhysicalObject::getSprite(){
	return m_sprite;
}

void PhysicalObject::updatePositions()
{
	m_previousPosition = m_smoothedPosition;
	m_smoothedPosition = getPositionSmoothed();

	m_previousAngle = m_smoothedAngle;
	m_smoothedAngle = getAngleSmoothed();
}

b2Vec2 PhysicalObject::getPositionSmoothed()
{
	//Par interpolation
	const float oneMinusRatio = 1.f - fixedTimestepAccumulatorRatio;
	m_smoothedPosition = fixedTimestepAccumulatorRatio * m_body->GetPosition() + oneMinusRatio * m_previousPosition;

	//Par extrapolation
	//const float dt = fixedTimestepAccumulatorRatio * 1.f/60.f;
	//b2Vec2 smoothedPosition = m_body->GetPosition() + dt * m_body->GetLinearVelocity();

	return m_smoothedPosition;
}

b2Vec2 PhysicalObject::getPosition()
{
	return m_smoothedPosition;
}

b2Vec2 PhysicalObject::getLastPosition()
{
	return m_previousPosition;
}

double PhysicalObject::getAngle()
{
	return m_smoothedAngle;
}

double PhysicalObject::getAngleSmoothed()
{
	//Par interpolation
	const float oneMinusRatio = 1.f - fixedTimestepAccumulatorRatio;
	m_smoothedAngle = fixedTimestepAccumulatorRatio * m_body->GetAngle() + oneMinusRatio * m_previousAngle;

	//Par extrapolation
	//const float dt = fixedTimestepAccumulatorRatio * 1.f/60.f;
	//double smoothedAngle = m_body->GetAngle() + dt * m_body->GetAngularVelocity();

	return m_smoothedAngle;
}

void PhysicalObject::clearSmoothAngleAndPosition()
{
	m_smoothedPosition /*= m_previousPosition */= m_body->GetPosition();
	m_smoothedAngle = m_previousAngle = m_body->GetAngle();
}