#ifndef __STATION_HPP__
#define __STATION_HPP__

#include "Block.hpp"
#include "Time.hpp"
#include "Passenger.hpp"

class Station : public Block
{
	public :
		// Make the passengers take a step, and when they arrive at destination, add the passenger to the train or suppress it if it goes out of the station
		void updatePassengers();
		
		void setTime(int h, int m);
		void setLeaving(int leave);
		void setEnter(int enter);
	private :
		// Theorical time at which the player has to arrive
		Time* m_theoricalArrivalTime;
		// Percentage of passengers leaving at this station
		int m_nbLeavingPassengers;
		// Percentage of maximal capacity of the train entering at this station
		int m_nbEnteringPassengers;
		// Passengers vector on the station
		std::vector<Passenger*> m_passengers;
};
#endif