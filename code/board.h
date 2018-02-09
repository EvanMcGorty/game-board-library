#pragma once
#include<utility>

#include"groups.h"

namespace raw_nodes
{

	template<typename...group_types>
	class board
	{
		
		std::tuple<group_types...> groups;

	};

}