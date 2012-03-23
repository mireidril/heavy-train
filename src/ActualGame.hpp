#ifndef __ACTUALGAME_HPP__
#define __ACTUALGAME_HPP__

#include "Train.hpp"
#include "Level.hpp"
#include "Time.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#include "SDL/SDL_ttf.h"
#else
#include <Box2D/Box2D.h>
#include <SDL/SDL_ttf.h>
#endif

#include <sstream>

class GameEngine;


//main collision call back function
class MyContactListener 
{
	
};

class ActualGame : public b2ContactListener
{
	public :
		ActualGame(unsigned int level, unsigned int island);
		virtual ~ActualGame();
		void runSimulation();

		void checkVictoryConditions();
		void updateActualBlock();
		//Gère l'arrêt du train en gare
		void trainAtStation();
		//Gère le départ du train de la gare
		void trainLeavingStation();
		//Scrolle le niveau en fonction du déplacement du train
		void scroll();

		void teleportTrainToLastStation();

		//Réinitialise les valeurs des PhysicalObjects après un smooth pour coller au framerate
		void clearAllSmoothAngleAndPosition();
		void smoothAllBodyPositions();

		void checkKeyboardEvent(GameEngine* g, const SDL_KeyboardEvent *event);
		void run(GameEngine * g, SDL_Surface * screen, int w, int h);
		void drawInterface(SDL_Surface * screen, const int & w, const int & h);
		//Add points to the total score
		void updateTotalScore();
		//Add points to the passenger score
		void updatePassengerScore(); 
		//Add points to the time score
		void updateTimeScore();
		//Add points to the satisfaction score
		void updateSatisfactionScore();
		//Add points to the stardust score
		void updateStarDustScore();
		//Add points to the obstacle score
		void updateObstacleScore(); //pas besoin de cette fonction puisqu'on diminue les passagers au fur et a mesure et on calculera le score a la fin

		int getTotalScore() {return m_totalScore;};
		int getPassengerScore() {return m_passengerScore;};
		int getTimeScore() {return m_timeScore;};
		int getSatisfactionScore() {return m_satisfactionScore;};
		int getStarDustScore() {return m_starDustScore;};
		int getObstacleScore() {return m_obstacleScore;};

		//Update the total score when stopping at a station
		//void calculateStopScore();
		//If an animal is visible on screen, return true
		bool isAnimalOnScreen();
		//At the end of a level, save the total score of the player in the xml file
		void saveScore(const std::string & player);
		Train * getTrain();
		//Sert a vérifier les collisions entre les obstacles et le train
		bool getObstacle(b2Contact* contact, Bonus * bonus);
		//Applique l'effet du bonus
		void bonusEffect(Bonus *);

		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact) ;

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
		unsigned int m_lastStation;
		//Factor of how many passengers will leave the train
		float m_animalsFactor;
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
		static const int m_missStationPoint = -2500;
		static const int m_nbPassengerPoint = 200;

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

		//Images de l'interface et positions des textes
		TTF_Font * m_font;
		std::vector<Sprite*> m_interfaceImages;

		//True si le joueur se trouve en condition de game over
		bool m_gameOver;

		bool m_gameWon;
};

#endif
