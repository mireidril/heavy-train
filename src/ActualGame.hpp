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
		//void updateStarDustScore(const int & points);
		void updateStarDustScore();
		//Add points to the obstacle score
		void updateObstacleScore();
		//Update the total score when stopping at a station
		void calculateStopScore(const int & points);
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
		//Factor of how many passengers will leave the train
		static float m_animalsFactor;
		//Factor of how many passengers will leave the train while in a limit speed zone
		static float m_speedLimitFactor;
		//How many points the player gains for each start dust
		static const int m_starsPoint = 900;
		//How many satisfaction point the player can lose if he drive so badly
		static const int m_drivePoint = -100;
		//How many satisfaction point the player win or lose when he stop his train correctly at the station
		static const int m_stopStationPoint = 500;
		//How many points per minute the player lose if he arrives too late AND how many point the gamer win (per minutes) if he arrives more than 10 minutes the time at the station
		static const int m_timePoint = 700;
		//How many points the player gains if he arrives between 1 and 10 minutes before time at the station
		static const int m_onTimeInfTenPoint = 1400;
		//How many points the player gains if he arrives on time at the station
		static const int m_onTimePoint = 5000;
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

		//On stocke ici la dernière position du train avant scrolling
		double m_lastPosXTrain;
};
#endif
