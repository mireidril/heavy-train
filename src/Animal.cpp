#include "Animal.hpp"


Animal::Animal(const char * type, int x, int y)
:PhysicalObject()
{
	m_posX = x*40/WINDOWS_W;
	m_posY = y*30/WINDOWS_H;
	m_type = type;
	m_die = false;
	m_tchou = false;
	m_hasEscape = false;

	//taille de l'animal

	if (strcmp(type,"tatou")==0)
	{
		m_sprite = new Sprite("../img/animaux/tatou1.png",  x-75, y);
		for (int i=2; i<8; i++) {
			 std::ostringstream oss;
			 oss << i;
			std::string s1 = "../img/animaux/tatou"; 
			std::string s2 = ".png"; 
			std::string s3 = s1 + oss.str() +s2;
			m_sprite->addImage(s3.c_str());
		}
	}
	else if (strcmp(type,"coyote")==0)
	{
		m_sprite = new Sprite("../img/animaux/coyote1.png",  x-70, y);
		for (int i=2; i<8; i++) {
			 std::ostringstream oss;
			 oss << i;
			std::string s1 = "../img/animaux/coyote"; 
			std::string s2 = ".png"; 
			std::string s3 = s1 + oss.str() +s2;
			m_sprite->addImage(s3.c_str());
		}
	}
	else {
		m_sprite = new Sprite("../img/animaux/vache1.png",  x-70, y);
		for (int i=2; i<8; i++) {
			 std::ostringstream oss;
			 oss << i;
			std::string s1 = "../img/animaux/vache"; 
			std::string s2 = ".png"; 
			std::string s3 = s1 + oss.str() +s2;
			m_sprite->addImage(s3.c_str());
		}
	}
	for (int i=1; i<8; i++) {
		 std::ostringstream oss;
		 oss << i;
		std::string s1 = "../img/animaux/collision"; 
		std::string s2 = ".png"; 
		std::string s3 = s1 + oss.str() +s2;
		m_sprite->addImage(s3.c_str());
	}


}

Animal::~Animal() 
{
	std::cout<<"Destruction animal"<<std::endl;
}

void Animal::build(b2World * world){
	//Création de la boite contenant l'animal
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(m_posX, m_posY);//position initial de l'animal
	b2PolygonShape bodyShape;
	b2Vec2 vertices[4];
	vertices[0].Set(-1.8f, -1.f);
	vertices[1].Set(1.8f, -1.f);
	vertices[2].Set(1.8f, 1.f);
	vertices[3].Set(-1.8f, 1.f);
	bodyShape.Set(vertices, 4);//corpds de l'animal

	m_body = world->CreateBody(&bd);
	m_body->CreateFixture(&bodyShape, 0.1f);
	m_body->SetUserData(this);
}

void Animal::scroll(int x){

	m_sprite->setPositionX(m_sprite->getPositionX()+x);
}

bool Animal::isDie() {
	return m_die;
}

void Animal::draw(SDL_Surface * screen, const int & width, const int & height){
	
	b2Vec2 bodyPos = m_body->GetPosition();
	double angle = m_body->GetAngle();
	double angledegrees = angle*180/M_PI;
	double x = bodyPos.x;
	double y = bodyPos.y;
	if (m_tchou == true){	
		if (m_sprite->animate(0,7)) {
			m_sprite->draw(screen,  width,  height);
		}
		else {
			m_tchou = false;
			m_hasEscape = true;
		}		
	}
	else if ( abs(x - m_posX) > 0.1 ){

		if (m_sprite->animate(8,15) || m_sprite->getActualFrame() == 0)
		{
			m_sprite->draw(screen,  width,  height);
		}
		else
		{
			die();
		}
	}
	else if(! m_hasEscape) {
		m_sprite->convertMetersToPixels(&x, &y,  width,  height);
		m_sprite->setPositionY( y-60);
		m_sprite->setAngle (angle);
		m_sprite->draw(screen,  width,  height);
	}
}

void Animal::die(){
	m_die = true;
	//Destruction du body
	m_body->SetActive(false);
}


/*
 * Animal keyboard
 */
void Animal::keyboard( const SDL_KeyboardEvent *event)
{
	switch ( (event->keysym).sym)
	{
	case SDLK_SPACE:
		m_tchou = true;
		m_body->SetActive(false);
		break;
	default:
		break;
	}
}
