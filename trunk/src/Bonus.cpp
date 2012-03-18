#include "Bonus.hpp"

Bonus::Bonus(BonusType type, int posX, int posY)
: PhysicalObject()
, m_type(type)
, m_posX(posX)
, m_posY(posY)
{

}

Bonus::~Bonus() 
{
	delete m_sprite;
}
