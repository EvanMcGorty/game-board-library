#pragma once
#include<utility>

#include"groups.h"

namespace raw_nodes
{

	template<bool dynamic_allocations, typename...groups>
	class board
	{

		std::tuple<groups...> static_groups;

	};

}