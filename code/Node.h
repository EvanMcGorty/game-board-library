#pragma once
#include<string>
#include<vector>

namespace raw_nodes
{

	//the data held by each node
	//todo: template everything out so that the type held can be chosen.
	struct Data
	{
		std::string val;
	};

	class Node;


	//a "to but not necessarily back" connection between two nodes.
	//only represents the access to the next node. a node might be
	//connected to another node but not contain an instance of a
	//connection. it just needs to be able to produce the connection.
	struct Connection
	{
		Connection()
		{
			to = nullptr;
		}

		Connection(Node* a)
		{
			to = a;
		}

		//There is no good reason for passing connections around instead of raw pointers.
		//in older versions of this code, connections were virtual and could have keys to groups.
		Node* to;
	};

	//virtual class representing something that has Connections and Data
	class Node
	{
	public:

		//access to data
		virtual Data& data() = 0;

		//const access to data
		virtual Data const& data() const = 0;

		//how many other nodes this node is connected to
		virtual size_t connection_count() const = 0;

		//gets connection number "n" in the enumeration
		virtual Connection nth_connection(size_t n) const = 0;

		//gives all connections to "target"
		virtual void all_connections(std::vector<Connection>& target) const = 0;
	};

}