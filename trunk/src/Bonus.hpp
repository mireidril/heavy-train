#ifndef __BONUS_HPP__
#define __BONUS_HPP__

#include "Sprite.hpp"
enum BonusType
{
	STAR_DUST = 0,
	ACCELERATOR
};

class Bonus
{
	public :
		Bonus();
		~Bonus();
		//Return the type of the Bonus
		BonusType getType();
		//Return m_used
		bool isUsed();
		void setType(BonusType type);
		void setPosX(int x);
		void setPosY(int y);
	private :
		int m_posX;
		int m_posY;
		// Bonus type
		BonusType m_type;
		// False if the bonus is not used yet
		bool m_used;
		// Sprite of the bonus
		Sprite* m_sprite;
		//Acceleration value if accelerator is used
		static int m_speedAccelerator;
};
#endif