#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

#ifdef _WIN32
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

#include "Box2D/Box2D.h"
#include "SDL/SDL_gfxPrimitives.h"
#else
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include <Box2D/Box2D.h>
#include <SDL/SDL_gfxPrimitives.h>
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

		static void convertMetersToPixels (double & x, double & y, const int & width, const int & height);
		static void convertPixelsToMeters (double & x, double & y, const int & width, const int & height);
		
		double getSizeX();
		double getSizeY();

		//static void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
		//static Uint32 getpixel(SDL_Surface *surface, int x, int y);
		static SDL_Surface* screen;

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

class DebugDraw : public b2Draw
{
  public:
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
		b2Color color2(1.0, 0.0, 0.0);
		for(int i = 1; i < vertexCount; ++i){
			DrawSegment(vertices[i-1], vertices[i], color2);
		}
		DrawSegment(vertices[vertexCount-1], vertices[0], color2);
	}
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
		b2Color color2(1.0, 0.0, 0.0);
		double x1, x2, y1, y2;
		if( vertexCount == 4) {
			float sizeX = abs(vertices[0].x - vertices[2].x);
			float sizeY = abs(vertices[1].y - vertices[3].y);
			//float decX = vertices[0].x - sizeX;
			//float decY = vertices[0].y - sizeY;
			//std::cout<<"coord : "<<decX<<", "<<decY<<std::endl;

			for(int i = 1; i < vertexCount; ++i){
				x1 = (vertices[i-1].x + sizeX/2) / 2;
				y1 = (vertices[i-1].y + sizeY/2) / 2;
				x2 = (vertices[i].x + sizeX/2) / 2;
				y2 = (vertices[i].y + sizeY/2) / 2;

				//std::cout<<"X2 : "<<x1<<" "<<y1<<std::endl;
				Sprite::convertMetersToPixels(x1, y1, 1024, 768);
				Sprite::convertMetersToPixels(x2, y2, 1024, 768);
				//std::cout<<"X2 : "<<x1<<" "<<y1<<std::endl;
				lineRGBA(Sprite::screen, (Sint16) x1 , (Sint16) y1, (Sint16) x2, (Sint16) y2, (Uint8) color2.r * 255, (Uint8) color2.g * 255, (Uint8) color2.b * 255, 255);
			}
			x1 = (vertices[vertexCount-1].x + sizeX/2) / 2;
			y1 = (vertices[vertexCount-1].y + sizeY/2) / 2;
			x2 = (vertices[0].x + sizeX/2) / 2;
			y2 = (vertices[0].y + sizeY/2) / 2;

			Sprite::convertMetersToPixels(x1, y1, 1024, 768);
			Sprite::convertMetersToPixels(x2, y2, 1024, 768);
			lineRGBA(Sprite::screen, (Sint16) x1 , (Sint16) y1, (Sint16) x2, (Sint16) y2, (Uint8) color2.r * 255, (Uint8) color2.g * 255, (Uint8) color2.b * 255, 255);
		}
		
		/*for(int i = 1; i < vertexCount; ++i){
			DrawSegment(vertices[i-1], vertices[i], color2);
		}
		DrawSegment(vertices[vertexCount-1], vertices[0], color2);*/
	}
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
		b2Color color2(1.0, 0.0, 0.0);
		double x = center.x;
		double y = center.y;
		Sprite::convertMetersToPixels(x, y, 1024, 768);
		double rX = radius;
		double rY = radius;
		Sprite::convertMetersToPixels(rX, rY, 1024, 768);

		ellipseRGBA(Sprite::screen, (Sint16) x, (Sint16) y, (Sint16) rX, (Sint16) rY, (Uint8) color.r, (Uint8) color2.g, (Uint8) color2.b, 255);
	}
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
		b2Color color2(1.0, 0.0, 0.0);
		double x = center.x + radius / 2;
		double y = center.y + radius / 2;
		Sprite::convertMetersToPixels(x, y, 1024, 768);
		double rX = radius / 2;
		double rY = radius / 2;
		Sprite::convertMetersToPixels(rX, rY, 1024, 768);

		ellipseRGBA(Sprite::screen, (Sint16) x, (Sint16) y, (Sint16) rX, (Sint16) rY, (Uint8) color.r, (Uint8) color2.g, (Uint8) color2.b, 255);
	}
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
		float sizeX = abs(p1.x - p2.x);
		float sizeY = abs(p1.y - p2.y);
		//std::cout<<"coord : "<<sizeX<<", "<<sizeY<<std::endl;
		double x1 = (p1.x + sizeX/2) / 2;
		double y1 = (p1.y + sizeY/2) / 2;
		double x2 = (p2.x + sizeX/2) / 2;
		double y2 = (p2.y + sizeY/2) / 2;

		//std::cout<<"coord : "<<x1<<", "<<y1<<std::endl;
		Sprite::convertMetersToPixels(x1, y1, 1024, 768);
		Sprite::convertMetersToPixels(x2, y2, 1024, 768);
		lineRGBA(Sprite::screen, (Sint16) x1 , (Sint16) y1, (Sint16) x2, (Sint16) y2, (Uint8) color.r * 255, (Uint8) color.g * 255, (Uint8) color.b * 255, 255);
	}
    void DrawTransform(const b2Transform& xf) {
	}
};

#endif
