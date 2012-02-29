#include "Passenger.hpp"

b2World * PhysicalObject::m_world;

Passenger::Passenger(double x, double y){
	m_speed = 1.0f;
	m_isEjected = false;
	m_destination = new b2Vec2(x, y);
	m_joint = NULL;

	//Création du BodyDef, le "modèle"
	b2BodyDef bodyDef;
	bodyDef.position.Set( x, y);
	bodyDef.type = b2_dynamicBody;
	// Par défaut on créée des passagers qui ne sont pas actifs 
	bodyDef.active = false;

	//Création du b2Body à partir du BodyDef 
	m_body = PhysicalObject::m_world->CreateBody(&bodyDef);
}

//Destructor
Passenger::~Passenger(){
	breakJoint();
	PhysicalObject::m_world->DestroyBody(getBody());
	setBody(NULL);
	delete m_destination;
}

void Passenger::breakJoint(){
	(PhysicalObject::m_world)->DestroyJoint(m_joint);
	m_joint = NULL;
}

void Passenger::step(){
	b2Vec2 pos = m_body->GetPosition();
	if( pos.x != m_destination->x ){
		//TODO
	}
	if( pos.y != m_destination->y ){
		//TODO
	}
}

void Passenger::switchStatic(){
	getBody()->SetActive(false);
}

void Passenger::switchDynamic(){
	//Change le body en actif ( participe aux collisions )
	getBody()->SetActive(true);

	//Initialisation du joint
	b2DistanceJointDef jointDef;
	jointDef.bodyA = m_body;
	// TODO 
	//jointDef.bodyB = myBodyB;
	//jointDef.localAnchorA = m_body->GetCenterPosition(); 
	//jointDef.localAnchorB = wagon body 
	m_joint = (b2DistanceJoint*)(PhysicalObject::m_world)->CreateJoint(&jointDef);
}

void Passenger::setDestinationPoint( double x, double y ){
	m_destination->Set( x, y );
}