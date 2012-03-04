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
	

	//Création de la locomotive
	float32 hz = 4.0f;
	float32 zeta = 0.7f;
	float32 speed = 50.0f;

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
	m_bodies[0]->CreateFixture(&chassis, 1.0f);

	b2CircleShape circle;
	circle.m_radius = 0.3f;

	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 1.0f;
	fd.friction = 0.9f;

	bd.position.Set(9.6f, 7.8f);
	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[1]->CreateFixture(&fd);

	bd.position.Set(10.4f, 7.8f);
	m_bodies.push_back(world->CreateBody(&bd));
	m_bodies[2]->CreateFixture(&fd);

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	jd.Initialize(m_bodies[0], m_bodies[1], m_bodies[1]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20.0f;
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
