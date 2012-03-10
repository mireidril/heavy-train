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
		m_blocks.push_back(new Block(GROUND, 1000, pos));
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
	m_backgroundPositions.push_back(posBg);
	m_backgroundImages.push_back(new Sprite("../img/niveau2/sky.png",  posBg,  size));
	m_backgroundImages.push_back(new Sprite("../img/niveau2/moutains.png", posBg,  size));

}

Level::~Level() 
{
        for(int i = 0; i < m_blocks.size(); ++i)
        {
                delete m_blocks[i];
        }
}

Block * Level::getBlock(int i) {
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
void Level::scrollLevel(const int & x){

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
							std::cout<< "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee : " << contenuLevel->Value() << std::endl;
							//si la balise dans level correspond a la balise block on entre dans ce if
							if (strcmp(contenuLevel->Value(),"block")==0){
								//on est dans une balise block !
								/*
		int m_sizeXMin;
		int m_sizeXMax;
		int m_y;
		int m_yMax;
		BlockType m_type;
		Sprite * m_sprite;
		b2Body * m_body;
		int m_sizeX;
							*/	
								Block * vBlock = new Block(JUNCTION_DOWN, 10, NULL); // smartpointer
								vBlock->setId(atoi(contenuLevel->Attribute("num")));
								vBlock->setSizeX(atoi(contenuLevel->Attribute("size")));
								//vBlock->setType((BlockType)contenuLevel->Attribute("type"));
								vBlock->setSpeed(atoi(contenuLevel->Attribute("speed")));
								//variable element qui check les balises contenu dans block
								TiXmlElement *contenuBlock = contenuLevel->FirstChildElement();
								while (contenuBlock){
									if (strcmp(contenuBlock->Value(),"obstacle")==0){
										//vBlock->setTypeObst(atoi(contenuBlock->Attribute("type")));
										//vBlock->setPosXObst(atoi(contenuBlock->Attribute("posX")));
										//vBlock->setPosYObst(atoi(contenuBlock->Attribute("posY")));

									}else if (strcmp(contenuBlock->Value(),"point")==0){										
										//!!!!!!!!!!!!!!!!!!!!attention il y a 2 points pas block : comment faire??? cpt qui rempli tableau? a quoi correspond ces points dans le code?
										//concerne m_groundPoints (vec 2)
										vBlock->setPoints(atoi(contenuBlock->Attribute("x")), atoi(contenuBlock->Attribute("y")));
									}
									contenuBlock = contenuBlock->NextSiblingElement();
								}
							}else if (strcmp(contenuLevel->Value(),"station")==0){
								//on est dans la balise station / gare
							}else if (strcmp(contenuLevel->Value(),"infobulle")==0){
								//on est dans la balise infobulle
							}
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
        for (int i=0; i<m_blocks.size(); i++) 
        {
                m_blocks.at(i)->draw( screen, w, h);
        }
}


/*
 * Level dessine les fonds d'écran
 */
void Level::drawBackgrounds(SDL_Surface * screen, int w, int h)
{
   m_backgroundPositions[0]->x -= 1;
   //m_backgroundImages[1]->setPosition(m_backgroundPositions[0]);
   m_backgroundImages[0]->draw(screen,w,h); 
   m_backgroundImages[1]->draw(screen,w,h);   
}
