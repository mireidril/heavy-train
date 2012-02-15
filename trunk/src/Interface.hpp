#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include "Sprite.hpp"

#include <map>

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
	GAME,
	ENDGAME,
	NB_SCREENS
};

/*
* Ecran de jeu
*/
class Interface
{
	public :
		//Constructeur
		Interface();
		//Destructeur
		virtual ~Interface();
 
		//Charge et stocke les images de l'interface
		void loadImages(const GameScreen & screen);

		//Gère les opérations de l'interface
		void update();
		//Gère l'affichage de l'interface
		void render(SDL_Surface * screen, const int & width, const int & height);

		//Gère les évènements de mouvement de la souris
		void checkMouseMotionEvent(const SDL_MouseMotionEvent *event);
		//Gère les évènements de la souris
		void checkMouseEvent(GameEngine * gameEngine, const SDL_MouseButtonEvent *event);
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

		//Sprites des images de fond de l'interface
		std::vector<Sprite*>		m_backgroundImages;
		//Sprites des boutons de l'interface
		std::vector<Sprite*>		m_buttonsImages;
		//Numéro du bouton actuellement sélectionné
		int							m_buttonSelected;
};

#endif