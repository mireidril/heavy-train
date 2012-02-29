#ifndef __PASSENGER_HPP__
#define __PASSENGER_HPP__

#include "PNJ.hpp"

/*
* Passenger, a PNJ that go into train.
* His behavior is really special : he’s a static object at the station and we move him manualy with updatePassengers called by the Station.
* When he enters a wagon, we create a Joint linking him to the wagon floor.
* His is made of a circle at the base and a rectangle for the up of the body.
*/
class Passenger : public PhysicalObject
{
    public :
		//Constructor
		Passenger(double x, double y);
		//Destructor
		virtual ~Passenger();
		//Suppress m_joint
		void breakJoint();
		// Makes the passenger take a step at the speed m_speed
		void step();
		// Switch the passenger to a static body
		void switchStatic();
		// Switch the passenger to a dynamic body, creates the joint
		void switchDynamic();
		// Set the destination point
		void setDestinationPoint( double x, double y );
        
	private :
		//Joint linking the body of the passenger to the wagon
		b2DistanceJoint * m_joint;
		// Destination point that the passenger wants to reach
		b2Vec2 * m_destination;
		// Speed of the passenger on the station
		float m_speed;
		// Is he ejected or not ?
		bool m_isEjected;
};
#endif