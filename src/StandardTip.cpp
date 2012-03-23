#include "StandardTip.hpp"
#include "Level.hpp"
#include "ActualGame.hpp"

/*
 * StandardTip Constructor
 */

StandardTip::StandardTip(const char* action, bool trigger, char* image)
:ToolTip(trigger,image)
{
	m_action=action;
	m_posX=200;
	m_posY=200;
	m_sizeX=800;
	m_sizeY=600;
	m_trigger=false;
	m_sprite = new Sprite(image,  m_posX, m_posY,  m_sizeX, m_sizeY);
}
