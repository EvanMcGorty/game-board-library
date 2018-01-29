#pragma once
#include<utility>

#include"groups.h"

template<typename...groups>
class board
{

	std::tuple<groups...>
};
