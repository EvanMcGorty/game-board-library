#pragma once
#include "points.h"

namespace raw_nodes
{

	//NodeList may be std::array<Node*,x>, std::vector<Node*>,
	template<typename NodeList>
	struct GenericLine
	{

		struct Key
		{
			size_t ind;
		};

		size_t connection_count(Key* p) const
		{
			assert(p->ind >= nodes.size());

			if (p->ind == 0 || p->ind == nodes.size() - 1)
			{
				return 1;
			}
			else
			{
				return 2;
			}
		}

		Connection nth_connection(Key* p, size_t n) const
		{
			assert(p->ind < nodes.size());

			if (p->ind == 0)
			{
				assert(n == 0);
				return nodes[1];
			}
			else if (p->ind == nodes.size() - 1)
			{
				assert(n == 0);
				return nodes[nodes.size() - 2]
			}
			else
			{
				assert(n <= 1);
				if (n == 0)
				{
					return nodes[p->ind - 1];
				}
				else //n==1
				{
					return nodes[p->ind + 1];
				}
			}
		}

		void all_connections(Key* p, std::vector<Connection>& target) const
		{
			assert(p->ind < nodes.size());

			if (p->ind == 0)
			{
				target.append(nodes[1]);
			}
			else if (p->ind == nodes.size() - 1)
			{
				target.appendnodes([nodes.size() - 2]);
			}
			else
			{
				target.append(nodes[p->ind - 1]);
				target.append(nodes[p->ind + 1]);
			}
		}

		NodeList nodes;
	};


	//yeah, i could re-copy and paste the class.
	//but i could also go work out. and start eating healthy.

	template<size_t length>
	//set sized line where each node is connected to the previous and next.
	//the first and last nodes are not connected.
	using Line = GenericLine <std::array<Node*, length>>;

	//dynamically sized line where each node is connected to the previous and next.
	//the first and last nodes are not connected.
	//this is really only intended for a varying its length at initialization.
	//that being said, if you're careful you can do stuff like push_back, insert, etc.
	//remember to re shift around keys if necessary. the class does not worry about this stuff.
	using GrowableLine = GenericLine<std::vector<Node*>>;



	//ToDo: implement a circular board, and a 2-D matrix-like board.
	//ToProbablyNotDo: implement a 3-D board.
	//ToDefinitelyNotDo: implement a generic, arbitrarily dimentioned board.

}