#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

#include "PhysicalObject.hpp"
/*
* Animal qui est un obstacle.
*/
class Animal : public PhysicalObject
{
	public :
		//Constructeur
		Animal();
		//Destructeur
		virtual ~Animal();
		//When the animal gets in contact with the train, change the displayed image of the animal then delete it
		void die();
		//When the train whistles next to the animal, change the displayed image of the animal then delete it
		void flee();        
	private :
};
#endif