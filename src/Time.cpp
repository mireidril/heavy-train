#include "Time.hpp"

Time::Time(int hours, int min, int sec){
	m_hours = hours;
	m_minutes = min;
	m_seconds = sec;
}

Time::~Time(){
}


//Set the Time to zero
void Time::setToZero(){
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
}

//Start the Time. Set m_started to true
void Time::startTime(){
	m_started = true;
}
//Stop the time. Set m_started to false
void Time::stopTime(){
	m_started = false;
}
//Get the values of the Time
void Time::getTime(int & hours, int & min, int & sec){
	m_hours = hours;
	m_minutes = min;
	m_seconds = sec;
}

//Run clockwise the Time if m_started = true
void Time::updateTime(){
	if(m_started == true){
		clock_t start, end;
		int elapsed;
		start = clock();
		while(1)
		{
			end = clock();
			elapsed = ((int)end - start) / CLOCKS_PER_SEC;
			//std::cout << elapsed <<std::endl;
		}
	}
}


//Run counter-clockwise the Time if m_started = true
void Time::updateTimeCounter(){
	if(m_started == true){
	}
}


Time& Time::operator+=(const Time& time){
    m_seconds += time.m_seconds; 
    m_minutes += m_seconds / 60;
    m_seconds %= 60;
    m_minutes += time.m_minutes;
    m_hours += m_minutes / 60;
    m_minutes %= 60;
    m_hours += time.m_hours;
    return *this;
}


Time& Time::operator-=(const Time& time){
    m_seconds -= time.m_seconds; 
    m_minutes -= m_seconds / 60;
    m_seconds %= 60;
    m_minutes -= time.m_minutes;
    m_hours -= m_minutes / 60;
    m_minutes %= 60;
    m_hours -= time.m_hours;
    return *this;
}

bool Time::isEqual(Time const& time) const{
    if (m_hours == time.m_hours && m_minutes == time.m_minutes && m_seconds == time.m_seconds)
        return true;
    else
        return false;

}
bool Time::isLessThan(Time const& time) const{
    if (m_hours < time.m_hours)
        return true;
    else if (m_hours == time.m_hours && m_minutes < time.m_minutes)
        return true;
    else if (m_hours == time.m_hours && m_minutes == time.m_minutes && m_seconds < time.m_seconds)
        return true;
    else
        return false;
}

bool Time::isHigherThan(Time const& time) const{
    if (m_hours > time.m_hours)
        return true;
    else if (m_hours == time.m_hours && m_minutes > time.m_minutes)
        return true;
    else if (m_hours == time.m_hours && m_minutes == time.m_minutes && m_seconds > time.m_seconds)
        return true;
    else
        return false;
}

bool Time::isLessThanOrEqual(Time const& time) const{
    if (m_hours <= time.m_hours)
        return true;
    else if (m_hours == time.m_hours && m_minutes <= time.m_minutes)
        return true;
    else if (m_hours == time.m_hours && m_minutes == time.m_minutes && m_seconds <= time.m_seconds)
        return true;
    else
        return false;
}

bool Time::isHigherThanOrEqual(Time const& time) const{
    if (m_hours >= time.m_hours)
        return true;
    else if (m_hours == time.m_hours && m_minutes >= time.m_minutes)
        return true;
    else if (m_hours == time.m_hours && m_minutes == time.m_minutes && m_seconds >= time.m_seconds)
        return true;
    else
        return false;
}

int Time::getHours(){
	return m_hours;
}

int Time::getMinutes(){
	return m_minutes;
}

int Time::getSeconds(){
	return m_seconds;
}


Time operator+(Time const& time1, Time const& time2){
    Time tmp(time1);
    tmp += time2;
    return tmp;
}

Time operator-(Time const& time1, Time const& time2){
    Time tmp(time1);
    tmp -= time2;
    return tmp;
}

bool operator==(const Time& time1, const Time& time2){
	return time1.isEqual(time2);
}

bool operator<(const Time& time1, const Time& time2){
    if(time1.isLessThan(time2))
        return true;
    else
        return false;
}

bool operator>(const Time& time1, const Time& time2){
    if(time1.isHigherThan(time2))
        return true;
    else
        return false;
}

bool operator<=(const Time& time1, const Time& time2){
    if(time1.isLessThanOrEqual(time2))
        return true;
    else
        return false;
}

bool operator>=(const Time& time1, const Time& time2){
    if(time1.isHigherThanOrEqual(time2))
        return true;
    else
        return false;
}



