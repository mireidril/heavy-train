#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include "Interface.hpp"
#include "ActualGame.hpp"

#ifdef _WIN32
#include "SDL/SDL.h"
#include "tinyXML/tinyxml.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_framerate.h"
#else
#include <SDL/SDL.h>
#include <tinyxml.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_framerate.h>
#endif

#include <map>

/*
* Classe principale du jeu. Contient les fonctions principale et la boucle de jeu
*/
class GameEngine
{
	public :
		//Contructeur
		GameEngine();
		//Destructeur
		virtual ~GameEngine();

		//Initialise la fenêtre SDL, SDl_ttf et SDL_mixer
		void initSDL();
		//Crée les écrans de jeu
		void loadInterfaces();
		//Chargement du XML des scores et des niveaux débloqués
		void loadXML();
		
		//Contient la boucle principale du jeu
		void run();
		//Gère les opérations du jeu
		void update();
		//Gère l'affichage du jeu
		void render();

		//Change l'interface actuellement affichée
		void changeScreen(const GameScreen & previousScreen, const GameScreen & screen, int level = -1, int island = -1);
		//Renvoie l'énum de l'interface actuellement affichée
		GameScreen getActualGameScreen();

		//Lance une partie
		void startGame();
		//Met en pause le jeu
		void pauseGame();
		//Quitte le jeu
		void quit();

		//Joue une musique
		void playMusic(const int & num);
		//Stoppe la musique actuellement jouée
		void stopMusic();

	private : 
		//Enum de l'interface actuellement affichée
		GameScreen					m_actualGameScreen;
		//Toutes les interfaces du jeu
		std::vector<Interface*>		m_interfaces;

		//Nombre de niveaux débloqués
		unsigned int				m_nbAvailableLevels;
		//Nombre d'îles débloquées
		unsigned int				m_nbAvailableIslands;
		
		//Ecran SDL 
		SDL_Surface*				m_screen;
		//Gestionnaire de framerate SDL
		FPSmanager					m_FPSManager;
		//Largeur de l'écran
		int							m_windowsWidth;
		//Hauteur de l'écran
		int							m_windowsHeight;

		//Quand le jeu est en cours, m_isRunning = true
		bool						m_isRunning;
		//Quand le jeu est en plein écran, m_isFullScreen = true
		bool						m_isFullScreen;

		//Partie de jeu actuellement jouée
		ActualGame*					m_actualGame;
		
		//Musique
		Mix_Music *					m_musique;
};

#endif
