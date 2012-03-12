#include "Animal.hpp"


Animal::Animal(){
	m_posX = 0;
	m_posY = 0;
}
Animal::~Animal() 
{
	delete m_sprite;
}
void Animal::setType(const char * type){
	int L = strlen(type);
	memcpy (m_type, type, L*sizeof(char));
}
void Animal::setPosX(int x){
	m_posX = x;
}
void Animal::setPosY(int y){
	m_posY = y;
}