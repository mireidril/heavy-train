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
, m_nbAvailableIslands(1)
, m_nbAvailableLevels(1)
, m_actualLeaderboard(0)
{
	m_font =  TTF_OpenFont("../fonts/GretoonHighlight.ttf", 40);
}

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

	for(unsigned int i = 0; i < m_leaderboards.size(); ++i)
	{
		delete m_leaderboards[i];
	}

	TTF_CloseFont(m_font);
}

/*
 * Charge et stocke les images de l'interface
 */
void Interface::load()
{
	switch(m_type)
	{
		case TITLE :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/menu_background.jpg", 0, 0, 1024, 768));
			//Buttons Images
			Sprite * play = new Sprite("../img/screens/play_button_unselected.png", 425, 250, 153, 83);
			play->addImage("../img/screens/play_button_selected.png");
			Sprite * score = new Sprite("../img/screens/scores_button_unselected.png", 390, 333, 249, 74);
			score->addImage("../img/screens/scores_button_selected.png");
			Sprite * instruc = new Sprite("../img/screens/instructions_button_unselected.png", 315, 407, 425, 67);
			instruc->addImage("../img/screens/instructions_button_selected.png");
			Sprite * option = new Sprite("../img/screens/options_button_unselected.png", 390, 474, 260, 66);
			option->addImage("../img/screens/options_button_selected.png");
			Sprite * quit = new Sprite("../img/screens/quit_button_unselected.png", 425, 540, 145, 59);
			quit->addImage("../img/screens/quit_button_selected.png");

			m_buttonsImages.push_back(play);
			m_buttonsImages.push_back(score);
			m_buttonsImages.push_back(instruc);
			m_buttonsImages.push_back(option);
			m_buttonsImages.push_back(quit);
			break;
		}
		case PAUSE :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/ecran1_test3.png", 0, 0, 1024, 768));
			break;
		}
		case SCORE :
		{
			//Récupération des informations du XML
			loadXML(0, 0);
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/leaderboard.jpg", 0, 0, 1024, 768));
			//Buttons Images
			Sprite * leftArrow1 = new Sprite("../img/screens/leftArrow_unselected.png", 300, 160, 60, 50);
			leftArrow1->addImage("../img/screens/leftArrow_selected.png");
			Sprite * rightArrow1 = new Sprite("../img/screens/rightArrow_unselected.png", 650, 160, 60, 50);
			rightArrow1->addImage("../img/screens/rightArrow_selected.png");
			
			m_buttonsImages.push_back(leftArrow1);
			m_buttonsImages.push_back(rightArrow1);

			break;
		}
		case HELP :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/ecran1_test3.png", 0, 0, 1024, 768));
			break;
		}
		case ISLAND :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/level_select_background.jpg", 0, 0, 1024, 768));
			break;
		}
		case WORLD :
		{
			//Récupération des informations du XML
			loadXML();
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/level_select_background.jpg", 0, 0, 1024, 768));
			//Buttons Images
			Sprite * isle1 = new Sprite("../img/screens/paradisio_unselected.png", 100, 200, 347, 290);
			isle1->addImage("../img/screens/paradisio_selected.png");
			Sprite * isle2 = new Sprite("../img/screens/dolfina_unselected.png", 500, 200, 347, 290);
			isle2->addImage("../img/screens/dolfina_selected.png");
			isle2->addImage("../img/screens/dolfina_locked.png");
			Sprite * isle3 = new Sprite("../img/screens/chicken_island_unselected.png", 300, 400, 347, 290);
			isle3->addImage("../img/screens/chicken_island_selected.png");
			isle3->addImage("../img/screens/chicken_island_locked.png");

			switch(m_nbAvailableIslands)
			{
				case 1:
					isle2->changeImageManually(2);
				case 2:
					isle3->changeImageManually(2);
				case 3:
					break;
			}

			m_buttonsImages.push_back(isle1);
			m_buttonsImages.push_back(isle2);
			m_buttonsImages.push_back(isle3);
			break;
		}
		case OPTIONS :
		{
			break;
		}
		case ENDGAME :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/ecran1_test3.png", 0, 0, 1024, 768));
			break;
		}
		default :
			break;
	}
}

