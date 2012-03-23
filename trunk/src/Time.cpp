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
		//convert time in seconds
		/*unsigned int timeInSeconds = this->m_seconds + this->m_minutes*60 + this->m_hours*3600 ;
		for (unsigned int i = 0 ; i<timeInSeconds ; i++){
			std::cout<<i/3600<<":"<<(i/60)%60<<":"<<i%60<<std::endl;	 
			clock_t end;
			end = clock () + 1 * CLOCKS_PER_SEC ;
			while (clock() < end) {}
		}*/
		
		    clock_t start, end;
    double elapsed;
    
    end = clock();       
    unsigned int timeInSeconds = this->m_seconds + this->m_minutes*60 + this->m_hours*3600  ;   
    start = (clock_t)timeInSeconds;                                        
    for (unsigned int i = 0 ; i<timeInSeconds ; i++){
    	elapsed = ((double)end - start) / CLOCKS_PER_SEC;
    	printf("%.2f secondes entre start et end.\n", elapsed);
    	this->m_seconds = (unsigned int)elapsed%60;
    	this->m_minutes = (unsigned int)(elapsed/60)%60; 
    	this->m_hours = (unsigned int)elapsed/3600; 
    }

	}
}


//Run counter-clockwise the Time if m_started = true
void Time::updateTimeCounter(){
	if(m_started == true){	
	//convert time in seconds
	unsigned int timeInSeconds = this->m_seconds + this->m_minutes*60 + this->m_hours*3600 ;
		for (unsigned int i = timeInSeconds ; i>0; i--){
			std::cout<<i/3600<<":"<<(i/60)%60<<":"<<i%60<<std::endl;	 
			clock_t end;
			end = clock () + 1 * CLOCKS_PER_SEC ;
			while (clock() < end) {}
		}
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

void Time::setHours(int hours){
	m_hours = hours;
}

void Time::setMinutes(int minutes){
	m_minutes = minutes;
}

void Time::setSeconds(int seconds){
	m_seconds = seconds;
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



