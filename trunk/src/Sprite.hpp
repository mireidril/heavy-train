#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

#ifdef _WIN32
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#else
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#endif

#include <vector>
#include <cassert>
#include <iostream>

class Sprite
{
	public :

		Sprite(const char* imageFileName, SDL_Rect * pos, SDL_Rect * size);
		virtual ~Sprite();

		void addImage(const char* imageFileName);
		void animate();
		void draw(SDL_Surface * screen, const int & width, const int & height);
		void changeImageManually(const int & imageNum);

	private :

		unsigned int				m_actualFrame;
		unsigned int				m_nbFrames;
		std::vector<SDL_Surface*>	m_frames;

		SDL_Rect*					m_position;
		double						m_angle;
		SDL_Rect*					m_size;

		int							m_timeActualFrame;
		int							m_timeFrame;
};

#endif