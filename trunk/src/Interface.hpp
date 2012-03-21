#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include "Sprite.hpp"

#ifdef _WIN32
#include "SDL/SDL_ttf.h"
#include "tinyXML/tinyxml.h"
#else
#include <SDL/SDL_ttf.h>
#include <tinyxml.h>
#endif

#include <map>
#include <sstream>

class GameEngine;

/*
* Type d'interface
*/
enum GameScreen
{
	TITLE = 0,
	PAUSE,
	SCORE,
	HELP,
	WORLD,
	ISLAND,
	ENDGAME,
	GAME,
	NB_SCREENS,
	OPTIONS
};

/*
* Leaderboard pour un niveau d'une ile précise
*/
typedef struct _leaderboard
{
	//Ile
	unsigned int island;
	//Niveau
	unsigned int level;
	//Multimap contenant le score(int) et le nom de la personne associée (std::string)
	std::multimap< int, std::string > m_scores;
} Leaderboard;

/*
* Ecran de jeu
*/
class Interface
{
	public :
		//Constructeur
		Interface(GameScreen type);
		//Destructeur
		virtual ~Interface();
 
		//Charge l'interface et stocke les images de l'interface
		void load();
		//Chargement du XML des scores et des niveaux débloqués
		void loadXML(int level = -1, int island = -1);

		//Gère les opérations de l'interface
		void update(GameEngine * gameEngine);
		//Gère l'affichage de l'interface
		void render(SDL_Surface * screen, const int & width, const int & height);

		//Gère les évènements de mouvement de la souris
		void checkMouseMotionEvent(const SDL_MouseMotionEvent *event);
		//Gère les évènements de la souris
		void checkMouseEvent(const SDL_MouseButtonEvent *event);
		//Gère les évènements clavier
		void checkKeyboardEvent(const SDL_KeyboardEvent *event);

		//Affiche du texte à l'écran
		void displayText(SDL_Surface * screen, const SDL_Rect * position, const std::string & text);
		
		//Charge le niveau n°level de l'île n°island
		std::multimap<std::string, int> loadScores(const int & island, const int & level);
		//Renvoie le nombre d'îles débloquées
		unsigned int getNbAvailableIslands();
		//Renvoie le nombre de niveaux débloqués pour la dernière île débloquée
		unsigned int getNbAvailableLevels();

	private :
		//const unsigned int						m_nbLevelByIsland;
		//Sprites des images de fond de l'interface
		std::vector<Sprite*>					m_backgroundImages;
		//Sprites des boutons de l'interface
		std::vector<Sprite*>					m_buttonsImages;
		//Type de l'interface
		GameScreen								m_type;
		//Informations souris
		int										m_mousePositionX;
		int										m_mousePositionY;
		int										m_clic;
		//Nombre de niveaux débloqués
		unsigned int							m_nbAvailableLevels;
		//Nombre d'îles débloquées
		unsigned int							m_nbAvailableIslands;

		//Scores
		std::vector<Leaderboard*>				m_leaderboards;
		unsigned int							m_actualLeaderboard;
		//Police d'écriture
		TTF_Font *								m_font;
		
};

#endif
