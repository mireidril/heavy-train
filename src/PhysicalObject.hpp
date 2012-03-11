#ifndef __PHYSICAL_OBJECT_HPP__
#define __PHYSICAL_OBJECT_HPP__

#ifdef _WIN32
#include "Box2D/Box2D.h"
#include "SDL/SDL_mixer.h"
#else
#include <Box2D/Box2D.h>
#include <SDL/SDL_mixer.h>
#endif

#include "Sprite.hpp"

class PhysicalObject
{
	public :
		PhysicalObject();
		PhysicalObject(Sprite * sprite);
		virtual ~PhysicalObject();

		//Retourne m_body
		b2Body * getBody();
		//Attribue un body
		void setBody(b2Body * body);
		//Retourne le m_sprite
		Sprite * getSprite();

		//Mets à jour les positions et angle actuelle et de la dernière frame
		void updatePositions();

		//Pointeur vers le m_world de ActualGame
		static b2World * m_world;
		//Ratio calculé en fonction du framerate
		static double fixedTimestepAccumulatorRatio;

		//Retourne la position smoothée en fonction de framerate de m_body
		b2Vec2 getPositionSmoothed();
		//Retourne l'angle smoothé en fonction de framerate de m_body
		double getAngleSmoothed();
		//Réinitialise les valeurs après un smooth
		void clearSmoothAngleAndPosition();

		//Retourne la position du body
		b2Vec2 getPosition();
		//Retourne la dernière position du body
		b2Vec2 getLastPosition();
		//Retourne l'angle du body
		double getAngle();
	protected :
		//Body of the physical object
		b2Body * m_body;
		//Sprite of the physical Object
		Sprite * m_sprite;

		//Position de m_body smoothée
		b2Vec2 m_smoothedPosition;
		//Position de m_body au dernier pas de simulation
		b2Vec2 m_previousPosition;
		//Angle de m_body smoothée
		double m_smoothedAngle;
		//Angle de m_body au dernier pas de simulation
		float m_previousAngle;
};
#endif