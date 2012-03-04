#include "Wagon.hpp"

/*
 * Wagon Constructor 
 */

Wagon::Wagon () 
{
	m_originalNumberOfPassengers=0;
	//Maximum number of passenger for the wagon
	m_maxCapacity=20;
	// Number of passengers actually in the wagon (not ejected ones)
	m_passengersCount=0;
	m_areDoorOpened= false;

}

Wagon::~Wagon () 
{
	//delete m_sprite;
	//suppr bodies, + sounds
}

b2Body * Wagon::getBody(){
	return m_bodies[0];
}


/*
 * wagon construction
 */
void Wagon::build(b2World * world, double x)
{	

	//Création des wagons
	float32 hz = 4.0f;
	float32 zeta = 0.7f;
	float32 speed = 2.0f;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(x, 9.0f);

	b2PolygonShape chassis;
	b2Vec2 vertices[8];
	vertices[0].Set(-1.0f, -1.0f);
	vertices[1].Set(1.0f, -1.0f);
	vertices[2].Set(1.0f, 1.0f);
	vertices[3].Set(0.8f, 1.0f);
	vertices[4].Set(0.8f, -0.2f);
	vertices[5].Set(-0.8f, -0.2f);
	vertices[6].Set(-0.8f, 1.0f);
	vertices[7].Set(-1.0f, 1.0f);
	chassis.Set(vertices, 8);

	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[0]->CreateFixture(&chassis, 0.5f);

	b2CircleShape circle;
	circle.m_radius = 0.3f;

	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 2.0f;
	fd.friction = 0.9f;

	bd.position.Set(x-0.5f, 7.8f);
	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[1]->CreateFixture(&fd);

	bd.position.Set(x+0.5f, 7.8f);
	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[2]->CreateFixture(&fd);

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	jd.Initialize(m_bodies[0], m_bodies[1], m_bodies[1]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = true;
	jd.frequencyHz = hz;
	jd.dampingRatio = zeta;
	m_spring1 = (b2WheelJoint*)world->CreateJoint(&jd);

	jd.Initialize(m_bodies[0], m_bodies[2], m_bodies[2]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = false;
	jd.frequencyHz = hz;
	jd.dampingRatio = zeta;
	m_spring2 = (b2WheelJoint*)world->CreateJoint(&jd);

}

