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
		void checkCollisions();
		

	private :
		Train * m_train;
		b2World * m_world;
		
};
#endif
