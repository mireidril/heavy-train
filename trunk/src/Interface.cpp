#include "Interface.hpp"
#include "GameEngine.hpp"

/*
 * Constructeur
 */
Interface::Interface()
: m_buttonSelected(-1)
{}

/*
 * Destructeur
 */
Interface::~Interface()
{
	for(unsigned int i = 0; i < m_buttonsImages.size(); ++i)
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
 * screen : enum correspondant au type d'interface
 */
void Interface::loadImages(const GameScreen & screen)
{
	Sprite * background;
	switch(screen)
	{
		case TITLE :
			background = new Sprite("../img/screens/title_screen.png", 0, 0, 1024, 768);
			assert(background);
			m_backgroundImages.push_back(background);
			break;
		case PAUSE :
			background = new Sprite("../img/screens/ecran1_test3.png", 0, 0, 800, 600);
			assert(background);
			m_backgroundImages.push_back(background);
			break;
	}
}

/*
 * Gère les opérations de l'interface
 */
void Interface::update()
{
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
		Sprite * img = m_backgroundImages[i];
		assert(img);
		img->draw(screen, width, height);
	}
}

/*
 * Gère les évènements de mouvement de la souris
 */
void Interface::checkMouseMotionEvent(const SDL_MouseMotionEvent *event)
{

}

/*
 * Gère les évènements de la souris
 */
void Interface::checkMouseEvent(GameEngine * gameEngine, const SDL_MouseButtonEvent *event)
{
	if( event->button == int(SDL_BUTTON_LEFT) && event->state == int(SDL_PRESSED) )
	{
		/*m_iMousePositionX = event->x;
		m_iMousePositionY = event->y;
		m_bButtonPressed = true;*/
	}

	if( event->button == int(SDL_BUTTON_LEFT) && event->state == int(SDL_RELEASED) )
	{
		//m_bButtonPressed = false;
		gameEngine->changeScreen(GAME);
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



