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


#ifndef tokens_and_stuff_hpp
#define tokens_and_stuff_hpp

#include "misc_includes.hpp"

class Tok
{
private:		// variables
	std::string __name;

public:		// functions
	inline Tok()
	{
	}
	inline Tok(const std::string& s_name) : __name(s_name)
	{
	}
	inline Tok(std::string&& s_name) : __name(std::move(s_name))
	{
	}
	inline Tok(const Tok& to_copy)
	{
		*this = to_copy;
	}
	inline Tok(Tok&& to_move)
	{
		*this = std::move(to_move);
	}

	inline Tok& operator = (const Tok& to_copy)
	{
		__name = to_copy.__name;
		return *this;
	}

	inline Tok& operator = (Tok&& to_move)
	{
		__name = std::move(to_move.__name);
		return *this;
	}

	inline bool operator == (const Tok& to_cmp) const
	{
		return (name() == to_cmp.name());
	}
	inline bool operator != (const Tok& to_cmp) const
	{
		return (name() != to_cmp.name());
	}

	inline bool operator < (const Tok& to_cmp) const
	{
		return (name() < to_cmp.name());
	}

	gen_getter_by_con_ref(name)

	gen_setter_by_con_ref(name)
	gen_setter_by_rval_ref(name)

};
namespace std
{
	template<>
	struct hash<Tok>
	{
		typedef Tok argument_type;
		typedef size_t result_type;
		result_type operator () (const argument_type& token) const
		{
			//return std::hash<std::string>(token.name());
			return hash<string>()(token.name());
		}
	};
}

#define LIST_OF_TOKENS(VAR_NAME_MACRO, VALUE_MACRO) \
\
/* "block" */ \
VAR_NAME_MACRO(Block) VALUE_MACRO("block") \
\
\
/* "sprite" */ \
VAR_NAME_MACRO(Sprite) VALUE_MACRO("sprite") \
\
/* "set_name" */ \
VAR_NAME_MACRO(SetName) VALUE_MACRO("set_name") \
\
/* "const" */ \
VAR_NAME_MACRO(Const) VALUE_MACRO("const") \
\
/* "(", ")" */ \
VAR_NAME_MACRO(LParen) VALUE_MACRO("(") \
VAR_NAME_MACRO(RParen) VALUE_MACRO(")") \
\
/* "{", "}" */ \
VAR_NAME_MACRO(LBrace) VALUE_MACRO("{") \
VAR_NAME_MACRO(RBrace) VALUE_MACRO("}") \
\
/* "=", ";", "," */ \
VAR_NAME_MACRO(Equals) VALUE_MACRO("=") \
VAR_NAME_MACRO(Semicolon) VALUE_MACRO(";") \
VAR_NAME_MACRO(Comma) VALUE_MACRO(",") \
\
\
/* "__keyword_number", "__keyword_ident" */ \
VAR_NAME_MACRO(Number) VALUE_MACRO("__keyword_number") \
VAR_NAME_MACRO(Ident) VALUE_MACRO("__keyword_ident") \
\
/* "__keyword_blank" */ \
VAR_NAME_MACRO(Blank) VALUE_MACRO("__keyword_blank")


#define VAR_NAME_MACRO(some_tok) \
	extern Tok some_tok;
#define VALUE_MACRO(some_str) 


#endif		// tokens_and_stuff_hpp
