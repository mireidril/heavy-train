#include "Train.hpp"


/*
 * Train Constructor 
 */

Train::Train () 
: m_size (4.0, 3.0)
, m_nbWagons(2)
, m_channel(-1)
{
	//la corps de la loco
	//position de la loco
	int x = 250; int y = 0; 
	//taille de la loco
	int sizeX = 130; int sizeY = 87;
	PhysicalObject * loco = new PhysicalObject(new Sprite("../img/elements/loco.png",  x, y, sizeX, sizeY));
	m_physicalObjects.push_back(loco);
	
	//les roues de la loco
	//position des roues
	x = 0; y = 0; 
	//taille roues
	sizeX = 39; sizeY = 36;
	PhysicalObject * roue1 = new PhysicalObject(new Sprite("../img/elements/roue.png",  x, y, sizeX, sizeY));
	PhysicalObject * roue2 = new PhysicalObject(new Sprite("../img/elements/roue.png",  x, y, sizeX, sizeY));
	m_physicalObjects.push_back(roue1);//roue1
	m_physicalObjects.push_back(roue2);//roue2
	// add wagons
	m_wagons.push_back(new Wagon(160));
	m_wagons.push_back(new Wagon(70));
	
	//sounds
	m_tchoutchouSound = Mix_LoadWAV("../musics/tchoutchou.ogg");
	if(m_tchoutchouSound == NULL) {
		printf("Unable to load OGG file: %s\n", Mix_GetError());
	}

}

Train::~Train () 
{
	for (int i=0; i< m_physicalObjects.size(); i++){
		delete m_physicalObjects[i]; 
	}
	for (int i=0; i< m_wagons.size(); i++){
		delete m_wagons[i]; 
	}
	//suppr bodies, + sounds
}

//Update the vertical position of the Train’s sprite according to the physical simulation
void Train::updatePosition()
{
	for(unsigned int i = 0; i < m_physicalObjects.size(); ++i)
	{
		m_physicalObjects[i]->updatePositions();
	}
}

/*
 * draw the train on the screen
 */
void Train::drawSprite(SDL_Surface * screen, const int & width, const int & height)
{
	double y, xLoco;
	int xLocoSprite; 
	xLocoSprite=m_physicalObjects[0]->getSprite()->getPositionX();
	b2Vec2 bodyPos;
	double angle, angledegrees;
	//locomotive
	bodyPos = m_physicalObjects[0]->getPosition();
	angle = m_physicalObjects[0]->getAngle();
	angledegrees = angle*180/M_PI;
	xLoco = bodyPos.x;
	y = bodyPos.y;
	m_physicalObjects[0]->getSprite()->convertMetersToPixels(&xLoco, &y,  width,  height);
	if (angle>=0){
		y = y-8-50*sin(angle)-35*cos(angle);
	}
	else {
		y = y-8+50*sin(M_PI-angle)+35*cos(M_PI-angle);
	}

	m_physicalObjects[0]->getSprite()->setPositionY(  y);
	m_physicalObjects[0]->getSprite()->setAngle(angledegrees);
	

	

	m_wagons[1]->drawSprite(screen, width, height,xLocoSprite+8 , xLoco );
	m_wagons[0]->drawSprite(screen, width, height, xLocoSprite+8 , xLoco);
	
	m_physicalObjects[0]->getSprite()->draw(screen, width, height);// dessiner la loco


	//roues de la loco
	double x;
	for (int i=1; i<3; i++){
		bodyPos = m_physicalObjects[i]->getPosition(); 
		y = bodyPos.y;
		m_physicalObjects[i]->getSprite()->convertMetersToPixels(NULL,  &y,  width,  height);
		angle = m_physicalObjects[0]->getAngle();
		if (angle>=0){
			x= m_physicalObjects[0]->getSprite()->getPositionX()+10+60*sin(angle)+(i-1)*70*cos(angle);
			y = y-10+10*sin(angle);//-10*cos(angle);
		}
		else {
			x= m_physicalObjects[0]->getSprite()->getPositionX()+10+12*sin(angle)+(i-1)*70*cos(angle);
			y = y-10;//+10*sin(M_PI-angle)+10*cos(M_PI-angle);
		}
		m_physicalObjects[i]->getSprite()->setPosition(x,y);
		angle = m_physicalObjects[i]->getAngle()*180/M_PI;
		m_physicalObjects[i]->getSprite()->setAngle(angle);
		m_physicalObjects[i]->getSprite()->draw(screen, width, height);
	}
}

/*
 * Train construction
 */

