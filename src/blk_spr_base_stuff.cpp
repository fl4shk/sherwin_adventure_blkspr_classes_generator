// This file is part of Sherwin's Adventure Block and Sprite Classes
// Generator.
// 
// Copyright 2017 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Block and Sprite Classes Generator is free software:
// you can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
// 
// Sherwin's Adventure Block and Sprite Classes Generator is distributed in
// the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure Block and Sprite Classes Generator.  If not,
// see <http://www.gnu.org/licenses/>.


#include "blk_spr_base_stuff.hpp"

void Constant::print_const_type()
{
	switch(type)
	{
		#define VARNAME(some_tok) \
			case ConstType::some_tok:
		#define VALUE(some_str) \
			printout(some_str); break;

		LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE)

		#undef VARNAME
		#undef VALUE
	}
}


bool ConstVec::has_constant(const std::string& some_name, 
	size_t& ret_index) const
{
	for (ret_index=0; ret_index<vec.size(); ++ret_index)
	{
		if (vec.at(ret_index).name == some_name)
		{
			return true;
		}
	}

	return false;
}

