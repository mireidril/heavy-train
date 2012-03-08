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

	SDL_Rect * pos = new SDL_Rect;
	pos->x = 0; pos->y = 0; 
	SDL_Rect * size = new SDL_Rect;
	size->x = 138; size->y = 97; 
	m_sprites.push_back(new Sprite("../img/elements/wagon.png",  pos,  size));//wagon
	size->x = 39; size->y = 36; 
	m_sprites.push_back(new Sprite("../img/elements/roue.png",  pos,  size));//roue1
	m_sprites.push_back(new Sprite("../img/elements/roue.png",  pos,  size));//roue2

}

Wagon::~Wagon () 
{
	//delete m_sprite;
	//suppr bodies, + sounds
}

b2Body * Wagon::getBody(unsigned int i)
{
	assert(i < m_bodies.size());
	return m_bodies[i];
}

/*
 * draw the wagon on the screen
 */
void Wagon::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	SDL_Rect * pos = new SDL_Rect;
	double x; 
	double y; 
	b2Vec2 bodyPos;
	double angle;
	//wagon
	bodyPos = m_bodies[0]->GetPosition();
	angle = m_bodies[0]->GetAngle()*180/M_PI;
	x = bodyPos.x; y = bodyPos.y;
	m_sprites[0]->convertMetersToPixels( x,  y,  width,  height);
	pos->x = x-30; pos->y = y-50;
	m_sprites[0]->setPosition(pos);
	m_sprites[0]->setAngle(angle);
	m_sprites[0]->draw(screen, width, height);

	//roues
	for (int i=1; i<3; i++){
		bodyPos = m_bodies[i]->GetPosition();
		x = bodyPos.x; y = bodyPos.y;
		angle = m_bodies[i]->GetAngle()*180/M_PI;
		m_sprites[i]->convertMetersToPixels( x,  y,  width,  height);
		pos->x = x-8; pos->y = y-8;
		m_sprites[i]->setPosition(pos);
		m_sprites[i]->setAngle(angle);
		m_sprites[i]->draw(screen, width, height);
	}


}

void Wagon::setMotorSpeed(float speed){
	m_spring1->SetMotorSpeed(speed);
	m_spring2->SetMotorSpeed(speed);
}



/*
 * wagon construction
 */
void Wagon::build(b2World * world, double x, float high)
{	
	//Création des wagons
	float32 hz = 4.0f;
	float32 zeta = 0.7f;
	float32 speed = 2.0f;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(x, high+9.0f);

	b2PolygonShape chassis;
	b2Vec2 vertices[4];
	vertices[0].Set(-1.5f, -0.2f);
	vertices[1].Set(1.5f, -0.2f);
	vertices[2].Set(1.5f, 0.2f);
	vertices[3].Set(-1.5f, 0.2f);
	chassis.Set(vertices, 4);

	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[0]->CreateFixture(&chassis, 0.5f);

	b2CircleShape circle;
	circle.m_radius = 0.5f;

	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 2.0f;
	fd.friction = 0.9f;

	bd.position.Set(x-1.0f, high+8.5f);
	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[1]->CreateFixture(&fd);// roue1

	bd.position.Set(x+1.0f, high+8.5f);
	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[2]->CreateFixture(&fd);// roue2

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	jd.Initialize(m_bodies[0], m_bodies[1], m_bodies[1]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = true;
	jd.frequencyHz = hz;
	jd.dampingRatio = zeta;
	m_spring1 = (b2WheelJoint*)world->CreateJoint(&jd);// joint pour la roue1

	jd.Initialize(m_bodies[0], m_bodies[2], m_bodies[2]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = false;
	jd.frequencyHz = hz;
	jd.dampingRatio = zeta;
	m_spring2 = (b2WheelJoint*)world->CreateJoint(&jd);// joint pour la roue2
}

