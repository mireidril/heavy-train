#ifndef __ACTUALGAME_HPP__
#define __ACTUALGAME_HPP__

#include "Train.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif

#include "Level.hpp"

class ActualGame
{
	public :
		ActualGame();
		~ActualGame();
		void checkCollisions();
		

	private :
		Time * m_timer;
		int m_totalScore;
		Time * m_actualTime;
		int m_passengerScore;
		int m_timeScore;
		int m_satisfactionScore;
		int m_starDustScore;
		int m_obstacleScore;
		int m_actualBlock;
		float m_animalsFactor;
		float m_speedLimitFactor;
		int m_stopStationPoint;
		int m_drivePoint;
		int m_starsPoint;
		int m_timePoint;
		int m_onTimePoint;
		int m_missStationPoint;
		int m_nbPassengerPoint;

		Level * m_actualLevel;
		Train * m_train;
		b2World * m_world;
		
};
#endif