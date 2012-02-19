#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "Bonus.hpp"
#include "Sprite.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif

enum BlockType
{
	GROUND = 0,
	PRECIPICE,
	STATION,
	TUNNEL,
	JUNCTION_UP,
	JUNCTION_DOWN
};

class Block
{
	public :
		Block(int sizeX);
		virtual ~Block();
		void build(b2World * world);
		void scroll(int);
		b2Body * getBody();
		void setBody(b2Body * body);
		void draw(SDL_Surface * screen, const int & width, const int & height);
	private :
		Sprite * m_sprite;
		b2Body * m_body;
		int m_sizeX;
		
		int m_maxSpeed;
		int m_id;
		int m_sizeXMin;
		int m_sizeXMax;
		int m_y;
		int m_yMax;
};
#endif
