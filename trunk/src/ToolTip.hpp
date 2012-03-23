#ifndef __TOOLTIP_HPP__
#define __TOOLTIP_HPP__

#include "Sprite.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif

class Level;
class ActualGame;

class ToolTip
{
	public :
		ToolTip(bool trigger, const char* image);
		virtual ~ToolTip();
		
		//Attribue une posX au bloc
		bool getTrigger();
		//Dessine l'info-bulle
		void draw(SDL_Surface * screen, ActualGame * game);
		
	protected :
		//Sprite de l'info-bulle
		Sprite * m_sprite;
		//Position (en pixels) en X de l'info-bulle
		int m_posX;
		//Position (en pixels) en Y de l'info-bulle
		int m_posY;
		//dimensions :
		int m_sizeX;
		int m_sizeY;
		//vérifie si l'info-bulle a déjà été affichée une fois dans le niveau
		bool m_trigger;
};
#endif
