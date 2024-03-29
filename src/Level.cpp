#include "Level.hpp"
#include "ActualGame.hpp"
#include "HelpTip.hpp"
/*Level Constructor */
Level::Level(b2World * world, unsigned int level, unsigned int island) 
: m_world (world)
, m_departureTime(NULL)
, m_position(NULL)
, m_islandNum(island)
, m_levelNum(level)
, m_groundImage(NULL)
{
	loadAndBuild();
	buildBlocks();
}

Level::~Level() 
{
	for(unsigned int i = 0; i < m_blocks.size(); ++i)
	{
		delete m_blocks[i];
	}

	for(unsigned int i = 0; i < m_backgroundImages.size(); ++i)
	{
		delete m_backgroundImages[i];
	}

	delete m_position;
	
	std::cout<<"Destruction level"<<std::endl;
}

Block * Level::getBlock(unsigned int i)
{
	if(i < m_blocks.size() )
	{
		return m_blocks.at(i);
	}
	return NULL;

}

/*
 * R�initialise les valeurs des PhysicalObjects apr�s un smooth pour coller au framerate
 */
void Level::clearAllSmoothAngleAndPosition()
{

}


/*
 * Move the level horizontally
 */
void Level::scrollLevel(const int & x)
{
	//Blocks
	for(unsigned int i = 0; i < m_blocks.size(); ++i)
	{
		m_blocks[i]->scroll(x);
	}

	//Backgrounds
	for(unsigned int i = 1; i < m_backgroundImages.size(); ++i)
	{
		int newX = (int) ( x + ( double(x) * i * 0.25) );
		m_backgroundImages[i]->setPositionX(m_backgroundImages[i]->getPositionX() + newX);
	}
}

/*
 * Load and build the level n�lvl of the island n�isle
 */
