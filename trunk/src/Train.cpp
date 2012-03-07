#include "Train.hpp"


/*
 * Train Constructor 
 */

Train::Train () 
{
	SDL_Rect * pos = new SDL_Rect;
	pos->x = 0; pos->y = 0; 
	SDL_Rect * size = new SDL_Rect;
	size->x = 166; size->y = 117; 
	m_sprites.push_back(new Sprite("../img/elements/loco.png",  pos,  size));//loco
	size->x = 39; size->y = 36; 
	m_sprites.push_back(new Sprite("../img/elements/roue.png",  pos,  size));//roue1
	m_sprites.push_back(new Sprite("../img/elements/roue.png",  pos,  size));//roue2
	// add wagons
	m_wagons.push_back(new Wagon());
	m_wagons.push_back(new Wagon());

}

Train::~Train () 
{
	for (int i=0; i< m_sprites.size(); i++){
		delete m_sprites[i]; 
	}
	for (int i=0; i< m_wagons.size(); i++){
		delete m_wagons[i]; 
	}
	//suppr bodies, + sounds
}



/*
 * draw the train on the screen
 */
void Train::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	SDL_Rect * pos = new SDL_Rect;
	double x; 
	double y; 
	b2Vec2 bodyPos;
	double angle;
	//loco
	bodyPos = m_bodies[0]->GetPosition();
	angle = m_bodies[0]->GetAngle()*180/M_PI;
	x = bodyPos.x; y = bodyPos.y;
	m_sprites[0]->convertMetersToPixels( x,  y,  width,  height);
	pos->x = x; pos->y = y-30;
	m_sprites[0]->setPosition(pos);
	m_sprites[0]->setAngle(angle);
	m_sprites[0]->draw(screen, width, height);

	//roues
	for (int i=1; i<3; i++){
		bodyPos = m_bodies[i]->GetPosition();
		x = bodyPos.x; y = bodyPos.y;
		angle = m_bodies[i]->GetAngle()*180/M_PI;
		m_sprites[i]->convertMetersToPixels( x,  y,  width,  height);
		pos->x = x+5*i*i; pos->y = y+20;
		m_sprites[i]->setPosition(pos);
		m_sprites[i]->setAngle(angle);
		m_sprites[i]->draw(screen, width, height);
	}

	m_wagons[0]->drawSprite(screen, width, height);
	m_wagons[1]->drawSprite(screen, width, height);
}

/*
 * Train construction
 */

void Train::build(b2World * world)
{
	

	//Création de la locomotive
	m_hz = 4.0f;
	float32 zeta = 0.7f;
	m_speed = 2.0f;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(10.0f, 9.0f);

	b2PolygonShape chassis;
	b2Vec2 vertices[6];
	vertices[0].Set(-1.0f, -1.0f);
	vertices[1].Set(1.0f, -1.0f);
	vertices[2].Set(1.0f, 1.0f);
	vertices[3].Set(-1.0f, 1.0f);
	chassis.Set(vertices, 4);

	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[0]->CreateFixture(&chassis, 0.5f);

	b2CircleShape circle;
	circle.m_radius = 0.3f;

	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 2.0f;
	fd.friction = 0.9f;

	bd.position.Set(9.5f, 7.8f);//position de la roue1
	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[1]->CreateFixture(&fd);

	bd.position.Set(10.5f, 7.8f);//position de la roue2
	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[2]->CreateFixture(&fd);

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	jd.Initialize(m_bodies[0], m_bodies[1], m_bodies[1]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = true;
	jd.frequencyHz = m_hz;
	jd.dampingRatio = zeta;
	m_spring1 = (b2WheelJoint*)world->CreateJoint(&jd);//joint pour la roue1

	jd.Initialize(m_bodies[0], m_bodies[2], m_bodies[2]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = false;
	jd.frequencyHz = m_hz;
	jd.dampingRatio = zeta;
	m_spring2 = (b2WheelJoint*)world->CreateJoint(&jd);//joint pour la roue2

	//wagon build
	m_wagons[0]->build(world, 7.0);
	m_wagons[1]->build(world, 4.0);

	// pour joindre la loco et le wagon1
	b2DistanceJointDef jdd;
	b2Vec2 p1, p2, d;

	jdd.frequencyHz = 2.0f;
	jdd.dampingRatio = 0.0f;

	jdd.bodyA = m_bodies[0];
	jdd.bodyB = m_wagons[0]->getBody();
	jdd.localAnchorA.Set(0.0f, 0.2f);
	jdd.localAnchorB.Set(0.0f, 0.2f);
	p1 = jdd.bodyA->GetWorldPoint(jdd.localAnchorA);
	p2 = jdd.bodyB->GetWorldPoint(jdd.localAnchorB);
	d = p2 - p1;
	jdd.length = d.Length();
	m_joints[0] = world->CreateJoint(&jdd);
	
	// pour joindre les 2 locos


	jdd.bodyA = m_wagons[0]->getBody();
	jdd.bodyB = m_wagons[1]->getBody();
	jdd.localAnchorA.Set(0.0f, 0.2f);
	jdd.localAnchorB.Set(0.0f, 0.2f);
	p1 = jdd.bodyA->GetWorldPoint(jdd.localAnchorA);
	p2 = jdd.bodyB->GetWorldPoint(jdd.localAnchorB);
	d = p2 - p1;
	jdd.length = d.Length();
	m_joints[1] = world->CreateJoint(&jdd);


}

/*
 * Train keyboard
 */
void Train::keyboard( const SDL_KeyboardEvent *event)
{
	switch ( (event->keysym).sym)
	{
	case SDLK_LEFT:
		m_spring1->SetMotorSpeed(m_speed);
		break;

	case SDLK_UP:
		m_spring1->SetMotorSpeed(0.0f);
		break;

	case SDLK_RIGHT:
		m_spring1->SetMotorSpeed(-m_speed);
		break;

	case 'q':
		m_hz = b2Max(0.0f, m_hz - 1.0f);
		m_spring1->SetSpringFrequencyHz(m_hz);
		m_spring2->SetSpringFrequencyHz(m_hz);
		break;

	case 'e':
		m_hz += 1.0f;
		m_spring1->SetSpringFrequencyHz(m_hz);
		m_spring2->SetSpringFrequencyHz(m_hz);
		break;
	}
}
