#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "Bonus.hpp"
#include "Animal.hpp"
#include "Sprite.hpp"

#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif

class Level;

enum BlockType
{
	NOTHING = -1,
	GROUND = 0,
	PRECIPICE,
	STATION,
	TUNNEL,
	JUNCTION_UP,
	JUNCTION_DOWN,
	NB_BLOCK_TYPES
};

class Block
{
	public :
		Block(int sizeX, int id, Level* l, int speed = -1);
		Block(BlockType type, int sizeX, int id, Level* l, int speed = -1);
		virtual ~Block();

		//Attribue un type au bloc
		void setBlockType(BlockType type);

		//Construit le bloc
		virtual int build(b2World * world);

		//Crée l'image correspondant au type du bloc
		void createImage();

		//Modifie la position du bloc en x
		void scroll(const int & x);

		//Retourne le body du bloc
		b2Body * getBody();
		
		//Attribue m_body au bloc
		void setBody(b2Body * body);

		//Attribue une posX au bloc
		void setPosX(const int & x);

		//Ajoute un point dans m_points
		void addPoint(int x, int y);
		//Retourne l'identifiant du point à l'ordonnée la plus basse
		int getYMinPoint();
		//Retourne l'identifiant du point à l'ordonnée la plus grande
		int getYMaxPoint();

		//Retourne la position en x de début et de fin du bloc
		double getPosInMeters();
		double getEndBlockPosInMeters();

		//Dessine le bloc
		void setBonus(BonusType type, int x, int y);
		void setAnimal(const char * type, int x, int y);
		void draw(SDL_Surface * screen, const int & width, const int & height, b2World * world);

		void keyboard(const SDL_KeyboardEvent *event);

		
	protected :
		//Pointeur vers le niveau actuel
		Level * m_level;
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
		//Vitesse maximale que le joueur doit respecter. -1 si pas de vitesse maximale
		int m_maxSpeed;

		//Si le bloc est GROUND, tous les points de la spline de base sont stockés ici
		std::vector<SDL_Rect*> m_points;
		//Tous les points du body sont stockés ici
		std::vector<b2Vec2> m_groundPoints;
		
		
		//Bonus present in the block
		std::vector <Bonus*> m_bonus;
		//Animals present in the block
		std::vector <Animal*> m_animals;

		//Min and Max size in pixels
		double m_sizeXMinStation;
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
