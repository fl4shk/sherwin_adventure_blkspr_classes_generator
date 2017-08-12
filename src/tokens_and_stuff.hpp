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

#define LIST_OF_TOKENS(VARNAME, VAL) \
\
/* "block" */ \
VARNAME(Block) VAL("block") \
\
\
/* "sprite" */ \
VARNAME(Sprite) VAL("sprite") \
\
/* "set_name" */ \
VARNAME(SetName) VAL("set_name") \
\
/* "const" */ \
VARNAME(Const) VAL("const") \
\
/* "(", ")" */ \
VARNAME(LParen) VAL("(") \
VARNAME(RParen) VAL(")") \
\
/* "{", "}" */ \
VARNAME(LBrace) VAL("{") \
VARNAME(RBrace) VAL("}") \
\
/* "=", ";", "," */ \
VARNAME(Equals) VAL("=") \
VARNAME(Semicolon) VAL(";") \
VARNAME(Comma) VAL(",") \
\
\
/* "__keyword_number", "__keyword_ident" */ \
VARNAME(Number) VAL("__keyword_number") \
VARNAME(Ident) VAL("__keyword_ident") \
\
/* "__keyword_blank" */ \
VARNAME(Blank) VAL("__keyword_blank")


#define VARNAME(some_tok) \
	extern const Tok some_tok;
#define VALUE(some_str) 

LIST_OF_TOKENS(VARNAME, VALUE)

#undef VARNAME
#undef VALUE

extern const std::vector<const Tok*> tok_vec;

#endif		// tokens_and_stuff_hpp
