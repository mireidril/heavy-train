#include "Station.hpp"

void Station::setTime(int h, int m){
	m_theoricalArrivalTime = new Time(h, m, 0);
}
void Station::setLeaving(int leave){
	m_nbLeavingPassengers = leave;
}
void Station::setEnter(int enter){
	m_nbEnteringPassengers = enter;
}