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
	double width = 0.5f;
	double height = 1.0f;
	//Un passager est composé d'un rectangle et d'un cercle à la base.
	//Rectangle
    b2PolygonShape sd1;
    //sd1.setAsBox(width / 2.0f, width / 2.0f);
	b2Vec2 vertices[4];
	float boxHeight = 2*height/6.f;
	float boxWidth = width/2.0f;
	vertices[0].Set(-boxWidth, -boxHeight);
	vertices[1].Set(boxWidth, -boxHeight);
	vertices[2].Set(boxWidth, boxHeight);
	vertices[3].Set(-boxWidth, boxHeight);
	sd1.Set(vertices, 4);

	b2FixtureDef fd;
	fd.shape = &sd1;
	fd.density = 3.0f;
	fd.friction = 0.9f;

	//Cercle	
	b2CircleShape sd2;
    sd2.m_radius = width / 2.0f;
    sd2.m_p.Set(0.0f, - 2*width / 3.0f);

	b2FixtureDef fd2;
	fd2.shape = &sd2;
	fd2.density = 3.0f;
	fd2.friction = 0.9f;
         
	//Création du BodyDef, le "modèle"
	b2BodyDef bodyDef;
	bodyDef.position.Set(x, y);
	bodyDef.type = b2_dynamicBody;
	// Par défaut on créée des passagers qui ne sont pas actifs 
	//bodyDef.active = false;

	//Création du b2Body à partir du BodyDef 
	setBody( PhysicalObject::m_world->CreateBody(&bodyDef) );

	//Assignation des Fixtures ( pour créer les formes)
	getBody()->CreateFixture( &fd );
	getBody()->CreateFixture( &fd2 );
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