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

/*
 * Ensemble d'images
 */
class Sprite
{
	public :
		//Constructeur
		Sprite(const char* imageFileName, SDL_Rect * pos, SDL_Rect * size);
		//Destructeur
		virtual ~Sprite();
		// Setter position
		void setPosition(SDL_Rect * pos);

		//Charge et ajoute une image au sprite
		void addImage(const char* imageFileName);
		//Change l'image actuellement affichée après un temps donné (m_timeFrame)
		void animate();
		//Dessine le sprite à l'écran
		void draw(SDL_Surface * screen, const int & width, const int & height);
		//Change l'image actuellement affichée par une autre
		void changeImageManually(const int & imageNum);

		//static void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
		//static Uint32 getpixel(SDL_Surface *surface, int x, int y);

	private :
		//Numero de l'image actuellment affichée
		unsigned int				m_actualFrame;
		//Nombre d'images du sprite
		unsigned int				m_nbFrames;
		//Toutes les images du sprite
		std::vector<SDL_Surface*>	m_frames;

		//Position du sprite
		SDL_Rect*					m_position;
		//Angle de rotation du sprite
		double						m_angle;
		//Taille X et Y du sprite
		SDL_Rect*					m_size;

		//Temps d'affichage de l'image actuelle
		int							m_timeActualFrame;
		//Temps d'affichage de chaque image
		int							m_timeFrame;
};

#endif
