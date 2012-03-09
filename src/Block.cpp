#include "Block.hpp"


/*
 * Block Constructor
 * sizeX and sizeY are dimension of the image in pixel 
 */

Block::Block(BlockType type, int sizeX, SDL_Rect * pos)
: m_type(type)
, m_hillSegmentWidth(10)
{
	SDL_Rect * p1, *p2, *p3, *p4, *p5;
	switch(type)
	{
		case GROUND :
			p1 = new SDL_Rect;
			p1->x = 0;
			p1->y = 384;
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
			p5->y = 384;
			m_points.push_back(p1);
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

	m_sprite = new Sprite("../img/ground.png",  pos,  NULL);
	
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
void Block::setPoints(int x, int y) 
{
	b2Vec2 pts = b2Vec2(x, y);
	m_groundPoints.push_back(pts);
}  


void Block::draw(SDL_Surface * screen, const int & width, const int & height)
{
	/*b2Vec2 bodyPos = m_body->GetPosition();
	SDL_Rect * pos = new SDL_Rect;
	double x = bodyPos.x;
	double y = bodyPos.y;
	
	Sprite::convertMetersToPixels(x, y, width, height);

	pos->x =  x;
	pos->y = y + bodyPos.y;

	m_sprite->setPosition(pos);
	m_sprite->draw(screen, width, height);

	delete pos;*/
	if(m_type == GROUND)
	{
		/*b2Color color(1.0, 0.0, 0.0);
		double x1, y1, x2, y2;
		for(int i = 1; i < m_points.size(); ++i)
		{
			x1 = m_points[i-1]->x;
			y1 = m_points[i-1]->y;
			x2 = m_points[i]->x;
			y2 = m_points[i]->y;
			lineRGBA(Sprite::screen, (Sint16) x1 , (Sint16) y1, (Sint16) x2, (Sint16) y2, (Uint8) color.r * 255, (Uint8) color.g * 255, (Uint8) color.b * 255, 255);
		}*/

		

		/*b2Color color2(1.0, 1.0, 0.0);
		for(int i = 1; i < newPoints.size(); ++i)
		{
			x1 = newPoints[i-1]->x;
			y1 = newPoints[i-1]->y;
			x2 = newPoints[i]->x;
			y2 = newPoints[i]->y;
			lineRGBA(Sprite::screen, (Sint16) x1 , (Sint16) y1, (Sint16) x2, (Sint16) y2, (Uint8) color2.r * 255, (Uint8) color2.g * 255, (Uint8) color2.b * 255, 255);
		}*/
	}
}

/*
 * Block construction
 */
void Block::build(b2World * world)
{
	if(m_type == GROUND)
	{
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
			Sprite::convertPixelsToMeters(x, y, 1024, 768);
			pt1.x = (float32) x;
			pt1.y = (float32) y;
			m_groundPoints.push_back(pt1);
			for (int j = 0; j < hSegments + 1; ++j)
			{
				pt2.x = p1.x + j*dx;
				pt2.y = yMid + ampl * cosf( (float) da*j);

				//Conversion en mètre
				x = pt2.x;
				y = pt2.y;
				Sprite::convertPixelsToMeters(x, y, 1024, 768);
				pt2.x = x;
				pt2.y = y;
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

		//Création d'un cercle pour les tests
		/*
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		b2Body * body;
		bodyDef.position.Set(15, 40);
		body = world->CreateBody(&bodyDef);
		b2CircleShape circle;
		circle.m_radius = 1;
		body->CreateFixture(&circle, 0.0f);
		*/
	}
	else
	{
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0, 0);

		m_body = world->CreateBody(&groundBodyDef);

		// Define the ground box shape.
		b2PolygonShape groundBox;
		//b2CircleShape groundBox;

		// The extents are the half-widths of the box.
		double sizeX = m_sizeX;
		double sizeY = 10;
		Sprite::convertPixelsToMeters(sizeX, sizeY, 1024, 768);
		//groundBox.SetAsBox(40, 5);
		//groundBox.m_radius = 15;

		b2Vec2 vertices[6];
		vertices[0].Set(0.0f, 0.0f);
		vertices[1].Set(40.0f, 0.0f);
		vertices[2].Set(40.0f, 5.0f);
		vertices[3].Set(0.0f, 5.0f);
		groundBox.Set(vertices, 4);

		// Add the ground fixture to the ground body.
		m_body->CreateFixture(&groundBox, 0.0f);
	}
}
