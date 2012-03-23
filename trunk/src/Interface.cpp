#include "Interface.hpp"
#include "GameEngine.hpp"
#include "ActualGame.hpp"

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
, m_page(0)
, m_name("")
, m_previousScreen(type)
, m_nameRegistered (false)
, m_leaderboardUpdated(false)
, m_levelUnlockedSaved(false)
{
	m_font =  TTF_OpenFont("../fonts/GretoonHighlight.ttf", 36);
	m_littleFont =  TTF_OpenFont("../fonts/GretoonHighlight.ttf", 30);
	m_name.str(std::string());
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
			m_backgroundImages.push_back(new Sprite("../img/screens/menu_background.jpg", 0, 0));
			//Buttons Images
			Sprite * play = new Sprite("../img/screens/play_button_unselected.png", 425, 250);
			play->addImage("../img/screens/play_button_selected.png");
			Sprite * score = new Sprite("../img/screens/scores_button_unselected.png", 390, 333);
			score->addImage("../img/screens/scores_button_selected.png");
			Sprite * instruc = new Sprite("../img/screens/instructions_button_unselected.png", 315, 407);
			instruc->addImage("../img/screens/instructions_button_selected.png");
			/*Sprite * option = new Sprite("../img/screens/options_button_unselected.png", 390, 474);
			option->addImage("../img/screens/options_button_selected.png");*/
			Sprite * quit = new Sprite("../img/screens/quit_button_unselected.png", 425, 540);
			quit->addImage("../img/screens/quit_button_selected.png");

			m_buttonsImages.push_back(play);
			m_buttonsImages.push_back(score);
			m_buttonsImages.push_back(instruc);
			//m_buttonsImages.push_back(option);
			m_buttonsImages.push_back(quit);
			break;
		}
		case PAUSE :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/pause_screen.jpg", 0, 0));
			//Buttons Images
			Sprite * bcontinue = new Sprite("../img/screens/continue_button_unselected.png", 350, 250);
			bcontinue->addImage("../img/screens/continue_button_selected.png");
			Sprite * instruc = new Sprite("../img/screens/instructions_button_unselected.png", 315, 320);
			instruc->addImage("../img/screens/instructions_button_selected.png");
			Sprite * title = new Sprite("../img/screens/quit_button_unselected.png", 425, 400);
			title->addImage("../img/screens/quit_button_selected.png");

			m_buttonsImages.push_back(bcontinue);
			m_buttonsImages.push_back(instruc);
			m_buttonsImages.push_back(title);
			break;
		}
		case SCORE :
		{
			//Récupération des informations du XML
			loadXML(0, 0);
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/leaderboard.jpg", 0, 0));
			//Buttons Images
			Sprite * leftArrow1 = new Sprite("../img/screens/leftArrow_unselected.png", 300, 160);
			leftArrow1->addImage("../img/screens/leftArrow_selected.png");
			Sprite * rightArrow1 = new Sprite("../img/screens/rightArrow_unselected.png", 650, 160);
			rightArrow1->addImage("../img/screens/rightArrow_selected.png");
			Sprite * returnB = new Sprite("../img/screens/return_button_unselected.png", 25, 648);
			returnB->addImage("../img/screens/return_button_selected.png");
			
			m_buttonsImages.push_back(leftArrow1);
			m_buttonsImages.push_back(rightArrow1);
			m_buttonsImages.push_back(returnB);

			break;
		}
		case HELP :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/instruction_screen.jpg", 0, 0));
			//Button images
			Sprite * returnB = new Sprite("../img/screens/return_button_unselected.png", 5, 655);
			returnB->addImage("../img/screens/return_button_selected.png");
			m_buttonsImages.push_back(returnB);
			break;
		}
		case ISLAND :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/level_select_background.jpg", 0, 0));
			break;
		}
		case WORLD :
		{
			//Récupération des informations du XML
			loadXML(0, 0);
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/level_select_background.jpg", 0, 0));
			//Buttons Images
			Sprite * isle1 = new Sprite("../img/screens/paradisio_unselected.png", 100, 200);
			isle1->addImage("../img/screens/paradisio_selected.png");
			Sprite * isle2 = new Sprite("../img/screens/dolfina_unselected.png", 500, 200);
			isle2->addImage("../img/screens/dolfina_selected.png");
			isle2->addImage("../img/screens/dolfina_locked.png");
			Sprite * isle3 = new Sprite("../img/screens/chicken_island_unselected.png", 300, 400);
			isle3->addImage("../img/screens/chicken_island_selected.png");
			isle3->addImage("../img/screens/chicken_island_locked.png");
			
			Sprite * returnB = new Sprite("../img/screens/return_button_unselected.png", 25, 648);
			returnB->addImage("../img/screens/return_button_selected.png");

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
			m_buttonsImages.push_back(returnB);
			break;
		}
		case OPTIONS :
		{
			break;
		}
		case GAMEOVER :
		{
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/game_over.png", 0, 0));
			//Button images
			Sprite * returnb = new Sprite("../img/screens/return_button_unselected.png", 25, 648);
			returnb->addImage("../img/screens/return_button_selected.png");
			/*Sprite * retry = new Sprite("../img/screens/retry_button_unselected.png", 850, 648, 160, 100);
			retry->addImage("../img/screens/retry_button_selected.png");*/
			
			m_buttonsImages.push_back(returnb);
			//m_buttonsImages.push_back(retry);
			break;
		}
		case ENDGAME :
		{
			loadXML(1, 1);
			//Background Images
			m_backgroundImages.push_back(new Sprite("../img/screens/score_level.png", 0, 0));
			//Button Images
			//Buttons Images
			Sprite * leftArrow1 = new Sprite("../img/screens/leftArrow_unselected.png", 300, 160);
			leftArrow1->addImage("../img/screens/leftArrow_selected.png");
			Sprite * rightArrow1 = new Sprite("../img/screens/rightArrow_unselected.png", 650, 160);
			rightArrow1->addImage("../img/screens/rightArrow_selected.png");
			Sprite * returnB = new Sprite("../img/screens/return_button_unselected.png", 25, 648);
			returnB->addImage("../img/screens/return_button_selected.png");

			m_buttonsImages.push_back(leftArrow1);
			m_buttonsImages.push_back(rightArrow1);
			m_buttonsImages.push_back(returnB);
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
	m_name.str(std::string());

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
		std::cout << "Interface.cpp : après TiXml " << std::endl;
		TiXmlElement * xmlScores = hdl.FirstChildElement().Element();
		TiXmlElement * xmlLevel = hdl.FirstChildElement().FirstChildElement().Element();
	
		//Récupère uniquement le nombre de niveaux débloqués
		if(xmlScores)
		{
			m_nbAvailableLevels = atoi(xmlScores->Attribute("nbLevel") );
			m_nbAvailableIslands = atoi(xmlScores->Attribute("nbIsland") );
		}
		else
		{
			std::cerr<< "Problemes a la recuperation du nb d'iles et de niveaux debloques" <<std::endl;
			m_nbAvailableLevels = 1;
			m_nbAvailableIslands = 1;
		}
	
		//Récupère tous les scores : UTILISE APRES L'ECRAN TITLE
		if(level == 0 && island == 0) 
		{
			Leaderboard * l;
			while(xmlLevel)
			{
				int i = atoi(xmlLevel->Attribute("island") );
				int lvl = atoi(xmlLevel->Attribute("level") );

				if( i <= m_nbAvailableIslands && lvl <= m_nbAvailableLevels)
				{
					l = new Leaderboard;

					l->island = i;
					l->level = lvl;

					TiXmlElement *xmlScore1 = xmlLevel->FirstChildElement();
					while (xmlScore1)
					{
						l->m_scores.insert(std::make_pair(atoi(xmlScore1->Attribute("value") ), xmlScore1->Attribute("player") ) );
						xmlScore1 = xmlScore1->NextSiblingElement();
					}

					m_leaderboards.push_back(l);
				}
				xmlLevel = xmlLevel->NextSiblingElement();
			}
		}
		//Récupère les scores du niveau "level" de l'ile "island" : UTILISE APRES L'ECRAN ISLAND ou A L'ECRAN ENDGAME
		else if(level > 0 && island > 0)
		{
			Leaderboard * l;
			while(xmlLevel)
			{
				int i = atoi(xmlLevel->Attribute("island") );
				int lvl = atoi(xmlLevel->Attribute("level") );
				if( i == island && lvl == level)
				{
					l = new Leaderboard;

					l->island = atoi(xmlLevel->Attribute("island"));
					l->level = atoi(xmlLevel->Attribute("level"));

					TiXmlElement *xmlScore1 = xmlLevel->FirstChildElement();
					while (xmlScore1)
					{
						l->m_scores.insert(std::make_pair(atoi(xmlScore1->Attribute("value") ), xmlScore1->Attribute("player") ) );
						xmlScore1 = xmlScore1->NextSiblingElement();
					}

					m_leaderboards.push_back(l);
				}
				xmlLevel = xmlLevel->NextSiblingElement();
			}
		}
	}
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
			if(m_clic == 1 &&  !(m_type == WORLD && i >= m_nbAvailableIslands) )
			{
				buttonChosen = i;
				m_clic = -1;
			}
			else if(m_clic == 1 &&  m_type == WORLD && i == m_buttonsImages.size() - 1 )
			{
				buttonChosen = i;
				m_clic = -1;
			}

			//Si on est dans l'écran WORLD, on ne change pas l'image des îles non débloquées
			if( ! (m_type == WORLD && i >= m_nbAvailableIslands) || (m_type == WORLD && i == m_buttonsImages.size() - 1) )
			{
				m_buttonsImages[i]->changeImageManually(1);
			}
		}
		else
		{
			//Si on est dans l'écran WORLD, on ne change pas l'image des îles non débloquées
			if(m_type == WORLD && i >= m_nbAvailableIslands && (i != m_buttonsImages.size() - 1) ) 
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
						/*gameEngine->changeScreen(m_type, OPTIONS, -1, -1);
						break;
					case 4:*/
						gameEngine->quit();
						break;
					default:
						break;
				}
				break;
			}
			case PAUSE :
			{
				switch(buttonChosen)
				{
					case 0:
						gameEngine->changeScreen(m_type, GAME, -1, -1);
						break;
					case 1:
						gameEngine->changeScreen(m_type, HELP, 0, 0);
						break;
					case 2:
						gameEngine->changeScreen(m_type, TITLE, -1, -1);
						break;
				}
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
				else if(buttonChosen == m_buttonsImages.size() - 1)
				{
					gameEngine->changeScreen(m_type, TITLE, -1, -1);
				}

				break;
			}
			case HELP :
			{
				if(buttonChosen == m_buttonsImages.size() - 1)
				{
					gameEngine->changeScreen(m_type, m_previousScreen, -1, -1);
				}
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
				else if(buttonChosen == m_buttonsImages.size() - 1)
				{
					gameEngine->changeScreen(m_type, TITLE, -1, -1);
				}
				break;
			}
			case OPTIONS:
				break;
			case GAMEOVER:
				if(buttonChosen == 0)
				{
					gameEngine->changeScreen(m_type, TITLE, -1, -1);
				}
				/*else if(buttonChosen == 1)
				{
					gameEngine->changeScreen(m_type, GAME, -1, -1);
				}*/
				break;
			case ENDGAME :
			{
				if(buttonChosen == 0 && m_page)
				{
					m_page = false;
				}
				else if(buttonChosen == 1 && !m_page)
				{
					m_page = true;
				}

				if(buttonChosen == m_buttonsImages.size() - 1)
				{
					gameEngine->changeScreen(m_type, TITLE, -1, -1);
				}
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

	//Enregistrement du score du joueur
	if(m_type == ENDGAME && m_nameRegistered && !m_leaderboardUpdated)
	{
		std::multimap< int, std::string >::iterator id = getScoreIdMinTotalScore();
		Leaderboard * l = m_leaderboards[m_actualLeaderboard];
		l->m_scores.insert(id, make_pair(m_allScores.at("Total points : "), m_name.str()) );
		l->m_scores.erase(id);
		m_leaderboardUpdated = true;

		saveLeaderboard();
	}

	if(m_type == ENDGAME && !m_levelUnlockedSaved)
	{
		if(m_leaderboards[m_actualLeaderboard]->island + 1 > m_nbAvailableIslands)
		{
			saveLevelsUnlocked();
		}
		m_levelUnlockedSaved = true;
	}
}

