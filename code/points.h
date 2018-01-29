#pragma once
#include"Node.h"
#include<array>

namespace raw_nodes
{

	class Point : public Node
	{
	public:
		Data& data() override
		{
			return contents;
		}

		Data const& data() const override
		{
			return contents;
		}

		size_t connection_count() const override
		{
			return connections.size();
		}

		Connection nth_connection(size_t n) const override
		{
			return connections[n];
		}

		void all_connections(std::vector<Connection>& target) const override
		{
			target.reserve(target.size() + connections.size());
			for (auto c : connections)
			{
				target.push_back(c);
			}
		}

		Data contents;
		std::vector<Connection> connections;
	};

	//a point that has a set amount of connections
	//e.g. point == vector, split == array
	template<size_t dirs>
	class Split : public Node
	{
		Data& data() override
		{
			return contents;
		}

		Data const& data() const override
		{
			return contents;
		}

		size_t connection_count() const override
		{
			return connections.size();
		}

		Connection nth_connection(size_t n) const override
		{
			return connections[n];
		}

		void all_connections(std::vector<Connection>& target) const override
		{
			target.reserve(target.size() + connections.size());
			for (auto c : connections)
			{
				target.push_back(c);
			}
		}

		Data contents;
		std::array<Connection, dirs> connections;
	};

	template<>
	class Split<0> : public Node
	{
		Data& data() override
		{
			return contents;
		}

		Data const& data() const override
		{
			return contents;
		}

		size_t connection_count() const override
		{
			return 0;
		}

		Connection nth_connection(size_t n) const override
		{
			std::array<Connection, 0> temp = {};
			temp[n]; //this has no connections so nth_connection should always cause an out of range.
		}

		void all_connections(std::vector<Connection>& target) const override
		{
			//do nothing
		}

		Data contents;
	};

	using Lone = Split<0>;


	template<typename Group_t, typename NodeType>
	class Held : public Node
	{
		static_assert(std::is_base_of<Node, NodeType>::value, "NodeType must derive from Node");

	public:
		Data& data() override
		{
			return other.data();
		}

		Data const& data() const override
		{
			return other.data();
		}

		size_t connection_count() const override
		{
			return other.connection_count() + owner->connection_count(key);
		}

		Connection nth_connection(size_t n) const override
		{
			auto c = other.connection_count()
				if (c <= n)
				{
					return owner->nth_connection(key, owner->connection_count() - c);
				}
				else
				{
					return other.nth_connection(c);
				}
		}

		void all_connections(std::vector<Connection>& target) const override
		{
			other.all_connections(target);
			owner->all_connections(key, target);
		}

		typename Group_t::Key key;

		NodeType other;

		Group_t* owner;
	};

}