#include "Train.hpp"


/*
 * Train Constructor 
 */

Train::Train () 
{
	SDL_Rect * pos = new SDL_Rect;
	pos->x = 10*1024/40;//the initial position in px
	pos->y = 20*768/30; 
	SDL_Rect * size = new SDL_Rect;
	size->x = 396;
	size->y = 165; 
	m_sprite = new Sprite("../img/trainvache.png",  pos,  size);

	

}

Train::~Train () 
{
	delete m_sprite;
	//suppr bodies, + sounds
}

b2Body * Train::getBody() 
{
	return m_body;
} 

void Train::setBody(b2Body * body) 
{
	m_body = body;
} 


/*
 * draw the train on the screen
 */
void Train::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	/*b2Vec2 bodyPos = m_body->GetPosition();
	SDL_Rect * pos = new SDL_Rect;
  
	//std::cout << bodyPos.y << std::endl;
	double x = bodyPos.x;
	double y = bodyPos.y;
	m_sprite->convertToPixel(x, y, width, height);
	pos->x = x;
	pos->y = y;
	m_sprite->setPosition(pos);
	//m_sprite->draw(screen, width, height);*/
}

/*
 * Train construction
 */

void Train::build(b2World * world)
{
	/*b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(10.0f, 20.0f);//initial position in meter
	m_body = world->CreateBody(&bodyDef);
	// Define the ground box shape.
	b2PolygonShape dynamicBox;
	// The extents are the half-widths of the box.

	dynamicBox.SetAsBox(5, 15);

	dynamicBox.SetAsBox(20.0, 15.0);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 3.0f;
	fixtureDef.friction = 0.3f;
	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&fixtureDef);*/
	
	//cloclo test pour car
	m_hz = 4.0f;
	m_zeta = 0.7f;
	m_speed = 50.0f;

	b2PolygonShape chassis;
	b2Vec2 vertices[8];
	vertices[0].Set(8.5f, 9.5f);
	vertices[1].Set(11.5f, 9.5f);
	vertices[2].Set(11.5f, 10.0f);
	vertices[3].Set(10.0f, 10.9f);
	vertices[4].Set(8.85f, 10.9f);
	vertices[5].Set(8.5f, 9.8f);
	chassis.Set(vertices, 6);


	//chassis.SetAsBox(2, 2);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(0.0f, 30.0f);
	m_car = world->CreateBody(&bd);
	m_car->CreateFixture(&chassis, 1.0f);

	b2CircleShape circle;
	circle.m_radius = 0.2f;

	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 1.0f;
	fd.friction = 0.9f;

	bd.position.Set(9.0f, 30.0f);
	m_wheel1 = world->CreateBody(&bd);
	m_wheel1->CreateFixture(&fd);

	bd.position.Set(10.0f, 30.0f);
	m_wheel2 = world->CreateBody(&bd);
	m_wheel2->CreateFixture(&fd);

	/*b2WheelJointDef jd;
	b2Vec2 axis(10.0f, 11.0f);

	jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20.0f;
	jd.enableMotor = true;
	jd.frequencyHz = m_hz;
	jd.dampingRatio = m_zeta;
	//m_spring1 = (b2WheelJoint*)world->CreateJoint(&jd);

	jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = false;
	jd.frequencyHz = m_hz;
	jd.dampingRatio = m_zeta;
	//m_spring2 = (b2WheelJoint*)world->CreateJoint(&jd);*/

}
