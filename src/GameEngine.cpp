#include "GameEngine.hpp"

/*
 * Constructeur
 */
GameEngine::GameEngine() {

	std::cout << "game Engine constructor" << std::endl;

	m_actualGameScreen = TITLE;
	m_nbAvailableIslands = 1;
	m_nbAvailableLevels = 1;
	m_screen = NULL;
	m_windowsWidth = 1024;
	m_windowsHeight = 768;
	m_isRunning=true;
	m_isFullScreen=false;
	m_actualGame = new ActualGame();
}

/* cloclo: j'ai changé parce ce que ça appelait pas le constructeur de actualGame
GameEngine::GameEngine()
: m_actualGameScreen(TITLE)
, m_nbAvailableIslands(1)
, m_nbAvailableLevels(1)
, m_screen(NULL)
, m_windowsWidth(1024)
, m_windowsHeight(768)
, m_isRunning(true)
, m_isFullScreen(false)
, m_actualGame()
{
}*/

/*
 * Destructeur
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
 * Initialise la fenêtre SDL, SDl_ttf et SDL_mixer
 */
void GameEngine::initSDL()
{
	//SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cerr << "Can't initialize SDL : " << SDL_GetError() << std::endl;
		m_isRunning = false;
	}

	SDL_WM_SetCaption("Heavy Train", NULL);

	m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32, SDL_DOUBLEBUF);
	assert(m_screen);

	//SDL_ttf
	TTF_Init();

	//SDL_mixer
	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		std::cerr << "Can't initialize SDL_mixer " << std::endl;
		m_isRunning = false;
	}
}

/*
 * Crée les écrans de jeu
 */
void GameEngine::loadInterfaces()
{
	Interface * titleScreen = new Interface;
	titleScreen->loadImages(TITLE);
	m_interfaces.push_back(titleScreen);

	Interface * pauseScreen = new Interface;
	pauseScreen->loadImages(PAUSE);
	m_interfaces.push_back(pauseScreen);
}

/*
 * Contient la boucle principale du jeu
 */
void GameEngine::run()
{
	std::cout << "Game Engine run" << std::endl;
	//Initialisation SDL
	initSDL();

	//Initialisation de l'interface
	loadInterfaces();

	while(m_isRunning)
	{
		update();
		render();
	}
}

/*
 * Gère les opérations du jeu
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
				m_isRunning = false;
				break;
			/*case SDL_VIDEORESIZE:
				m_windowsWidth = event.resize.w;
				m_windowsHeight = event.resize.h;
				m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32, SDL_VIDEORESIZE | SDL_DOUBLEBUF);
				break;
			*/
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					m_isRunning = false;
				}
				else if(event.key.keysym.sym == SDLK_F11)
				{
					if(!m_isFullScreen)
					{
						m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32, SDL_FULLSCREEN | SDL_DOUBLEBUF);
						m_isFullScreen = true;
					}
					else
					{
						m_screen = SDL_SetVideoMode(m_windowsWidth, m_windowsHeight, 32,  SDL_DOUBLEBUF);
						m_isFullScreen = false;
					}

				}
				else
				{
					m_interfaces[m_actualGameScreen]->checkKeyboardEvent(&(event.key));
				}
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				m_interfaces[m_actualGameScreen]->checkMouseEvent(this, &(event.button));
				break;
			case SDL_MOUSEMOTION:
				m_interfaces[m_actualGameScreen]->checkMouseMotionEvent(&(event.motion));
				break;
		}
	}
}

/*
 * Gère l'affichage du jeu
 */
void GameEngine::render()
{
	SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );

	assert(m_actualGameScreen < m_interfaces.size() );
	m_interfaces[m_actualGameScreen]->render(m_screen, m_windowsWidth, m_windowsHeight);

	// Met à jour l'affichage
	SDL_UpdateRect(m_screen, 0, 0, m_windowsWidth, m_windowsHeight);
	SDL_Flip(m_screen);
}

/*
 * Change l'interface actuellement affichée
 * screen : Enum du nouvel écran de jeu
 */
void GameEngine::changeScreen(const GameScreen & screen)
{
	if(screen < NB_SCREENS)
	{
		m_actualGameScreen = screen;
	}
}

/*
 * Renvoie l'énum de l'interface actuellement affichée
 */
GameScreen GameEngine::getActualGameScreen()
{
	return m_actualGameScreen;
}