void Interface::saveLeaderboard()
{
	//Ouvre le XML save.xml
	//Cherche si le leaderboard pour l'ile "m_leaderboards[m_actualLeaderboard]->island" et le niveau "m_leaderboards[m_actualLeaderboard]->level" existe déjà
		//si c'est le cas on la remplace
		//sinon on ajoute une nouvelle balise <leaderboard> avec les score dedans	
	TiXmlDocument doc("../levels/save.xml");
	int score;
	std::string player;
	Leaderboard l;
	m_name.str(std::string());

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
		std::cout << "Interface.cpp : après TiXml " << std::endl;
		TiXmlElement * xmlScores = hdl.FirstChildElement().Element();
		TiXmlElement * xmlLevel = hdl.FirstChildElement().FirstChildElement().Element();

		while(xmlLevel)
		{
			int i = atoi(xmlLevel->Attribute("island") );
			int lvl = atoi(xmlLevel->Attribute("level") );
			if( i == m_leaderboards[0]->island && lvl == m_leaderboards[0]->level)
			{
				TiXmlElement *xmlScore1 = xmlLevel->FirstChildElement();
				std::multimap<int, std::string>::const_iterator it = m_leaderboards[0]->m_scores.begin();
				while (xmlScore1 || it != m_leaderboards[0]->m_scores.end ())
				{
					xmlLevel->RemoveChild(xmlScore1);
					TiXmlElement newScore("score");
					newScore.SetAttribute("player", (*it).second.c_str());
					newScore.SetAttribute("value", (*it).first);
					xmlLevel->InsertEndChild(newScore);

					++it;
					xmlScore1 = xmlScore1->NextSiblingElement();
				}
			}
			xmlLevel = xmlLevel->NextSiblingElement();
		}
		doc.SaveFile("../levels/save.xml");
	}
}

