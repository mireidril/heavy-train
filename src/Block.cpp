#include "Block.hpp"


/*
 * Block Constructor
 * sizeX est la dimension du bloc en pixel
 * posX est la position du bloc en pixels dans l'espace
 */

Block::Block(BlockType type, int sizeX, int posX, int id)
: m_type(type)
, m_posX(posX)
, m_sizeX(sizeX)
, m_id(id)
, m_hillSegmentWidth(10)
, m_sizeXMin(256)
, m_sizeXMax(2048)
, m_sizeYMin(384)
, m_y (668)
, m_tunnelHeight (200)
{
	SDL_Rect * p1, *p01, *p2, *p3, *p4, *p5;
	switch(type)
	{
		case GROUND :
			p1 = new SDL_Rect;
			p1->x = 0;
			p1->y = m_y;
			p01 = new SDL_Rect;
			p01->x = 10;
			p01->y = 384;
			p2 = new SDL_Rect;
			p2->x = 256;
			p2->y = 600;
			p3 = new SDL_Rect;
			p3->x = 512;
			p3->y = 450;
			p4 = new SDL_Rect;
			p4->x = 768;
			p4->y = 500;
			p5 = new SDL_Rect;
			p5->x = 1024;
			p5->y = m_y;
			m_points.push_back(p1);
			m_points.push_back(p01);
			m_points.push_back(p2);
			m_points.push_back(p3);
			m_points.push_back(p4);
			m_points.push_back(p5);
			break;
		case PRECIPICE :
			break;
		case STATION :
			break;
		case TUNNEL :
			break;
		default:
			m_sizeX = sizeX;
			break;

	}

	m_sprite = NULL;
	
}

Block::~Block() 
{
	for( unsigned int i = 0; i < m_points.size(); ++i)
	{
		delete m_points[i];
	}

	delete m_sprite;
	//supprimer le body
}


b2Body * Block::getBody() 
{
	return m_body;
} 

void Block::setBody(b2Body * body) 
{
	m_body = body;
} 
void Block::setId(int num) 
{
	m_id = num;
} 
void Block::setSizeX(int size) 
{
	m_sizeX = size;
}  
void Block::setType(BlockType type) 
{
	m_type = type;
}  
void Block::setSpeed(int speed) 
{
	m_maxSpeed = speed;
}

void Block::addPoint(int x, int y) 
{
/*b2Vec2 pts = b2Vec2(x, y);
	m_groundPoints.push_back(pts);*/
		SDL_Rect * pts = new SDL_Rect;
	pts->x = x;
	pts->y = y;
	m_points.push_back(pts);
} 
void Block::setBonus(Bonus* bonus) 
{
	m_bonus.push_back(bonus);
}
void Block::setAnimal(const char * type, int x, int y) 
{
	Animal * animal = new Animal();
	animal->setType(type);
	animal->setPosX(x);
	animal->setPosY(y);
	m_animals.push_back(animal);
}
//Retourne l'identifiant du point à l'ordonnée la plus basse
int Block::getYMinPoint()
{
	int min = 9999999;
	int idMin = -1;
	for(unsigned int i = 0; i < m_points.size(); ++i)
	{
		if(m_points[i]->y < min)
		{
			min = m_points[i]->y;
			idMin = i;
		}
	}

	return idMin;
}
//Retourne l'identifiant du point à l'ordonnée la plus grande
int Block::getYMaxPoint()
{
	int max = -9999999;
	int idMax = -1;
	for(unsigned int i = 0; i < m_points.size(); ++i)
	{
		if(m_points[i]->y > max)
		{
			max = m_points[i]->y;
			idMax = i;
		}
	}

	return idMax;
}

