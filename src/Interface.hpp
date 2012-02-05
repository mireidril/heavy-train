#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include "Sprite.hpp"

#include <map>

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

class Interface
{
	public :

		Interface();
		virtual ~Interface();
 
		void loadImages(const GameScreen & screen);

		void update();
		void render(SDL_Surface * screen, const int & width, const int & height);

		void checkMouseEvent(const SDL_MouseButtonEvent *event);
		void checkKeyboardEvent(const SDL_KeyboardEvent *event);

		//void displayText(const Point & position, const std::string & text);

	private :

		std::vector<Sprite*>		m_backgroundImages;
		std::vector<Sprite*>		m_buttonsImages;
		int							m_buttonSelected;
};

#endif