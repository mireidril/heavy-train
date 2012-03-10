#include "PhysicalObject.hpp"

PhysicalObject::PhysicalObject()
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
	m_previousPosition = m_body->GetPosition();
	m_previousAngle = m_body->GetAngle();
}

Sprite * PhysicalObject::getSprite(){
	return m_sprite;
}

b2Vec2 PhysicalObject::getPositionSmoothed()
{
	//Par interpolation
	const float oneMinusRatio = 1.f - fixedTimestepAccumulatorRatio;
	b2Vec2 smoothedPosition = fixedTimestepAccumulatorRatio * m_body->GetPosition() + oneMinusRatio * m_previousPosition;
	m_previousPosition = smoothedPosition;

	//Par extrapolation
	//const float dt = fixedTimestepAccumulatorRatio * 1.f/60.f;
	//b2Vec2 smoothedPosition = m_body->GetPosition() + dt * m_body->GetLinearVelocity();

	return smoothedPosition;
}

double PhysicalObject::getAngleSmoothed()
{
	//Par interpolation
	const float oneMinusRatio = 1.f - fixedTimestepAccumulatorRatio;
	double smoothedAngle = fixedTimestepAccumulatorRatio * m_body->GetAngle() + oneMinusRatio * m_previousAngle;
	m_previousAngle = smoothedAngle;

	//Par extrapolation
	//const float dt = fixedTimestepAccumulatorRatio * 1.f/60.f;
	//double smoothedAngle = m_body->GetAngle() + dt * m_body->GetAngularVelocity();

	return smoothedAngle;
}

void PhysicalObject::clearSmoothAngleAndPosition()
{
	m_previousPosition = m_body->GetPosition();
	m_previousAngle = m_body->GetAngle();
}