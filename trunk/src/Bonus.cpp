#include "Bonus.hpp"

Bonus::Bonus(BonusType type, int posX, int posY)
: PhysicalObject()
, m_type(type)
, m_used(false)
{
	m_posX = posX*40/WINDOWS_W;
	m_posY = posY*30/WINDOWS_H;

	int sizeX, sizeY;
	//Sprite
	switch(type){
		case STAR_DUST:
			sizeX = 200; sizeY = 400;
			m_sprite = new Sprite("../img/bonus/anneau.png",  posX-75, posY,  sizeX, sizeY);
			break;
		case ACCELERATOR:
			sizeX = 200; sizeY = 400;
			m_sprite = new Sprite("../img/bonus/anneau.png",  posX-75, posY,  sizeX, sizeY);
			break;
	}
}

Bonus::~Bonus() 
{
	delete m_sprite;
}
