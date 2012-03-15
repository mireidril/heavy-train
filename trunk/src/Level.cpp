#include "Level.hpp"
/*Level Constructor */
Level::Level () 
{
        //All the blocks of the level
        SDL_Rect * pos = new SDL_Rect;
        pos->x = 0;
        pos->y = 0;
        //m_blocks.push_back(new Block(BlockType::JUNCTION_DOWN, 1000, pos));
        //m_blocks.push_back(new Block(JUNCTION_DOWN, 1000, pos));
	//m_blocks.push_back(new Block(JUNCTION_UP, 1000, pos));
		m_blocks.push_back(new Block(GROUND, 500, 0, 0));
        //m_departureTime = ...;
        //m_position = ...;
        m_islandNum = 0;
        m_levelNum = 0;
        //m_backgroundImages = ;
        //m_idStations= ...;

	SDL_Rect * size = new SDL_Rect;
	size->x = 1024; size->y = 768; 
	SDL_Rect * posBg = new SDL_Rect();
        posBg->x = 0; posBg->y = 0;
	SDL_Rect * posBg2 = new SDL_Rect();
        posBg2->x = 0; posBg2->y = 0;
	SDL_Rect * posBg3 = new SDL_Rect();
        posBg3->x = 0; posBg3->y = 0;
	m_backgroundImages.push_back(new Sprite("../img/niveau2/sky.png",  posBg,  size));
	m_backgroundImages.push_back(new Sprite("../img/niveau2/moutains.png", posBg2,  size));
	m_backgroundImages.push_back(new Sprite("../img/niveau2/tree.png", posBg3,  size));

}

Level::~Level() 
{
	for(unsigned int i = 0; i < m_blocks.size(); ++i)
	{
			delete m_blocks[i];
	}
}

Block * Level::getBlock(unsigned int i) {
	if(i < m_blocks.size() )
	{
		return m_blocks.at(i);
	}
	return NULL;

}

/*
 * Réinitialise les valeurs des PhysicalObjects après un smooth pour coller au framerate
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
	for(int i = 1; i < m_backgroundImages.size(); ++i)
	{
		int newX = (int) ( x + ( double(x) * i * 0.25) );
		m_backgroundImages[i]->setPositionX(m_backgroundImages[i]->getPositionX() + newX);
	}
}

/*
 * Load and build the level n°lvl of the island n°isle
 */
