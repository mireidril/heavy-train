#ifndef __ACTUALGAME_HPP__
#define __ACTUALGAME_HPP__

#include "Train.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif

class ActualGame
{
	public :
		ActualGame();
		~ActualGame();
		void constructGround();
		void checkCollisions();
		

	private :
		Train * train;
		b2World * world;
		
};
#endif
