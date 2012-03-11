#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "Bonus.hpp"
#include "Sprite.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif

enum BlockType
{
	GROUND = 0,
	PRECIPICE,
	STATION,
	TUNNEL,
	JUNCTION_UP,
	JUNCTION_DOWN
};

class Block
{
	public :
		Block(BlockType type, int sizeX, int posX, int id);
		virtual ~Block();

		//Construit le bloc
		void build(b2World * world);

		//Crée l'image correspondant au type du bloc
		void createImage();

		//Modifie la position du bloc en x
		void scroll(int);

		//Retourne le body du bloc
		b2Body * getBody();
		
		//Attribue m_body au bloc
		void setBody(b2Body * body);
		//Attribue m_id au bloc
		void setId(int num);
		//Attribue m_sizeX au bloc
		void setSizeX(int size);
		//Attribue m_type au bloc
		void setType(BlockType type);

		void setSpeed(int speed); //utile ?

		//Ajoute un point dans m_points
		void addPoint(int x, int y);
		//Retourne l'identifiant du point à l'ordonnée la plus basse
		int getYMinPoint();
		//Retourne l'identifiant du point à l'ordonnée la plus grande
		int getYMaxPoint();

		//Dessine le bloc
		void draw(SDL_Surface * screen, const int & width, const int & height);

		
	private :
		//Sprite du bloc
		Sprite * m_sprite;
		//Body du bloc
		b2Body * m_body;

		//Position (en pixels) en X du bloc
		int m_posX;
		//Longueur en pixel du bloc
		int m_sizeX;
		//Type du bloc
		BlockType m_type;
		//Identifiant du bloc dans le niveau
		int m_id;

		//Si le bloc est GROUND, tous les points de la spline de base sont stockés ici
		std::vector<SDL_Rect*> m_points;
		//Tous les points du body sont stockés ici
		std::vector<b2Vec2> m_groundPoints;
		
		int m_maxSpeed; //utile ?

		//Min and Max size in pixels
		const double m_sizeXMin;
		const double m_sizeXMax;
		const double m_sizeYMin;
		const double m_y;

		//Hauteur du tunnel si le bloc est TUNNEL
		const double m_tunnelHeight;
		
		//Pour discrétiser la spline si le bloc est GROUND
		const float m_hillSegmentWidth;
};
#endif
