#include "Sprite.hpp"

/**
 * Sprite Constructor
 */
Sprite::Sprite(const char* imageFileName, SDL_Rect * pos, SDL_Rect * size)
: m_actualFrame(0)
, m_nbFrames(0)
, m_position(pos)
, m_angle(0.0)
, m_size(size)
, m_timeActualFrame(0)
, m_timeFrame(10)
{
	SDL_Surface * img = IMG_Load(imageFileName);
	if(img)
	{
		m_frames.push_back(img);
		m_nbFrames++;
	}
	//If pos is not in percentage
	assert( m_position->x >= 0 && m_position->y >= 0 && m_position->x <= 100 && m_position->y <= 100 );
}

/**
 * Sprite Destructor
 */
Sprite::~Sprite()
{
	for(unsigned int i = 0; i < m_frames.size(); ++i)
	{
		SDL_FreeSurface(m_frames[i]);
	}

	delete m_position;
	delete m_size;
}

/**
 * Add an new image in the sprite
 */
void Sprite::addImage(const char* imageFileName)
{
	SDL_Surface * img = IMG_Load(imageFileName);
	if(img)
	{
		m_frames.push_back(img);
		m_nbFrames++;
	}
}

/**
 * Animate the sprite, alternating its images every "m_nbFrames" seconds
 */
void Sprite::animate()
{
	if(m_nbFrames > 1)
	{
		//increments m_timeActualFrame (TODO : en secondes et pas en frame)
		m_actualFrame++;
		if(m_timeActualFrame >= m_timeFrame)
		{
			m_timeActualFrame = 0;
			m_actualFrame++;
			if(m_actualFrame >= m_nbFrames)
			{
				m_actualFrame = 0;
			}
		}
	}
}

/**
 * Draw the sprite in the screen
 */
void Sprite::draw(SDL_Surface * screen, const int & width, const int & height)
{
	if(m_actualFrame < m_nbFrames)
	{
		//Rotation and zoom
		SDL_Surface * image = rotozoomSurface(m_frames[m_actualFrame], m_angle, 1.0, 1);

		//Drawing to a position
		SDL_Rect * realPos = new SDL_Rect;
		realPos->x = width * m_position->x * 0.01;
		realPos->y = height * m_position->y * 0.01;
		SDL_BlitSurface(image, NULL, screen, realPos);
		
		delete realPos;
		SDL_FreeSurface(image);
	}
}

/**
 * Change the sprite's image actually displayed
 */
void Sprite::changeImageManually(const int & imageNum)
{
	if(imageNum < m_nbFrames)
	{
		m_actualFrame = imageNum;
	}
}