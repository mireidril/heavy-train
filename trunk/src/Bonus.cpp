#include "Bonus.hpp"

Bonus::Bonus(){
	m_posX = 0;
	m_posY = 0;
}
Bonus::~Bonus() 
{
	delete m_sprite;
}
void Bonus::setType(BonusType type){
	m_type = type;
}
void Bonus::setPosX(int x){
	m_posX = x;
}
void Bonus::setPosY(int y){
	m_posY = y;
}