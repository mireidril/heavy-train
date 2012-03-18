#include "Interface.hpp"
#include "GameEngine.hpp"

/*
 * Constructeur
 */
Interface::Interface(GameScreen type)
: m_type(type)
, m_mousePositionX(-1)
, m_mousePositionY(-1)
, m_clic(-1)
{}

/*
 * Destructeur
 */
Interface::~Interface()
{
	for(unsigned int i = 0; i < m_backgroundImages.size(); ++i)
	{
		delete m_backgroundImages[i];
	}

	for(unsigned int i = 0; i < m_buttonsImages.size(); ++i)
	{
		delete m_buttonsImages[i];
	}
}

/*
 * Charge et stocke les images de l'interface
 */
void Interface::loadImages()
{
	switch(m_type)
	{
		case TITLE :
		{
			m_backgroundImages.push_back(new Sprite("../img/screens/title_screen.png", 0, 0, 1024, 768));
			//Buttons
			break;
		}
		case PAUSE :
		{
			m_backgroundImages.push_back(new Sprite("../img/screens/title_screen.png", 0, 0, 1024, 768));
			break;
		}
		case SCORE :
		{
			m_backgroundImages.push_back(new Sprite("../img/screens/leaderboard.jpg", 0, 0, 1024, 768));
			break;
		}
		case HELP :
		{
			m_backgroundImages.push_back(new Sprite("../img/screens/title_screen.png", 0, 0, 1024, 768));
			break;
		}
		case ISLAND :
		{
			m_backgroundImages.push_back(new Sprite("../img/screens/level_select_background.jpg", 0, 0, 1024, 768));
			break;
		}
		case WORLD :
		{
			m_backgroundImages.push_back(new Sprite("../img/screens/level_select_background.jpg", 0, 0, 1024, 768));
			//Buttons
			Sprite * isle1 = new Sprite("../img/screens/paradisio_unselected.png", 100, 200, 347, 290);
			isle1->addImage("../img/screens/paradisio_selected.png");
			m_buttonsImages.push_back(isle1);
			Sprite * isle2 = new Sprite("../img/screens/dolfina_unselected.png", 500, 200, 347, 290);
			isle2->addImage("../img/screens/dolfina_selected.png");
			isle2->addImage("../img/screens/dolfina_locked.png");
			m_buttonsImages.push_back(isle2);
			Sprite * isle3 = new Sprite("../img/screens/chicken_island_unselected.png", 300, 400, 347, 290);
			isle3->addImage("../img/screens/chicken_island_selected.png");
			isle3->addImage("../img/screens/chicken_island_locked.png");
			m_buttonsImages.push_back(isle3);
			break;
		}
		case ENDGAME :
		{
			m_backgroundImages.push_back(new Sprite("../img/screens/title_screen.png", 0, 0, 1024, 768));
			break;
		}
		default :
			break;
	}
}

/*
 * Gère les opérations de l'interface
 */
void Interface::update(GameEngine * gameEngine)
{
	for(unsigned int i = 0; i < m_buttonsImages.size(); ++i)
	{
		if(m_mousePositionX >= m_buttonsImages[i]->getPositionX() && m_mousePositionX < (m_buttonsImages[i]->getPositionX() + m_buttonsImages[i]->getSizeX() ) &&
		   m_mousePositionY >= m_buttonsImages[i]->getPositionY() && m_mousePositionY < (m_buttonsImages[i]->getPositionY() + m_buttonsImages[i]->getSizeY() ) )
		{
			if(m_clic == 1)
			{
				gameEngine->changeScreen(GAME);
				m_clic = -1;
			}
			m_buttonsImages[i]->changeImageManually(1);
		}
		else
		{
			m_buttonsImages[i]->changeImageManually(0);
		}
	}

	if(m_clic == 1)
	{
		m_clic = -1;
	}
}

/*
 * Gère l'affichage de l'interface
 * screen : fenêtre SDL
 * width : largeur de l'écran
 * height : hauteur de l'écran
 */
void Interface::render(SDL_Surface * screen, const int & width, const int & height)
{
	for(unsigned int i = 0; i < m_backgroundImages.size(); ++i)
	{
		m_backgroundImages[i]->draw(screen, width, height);
	}
	for(unsigned int i = 0; i < m_buttonsImages.size(); ++i)
	{
		m_buttonsImages[i]->draw(screen, width, height);
	}
}

/*
 * Gère les évènements de mouvement de la souris
 */
void Interface::checkMouseMotionEvent(const SDL_MouseMotionEvent *event)
{
	m_mousePositionX = event->x;
	m_mousePositionY = event->y;
}

/*
 * Gère les évènements de la souris
 */
void Interface::checkMouseEvent(const SDL_MouseButtonEvent *event)
{
	if( event->button == int(SDL_BUTTON_LEFT) && event->state == int(SDL_PRESSED) )
	{
		m_clic = 0;
	}

	if( event->button == int(SDL_BUTTON_LEFT) && event->state == int(SDL_RELEASED) )
	{
		if(m_clic == 0)
		{
			m_clic = 1;
		}
	}
}

/*
 * Gère les évènements clavier
 */
void Interface::checkKeyboardEvent(const SDL_KeyboardEvent *event)
{
	switch(event->keysym.sym)
	{
		case SDLK_UP :
			std::cout<<"UP arrow"<<std::endl;
			break;
		default:
			break;
	}
}



