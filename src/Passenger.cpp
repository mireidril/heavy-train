#include "Passenger.hpp"

b2World * PhysicalObject::m_world;

Passenger::Passenger(double x, double y)
: PhysicalObject(NULL)
{
	m_speed = 1.0f;
	m_isEjected = false;
	m_destination = new b2Vec2(x, y);
	m_joint = NULL;

	//---Creation des "shapes"---
	double width = 1.0f;
	double height = 2.0f;
	float mHeight=(float)width * 1.5f / 2.0f;
    float mWidth=(float)width / 2.0f;
	//Un passager est composé d'un rectangle et d'un cercle à la base.
	//Rectangle
    b2PolygonShape sd1;
    //sd1.setAsBox(width / 2.0f, width / 2.0f);
	b2Vec2 vertices[4];
	float boxHeight = 3*height/4.f;
	float boxWidth = width/2.0f;
	vertices[0].Set(-boxHeight, -boxWidth);
	vertices[1].Set(boxHeight, -boxWidth);
	vertices[2].Set(boxHeight, boxWidth);
	vertices[3].Set(-boxHeight, boxWidth);
	sd1.Set(vertices, 4);

	b2FixtureDef fd;
	fd.shape = &sd1;
	fd.density = 3.0f;
	fd.friction = 0.9f;

    //sd1.density = density/2;
	/*
	b2CircleShape sd2;
    sd2 = new b2CircleShape();
    sd2.radius = width / 2.0f;
    sd2.localPosition.set(0.0f, width / 2.0f);
    sd2.density = density/2; // massless
    */          
	//Création du BodyDef, le "modèle"
	b2BodyDef bodyDef;
	bodyDef.position.Set(x, y);
	bodyDef.type = b2_dynamicBody;
	// Par défaut on créée des passagers qui ne sont pas actifs 
	bodyDef.active = false;

	//Création du b2Body à partir du BodyDef 
	setBody( PhysicalObject::m_world->CreateBody(&bodyDef) );
	getBody()->CreateFixture( &fd );
    //m_body.createShape(sd2);
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

void Passenger::setJoint(b2DistanceJoint * j){
	m_joint = j;
}