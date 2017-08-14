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


#ifndef blk_spr_base_stuff_hpp
#define blk_spr_base_stuff_hpp

#include "misc_includes.hpp"

#include "symbol_table_class.hpp"


enum class ConstType
{
	#define VARNAME(some_tok) \
		some_tok,

	#define VALUE(some_str) 

	LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE)

	#undef VARNAME
	#undef VALUE

};
class Constant
{
public:		// variables
	std::string name;
	ConstType type;
	s64 value;

public:		// functions
	inline Constant()
	{
	}

	inline Constant(const std::string& s_name, ConstType s_type,
		s64 s_value) : name(s_name), type(s_type), value(s_value)
	{
	}
	inline Constant(std::string&& s_name, ConstType s_type,
		s64 s_value) : name(std::move(s_name)), type(s_type), 
		value(s_value)
	{
	}

	Constant(const Constant& to_copy) = default;
	Constant(Constant&& to_move) = default;

	Constant& operator = (const Constant& to_copy) = default;
	Constant& operator = (Constant&& to_move) = default;

	void print_const_type();
};

class ConstVec
{
public:		// variables
	std::vector<Constant> vec;

public:		// functions
	inline bool has_constant(const std::string& some_name) const
	{
		size_t temp;
		return has_constant(some_name, temp);
	}
	bool has_constant(const std::string& some_name, size_t& ret_index) 
		const;

};


class BlkSprBase
{
public:		// variables
	std::string name, filename_stuff;

	//std::map<std::string, Constant> cmap;
	//std::vector<Constant> cvec;
	ConstVec cvec;

public:		// functions
	
};



class Block : public BlkSprBase
{
public:		// variables
};

class Sprite : public BlkSprBase
{
public:		// variables
};

#endif		// blk_spr_base_stuff_hpp
