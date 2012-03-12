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

	PhysicalObject * wagon = new PhysicalObject(new Sprite("../img/elements/wagon.png",  pos,  size) );
	m_physicalObjects.push_back(wagon);
	size->x = 39; size->y = 36; 
	PhysicalObject * roue1 = new PhysicalObject(new Sprite("../img/elements/roue.png",  pos,  size) );
	m_physicalObjects.push_back(roue1);
	PhysicalObject * roue2 = new PhysicalObject(new Sprite("../img/elements/roue.png",  pos,  size) );
	m_physicalObjects.push_back(roue2);


}

Wagon::~Wagon () 
{
	for(int i = 0; i < m_physicalObjects.size(); ++i)
	{
		delete m_physicalObjects[i];
	}
}

b2Body * Wagon::getBody(unsigned int i)
{
	assert(i < m_physicalObjects.size());
	return m_physicalObjects[i]->getBody();
}

/*
 * Réinitialise les valeurs des PhysicalObjects après un smooth pour coller au framerate
 */
void Wagon::clearAllSmoothAngleAndPosition()
{
	for(int i = 0; i < m_physicalObjects.size(); ++i)
	{
		m_physicalObjects[i]->clearSmoothAngleAndPosition();
	}

	for(int i = 0; i < m_passengers.size(); ++i)
	{
		m_passengers[i]->clearSmoothAngleAndPosition();
	}
}

/*
 * draw the wagon on the screen
 */
