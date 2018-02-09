#pragma once
#include<utility>

#include"groups.h"

namespace raw_nodes
{

	template<bool dynamic_allocations, typename...group_types>
	class board
	{
		
		std::tuple<groups...> groups;

	};

}