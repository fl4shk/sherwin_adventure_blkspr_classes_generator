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
	#define VARNAME(some_tok) some_tok,
	#define VALUE(some_str) 

	LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE)


};



class Constant
{
public:		// typedefs
	typedef std::variant<LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE) 
		nullptr_t> ValueType;

	#undef VARNAME
	#undef VALUE

public:		// variables
	std::string name;
	ConstType type;
	ValueType value;


public:		// functions
	inline Constant()
	{
	}

	inline Constant(const std::string& s_name, ConstType s_type,
		ValueType s_value) : name(s_name), type(s_type), value(s_value)
	{
	}
	inline Constant(std::string&& s_name, ConstType s_type,
		ValueType s_value) : name(std::move(s_name)), type(s_type), 
		value(s_value)
	{
	}

	Constant(const Constant& to_copy) = default;
	Constant(Constant&& to_move) = default;

	Constant& operator = (const Constant& to_copy) = default;
	Constant& operator = (Constant&& to_move) = default;

	s64 get_s64() const;

	std::ostream& print_const_type(std::ostream& os) const;
	std::ostream& print_value(std::ostream& os) const;
};

class ConstVec
{
public:		// variables
	std::vector<Constant> vec;

public:		// functions
	inline bool contains(const std::string& some_name) const
	{
		size_t temp;
		return contains(some_name, temp);
	}
	bool contains(const std::string& some_name, size_t& ret_index) 
		const;
	

};

std::ostream& operator << (std::ostream& os, const ConstVec& to_print);

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
