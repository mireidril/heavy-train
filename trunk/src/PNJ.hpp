#ifndef __PNJ_HPP__
#define __PNJ_HPP__

#ifdef _WIN32
#include "Box2D/Box2D.h"
#include "SDL/SDL_mixer.h"
#else
#include <Box2D/Box2D.h>
#include <SDL/SDL_mixer.h>
#endif

#include "Sprite.hpp"

//TODO renommer le fichier en PhysicalObject.hpp et modifier le CMAKE en conséquence.

class PhysicalObject
{
	public :
		b2Body * getBody();
		void setBody(b2Body * body);
		Sprite * getSprite();
		//Pointeur vers le m_world de ActualGame
		static b2World * m_world;
	protected :
		//Body of the physical object
		b2Body * m_body;
		//Sprite of the physical Object
		Sprite * m_sprite;
};
#endif