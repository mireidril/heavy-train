#include "Sprite.hpp"

/**
 * Constructeur
 */
Sprite::Sprite(const char* imageFileName, int posX, int posY, int sizeX, int sizeY)
: m_actualFrame(0)
, m_nbFrames(0)
, m_position(NULL)
, m_angle(0.0)
, m_size(NULL)
, m_timeActualFrame(0)
, m_timeFrame(4)
{
	m_position = new SDL_Rect();
	m_position->x = posX;
	m_position->y = posY;
	m_size = new SDL_Rect();
	m_size->x = sizeX;
	m_size->y = sizeY;
	SDL_Surface * img = IMG_Load(imageFileName);
	if(img)
	{
		SDL_Surface * tmp = SDL_DisplayFormatAlpha(img);
		SDL_FreeSurface(img);
		img = tmp;
		
		m_frames.push_back(img);
		m_nbFrames++;
	}
}

/**
 * Constructeur
 */
Sprite::Sprite(SDL_Surface * sdlSurface, int posX, int posY, int sizeX, int sizeY)
: m_actualFrame(0)
, m_nbFrames(0)
, m_position(NULL)
, m_angle(0.0)
, m_size(NULL)
, m_timeActualFrame(0)
, m_timeFrame(10)
{
	m_position = new SDL_Rect();
	m_position->x = posX;
	m_position->y = posY;
	m_size = new SDL_Rect();
	m_size->x = sizeX;
	m_size->y = sizeY;
	if(sdlSurface)
	{
		SDL_Surface * tmp = SDL_DisplayFormatAlpha(sdlSurface);
		SDL_FreeSurface(sdlSurface);
		sdlSurface = tmp;
	}

	m_frames.push_back(sdlSurface);
	m_nbFrames++;
}


/**
 * Destructeur
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
 * Setter Nbframes
 */
void Sprite::setNbFrames(int x){
	m_nbFrames = x;
}

/**
 * Setter position
 */
void Sprite::setPosition(int x, int y){
	m_position->x = x;
	m_position->y = y;
}
/**
 * Setter positionX
 */
void Sprite::setPositionX(int x){
	m_position->x = x;
}

/**
 * Setter positionY
 */
void Sprite::setPositionY(int y){
	m_position->y = y;
}



/**
 * Getter position X
 */
int Sprite::getPositionX(){
	return m_position->x;
}

/**
 * Getter position Y
 */
int Sprite::getPositionY(){
	return m_position->y;
}

/**
 * Setter angle
 */
void Sprite::setAngle(double & angle){
	m_angle = angle;
}

/**
 * Charge et ajoute une image au sprite
 * imageFileName : chemin de l'image à rajouter
 */
void Sprite::addImage(const char* imageFileName)
{
	SDL_Surface * img = IMG_Load(imageFileName);
	if(img)
	{
		SDL_Surface * tmp = SDL_DisplayFormatAlpha(img);
		SDL_FreeSurface(img);
		img = tmp;
		m_frames.push_back(img);
		m_nbFrames++;
	}
}

/**
 * Ajoute une image au sprite
 * sdlSurface : SDL_Surface à rajouter
 */
void Sprite::addImage(SDL_Surface * sdlSurface)
{
	SDL_Surface * img = SDL_DisplayFormat(sdlSurface);
	if(sdlSurface)
	{
		m_frames.push_back(img);
		m_nbFrames++;
	}
}

/*
 * Gère les conversions du monde physique vers l'affichage
 */
void Sprite::convertMetersToPixels(double * x, double * y, const int & width, const int & height){
	//largeur de l'écran : 1024 = 40 metres
	//hauteur de l'écran : 768 = 30 metres (pour respecter le ratio de l'écran)
	if(x)
		(*x) = width * (*x) / 40;
	if(y)
		(*y) = height - height * (*y) / 30;
}


/*
 * Gère les conversions du monde physique vers l'affichage
 */
void Sprite::convertMetersToPixelsY( double * y, const int & width, const int & height){
	if(y)
		(*y) = height - height * (*y) / 30;
}

/*
 * Gère les conversions de l'affichage vers l'écran
 */
void Sprite::convertPixelsToMeters(double * x, double * y, const int & width, const int & height){
	//largeur de l'écran : 1024 = 40 metres
	//hauteur de l'écran : 768 = 30 metres (pour respecter le ratio de l'écran)
	if(x)
		(*x) = (double) (*x) * 40.0 / width;
	if(y)
		(*y) = (double) 30 - ( (*y) * 30.0 / height );
}

double Sprite::getSizeX(){
	return   m_size->x ;
	
}

double Sprite::getSizeY(){
	return  m_size->y ;
	
}



/**
 * Change l'image actuellement affichée après un temps donné (m_timeFrame) et renvoi false si l'anim est terminé
 */
bool Sprite::animate()
{
	if(m_nbFrames > 1)
	{
		//incrémenter m_timeActualFrame (TODO : en secondes et pas en frame)
		m_timeActualFrame++;
		 
		if(m_timeActualFrame >= m_timeFrame)
		{
			m_timeActualFrame = 0;
			m_actualFrame++;
			if(m_actualFrame >= m_nbFrames)
			{
				
				m_actualFrame = 0;
				return false;
			}
			else {
				return true;
			}
		}
	}
}

/**
 * Dessine le sprite à l'écran
 * screen : fenêtre SDL
 * width : largeur de l'écran
 * height : hauteur de l'écran
 */
void Sprite::draw(SDL_Surface * screen, const int & width, const int & height)
{
	if(m_actualFrame < m_nbFrames)
	{
		//Rotation et zoom
		float zoomX = (float)width /m_size->x;
		float zoomY = (float)height/m_size->y;
		SDL_Surface * image = rotozoomSurfaceXY(m_frames[m_actualFrame], m_angle, 1.0, 1.0, 1);

		//Dessine à sa position
		SDL_Rect * realPos = new SDL_Rect;
		realPos->x = m_position->x;
		realPos->y = m_position->y;
		//On le dessine seulement s'il est visible à l'écran
		if(realPos->x >= - m_size->x && realPos->x <= width && realPos->y >= - m_size->y && realPos->y <= height )
		{
			SDL_BlitSurface(image, NULL, screen, realPos);
		}
		
		delete realPos;
		SDL_FreeSurface(image);
	}
}

/**
 * Change l'image actuellement affichée par une autre
 */
void Sprite::changeImageManually(const int & imageNum)
{
	if(imageNum < m_nbFrames)
	{
		m_actualFrame = imageNum;
	}
}

Uint32 Sprite::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to retrieve
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       // shouldn't happen, but avoids warnings
    }
}

void Sprite::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to set
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}