//Chargement du XML des scores et des niveaux débloqués
void Interface::loadXML(int level, int island)
{
	m_leaderboards.clear();
	
	TiXmlDocument doc("../levels/save.xml");
	int score;
	std::string player;
	Leaderboard l;
	
	if(!doc.LoadFile())
	{
		std::cerr << "erreur lors du chargement du XML des scores" << std::endl;
		std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
		exit(0);
	}
	else
	{
	
		//permet de sécuriser le pacours des noeud (dans le cas ou l'un des noeuds n'existerait pas)
		TiXmlHandle hdl(&doc);
		std::cerr << "Interface.cpp : après TiXmlHandle hdl(&doc) " << std::endl;
		TiXmlElement *level = hdl.FirstChildElement().FirstChildElement().Element();
		
		if(!level){
			std::cerr << "le noeud à atteindre n'existe pas" << std::endl;
			exit(0);
		}
		
		if(atoi(level->Attribute("id")) == 1){
		TiXmlElement *scorePlayer = level->FirstChildElement();
			while(scorePlayer){
				player = scorePlayer->Attribute("player");
				score = atoi(scorePlayer->Attribute("value"));
				std::cout<<"player : "<<player<<std::endl;
				std::cout<<"value : "<<score<<std::endl;
			  	//l.m_scores.insert ( std::pair<std::string,int>(player,score) );
			  	scorePlayer = scorePlayer->NextSiblingElement(); 
		

			}
		}
		
		


	}
	
	
	
	/////////////////////////////////////
	
	
			//Récupère uniquement le nombre de niveaux débloqués
		/*if(level <= 0 && island <= 0)
		{
			//A REMPLIR
		
			//TESTS : à virer après le chargement XML
			m_nbAvailableLevels = 1;
			m_nbAvailableIslands = 2;
		}
	
		//Récupère tous les scores : UTILISE APRES L'ECRAN TITLE
		if(level == 0 && island == 0) 
		{*/
			/*S'il n'y a rien dans le XML concernant un niveau, on ajoute le leaderboard suivant
			Leaderboard * levelL = new Leaderboard;
			levelL->island = island;
			levelL->level = level;
			for(unsigned int i = 1; i < 5; ++i)
			{
				levelL->m_scores.insert(std::make_pair(i * 1000, "BabyBool"));
			}
			m_leaderboards.push_back(levelL);
			*/

			//A REMPLIR

			//TESTS : à virer après le chargement XML
			/*for(unsigned int i = 1; i <= m_nbAvailableIslands; ++i)
			{
				for(unsigned int l = 1; l <= m_nbAvailableLevels; ++l)
				{
					Leaderboard * levelL = new Leaderboard;
					levelL->island = i;
					levelL->level = l;
					for(unsigned int i = 1; i < 6; ++i)
					{
						levelL->m_scores.insert(std::make_pair(i * 1000, "Level" ) );
					}
					m_leaderboards.push_back(levelL);
				}
			}
		}
		//Récupère les scores du niveau "level" de l'ile "island" : UTILISE APRES L'ECRAN ISLAND ou A L'ECRAN ENDGAME
		else if(level > 0 && island > 0)
		{*/
			/*S'il n'y a rien dans le XML concernant un niveau, on ajoute le leaderboard suivant
			Leaderboard * levelL = new Leaderboard;
			levelL->island = island;
			levelL->level = level;
			for(unsigned int i = 1; i < 5; ++i)
			{
				levelL->m_scores.insert(std::make_pair(i * 1000, "BabyBool"));
			}
			m_leaderboards.push_back(levelL);
			*/

			//A REMPLIR
		//}


}

/*
 * Gère les opérations de l'interface
 */
