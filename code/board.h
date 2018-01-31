#pragma once
#include<utility>

#include"groups.h"

namespace raw_nodes
{

	template<typename last_group>
	constexpr size_t total_static_allocations()
	{
		return last_group::static_node_count();
	}

	template<typename first_group, typename...groups>
	constexpr size_t total_static_allocations()
	{
		return first_group::static_node_count()+total_static_allocations<groups...>();
	}

	template<bool exists>
	struct optional_allocator;

	template<>
	struct optional_allocator<true>
	{
		std::vector<std::unique_ptr<Node>> instance;
	};

	template<>
	struct optional_allocator<false>
	{

	};

	template<bool dynamic_allocations, typename...groups>
	class board
	{
		
		std::tuple<groups...> static_groups;

		std::array<std::unique_ptr<Node>,total_static_allocations<groups...>()> static_allocations;

		
	};

}