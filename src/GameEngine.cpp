#include "GameEngine.hpp"

/*
 * GameEngine Constructor
 */
GameEngine::GameEngine()
: m_actualGameScreen(TITLE)
, m_nbAvailableIslands(1)
, m_nbAvailableLevels(1)
, m_screen(NULL)
, m_windowsWidth(800)
, m_windowsHeight(600)
, m_quit(false)
, m_actualGame()
{}

/*
 * GameEngine Destructor
 */
GameEngine::~GameEngine()
{
	for(unsigned int i = 0; i < m_interfaces.size(); ++i)
	{
		delete m_interfaces[i];
	}

	//delete m_actualGame;

	SDL_FreeSurface(m_screen);

	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

/*
 * Init the SDL window, SDL_ttf, and SDL_mixer
 */
void GameEngine::initSDL()
{
	//SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cerr << "Can't initialize SDL : " << SDL_GetError() << std::endl;
		m_quit = true;
	}

	SDL_WM_SetCaption("Heavy Train", NULL);

	m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32, SDL_VIDEORESIZE | SDL_DOUBLEBUF);
	assert(m_screen);

	//SDL_ttf
	TTF_Init();

	//SDL_mixer
	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		std::cerr << "Can't initialize SDL_mixer " << std::endl;
		m_quit = true;
	}
}

/*
 * Build all the interface of the game
 */
void GameEngine::loadInterfaces()
{
	Interface * titleScreen = new Interface;
	titleScreen->loadImages(TITLE);
	m_interfaces.push_back(titleScreen);
}

/*
 * Main function of the game. Contain the game loop
 */
void GameEngine::run()
{
	//SDL initialization
	initSDL();

	//Interface initialization
	loadInterfaces();

	while(!m_quit)
	{
		update();
		render();
	}
}

/*
 * Proceed operations of the game
 */
void GameEngine::update()
{
	assert(m_actualGameScreen < m_interfaces.size() );
	m_interfaces[m_actualGameScreen]->update();

	SDL_Event event;
	if( SDL_PollEvent(&event) )
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_quit = true;
				break;
			case SDL_VIDEORESIZE:
				m_windowsWidth = event.resize.w;
				m_windowsHeight = event.resize.h;
				m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32, SDL_VIDEORESIZE | SDL_DOUBLEBUF);
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					m_quit = true;
				}
				else
				{
					m_interfaces[m_actualGameScreen]->checkKeyboardEvent(&(event.key));
				}
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				m_interfaces[m_actualGameScreen]->checkMouseEvent(&(event.button));
				break;
		}
	}
}

/*
 * Render the game
 */
void GameEngine::render()
{
	SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );

	assert(m_actualGameScreen < m_interfaces.size() );
	m_interfaces[m_actualGameScreen]->render(m_screen, m_windowsWidth, m_windowsHeight);

	// Update screen
	SDL_UpdateRect(m_screen, 0, 0, m_windowsWidth, m_windowsHeight);
	SDL_Flip(m_screen);
}

/*
 * Change the actual game screen
 */
void GameEngine::changeScreen(const GameScreen & screen)
{
	if(screen < NB_SCREENS)
	{
		m_actualGameScreen = screen;
	}
}

/*
 * Get the identifiant of the actual game screen
 */
GameScreen GameEngine::getActualGameScreen()
{
	return m_actualGameScreen;
}