void Interface::update(GameEngine * gameEngine)
{
	//On récupère le bouton cliqué
	int buttonChosen = -1;
	for(unsigned int i = 0; i < m_buttonsImages.size(); ++i)
	{
		if(m_mousePositionX >= m_buttonsImages[i]->getPositionX() && m_mousePositionX < (m_buttonsImages[i]->getPositionX() + m_buttonsImages[i]->getSizeX() ) &&
		   m_mousePositionY >= m_buttonsImages[i]->getPositionY() && m_mousePositionY < (m_buttonsImages[i]->getPositionY() + m_buttonsImages[i]->getSizeY() ) )
		{
			if(m_clic == 1 && !(m_type == WORLD && i >= m_nbAvailableIslands) )
			{
				buttonChosen = i;
				m_clic = -1;
			}
			
			//Si on est dans l'écran WORLD, on ne change pas l'image des îles non débloquées
			if( ! (m_type == WORLD && i >= m_nbAvailableIslands) )
			{
				m_buttonsImages[i]->changeImageManually(1);
			}
		}
		else
		{
			//Si on est dans l'écran WORLD, on ne change pas l'image des îles non débloquées
			if(m_type == WORLD && i >= m_nbAvailableIslands) 
			{
				m_buttonsImages[i]->changeImageManually(2);
			}
			else
			{
				m_buttonsImages[i]->changeImageManually(0);
			}
		}
	}

	//On effectue l'action correspondant au bouton cliqué
	if(buttonChosen != -1)
	{
		switch(m_type)
		{
			case TITLE :
			{
				switch(buttonChosen)
				{
					case 0:
						gameEngine->changeScreen(m_type, WORLD, -1, -1);
						break;
					case 1:
						gameEngine->changeScreen(m_type, SCORE, 0, 0);
						break;
					case 2:
						gameEngine->changeScreen(m_type, HELP, -1, -1);
						break;
					case 3:
						gameEngine->changeScreen(m_type, OPTIONS, -1, -1);
						break;
					case 4:
						gameEngine->quit();
						break;
					default:
						break;
				}
				break;
			}
			case PAUSE :
			{
				break;
			}
			case SCORE :
			{
				//On affiche le score précédent
				if(buttonChosen == 0)
				{
					if(m_actualLeaderboard > 0)
					{
						m_actualLeaderboard--;
					}
				}
				else if(buttonChosen == 1)
				{
					if(m_actualLeaderboard < m_leaderboards.size() - 1)
					{
						m_actualLeaderboard++;
					}
				}

				break;
			}
			case HELP :
			{
				break;
			}
			case ISLAND :
			{
				break;
			}
			case WORLD :
			{
				//Si on clique sur une île
				if(buttonChosen < m_nbAvailableIslands)
				{
					gameEngine->changeScreen(m_type, GAME, 1, buttonChosen+1);
				}
				break;
			}
			case OPTIONS:
				break;
			case ENDGAME :
			{
				break;
			}
			default :
				break;
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
		if(m_type != SCORE)
		{
			m_buttonsImages[i]->draw(screen, width, height);
		}
		else
		{
			if(m_actualLeaderboard != 0)
			{
				m_buttonsImages[0]->draw(screen, width, height);
			}
			if(m_actualLeaderboard < m_leaderboards.size() - 1)
			{
				m_buttonsImages[1]->draw(screen, width, height);
			}
		}
	}

	//Si on est dans un écran de type SCORE, on affiche les scores
	if(m_type == SCORE)
	{
		SDL_Rect position;
		SDL_Surface * text;
		std::stringstream string1, string2;
		SDL_Color color = {255, 0, 0};
		SDL_Color color2 = {255, 255, 0};

		//On affiche chaque Leaderboard sur un écran et on ajoute des flèches pour naviguer entre les scores
		string1.str(std::string());
		string2.str(std::string());
		string1 << "Island " << m_leaderboards[m_actualLeaderboard]->island;
		string2 << "Level " << m_leaderboards[m_actualLeaderboard]->level;
			
		position.x = 400;
		position.y = 120;
		text = TTF_RenderText_Blended(m_font, string1.str().c_str(),  color);
		SDL_BlitSurface(text, NULL, screen, &position);
		position.y = 200;
		text = TTF_RenderText_Blended(m_font, string2.str().c_str(),  color);
		SDL_BlitSurface(text, NULL, screen, &position);
			
		std::multimap< int, std::string >::const_iterator it = m_leaderboards[m_actualLeaderboard]->m_scores.end();
		int posY = 0;
		do
		{
			--it;

			string1.str(std::string());  
			string1 << it->second << "                " << it->first;
				
			position.x = 240;
			position.y = 310 + posY * 80;
			text = TTF_RenderText_Blended(m_font, string1.str().c_str(),  color2);
			SDL_BlitSurface(text, NULL, screen, &position);

			posY++;
		}
		while(it != m_leaderboards[m_actualLeaderboard]->m_scores.begin());

		SDL_FreeSurface(text);
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
			//std::cout<<"UP arrow"<<std::endl;
			break;
		default:
			break;
	}
}



