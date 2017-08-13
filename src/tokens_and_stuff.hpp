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

#define LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE) \
/* "u32", etc. */ \
VARNAME(SizeT) VALUE("size_t") \
VARNAME(U32) VALUE("u32") \
VARNAME(S32) VALUE("s32") \
VARNAME(U16) VALUE("u16") \
VARNAME(S16) VALUE("s16") \
VARNAME(U8) VALUE("u8") \
VARNAME(S8) VALUE("s8") \


#define LIST_OF_IDENT_LIKE_TOKENS(VARNAME, VALUE) \
/* "block" */ \
VARNAME(Block) VALUE("block") \
\
/* "sprite" */ \
VARNAME(Sprite) VALUE("sprite") \
\
/* "set_name" */ \
VARNAME(SetName) VALUE("set_name") \
\
/* "set_filename_stuff" */ \
VARNAME(SetFilenameStuff) VALUE("set_filename_stuff") \
\
/* "const" */ \
VARNAME(Const) VALUE("const") \
\
LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE)


#define LIST_OF_PUNCT_TOKENS(VARNAME, VALUE) \
/* "(", ")" */ \
VARNAME(LParen) VALUE("(") \
VARNAME(RParen) VALUE(")") \
\
/* "{", "}" */ \
VARNAME(LBrace) VALUE("{") \
VARNAME(RBrace) VALUE("}") \
\
/* "=", ";", "," */ \
VARNAME(Equals) VALUE("=") \
VARNAME(Semicolon) VALUE(";") \
VARNAME(Comma) VALUE(",") \


#define LIST_OF_EXTRA_KEYWORD_TOKENS(VARNAME, VALUE) \
/* "Number", "Identifier" */ \
VARNAME(Number) VALUE("Number") \
VARNAME(Ident) VALUE("Identifier") \
\
/* "Blank" */ \
VARNAME(Blank) VALUE("Blank")



#define LIST_OF_TOKENS(VARNAME, VALUE) \
LIST_OF_IDENT_LIKE_TOKENS(VARNAME, VALUE) \
LIST_OF_PUNCT_TOKENS(VARNAME, VALUE) \
LIST_OF_EXTRA_KEYWORD_TOKENS(VARNAME, VALUE)




class Tok;
typedef const Tok* PTok;

// Why is this class holding all the instances of itself?  Jeez.  It works
// fine; don't get me wrong.  It's just a little weird.
class Tok
{
private:		// variables
	std::string __str;

public:		// constants
	#define VARNAME(some_tok) \
		some_tok,
	#define VALUE(some_str) 

	static const Tok LIST_OF_TOKENS(VARNAME, VALUE) Dummy;

	#undef VARNAME
	#undef VALUE

	static const std::vector<PTok> tok_vec;

public:		// functions
	inline Tok()
	{
	}
	inline Tok(const std::string& s_str) : __str(s_str)
	{
	}
	inline Tok(std::string&& s_str) : __str(std::move(s_str))
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
		__str = to_copy.__str;
		return *this;
	}

	inline Tok& operator = (Tok&& to_move)
	{
		__str = std::move(to_move.__str);
		return *this;
	}

	inline bool operator == (const Tok& to_cmp) const
	{
		return (str() == to_cmp.str());
	}
	inline bool operator != (const Tok& to_cmp) const
	{
		return (str() != to_cmp.str());
	}

	inline bool operator < (const Tok& to_cmp) const
	{
		return (str() < to_cmp.str());
	}

	gen_getter_by_con_ref(str)

	gen_setter_by_con_ref(str)
	gen_setter_by_rval_ref(str)

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
			return hash<string>()(token.str());
		}
	};
}


#endif		// tokens_and_stuff_hpp
