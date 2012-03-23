#include "ToolTip.hpp"
#include "Level.hpp"
#include "ActualGame.hpp"

/*
 * ToolTip Constructor
 */

ToolTip::ToolTip(bool trigger, const char* image)
: m_posX(200)
,m_posY(200)
,m_sizeX(800)
,m_sizeY(600)
,m_trigger(false)
{
	m_sprite = new Sprite(image,  m_posX, m_posY,  m_sizeX, m_sizeY);

}

ToolTip::~ToolTip() 
{
	delete m_sprite;
} 

bool ToolTip::getTrigger()
{
	return m_trigger;
}

void ToolTip::draw(SDL_Surface * screen, ActualGame * game)
{
	if(m_sprite){
		m_sprite->draw(screen, m_sizeX, m_sizeY);	
	}
}
