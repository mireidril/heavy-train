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
		
			std::cout<< "island : " << island->Value()<<std::endl;
			//std::cout<< "level : " << level->Value()<<std::endl;
			//std::cout<< "contenuLevel : " << contenuLevel->Value()<<std::endl;
			//std::cout<< "contenuBlock : " << contenuBlock->Value()<<std::endl;
					//std::cout<< "island : island->Attribute(id) : " << (int)island->Attribute("id") <<std::endl;
					//std::cout<< "island : isle : " << isle <<std::endl;
					
					//island->QueryIntAttribute("id", &i);
					//std::cout<< "island : island->QueryIntAttribute() : " << island->QueryIntAttribute("id", m_islandNum) <<std::endl;


					//std::cout<< "level : level->Attribute(id) : " << int(level->QueryIntAttribute ("id", lvl)) <<std::endl;
					//std::cout<< "level : lvl : " << lvl <<std::endl;
		while (island){
			if(atoi(island->Attribute("id"))){
				
				TiXmlElement *level = island->FirstChildElement();
				while (level){//ca marche???
					//std::cout<< "CAST level->Attribute(id) : " << atoi (level->Attribute("id")) << std::endl;
					//std::cout<< "level : lvl : " << lvl <<std::endl;
					if(atoi(level->Attribute("id")) == lvl){
						
						TiXmlElement *contenuLevel = level->FirstChildElement();
						while (contenuLevel){
								std::cout<< "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee : " << contenuLevel->Value() << std::endl;
							if (strcmp(contenuLevel->Value(),"block")==0){
								std::cout<< "ON EST DEDANS : " << std::endl;
								//contenuLevel->Value().c_str()
								/*std::cout<< "contenuBlock : " << contenuBlock->Value()<<std::endl;
								//Block * vBlock = new Block(JUNCTION_DOWN, 10, NULL); // smartpointer
								std::auto_ptr<Block> vBlock (new Block(JUNCTION_DOWN, 10, NULL));
								std::cout<< "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee : " << std::endl;
								//vBlock.setId(block->Attribute("numBlock"));
								//vBlock.setSizeX(block->Attribute("sizeBlock"));
								//m_blocks.m_type = block->Attribute("typeBlock");
								//vBlock.m_maxSpeed = block->Attribute("speedBlock");
								m_blocks.push_back(vBlock.release());*/
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
