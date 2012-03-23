#include "Passenger.hpp"

b2World * PhysicalObject::m_world;
const float Passenger::m_width = .5f;
const float Passenger::m_height = 1.0f;

Passenger::Passenger(double x, double y)
	: PhysicalObject(new Sprite("../img/passengers/passagers5.png", x, y, 16, 30))
{
	m_speed = 1.0f;
	m_isEjected = false;
	m_destination = new b2Vec2(x, y);
	m_joint = NULL;

	//---Creation des "shapes"---
	
	//Un passager est composé d'un rectangle et d'un cercle à la base.
	//Rectangle
    b2PolygonShape sd1;
	b2Vec2 vertices[4];
	float boxHeight = (m_height-m_width/2.f)/2.f;
	float boxWidth = m_width/2.0f;
	vertices[0].Set(-boxWidth, -boxHeight);
	vertices[1].Set(boxWidth, -boxHeight);
	vertices[2].Set(boxWidth, boxHeight);
	vertices[3].Set(-boxWidth, boxHeight);
	sd1.Set(vertices, 4);

	b2FixtureDef fd;
	fd.shape = &sd1;
	fd.density = 0.1f;
	fd.friction = 0.9f;
	fd.filter.groupIndex = -1; // pour que les passagers n'aient pas de collision entre eux

	//Cercle	
	b2CircleShape sd2;
    sd2.m_radius = m_width / 2.0f;
    sd2.m_p.Set(0.0f, -m_height/2.f + m_width/4.f);

	b2FixtureDef fd2;
	fd2.shape = &sd2;
	fd2.density = 0.1f;
	fd2.friction = 0.9f;
	fd2.filter.groupIndex = -1; // pour que les passagers n'aient pas de collision entre eux
         
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

	//Sprite init
	double xMeter, yMeter;
	Sprite::convertMetersToPixels(&xMeter, &yMeter, WINDOWS_W, WINDOWS_H);
	m_sprite->setPositionX(xMeter);
}

//Destructor
Passenger::~Passenger(){
	/*if( m_isEjected == false )
		breakJoint();*/
	if( m_destination != NULL )
		delete m_destination;
}

void Passenger::breakJoint(){
	if( m_joint )
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
}

void Passenger::setDestinationPoint( double x, double y ){
	m_destination->Set( x, y );
}

void Passenger::setJoint(b2Joint * j){
	m_joint = j;
}

b2Joint * Passenger::getJoint(){
	return m_joint;
}

bool Passenger::getIsEjected(){
	return m_isEjected;
}

void Passenger::setIsEjected(bool b){
	m_isEjected = b;
}

void Passenger::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	double x, y; 
	b2Vec2 bodyPos;
	double angle,angledegrees;
	bodyPos = getPosition();
	angle = getAngle();
	angledegrees= angle*180/M_PI;
	x = bodyPos.x;
	y = bodyPos.y;
	Sprite::convertMetersToPixels(&x, &y,  width,  height);
	m_sprite->setPositionY(x);
	m_sprite->setPositionY(y-60);
	m_sprite->setAngle (angle);
	m_sprite->draw(screen,  width,  height);
}