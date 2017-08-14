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

#define CASE_VARNAME(some_tok) case ConstType::some_tok:

s64 Constant::get_s64() const
{
	switch (type)
	{
		#define VARNAME(some_tok) \
			CASE_VARNAME(some_tok) \
				return std::get<some_tok>(value);
				break;


		#define VALUE(some_str)

		LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE)

		#undef VARNAME
		#undef VALUE
	}

	return 9001;
}

std::ostream& Constant::print_const_type(std::ostream& os) const
{
	switch (type)
	{
		#define VALUE(some_str) \
			osprintout(os, some_str); \
			break;

		LIST_OF_CONST_TYPE_TOKENS(CASE_VARNAME, VALUE)

		#undef VALUE
	}

	return os;
}

std::ostream& Constant::print_value(std::ostream& os) const
{
	switch (type)
	{
		#define VARNAME(some_tok) \
			CASE_VARNAME(some_tok) \
				osprintout(os, std::get<some_tok>(value)); \
				break;

		#define VALUE(some_str)

		LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE)

		#undef VARNAME
		#undef VALUE
	}

	return os;
}

#undef CASE_VARNAME

bool ConstVec::contains(const std::string& some_name, 
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

std::ostream& operator << (std::ostream& os, const ConstVec& to_print)
{
	if (to_print.vec.size() != 0)
	{
		printout("And constants\n");

		for (auto& citer : to_print.vec)
		{
			citer.print_const_type(os);
			osprintout(os, " \"", citer.name, "\" = ");
			citer.print_value(os);
			osprintout(os, "\n");
		}
	}

	return os;
}

