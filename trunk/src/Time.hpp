#ifndef __TIME_HPP__
#define __TIME_HPP__

#ifdef _WIN32
#include "time.h"
#else
#include <time.h>
#endif

#include <iostream>
#include <cstdio>


class Time
{
	public :
		//Constructor
		Time(int hours = 0, int min = 0, int sec = 0);
		//Destructor
		virtual ~Time();
		//Set the Time to zero
		void setToZero();
		//Start the Time. Set m_started to true
		void startTime();
		//Stop the time. Set m_started to false
		void stopTime();
		//Get the values of the Time
		void getTime(int & hours, int & min, int & sec);
		//Run clockwise the Time if m_started = true
		void updateTime(Time &time);
		//Run counter-clockwise the Time if m_started = true
		void updateTimeCounter(Time &time);
		//Operators
		Time& operator+=(const Time& time);
		Time& operator-=(const Time& time);
		
		bool isEqual(Time const& time) const;
    		bool isLessThan(Time const& time) const;
    		bool isHigherThan(Time const& time) const;
    		bool isLessThanOrEqual(Time const& time) const;
    		bool isHigherThanOrEqual(Time const& time) const;

		int getHours();
		int getMinutes();
		int getSeconds();
		
	private :
		//Hours
		unsigned int m_hours;
		//Minutes
		unsigned int m_minutes;
		//Seconds
		unsigned int m_seconds;
		//True if the Time is running
		bool m_started;
};


		Time operator+(const Time& time1, const Time& time2);
		Time operator-(const Time& time1, const Time& time2);
		bool operator==(const Time& time1, const Time& time2);
		bool operator<(const Time& time1, const Time& time2);
		bool operator>(const Time& time1, const Time& time2);
		bool operator<=(const Time& time1, const Time& time2);
		bool operator>=(const Time& time1, const Time& time2);
		
#endif
