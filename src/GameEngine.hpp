#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include "Interface.hpp"

#ifdef _WIN32
#include "SDL/SDL.h"
#include "tinyXML/tinyxml.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#else
#include <SDL/SDL.h>
#include <tinyxml.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#endif

#include <map>

class GameEngine
{
	public :

		GameEngine();
		virtual ~GameEngine();

		void initSDL();
		void loadInterfaces();
		
		void run();
		void update();
		void render();

		void changeScreen(const GameScreen & screen);
		GameScreen getActualGameScreen();

		void startGame();
		void pauseGame();
		void quit();

		void playSound(const int & num);
		void playMusic(const int & num);
		void stopMusic();

		std::multimap<std::string, int> loadScores(const int & island, const int & level);
		unsigned int getNbAvailableIslands();
		unsigned int getNbAvailableLevels();

	private : 

		GameScreen					m_actualGameScreen;
		std::vector<Interface*>		m_interfaces;

		unsigned int				m_nbAvailableLevels;
		unsigned int				m_nbAvailableIslands;
		
		SDL_Surface*				m_screen;
		int							m_windowsWidth;
		int							m_windowsHeight;

		bool						m_quit;

		//ActualGame*					m_actualGame;

};

#endif