void Level::loadAndBuild(const int & isle, const int & lvl){
	TiXmlDocument doc("../levels/niveaux.xml");

	
	if(!doc.LoadFile()){
		std::cerr << "erreur lors du chargement du XML block" << std::endl;
		std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
		exit(0);
	}else{
		
		//permet de sécuriser le pacours des noeud (dans le cas ou l'un des noeuds n'existerait pas)
		TiXmlHandle hdl(&doc);
		std::cerr << "Level.cpp : après TiXmlHandle hdl(&doc) " << std::endl;
		TiXmlElement *island = hdl.FirstChildElement().FirstChildElement().Element();
		TiXmlElement *contenuBlock = hdl.FirstChildElement().FirstChildElement().FirstChildElement().FirstChildElement().FirstChildElement().Element();
		
		while (island){
			if(atoi(island->Attribute("id"))){
				
				TiXmlElement *level = island->FirstChildElement();
				//on entre dans la balise island et on chack toutes les balises level
				while (level){
					//si l'id du level correspond à lvl, on entre dans le if pour pouvoir checker toutes les balises du level choisi
					if(atoi(level->Attribute("id")) == lvl){
						
						TiXmlElement *contenuLevel = level->FirstChildElement();
						while (contenuLevel){
							//si la balise dans level correspond a la balise block on entre dans ce if
							if (strcmp(contenuLevel->Value(),"block")==0){
								//on est dans une balise block !
								Block * vBlock = new Block(JUNCTION_DOWN, 10, NULL,-1); // smartpointer
								vBlock->setId(atoi(contenuLevel->Attribute("num")));
								vBlock->setSizeX(atoi(contenuLevel->Attribute("size")));
								vBlock->setSpeed(atoi(contenuLevel->Attribute("speed")));

								if (strcmp(contenuLevel->Attribute("type"),"GROUND")==0){
									vBlock->setType(GROUND);

									//variable element qui check les balises contenu dans block
									TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
									while (contenuBlock){
										if (strcmp(contenuBlock->Value(),"obstacle")==0){
											if (strcmp(contenuBlock->Attribute("type"),"animal")){
												vBlock->setAnimal(contenuBlock->Attribute("nom"), atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posX")));
											}else if (strcmp(contenuBlock->Attribute("type"),"bonus")){
												if (strcmp(contenuBlock->Attribute("nom"),"etoile")){
													vBlock->setBonus(STAR_DUST, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posX")));
												}else if (strcmp(contenuBlock->Attribute("nom"),"accelerateur")){
													vBlock->setBonus(ACCELERATOR, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posX")));
												}
											}
										}else if (strcmp(contenuBlock->Value(),"point")==0){
											vBlock->addPoint(atoi(contenuBlock->Attribute("x")), atoi(contenuBlock->Attribute("y")));
										}
										contenuBlock = contenuBlock->NextSiblingElement();
									}// fin du while dans le block


								}else if (strcmp(contenuLevel->Attribute("type"),"PRECIPICE")==0){
									vBlock->setType(PRECIPICE);
								}else if (strcmp(contenuLevel->Attribute("type"),"TUNNEL")==0){
									vBlock->setType(TUNNEL);
								}else if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_UP")==0 || strcmp(contenuLevel->Attribute("type"),"JUNCTION_DOWN")==0){

									if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_UP")==0){
										vBlock->setType(JUNCTION_UP);
									}else if (strcmp(contenuLevel->Attribute("type"),"JUNCTION_DOWN")==0){
										vBlock->setType(JUNCTION_DOWN);
									}
									//variable element qui check les balises contenu dans block
									TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
									while (contenuBlock){
										if (strcmp(contenuBlock->Value(),"obstacle")==0){
											if (strcmp(contenuBlock->Attribute("type"),"animal")){
												vBlock->setAnimal(contenuBlock->Attribute("nom"), atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posX")));
											}else if (strcmp(contenuBlock->Attribute("type"),"bonus")){
												if (strcmp(contenuBlock->Attribute("nom"),"STAR_DUST")){
													vBlock->setBonus(STAR_DUST, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posX")));
												}else if (strcmp(contenuBlock->Attribute("nom"),"ACCELERATOR")){
													vBlock->setBonus(ACCELERATOR, atoi(contenuBlock->Attribute("posX")), atoi(contenuBlock->Attribute("posX")));
												}
											}
										}
										contenuBlock = contenuBlock->NextSiblingElement();
									}// fin du while dans le block

								}
								m_blocks.push_back(vBlock);
							}else if (strcmp(contenuLevel->Value(),"station")==0){
								//on est dans la balise station / gare
								
								//Station * vStation= new Station(); // smartpointer
								//vStation = new Block(STATION, 10, NULL,-1);
								//vStation->setType(STATION);
								/*vStation->setId(atoi(contenuLevel->Attribute("num")));
								vStation->setSizeX(atoi(contenuLevel->Attribute("size")));
								//variable element qui check les balises contenu dans block
								TiXmlElement *contenuStation = contenuLevel->FirstChildElement();
								while (contenuStation){
									if (strcmp(contenuStation->Value(),"option")==0){
										vStation->setTime(atoi(contenuStation->Attribute("hours")), atoi(contenuStation->Attribute("minutes")));
										vStation->setLeaving(atoi(contenuStation->Attribute("leaving")));
										vStation->setEnter(atoi(contenuStation->Attribute("entering")));
									}
									contenuStation = contenuStation->NextSiblingElement();
								}
								m_blocks.push_back(vStation);
								*/
								
							}else if (strcmp(contenuLevel->Value(),"infobulle")==0){
								//on est dans la balise infobulle
								if (strcmp(contenuLevel->Attribute("type"),"standard")){
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
								}else if (strcmp(contenuLevel->Attribute("type"),"aide")){
									/*HelpTip * infoAide = new HelpTip();
									infoAide->setNumBlock(contenuLevel->Attribute("numBlock"));
									infoAide->setDeclenche(contenuLevel->Attribute("declenche"));
									TiXmlElement *contenuBulle = contenuLevel->FirstChildElement();
									while (contenuBulle){
										if (strcmp(contenuBulle->Value(),"sprite")==0){
											infoAide->setSprite(contenuBulle->Attribute("img"));
										}
										contenuBulle = contenuBulle->NextSiblingElement();
									}*/
								}
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

void Level::render(SDL_Surface * screen, int w, int h)
{
	drawBackgrounds(screen,  w,  h);
	drawBlocks(screen, w, h);
}

/*
 * Level dessine tous les blocs du vector
 */
void Level::drawBlocks(SDL_Surface * screen, int w, int h)
{
	for (unsigned int i=0; i<m_blocks.size(); i++) 
	{
		m_blocks.at(i)->draw( screen, w, h);
	}
}


/*
 * Level dessine les fonds d'écran
 */
void Level::drawBackgrounds(SDL_Surface * screen, int w, int h)
{
   m_backgroundImages[0]->draw(screen, w, h); 
   m_backgroundImages[1]->draw(screen, w, h);
   m_backgroundImages[2]->draw(screen, w, h);  
}