void Wagon::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	double x; 
	double y; 
	b2Vec2 bodyPos;
	double angle;
	double angledegrees;
	//wagon
	bodyPos = m_physicalObjects[0]->getPosition();
	angle = m_physicalObjects[0]->getAngle();
	angledegrees= angle*180/M_PI;
	x = bodyPos.x; y = bodyPos.y;
	m_physicalObjects[0]->getSprite()->convertMetersToPixels( &x,  &y,  width,  height);
	if (angle>=-0.01){
		x = x-30*cos(angle)-35*sin(angle); 
		y = y-30*sin(angle)-35*cos(angle);
	}
	else {
		x = x+30*cos(M_PI-angle)+35*sin(M_PI-angle); 
		y = y+30*sin(M_PI-angle)+35*cos(M_PI-angle);
	}
	m_physicalObjects[0]->getSprite()->setPosition(x, y);
	m_physicalObjects[0]->getSprite()->setAngle(angledegrees);
	m_physicalObjects[0]->getSprite()->draw(screen, width, height);

	//roues
	for (int i=1; i<3; i++){
		bodyPos = m_physicalObjects[i]->getPosition();
		x = bodyPos.x; y = bodyPos.y;
		angle = m_physicalObjects[i]->getAngle()*180/M_PI;
		m_physicalObjects[i]->getSprite()->convertMetersToPixels( &x,  &y,  width,  height);
		x = x-8; y = y-8;
		m_physicalObjects[i]->getSprite()->setPosition(x, y);
		m_physicalObjects[i]->getSprite()->setAngle(angle);
		m_physicalObjects[i]->getSprite()->draw(screen, width, height);
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

	m_physicalObjects[0]->setBody(world->CreateBody(&bd));

	int typeWagon = 1;
	if( typeWagon == 0 ){
		//Le code qui donne un rectangle tout simple
		b2PolygonShape chassis;
		b2Vec2 vertices[4];
		vertices[0].Set(-1.5f, -0.8f);
		vertices[1].Set(1.5f, -0.8f);
		vertices[2].Set(1.5f, 0.8f);
		vertices[3].Set(-1.5f, 0.8f);
		chassis.Set(vertices, 4);

		m_physicalObjects[0]->getBody()->CreateFixture(&chassis, 0.1f);
	}else if( typeWagon == 1 ){
		//avec des polygones
		b2PolygonShape chassisGauche;
		b2Vec2 vertices[4];
		vertices[0].Set(-1.6f, -0.8f);
		vertices[1].Set(-1.5f, -0.8f);
		vertices[2].Set(-1.5f, 0.8f);
		vertices[3].Set(-1.6f, 0.8f);
		chassisGauche.Set(vertices, 4);
		b2PolygonShape chassisSol;
		vertices[0].Set(-1.6f, -0.9f);
		vertices[1].Set(1.6f, -0.9f);
		vertices[2].Set(1.6f, -0.8f);
		vertices[3].Set(-1.6f, -0.8f);
		chassisSol.Set(vertices, 4);

		b2PolygonShape chassisDroite;
		vertices[0].Set(1.5f, -0.9f);
		vertices[1].Set(1.6f, -0.9f);
		vertices[2].Set(1.6f, 0.9f);
		vertices[3].Set(1.5f, 0.9f);
		chassisDroite.Set(vertices, 4);
		//Le toit fait planter l'appli :/
		b2PolygonShape chassisToit;
		vertices[0].Set(-1.6f, 0.8f);
		vertices[1].Set(1.6f, 0.8f);
		vertices[2].Set(1.6f, 0.9f);
		vertices[3].Set(-1.6f, 0.9f);
		chassisToit.Set(vertices, 4);
		//*/
	
		m_physicalObjects[0]->getBody()->CreateFixture(&chassisSol, 5.0f);
		m_physicalObjects[0]->getBody()->CreateFixture(&chassisGauche, 5.0f);
		m_physicalObjects[0]->getBody()->CreateFixture(&chassisDroite, 5.0f);
		m_physicalObjects[0]->getBody()->CreateFixture(&chassisToit, 5.0f);
	}
	b2CircleShape circle;
	circle.m_radius = 0.5f;

	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 3.0f;
	fd.friction = 0.9f;

	bd.position.Set(x-1.0f, high+7.9f);
	m_physicalObjects[1]->setBody(world->CreateBody(&bd));
	m_physicalObjects[1]->getBody()->CreateFixture(&fd);// roue1

	bd.position.Set(x+1.0f, high+7.9f);
	m_physicalObjects[2]->setBody(world->CreateBody(&bd));
	m_physicalObjects[2]->getBody()->CreateFixture(&fd);// roue2

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	jd.Initialize(m_physicalObjects[0]->getBody(), m_physicalObjects[1]->getBody(), m_physicalObjects[1]->getBody()->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = true;
	jd.frequencyHz = hz;
	jd.dampingRatio = zeta;
	m_spring1 = (b2WheelJoint*)world->CreateJoint(&jd);// joint pour la roue1

	jd.Initialize(m_physicalObjects[0]->getBody(), m_physicalObjects[2]->getBody(), m_physicalObjects[2]->getBody()->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = false;
	jd.frequencyHz = hz;
	jd.dampingRatio = zeta;
	m_spring2 = (b2WheelJoint*)world->CreateJoint(&jd);// joint pour la roue2


	//TEST Création d'un passager
	Passenger *p = new Passenger(0.0f, 0.0f);
	addPassenger(p);
}

// Add the Passenger also creates the passenger joint. Call checkCapacity at the end.
void Wagon::addPassenger(Passenger* p)
{
	m_passengers.push_back(p);
	++ m_passengersCount;
	p->switchDynamic();

	//On le déplace dans le wagon
	p->getBody()->SetTransform(m_physicalObjects[0]->getBody()->GetPosition(), 0.0);

	//Création du joint pour lier le passager au wagon
	b2DistanceJointDef jointDef;
	b2Vec2 worldAnchorWagon(m_physicalObjects[0]->getBody()->GetPosition().x, m_physicalObjects[0]->getBody()->GetPosition().y - 0.9f);
	b2Vec2 worldAnchorPassenger(p->getBody()->GetPosition().x, p->getBody()->GetPosition().y - p->m_height/2.0f + p->m_width/4.0f );

	//TODO a revoir, fait à l'arrache
	jointDef.Initialize(p->getBody(), m_physicalObjects[0]->getBody(), worldAnchorPassenger, worldAnchorWagon);
	jointDef.length =  p->m_width/2.f + 0.055f;
	jointDef.dampingRatio = 0.9f;
	p->setJoint( (b2DistanceJoint*)PhysicalObject::m_world->CreateJoint(&jointDef) );

	p->getBody()->SetTransform(m_physicalObjects[0]->getBody()->GetPosition(), 0.0);
	
	//checkCapacity();
}