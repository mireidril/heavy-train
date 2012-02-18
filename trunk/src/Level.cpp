#include "Level.hpp"



/*Block Constructor */

Level::Level () 
{
	//All the blocks of the level
		m_blocks.push_back(new Block(10));
		//m_departureTime = ...;
		//m_position = ...;
		m_islandNum =0;
		m_levelNum = 0;
		//m_backgroundImages = ;
		//m_idStations= ...;

}


Block * Level::getBlock(int i) {
	return m_blocks.at(i);

}

