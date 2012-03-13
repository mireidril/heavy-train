#ifndef __ACTUALGAME_HPP__
#define __ACTUALGAME_HPP__

#include "Train.hpp"
#include "Level.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif



class ActualGame
{
	public :
		ActualGame();
		virtual ~ActualGame();
		void runSimulation();
		//Scrolle le niveau en fonction du déplacement du train
		void scroll();

		//Réinitialise les valeurs des PhysicalObjects après un smooth pour coller au framerate
		void clearAllSmoothAngleAndPosition();

		void checkKeyboardEvent(const SDL_KeyboardEvent *event);
		void run(SDL_Surface * screen, int w, int h);
		//Add points to the total score
		void updateTotalScore(const int & points);
		//Add points to the passenger score
		void updatePassengerScore(const int & points);
		//Add points to the time score
		void updateTimeScore(const int & points);
		//Add points to the satisfaction score
		void updateSatisfactionScore(const int & points);
		//Add points to the stardust score
		void updateStarDustScore(const int & points);
		//Add points to the obstacle score
		void updateObstacleScore(const int & points);
		//Update the total score when stopping at a station
		void calculateStopScore();
		//If an animal is visible on screen, return true
		bool isAnimalOnScreen();
		//At the end of a level, save the total score of the player in the xml file
		void saveScore(const std::string & player);

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
		float32 m_timeStep;
		int32 m_velocityIterations;
		int32 m_positionIterations;
		
		//Pour le debug drawing
		DebugDraw * fooDrawInstance;

		//Pour caler la simulation avec le framerate
		double fixedTimestepAccumulator;
		double fixedTimestepAccumulatorRatio;
};
#endif
