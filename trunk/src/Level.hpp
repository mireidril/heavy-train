#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#ifdef _WIN32
#include "SDL/SDL.h"
#include "tinyXML/tinyxml.h"
#include "SDL/SDL_image.h"
#else
#include <SDL/SDL.h>
#include <tinyxml.h>
#include <SDL/SDL_image.h>
#endif

#include <map>
#include "Sprite.hpp"
#include "Block.hpp"
#include "Time.hpp"
#include "Station.hpp"

class ActualGame;

class Level
{
	public :
		//Constructor
		Level(b2World * world, unsigned int level, unsigned int island);
		//Destructor
		virtual ~Level();
		//Move the level horizontally
		void scrollLevel(const int & x);
		//Load and build the level n°lvl of the island n°isle
		void loadAndBuild();
		//Ajoute une image de fond
		void addBackgroundImage(const std::string & path, const int & posY, const std::string & path2 = "");
		//Crée un Sprite pour m_ground
		void loadGroundImage(const std::string & path);
		//Retourne le sprite du sol du niveau
		SDL_Surface * getGroundImage() { return m_groundImage; } ;
		//Construit tous les blocs
		void buildBlocks();
		Block * getBlock(unsigned int i);
		unsigned int getNbBlocks() { return m_blocks.size(); } ;

		//Réinitialise les valeurs des PhysicalObjects après un smooth pour coller au framerate
		void clearAllSmoothAngleAndPosition();

		void render(SDL_Surface * screen, int w, int h, ActualGame * game, b2World * world);
		void drawBlocks(SDL_Surface * screen, int w, int h, ActualGame * game, b2World * world);
		void drawTunnels(SDL_Surface * screen, int w, int h, ActualGame * game, b2World * world);

		void drawBackgrounds(SDL_Surface * screen, int w, int h);

		unsigned int getIslandNum() { return m_islandNum;};
		unsigned int getLevelNum() { return m_levelNum;};

	private :
		//World
		b2World * m_world;
		//All the blocks of the level
		std::vector<Block*>	m_blocks;
		//Departure time of the level
		Time* m_departureTime;
		//Position of the level at the screen (bottom-left of the first block)
		SDL_Rect*	m_position;
		//Numero of the level’s island
		unsigned int	m_islandNum;
		//Numero of the level
		unsigned int	m_levelNum;
		//Background image of the level
		std::vector<Sprite*> m_backgroundImages;
		//Ground image of the level
		SDL_Surface *		m_groundImage;
		//Numeros of the blocks which are stations
		std::vector<int> m_idStations;
};
#endif