void Level::loadAndBuild()
{
	TiXmlDocument doc("../levels/levels.xml");
	int sizeX, posY = 0,speed = -1;
	std::string path;
	Block * vBlock;
	Station * vStation;
	int numBlock = 0;

	if(!doc.LoadFile())
	{
		std::cerr << "erreur lors du chargement du XML block" << std::endl;
		std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
		exit(0);
	}
	else
	{
		//permet de s�curiser le pacours des noeud (dans le cas ou l'un des noeuds n'existerait pas)
		TiXmlHandle hdl(&doc);
		std::cerr << "Level.cpp : apr�s TiXmlHandle hdl(&doc) " << std::endl;
		TiXmlElement *island = hdl.FirstChildElement().FirstChildElement().Element();
		TiXmlElement *contenuBlock = hdl.FirstChildElement().FirstChildElement().FirstChildElement().FirstChildElement().FirstChildElement().Element();
		
		while (island)
		{
			//si l'id du level correspond � m_islandNum, on entre dans le if
			if(atoi(island->Attribute("id")) == m_islandNum)
			{
				TiXmlElement *level = island->FirstChildElement();
				//on entre dans la balise island et on check toutes les balises level
				while (level)
				{
					//si l'id du level correspond � m_levelNum, on entre dans le if pour pouvoir checker toutes les balises du level choisi
					if(atoi(level->Attribute("id")) == m_levelNum)
					{
						TiXmlElement *contenuLevel = level->FirstChildElement();
						while (contenuLevel)
						{
							//si la balise dans level correspond a la balise block on entre dans ce if
							if (strcmp(contenuLevel->Value(),"sprite")==0)
							{
								path = contenuLevel->Attribute("img");

								posY = 0;
								if(contenuLevel->Attribute("posY") )
								{
									posY = atoi(contenuLevel->Attribute("posY") );
								}
						
								if( strcmp(contenuLevel->Attribute("type"),"ground") == 0 )
								{
									loadGroundImage(path);
								}
								else if( strcmp(contenuLevel->Attribute("type"),"background") == 0 )
								{
									if(contenuLevel->Attribute("img2") )
									{
										addBackgroundImage(path, posY, contenuLevel->Attribute("img2"));
									}
									else
									{
										addBackgroundImage(path, posY);
									}
								}
							}
							//si la balise dans level correspond a la balise block on entre dans ce if
							if (strcmp(contenuLevel->Value(),"block")==0)
							{
								//on est dans une balise block !
								sizeX = atoi(contenuLevel->Attribute("size") );
								if(contenuLevel->Attribute("speed"))
								{
									speed = atoi(contenuLevel->Attribute("speed") );
								}

								vBlock = new Block(sizeX, numBlock, this, speed);
								numBlock++;

								if (strcmp(contenuLevel->Attribute("type"),"GROUND")==0)
								{
									vBlock->setBlockType(GROUND); // smartpointer

									//variable element qui check les balises contenu dans block
									TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
									while (contenuBlock)
									{
										if (strcmp(contenuBlock->Value(),"obstacle")==0)
										{
											if (strcmp(contenuBlock->Attribute("type"),"animal") == 0)
											{
												vBlock->setAnimal(contenuBlock->Attribute("nom"), atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
											}
											else if (strcmp(contenuBlock->Attribute("type"),"bonus") == 0)
											{
												if (strcmp(contenuBlock->Attribute("nom"),"etoile") == 0)
												{
													vBlock->setBonus(STAR_DUST, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
												else if (strcmp(contenuBlock->Attribute("nom"),"accelerateur") == 0)
												{
													vBlock->setBonus(ACCELERATOR, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
											}
										}else if (strcmp(contenuBlock->Value(),"point")==0)
										{
											vBlock->addPoint(atoi(contenuBlock->Attribute("x")), atoi(contenuBlock->Attribute("y")));
										}else if (strcmp(contenuBlock->Value(),"infobulle")==0)
										{
											if (strcmp(contenuBlock->Attribute("type"),"aide") == 0)
											{
												/*HelpTip * infoAide = new HelpTip();
												infoAide->setNumBlock(numBlock);
												infoAide->setDeclenche(contenuLevel->Attribute("declenche"));
												infoAide->setPosition(contenuLevel->Attribute("posX"));
												TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
												while (contenuBulle){
													if (strcmp(contenuBulle->Value(),"sprite")==0){
														infoAide->setSprite(contenuBulle->Attribute("img"));
													}
													contenuBulle = contenuBulle->NextSiblingElement();
												}*/
											}
										}
										contenuBlock = contenuBlock->NextSiblingElement();
									}// fin du while dans le block
								}
								else if (strcmp(contenuLevel->Attribute("type"),"PRECIPICE")==0)
								{
									vBlock->setBlockType(PRECIPICE);
									
									//variable element qui check les balises contenu dans block
									TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
									while (contenuBlock)
									{
										if (strcmp(contenuBlock->Value(),"obstacle")==0)
										{
											if (strcmp(contenuBlock->Attribute("type"),"bonus") == 0)
											{
												if (strcmp(contenuBlock->Attribute("nom"),"STAR_DUST") == 0)
												{
													vBlock->setBonus(STAR_DUST, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
												else if (strcmp(contenuBlock->Attribute("nom"),"ACCELERATOR") == 0)
												{
													vBlock->setBonus(ACCELERATOR, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
											}else if (strcmp(contenuBlock->Value(),"infobulle")==0)
											{
												if (strcmp(contenuBlock->Attribute("type"),"aide") == 0)
												{
													/*HelpTip * infoAide = new HelpTip();
													infoAide->setNumBlock(numBlock);
													infoAide->setDeclenche(contenuLevel->Attribute("declenche"));
													infoAide->setPosition(contenuLevel->Attribute("posX"));
													TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
													while (contenuBulle){
														if (strcmp(contenuBulle->Value(),"sprite")==0){
															infoAide->setSprite(contenuBulle->Attribute("img"));
														}
														contenuBulle = contenuBulle->NextSiblingElement();
													}*/
												}
											}
										}
										contenuBlock = contenuBlock->NextSiblingElement();
									}// fin du while dans le block
								}
								else if (strcmp(contenuLevel->Attribute("type"),"TUNNEL")==0)
								{
									vBlock->setBlockType(TUNNEL);
									
									//variable element qui check les balises contenu dans block
									TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
									while (contenuBlock)
									{
										if (strcmp(contenuBlock->Value(),"obstacle")==0)
										{
											if (strcmp(contenuBlock->Attribute("type"),"animal") == 0)
											{
												vBlock->setAnimal(contenuBlock->Attribute("nom"), atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
											}
											else if (strcmp(contenuBlock->Attribute("type"),"bonus") == 0)
											{
												if (strcmp(contenuBlock->Attribute("nom"),"STAR_DUST") == 0)
												{
													vBlock->setBonus(STAR_DUST, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
												else if (strcmp(contenuBlock->Attribute("nom"),"ACCELERATOR") == 0)
												{
													vBlock->setBonus(ACCELERATOR, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posY")));
												}
											}
										}else if (strcmp(contenuBlock->Value(),"infobulle")==0)
										{
											if (strcmp(contenuBlock->Attribute("type"),"aide") == 0)
											{
												/*HelpTip * infoAide = new HelpTip();
												infoAide->setNumBlock(numBlock);
												infoAide->setDeclenche(contenuLevel->Attribute("declenche"));
												infoAide->setPosition(contenuLevel->Attribute("posX"));
												TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
												while (contenuBulle){
													if (strcmp(contenuBulle->Value(),"sprite")==0){
														infoAide->setSprite(contenuBulle->Attribute("img"));
													}
													contenuBulle = contenuBulle->NextSiblingElement();
												}*/
											}
										}
										contenuBlock = contenuBlock->NextSiblingElement();
									}// fin du while dans le block
								}
								else if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_UP")==0 || strcmp(contenuLevel->Attribute("type"),"JUNCTION_DOWN")==0)
								{
									if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_UP")==0)
									{
										vBlock->setBlockType(JUNCTION_UP);
									}
									else if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_DOWN")==0)
									{
										vBlock->setBlockType(JUNCTION_DOWN);
									}
								}
								m_blocks.push_back(vBlock);
							}
							else if (strcmp(contenuLevel->Value(),"station")==0)
							{
								//on est dans la balise station / gare
								sizeX = atoi(contenuLevel->Attribute("size"));

								vStation = new Station(sizeX, numBlock, this); // smartpointer
								numBlock++;

								//variable element qui check les balises contenu dans block
								TiXmlElement *contenuStation = contenuLevel->FirstChildElement();
								while (contenuStation)
								{
									if (strcmp(contenuStation->Value(),"option")==0)
									{
										vStation->setTime(atoi(contenuStation->Attribute("hours")), atoi(contenuStation->Attribute("minutes")));
										vStation->setLeaving(atoi(contenuStation->Attribute("leaving")));
										vStation->setEnter(atoi(contenuStation->Attribute("entering")));
									}else if (strcmp(contenuStation->Value(),"infobulle")==0)
										{
											if (strcmp(contenuStation->Attribute("type"),"aide") == 0)
											{
												/*HelpTip * infoAide = new HelpTip();
												infoAide->setNumBlock(numBlock);
												infoAide->setDeclenche(contenuLevel->Attribute("declenche"));
												infoAide->setPosition(contenuLevel->Attribute("posX"));
												TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
												while (contenuBulle){
													if (strcmp(contenuBulle->Value(),"sprite")==0){
														infoAide->setSprite(contenuBulle->Attribute("img"));
													}
													contenuBulle = contenuBulle->NextSiblingElement();
												}*/
											}
										}
									contenuStation = contenuStation->NextSiblingElement();
								}
								m_blocks.push_back(vStation);
								
							}
							else if (strcmp(contenuLevel->Value(),"infobulle")==0)
							{
								//on est dans la balise infobulle
								if (strcmp(contenuLevel->Attribute("type"),"standard") == 0)
								{
									/*StandardTip * infoStandard = new StandardTip();
									infoStandard->setAction(contenuLevel->Attribute("action"));
									infoStandard->setDeclenche(contenuLevel->Attribute("declenche"));
									TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
									while (contenuBulle){
										if (strcmp(contenuBulle->Value(),"sprite")==0){
											infoStandard->setSprite(contenuBulle->Attribute("img"));
										}
										contenuBulle = contenuBulle->NextSiblingElement();
									}*/
								}
								/*else if (strcmp(contenuBlock->Attribute("type"),"aide") == 0)
								{
									HelpTip * infoAide = new HelpTip();
									infoAide->setNumBlock(contenuLevel->Attribute("numBlock"));
									infoAide->setDeclenche(contenuLevel->Attribute("declenche"));
									TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
									while (contenuBulle){
										if (strcmp(contenuBulle->Value(),"sprite")==0){
											infoAide->setSprite(contenuBulle->Attribute("img"));
										}
										contenuBulle = contenuBulle->NextSiblingElement();
									}
								}
								}*/
							}

							//}
							contenuLevel = contenuLevel->NextSiblingElement(); // iteration 
			
						} //fin while contenuLevel

					} //fin if level
					level = level->NextSiblingElement(); // iteration 
				} //fin while level
			} //fin if island
			island = island->NextSiblingElement(); // iteration 
		} //fin while island
	}
}

//Ajoute une image de fond
void Level::addBackgroundImage(const std::string & path, const int & posY, const std::string & path2)
{
	Sprite * backg = new Sprite(path.c_str(), 0, posY);
	if(path2 != "")
	{
		backg->addImage(path2.c_str());
	}
	if(backg != NULL)
	{
		m_backgroundImages.push_back(backg);
	}
}

//Cr�e un Sprite pour m_ground
void Level::loadGroundImage(const std::string & path)
{
	m_groundImage = IMG_Load(path.c_str());
}

//Construit tous les blocs
void Level::buildBlocks()
{
	int posX = 0;
	for(unsigned int i = 0; i < m_blocks.size(); ++i)
	{
		m_blocks[i]->setPosX(posX);
		posX += m_blocks[i]->build(m_world);
	}
}

void Level::render(SDL_Surface * screen, int w, int h, ActualGame * game, b2World * world)

{
	drawBackgrounds(screen,  w,  h);

	drawBlocks(screen, w, h, game, world);

}

/*
 * Level dessine tous les blocs du vector
 */
void Level::drawBlocks(SDL_Surface * screen, int w, int h, ActualGame * game, b2World * world)
{
	for (unsigned int i=0; i<m_blocks.size(); i++) 
	{
		if(m_blocks.at(i)->getType() != TUNNEL)
			m_blocks.at(i)->draw (screen, w, h, game, world);
	}
}

/*
 * Level dessine tous les blocs du vector
 */
void Level::drawTunnels(SDL_Surface * screen, int w, int h, ActualGame * game, b2World * world)
{
	for (unsigned int i=0; i<m_blocks.size(); i++) 
	{
		if(m_blocks.at(i)->getType() == TUNNEL)
			m_blocks.at(i)->draw (screen, w, h, game, world);
	}
}


/*
 * Level dessine les fonds d'�cran
 */
void Level::drawBackgrounds(SDL_Surface * screen, int w, int h)
{
	for(int i = 0; i < m_backgroundImages.size(); ++i)
	{
		m_backgroundImages[i]->draw(screen, w, h);
		int image2ToDraw = 0;
		//Si c'est pas l'image de fond
		if( i > 0 )
		{
			int leftPosX = m_backgroundImages[i]->getPositionX();
			int rightPosX = m_backgroundImages[i]->getPositionX() + m_backgroundImages[i]->getSizeX();
			image2ToDraw = m_backgroundImages[i]->getNbFrames() - 1;

			if(leftPosX < 0)
			{
				int step = leftPosX + m_backgroundImages[i]->getSizeX();
				m_backgroundImages[i]->drawAtPosition(screen, step, m_backgroundImages[i]->getPositionY(), w, h, image2ToDraw);

				if(leftPosX < -WINDOWS_W)
				{
					m_backgroundImages[i]->setPositionX(WINDOWS_W);
				}
			}
			
			if( rightPosX > WINDOWS_W)
			{
				int step = rightPosX - m_backgroundImages[i]->getSizeX(); 
				m_backgroundImages[i]->drawAtPosition(screen, step - m_backgroundImages[i]->getSizeX(), m_backgroundImages[i]->getPositionY(), w, h, image2ToDraw);
				
				if(leftPosX > WINDOWS_W)
				{
					m_backgroundImages[i]->setPositionX(-WINDOWS_W);
				}
			}
		}
	}
}