void Block::createImage()
{
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 rmask = 0xff000000;
		Uint32 gmask = 0x00ff0000;
		Uint32 bmask = 0x0000ff00;
		Uint32 amask = 0x000000ff;
	#else
		Uint32 rmask = 0x000000ff;
		Uint32 gmask = 0x0000ff00;
		Uint32 bmask = 0x00ff0000;
		Uint32 amask = 0xff000000;
	#endif

	switch(m_type)
	{
		case GROUND :
		{
			//Création du masque
			SDL_Surface * image = SDL_CreateRGBSurface(SDL_HWSURFACE, m_sizeX, (int) m_sizeYMin, 32, rmask, gmask, bmask, amask);
	
			for(int x = 0; x < m_sizeX; ++x)
			{
				for(int y = 0; y < m_sizeYMin; ++y)
				{
					Sprite::putpixel(image, x, y, 0xffffffff);
				}
			}
			double x1, y1, x2, y2;
			for(unsigned int i = 1; i < m_groundPoints.size(); ++i)
			{
				//Conversion en mètre
				x1 = m_groundPoints[i-1].x;
				y1 = m_groundPoints[i-1].y;
				x2 = m_groundPoints[i].x;
				y2 = m_groundPoints[i].y;
				Sprite::convertMetersToPixels(&x1, &y1, WINDOWS_W, WINDOWS_H);
				Sprite::convertMetersToPixels(&x2, &y2, WINDOWS_W, WINDOWS_H);

				//Remplissage du haut de l'écran par du noir
				int nbSide = 4;
				Sint16 * xPolygon = new Sint16[nbSide];
				Sint16 * yPolygon = new Sint16[nbSide];
				xPolygon[0] = (Sint16) x1; yPolygon[0] = 0;
				xPolygon[1] = (Sint16) x2; yPolygon[1] = 0;
				xPolygon[2] = (Sint16) x2; yPolygon[2] = (Sint16) (y2 - m_sizeYMin);
				xPolygon[3] = (Sint16) x1; yPolygon[3] = (Sint16) (y1 - m_sizeYMin);
				filledPolygonRGBA(image, xPolygon, yPolygon, nbSide, 0, 0, 0, 255);
				delete [] xPolygon;
				delete [] yPolygon;
			}
	
			SDL_SaveBMP(image, "masque.bmp");

			//Chargement de l'image ground
			SDL_Surface * ground = IMG_Load("../img/levels/ground.png");
			if(!ground)
			{
				std::cout<<std::endl;
			}
			//Changement de la taille pour correspondre à la taille du bloc
			ground->w = m_sizeX;
			SDL_SaveBMP(ground, "ground2.bmp");

			//Construction de l'image du bloc
			SDL_Surface * imageTest = SDL_CreateRGBSurface(SDL_HWSURFACE, m_sizeX, (int) m_sizeYMin, 32, rmask, gmask, bmask, amask);
			Uint32 actualPixel;
			for(int x = 0; x < m_sizeX; ++x)
			{
				for(int y = 0; y < m_sizeYMin; ++y)
				{
					if( Sprite::getpixel(image, x, y) == 0xff000000)
					{
						actualPixel = 0x00000000;
					}
					else if( Sprite::getpixel(image, x, y) == 0xffffffff)
					{
						actualPixel = Sprite::getpixel(image, x, y) & Sprite::getpixel(ground, x, y);
					}
					Sprite::putpixel(imageTest, x, y, actualPixel);
				}
			}

			SDL_SaveBMP(imageTest, "bloc.bmp");

			SDL_Rect * position = new SDL_Rect;
			position->x = 0;
			position->y = (Sint16) m_sizeYMin;
			SDL_Rect * size = new SDL_Rect;
			size->x = (Sint16) m_sizeX;
			size->y = (Sint16) m_sizeYMin;
			m_sprite = new Sprite(imageTest, position, size);
		}
		break;

		case STATION :
		{
			//Créer une image avec du plat et la gare au milieu ?
		}
		break;

		case TUNNEL :
		{
			//Créer une image avec les bords du tunnel aux extrémités ?
		}
		break;

		case PRECIPICE :
		{
			//Créer une image avec les bords du précipice aux extrémités ?
		}
		break;
	}

	

	
}

void Block::scroll(const int & x)
{
	if(m_sprite)
		m_sprite->setPositionX(m_sprite->getPositionX() + x);
}


void Block::draw(SDL_Surface * screen, const int & width, const int & height)
{
	if(m_sprite)
		m_sprite->draw(screen, width, height);
}

/*
 * Block construction
 */
