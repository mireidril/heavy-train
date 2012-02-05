#include "Interface.hpp"

/*
 * Interface Constructor
 */
Interface::Interface()
: m_buttonSelected(-1)
{}

/*
 * Interface Destructor
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
 * Load all the images of the interface
 */
void Interface::loadImages(const GameScreen & screen)
{
	switch(screen)
	{
		case TITLE :
			SDL_Rect * position = new SDL_Rect;
			assert(position);
			position->x = 0;
			position->y = 0;
			SDL_Rect * size = new SDL_Rect;
			assert(size);
			size->x = 800;
			size->y = 600;
			Sprite * background = new Sprite("../img/title.jpg", position, size);
			assert(background);
			m_backgroundImages.push_back(background);
			break;
	}
}

/*
 * Proceed operations of the interface
 */
void Interface::update()
{
}

/*
 * Render the interface
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
 * Keyboard events listener of the interface
 */
void Interface::checkKeyboardEvent(const SDL_KeyboardEvent *event)
{
	switch(event->keysym.sym)
	{
		default:
			break;
	}
}

/*
 * Mouse events listener of the interface
 */
void Interface::checkMouseEvent(const SDL_MouseButtonEvent *event)
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
	}
}

