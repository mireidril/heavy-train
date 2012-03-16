#include "Station.hpp"

Station::Station(int sizeX, int posX, int id)
:Block(STATION, sizeX, posX, id )
{

}


void Station::setTime(int h, int m)
{
	m_theoricalArrivalTime = new Time(h, m, 0);
}
void Station::setLeaving(int leave)
{
	m_nbLeavingPassengers = leave;
}
void Station::setEnter(int enter)
{
	m_nbEnteringPassengers = enter;
}

void Station::initPassengers(){
	Passenger *p ;
	for(int i = 0; i< m_nbEnteringPassengers; i++ )
	{
		float x = rand()% (m_sizeX-5);
		std::cout<<"float rand :"<<x<<" \tm_posX + x = "<<m_posX+x<<std::endl;
		p = new Passenger(m_posX + x, 0.0f);
		m_passengers.push_back(p);
	}
}