void Block::build(b2World * world)
{
	switch(m_type)
	{
		case GROUND:
		{
			//Vérification taille de la future spline
			//On suppose que les points sont dans l'ordre et que le x du premier point > 0
			if(m_points[m_points.size() - 1]->x < m_sizeXMin)
			{
				m_points[m_points.size() - 1]->x = (Sint16) m_sizeXMin;
			}
			else if(m_points[m_points.size() - 1]->x > m_sizeXMax)
			{
				m_points[m_points.size() - 1]->x = (Sint16) m_sizeXMax;
			}
			m_sizeX = m_points[m_points.size() - 1]->x;

			int id = getYMinPoint();
			if( id != -1)
			{
				assert(id < m_points.size());
				if(m_points[id]->y < m_sizeYMin)
				{
					m_points[id]->y = (Sint16) m_sizeYMin;
				}
			}

			id = getYMaxPoint();
			if( id != -1 )
			{
				assert(id < m_points.size());
				if(m_points[id]->y > WINDOWS_H)
				{
					m_points[id]->y = WINDOWS_H;
				}
			}
			
			//Smoothing de la spline et conversion des pixels en mètres
			b2Vec2 p1, p2;
			b2Vec2 pt1, pt2;
			int hSegments;
			double dx, da, yMid, ampl;
			double x, y;
			for(unsigned int i = 1; i < m_points.size(); ++i)
			{
				p1 = b2Vec2(m_points[i-1]->x, m_points[i-1]->y);
				p2 = b2Vec2(m_points[i]->x, m_points[i]->y);

				hSegments = (int) floorf( (p2.x - p1.x) / m_hillSegmentWidth );
				dx = (p2.x - p1.x) / hSegments;
				da = M_PI / hSegments;
				yMid = (p1.y + p2.y) / 2.0;
				ampl = (p1.y - p2.y) / 2.0;
 
				pt1 = p1;
				//Conversion en mètre
				x = pt1.x;
				y = pt1.y;
				Sprite::convertPixelsToMeters(&x, &y, WINDOWS_W, WINDOWS_H);
				pt1.x = (float32) x;
				pt1.y = (float32) y;
				m_groundPoints.push_back(pt1);
				for (int j = 0; j < hSegments + 1; ++j)
				{
					pt2.x = (float32) (p1.x + j*dx);
					pt2.y = (float32) (yMid + ampl * cosf( (float) da*j) );

					//Conversion en mètre
					x = pt2.x;
					y = pt2.y;
					Sprite::convertPixelsToMeters(&x, &y, WINDOWS_W, WINDOWS_H);
					pt2.x = (float32) x;
					pt2.y = (float32) y;
					m_groundPoints.push_back(pt2);

					pt1 = pt2;
				}
			}

			//Construction du body
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(0, 0); //Position à changer plus tard
			m_body = world->CreateBody(&groundBodyDef);

			b2EdgeShape shape;
			for (unsigned int i = 1; i < m_groundPoints.size(); ++i)
			{
				if(i > 1)
				{
					shape.m_hasVertex0 = true;
					shape.m_vertex0 = m_groundPoints[i-2];
				}
			
				if(i < m_groundPoints.size() - 1)
				{
					shape.m_hasVertex3 = true;
					shape.m_vertex3 = m_groundPoints[i+1];
				}

				p1 = m_groundPoints[i-1];
				p2 = m_groundPoints[i];
				shape.Set(p1, p2);
				m_body->CreateFixture(&shape, 0);
			}
		}
		break;

		case STATION :
		{
			//On suppose que la taille de la gare est supérieure à zéro
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(0, 0); //Position à changer plus tard
			m_body = world->CreateBody(&groundBodyDef);

			b2EdgeShape shape;
			//Attention aux blocs mitoyens : y'a t-il besoin de mettre shape.m_hasVertex0 et shape.m_hasVertex3 ?
			double x1 = m_posX, y1 = m_sizeYMin;
			double x2 = m_posX + m_sizeX, y2 = m_sizeYMin;
			Sprite::convertPixelsToMeters(&x1, &y1, WINDOWS_W, WINDOWS_H);
			Sprite::convertPixelsToMeters(&x2, &y2, WINDOWS_W, WINDOWS_H);
			b2Vec2 p1((float32) x1, (float32) y1);
			b2Vec2 p2((float32) x2, (float32) y2);
			shape.Set(p1, p2);
			m_body->CreateFixture(&shape, 0);
		}

		case TUNNEL :
		{
			//On suppose que la taille du tunnel est supérieure à zéro
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(0, 0); //Position à changer plus tard
			m_body = world->CreateBody(&groundBodyDef);

			//Attention aux blocs mitoyens : y'a t-il besoin de mettre shape.m_hasVertex0 et shape.m_hasVertex3 ?

			//Sol du tunnel
			b2EdgeShape sol;
			double x1 = m_posX, y1 = m_y;
			double x2 = m_posX + m_sizeX, y2 = m_y;
			Sprite::convertPixelsToMeters(&x1, &y1, WINDOWS_W, WINDOWS_H);
			Sprite::convertPixelsToMeters(&x2, &y2, WINDOWS_W, WINDOWS_H);
			b2Vec2 p1((float32) x1, (float32) y1);
			b2Vec2 p2((float32) x2, (float32) y2);
			sol.Set(p1, p2);
			m_body->CreateFixture(&sol, 0);

			//Sol du tunnel
			b2EdgeShape plafond;
			x1 = m_posX; y1 = m_y - m_tunnelHeight;
			x2 = m_posX + m_sizeX; y2 = m_y - m_tunnelHeight;
			Sprite::convertPixelsToMeters(&x1, &y1, WINDOWS_W, WINDOWS_H);
			Sprite::convertPixelsToMeters(&x2, &y2, WINDOWS_W, WINDOWS_H);
			p1.x = (float32) x1; p1.y = (float32) y1;
			p2.x = (float32) x2; p2.y = (float32) y2;
			plafond.Set(p1, p2);
			m_body->CreateFixture(&plafond, 0);
		}

		case PRECIPICE :
		{
			//Pas de body
		}
		break;
	}
	
	createImage();
}
