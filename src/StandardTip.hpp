#ifndef __STANDARDTIP_HPP__
#define __STANDARDTIP_HPP__

#include "Block.hpp"
#include "Time.hpp"
#include "Passenger.hpp"
#include <list>
#include "ToolTip.hpp"

class StandardTip : public ToolTip
{
	public :
		StandardTip(const char* action, bool trigger, char* image);
		
	private :
		const char* m_action;
};
#endif
