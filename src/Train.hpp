#ifndef __TRAIN_HPP__
#define __TRAIN_HPP__

#ifdef _WIN32
#include "Box2D/Box2D.h"
#include "SDL/SDL_mixer.h"
#else
#include <Box2D/Box2D.h>
#include <SDL/SDL_mixer.h>
#endif

#include "Sprite.hpp"
#include "Bonus.hpp"
#include "Wagon.hpp"

class Train
{
	public :

	//Constructeur
	Train();
	//Destructeur
	virtual ~Train();

	//Apply the force m_impetus to move the train
	void speedUp();
	//Apply the force -m_impetus to move the train
	void speedDown();
	//Apply the force m_jumpImpetus to make the train jumping
	void jump();
	//Make the train whistling
	void whistle();
	//When the train is stopped at a station, check if he is well-placed, at the center of the platform
	void checkPositionStation();
	//Update the vertical position of the Train’s sprite according to the physical simulation
	void updatePosition();
	//When the train derail, change the displayed image of the train then the player restart at the last station reached
	void derail();
	//Use a bonus
	void useBonus(const BonusType& bonus);
	//When the train get in contact with an animal, change the displayed image of the train then the player restart at the last station reached
	void crushAnimal();
	//When the train falls in a precipice, change the displayed image of the train then the player restart at the last station reached
	void die();
	//Return the total number of passengers in the train
	int getNbPassengers();
	//Ejects n passengers from the wagons
	void ejectPassengers(int n);
	// Take off n passengers at the Station
	void takeOffPassengers(int n, Station *);
	//Check if the train is shaken
	void isShaken();
	// dessiner le train
	void drawSprite(SDL_Surface * screen, const int & width, const int & height);
	// Creer la physique du train
	void build(b2World * world);

	void keyboard( const SDL_KeyboardEvent *event);



   private :
	//Current speed of the train
	int m_actualSpeed;
	//Maximal speed that the train is able to reach
	int m_maxSpeed;
	//Maximal backward speed that the train is able to reach
	int m_maxSpeedBack;
	//Horizontal impetus applied to move the train
	int m_impetus;
	//Vertical impetus applied to make the train jumping
	int m_jumpImpetus;

	//Physical bodies of the steam engine
	std::vector<b2Body * > m_bodies; // 3 bodies -- 0: loco - 1: wheel1 - 2: wheel2
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	float32 m_speed;
	float32 m_hz;
	b2Joint* m_joints[2];// pour joindre les wagons et le train

	//Box2D actor that allows the train to react physically
	//GameActor* m_actor;
	//Sprite of the steam engine
	Sprite* m_sprite;
	//Above 0 if the train is currently using an accelerator bonus. Decrease at each frame
	int m_usingTimeAccelerator;
	//The two wagons of the game
	std::vector<Wagon*> m_wagons;
	//Increase if the train is shaken
	int m_shaken;
	// Sound of the tchoutchou
	Mix_Chunk * m_tchoutchouSound;	
	// Sounf of the scared passengers
	Mix_Chunk * m_passengerSound;



};
#endif