void Interface::saveLevelsUnlocked()
{
	//Ouvre le XML save.xml
	//Remplace les attributs de la balise score par 
	 // nbIsland = m_leaderboards[m_actualLeaderboard]->island + 1
	 // nbLevel = m_leaderboards[m_actualLeaderboard]->level
	
	TiXmlDocument doc("../levels/save.xml");
	int score;
	std::string player;
	Leaderboard l;
	m_name.str(std::string());

	if(!doc.LoadFile())
	{
		std::cerr << "erreur lors du chargement du XML des scores" << std::endl;
		std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
		exit(0);
	}
	else
	{
		if( m_leaderboards[m_actualLeaderboard]->island + 1 <= 3)
		{
			//permet de sécuriser le pacours des noeud (dans le cas ou l'un des noeuds n'existerait pas)
			TiXmlHandle hdl(&doc);
			std::cout << "Interface.cpp : après TiXml " << std::endl;
			TiXmlElement * xmlScores = hdl.FirstChildElement().Element();

			xmlScores->SetAttribute("nbIsland", m_leaderboards[m_actualLeaderboard]->island + 1);
			doc.SaveFile("../levels/save.xml");
		}
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
		if(m_type != SCORE && m_type != ENDGAME)
		{
			m_buttonsImages[i]->draw(screen, width, height);
		}
		else if(m_type == ENDGAME)
		{
			if(m_page)
			{
				m_buttonsImages[0]->draw(screen, width, height);
			}
			else
			{
				m_buttonsImages[1]->draw(screen, width, height);
			}
			
			m_buttonsImages[2]->draw(screen, width, height);
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
			//Bouton Return
			if( i  == m_buttonsImages.size() - 1)
			{
				m_buttonsImages[i]->draw(screen, width, height);
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
			string1 << it->second << " : " << it->first;
				
			position.x = 350;
			position.y = 310 + posY * 80;
			text = TTF_RenderText_Blended(m_font, string1.str().c_str(),  color2);
			SDL_BlitSurface(text, NULL, screen, &position);

			posY++;
		}
		while(it != m_leaderboards[m_actualLeaderboard]->m_scores.begin());

		SDL_FreeSurface(text);
	}
	else if(m_type == ENDGAME)
	{
		//Page du leaderboard (droite)
		if(m_page)
		{
			SDL_Rect position;
			SDL_Surface * text;
			std::stringstream string1, string2;
			SDL_Color color = {255, 0, 0};
			SDL_Color color2 = {232, 175, 20};

			//On affiche chaque Leaderboard sur un écran et on ajoute des flèches pour naviguer entre les scores
			string1.str(std::string());
			string1 << "Enter your name : ";

			int scoreMin = getScoreMin();
			if(!m_nameRegistered && m_allScores.at("Total points : ") > scoreMin)
			{
				position.x = 400;
				position.y = 150;
				text = TTF_RenderText_Blended(m_font, string1.str().c_str(),  color);
				SDL_BlitSurface(text, NULL, screen, &position);
				position.y = 220;
				text = TTF_RenderText_Blended(m_font, m_name.str().c_str(),  color);
				SDL_BlitSurface(text, NULL, screen, &position);
			}
			
			std::multimap< int, std::string >::const_iterator it = m_leaderboards[m_actualLeaderboard]->m_scores.end();
			int posY = 0;
			do
			{
				--it;

				string1.str(std::string());  
				string1 << it->second << " : " << it->first;
				
				position.x = 350;
				position.y = 300 + posY * 80;
				text = TTF_RenderText_Blended(m_font, string1.str().c_str(),  color2);
				SDL_BlitSurface(text, NULL, screen, &position);

				posY++;
			}
			while(it != m_leaderboards[m_actualLeaderboard]->m_scores.begin());

			SDL_FreeSurface(text);
		}
		//Page gauche, détails des scores
		else
		{
			SDL_Rect position;
			SDL_Surface * text;
			std::stringstream string1, string2;
			SDL_Color color = {255, 0, 0};
			SDL_Color color2 = {232, 175, 20};

			//On affiche chaque Leaderboard sur un écran et on ajoute des flèches pour naviguer entre les scores
			string1.str(std::string());
			string1 << "Score Detail ";
			
			position.x = 290;
			position.y = 155;
			text = TTF_RenderText_Blended(m_font, string1.str().c_str(),  color);
			SDL_BlitSurface(text, NULL, screen, &position);

			int posY = 0;
			std::map< std::string, int >::const_iterator it = m_allScores.begin();
			for(; it != m_allScores.end(); ++it)
			{
				position.x = 240;
				position.y = 300 + posY * 80;

				string1.str(std::string());  
				string1 << it->first << it->second;
				
				position.x = 240;
				position.y = 300 + posY * 70;
				text = TTF_RenderText_Blended(m_littleFont, string1.str().c_str(),  color2);
				SDL_BlitSurface(text, NULL, screen, &position);

				posY++;
			}
			
			SDL_FreeSurface(text);
		}
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
	if(m_type == ENDGAME && m_page)
	{
		switch(event->keysym.sym)
		{
			case SDLK_BACKSPACE :
				if(m_name.str().length() > 0 && !m_nameRegistered)
				{
					std::string s = m_name.str();
					s.erase(m_name.str().size() - 1);
					m_name.str("");
					m_name << s;
				}
				break;
			case SDLK_RETURN:
				m_nameRegistered = true;
				break;
			default:
				if(m_name.str().length() < 8 && !m_nameRegistered)
					m_name << (char) (event->keysym.sym);
				break;
		}
	}
}

void Interface::setActualGameForScores(ActualGame * ag)
{
	m_allScores.insert(std::make_pair("Obstacle hit : ", ag->getObstacleScore()));
	m_allScores.insert(std::make_pair("StarDust points : ",ag->getStarDustScore()));
	m_allScores.insert(std::make_pair("Passangers points : ",ag->getPassengerScore()));
	m_allScores.insert(std::make_pair("Satisfaction points : ",ag->getSatisfactionScore()));
	m_allScores.insert(std::make_pair("Time points : ",ag->getTimeScore()));
	m_allScores.insert(std::make_pair("Total points : ",ag->getTotalScore()));
}

int Interface::getScoreMin()
{
	Leaderboard * l = m_leaderboards[m_actualLeaderboard];
	int scoreMin = INFINITE;
	std::multimap< int, std::string >::iterator it;
	for(it = l->m_scores.begin(); it != l->m_scores.end(); ++it)
	{
		if((*it).first < scoreMin)
		{
			scoreMin = (*it).first;
		}
	}

	return scoreMin;
}

std::multimap< int, std::string >::iterator Interface::getScoreIdMinTotalScore()
{
	Leaderboard * l = m_leaderboards[m_actualLeaderboard];
	int scoreMin = m_allScores.at("Total points : ");
	std::multimap< int, std::string >::iterator id;

	std::multimap< int, std::string >::iterator it;
	for(it = l->m_scores.begin(); it != l->m_scores.end(); ++it)
	{
		if((*it).first < scoreMin)
		{
			scoreMin = (*it).first;
			id = it;
		}
	}

	return id;
}

