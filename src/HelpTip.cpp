#include "HelpTip.hpp"
#include "Level.hpp"
#include "ActualGame.hpp"

/*
 * HelpTip Constructor
 */

HelpTip::HelpTip(int numblock, bool trigger, const char* image)
:ToolTip(trigger,image)
{
	m_numblock=numblock;
	m_posX=200;
	m_posY=200;
	m_sizeX=800;
	m_sizeY=600;
	m_trigger=false;
	m_sprite = new Sprite(image,  m_posX, m_posY,  m_sizeX, m_sizeY);
}
