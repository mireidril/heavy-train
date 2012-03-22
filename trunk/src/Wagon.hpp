#ifndef __WAGON_HPP__
#define __WAGON_HPP__

#include "Passenger.hpp"
#include "Station.hpp"
#include "PhysicalObject.hpp"
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* Represents a wagon of the train. Has passengers, a body, doors ...
*/
class Wagon{
    public :
	Wagon(int);
	~Wagon();
    // The train jumps with an impulsion of force N
    void jump(int);
    // Add the Passenger also creates the passenger joint. Call checkCapacity at the end.
	void addPassenger(Passenger*);
	// Eject the passenger by removing its joint, set the passenger’s “isEjected” to true. 
	void ejectPassenger(Passenger*);
	// Appellé à l'arrêt aux gares, avant l'ouverture des portes. 
	void deletePassenger(Passenger*);
	// Make the passenger take off at the station
	void takeOffPassenger(Passenger*, Station *);
	// Open the wagon’s doors
	void openDoors();
	// Close the wagon’s doors
	void closeDoors();
	// check if the wagon has reached max capacity, if it’s the case, close doors.
	void checkCapacity();
	// Return the position of the door of the wagon
	SDL_Rect * doorPosition();

	void build(b2World * world, double x, float high);
	b2Body * getBody(unsigned int i);
	std::vector<PhysicalObject *> getPhysicalObjects() { return m_physicalObjects; };

	//Réinitialise les valeurs des PhysicalObjects après un smooth pour coller au framerate
	void clearAllSmoothAngleAndPosition();

	void drawSprite(SDL_Surface * screen, const int & width, const int & height, const int & posXLocoSprite, const double & posXLocoBody);
	void setMotorSpeed(float speed);

	int getNbPassengerWagon();
   private :
	// Number of passengers that the wagon have when it quits the station
	int m_originalNumberOfPassengers;
	//Maximum number of passenger for the wagon
	int m_maxCapacity;
	// Number of passengers actually in the wagon (not ejected ones)
	int m_passengersCount;
	// Box2D objects fitting the wagon in the simulation (wagon and wheels)
	std::vector<PhysicalObject *>  m_physicalObjects; // 3 bodies -- 0: loco - 1: wheel1 - 2: wheel2
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	// Passengers in the wagon
	std::list<Passenger*> m_passengers;
	// Linking the wagon to the one ahead, or to the locomotive
	//b2RevoluteJoint *       m_joint;// pk une revolute joint???


	// Return true if doors are opened
	bool m_areDoorOpened;
};
#endif
