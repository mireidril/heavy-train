#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

#include "PhysicalObject.hpp"
#include "Sprite.hpp"
/*
* Animal qui est un obstacle.
*/
class Animal : public PhysicalObject
{
	public :
		//Constructeur
		Animal(int type, int x, int y);
		//Destructeur
		virtual ~Animal();
		//When the animal gets in contact with the train, change the displayed image of the animal then delete it
		void die();
		//When the train whistles next to the animal, change the displayed image of the animal then delete it
		void flee();  
		
		void setType(const char * type);
		void setPosX(int x);
		void setPosY(int y);

		void build(b2World * world);
		void draw(SDL_Surface * screen, const int & width, const int & height);
		void scroll(int x);
		bool isDie();
	private :
		int m_posX;
		int m_posY;
		int m_typeAnimal;//0:tatou 1:coyote 2:vache
		char * m_type;
		Sprite * m_sprite;
		bool m_die;//Pour dire quand le train est mort à Bloc
};
#endif