void Train::build(b2World * world)
{
	//Création de la locomotive
	m_hz = 4.0f;
	float32 zeta = 0.7f;
	m_speed = 20.0f;
	float high =6;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(12.0f, high+9.5f);//position initial train

	b2PolygonShape chassis;
	b2Vec2 vertices[4];
	vertices[0].Set(- (m_size.x/2.0), - (m_size.y/2.0));
	vertices[1].Set(m_size.x/2.0, - (m_size.y/2.0));
	vertices[2].Set(m_size.x/2.0, m_size.y/2.0);
	vertices[3].Set(- (m_size.x/2.0), m_size.y/2.0);
	chassis.Set(vertices, 4);//locomotive

	m_physicalObjects[0]->setBody(world->CreateBody(&bd));
	m_physicalObjects[0]->getBody()->CreateFixture(&chassis, 0.1f);

	b2CircleShape circle;
	circle.m_radius = 0.5f;//rayon roues

	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 3.0f;
	fd.friction = 0.9f;

	bd.position.Set(10.6f, high+7.9f);//position de la roue1
	m_physicalObjects[1]->setBody(world->CreateBody(&bd));
	m_physicalObjects[1]->getBody()->CreateFixture(&fd);

	bd.position.Set(13.4f, high+7.9f);//position de la roue2
	m_physicalObjects[2]->setBody(world->CreateBody(&bd));
	m_physicalObjects[2]->getBody()->CreateFixture(&fd);

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	jd.Initialize(m_physicalObjects[0]->getBody(), m_physicalObjects[1]->getBody(), m_physicalObjects[1]->getBody()->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = true;
	jd.frequencyHz = m_hz;
	jd.dampingRatio = zeta;
	m_spring1 = (b2WheelJoint*)world->CreateJoint(&jd);//joint pour la roue1

	jd.Initialize(m_physicalObjects[0]->getBody(), m_physicalObjects[2]->getBody(), m_physicalObjects[2]->getBody()->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = false;
	jd.frequencyHz = m_hz;
	jd.dampingRatio = zeta;
	m_spring2 = (b2WheelJoint*)world->CreateJoint(&jd);//joint pour la roue2

	//wagon build

	m_wagons[0]->build(world, 7.8, high);
	m_wagons[1]->build(world, 4.2, high);
	
	// pour joindre la loco et le wagon1
	b2DistanceJointDef jdd;
	b2Vec2 p1, p2, d;

	jdd.frequencyHz = 2.0f;
	jdd.dampingRatio = 0.0f;

	jdd.bodyA = m_physicalObjects[0]->getBody();
	jdd.bodyB = m_wagons[0]->getBody(0);
	jdd.localAnchorA.Set(0.f, -1.0f);
	jdd.localAnchorB.Set(0.f, -0.3f);
	p1 = jdd.bodyA->GetWorldPoint(jdd.localAnchorA);
	p2 = jdd.bodyB->GetWorldPoint(jdd.localAnchorB);
	d = p2 - p1;
	jdd.length = d.Length();
	jdd.collideConnected = false;
	m_joints[0] = world->CreateJoint(&jdd);

	
	// pour joindre les 2 locos


	jdd.bodyA = m_wagons[0]->getBody(0);
	jdd.bodyB = m_wagons[1]->getBody(0);
	jdd.localAnchorA.Set(0.0f, -0.3f);
	jdd.localAnchorB.Set(0.0f, -0.3f);
	p1 = jdd.bodyA->GetWorldPoint(jdd.localAnchorA);
	p2 = jdd.bodyB->GetWorldPoint(jdd.localAnchorB);
	d = p2 - p1;
	jdd.length = d.Length();

	m_joints[1] = world->CreateJoint(&jdd);



}
b2Body * Train::getBody(unsigned int i)
{
	assert(i < m_physicalObjects.size());
	return m_physicalObjects[i]->getBody();
}
//Permet au train de sauter en 3 fois. La première pulsion est exercée sur loco puis wagon1 puis wagon2
void Train::jump(){
			m_physicalObjects[0]->getBody()->ApplyForce(b2Vec2(10, 300),m_physicalObjects[0]->getBody()->GetWorldCenter());

	for (int i=0; i< m_wagons.size(); i++){
				m_wagons[i]->getBody(0)->ApplyForce(b2Vec2(10, 500),m_wagons[i]->getBody(0)->GetWorldCenter());
	}
}

//Réinitialise les valeurs des PhysicalObjects après un smooth pour coller au framerate
void Train::clearAllSmoothAngleAndPosition()
{
	for(int i = 0; i < m_physicalObjects.size(); ++i)
	{
		m_physicalObjects[i]->clearSmoothAngleAndPosition();
	}

	for(int i = 0; i < m_wagons.size(); ++i)
	{
		m_wagons[i]->clearAllSmoothAngleAndPosition();
	}
}

/*
 * Train keyboard
 */
void Train::keyboard( const SDL_KeyboardEvent *event)
{
	if (event->type == SDL_KEYUP)
	{
		switch ( (event->keysym).sym)
		{
			case SDLK_LEFT:
			case SDLK_RIGHT:
				m_spring1->SetMotorSpeed(0);
				m_spring2->SetMotorSpeed(0);
				m_wagons[0]->setMotorSpeed(0);
				m_wagons[1]->setMotorSpeed(0);
			break;
		}
	}
	else if (event->type == SDL_KEYDOWN)
	{
		switch ( (event->keysym).sym)
		{
		case SDLK_SPACE:
			if( m_channel == -1 || Mix_Playing(m_channel) == 0 )
				m_channel = Mix_PlayChannel(-1, m_tchoutchouSound, 0);
			if( m_channel == -1) {
				printf("Unable to play OGG file: %s\n", Mix_GetError());
			}
			break;

		case SDLK_LEFT:

			m_speed = 20;
			m_spring1->SetMotorSpeed(m_speed);
			m_spring2->SetMotorSpeed(m_speed);
			m_wagons[0]->setMotorSpeed(m_speed);
			m_wagons[1]->setMotorSpeed(m_speed);
			break;

		case SDLK_UP:
			jump();
		break;

		case SDLK_RIGHT:
			m_speed = -20;
			m_spring1->SetMotorSpeed(m_speed);
			m_spring2->SetMotorSpeed(m_speed);
			m_wagons[0]->setMotorSpeed(m_speed);
			m_wagons[1]->setMotorSpeed(m_speed);
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
		default:
			break;
		}
	}
}

//Donne la position actuelle du body de la loco
b2Vec2 Train::getLocoBodyPosition()
{
	return m_physicalObjects[0]->getPosition();
}
int Train::getNbPassengers()
{
	int nbWagon = m_wagons.size();
	int nbPassenger =0;
	for(int i=0; i<nbWagon ; i++){
		nbPassenger += m_wagons[i]->getNbPassengerWagon();
	}
	return nbPassenger;
}
