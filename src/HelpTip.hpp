#ifndef __HELPTIP_HPP__
#define __HELPTIP_HPP__

#include "ToolTip.hpp"

class HelpTip : public ToolTip
{
	public :
		HelpTip(int numbloc, bool trigger, const char* image);
		
	private :
		int m_numblock;
};
#endif
