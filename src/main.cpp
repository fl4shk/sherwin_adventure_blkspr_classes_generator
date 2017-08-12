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


#include "misc_includes.hpp"


enum class Tok : int
{

	// "block"
	Block,


	// "sprite"
	Sprite,

	// "set_name"
	SetName,

	// "const"
	Const,

	// "(", ")"
	LParen,
	RParen,

	// "{", "}"
	LBrace,
	RBrace,

	// "=", ";", ","
	Equals,
	Semicolon,
	Comma,


	Number,
	Ident,


	// 
	Blank = -1,
};

// Temporarily make this a global variable
Tok next_tok;

class Symbol
{
private:		// variables
	std::string __name;
	Tok __token;

public:		// functions
	inline Symbol()
	{
	}
	inline Symbol(const std::string& s_name, Tok s_token) : __name(s_name),
		__token(s_token)
	{
	}

	gen_getter_by_con_ref(name)
	gen_getter_by_val(token)

	gen_setter_by_con_ref(name)
	gen_setter_by_rval_ref(name)
	gen_setter_by_val(token)

};

class SymbolTable
{
private:		// variables
	std::map<std::string, Symbol> __table;
	std::map<Tok, std::string> __tok_to_str_map;

public:		// functions
	SymbolTable();

	inline Symbol& at(const std::string& some_name)
	{
		return __table[some_name];
	}

	inline const Symbol& at(const std::string& some_name) const
	{
		return __table.at(some_name);
	}

	inline bool contains(const std::string& some_name) const
	{
		return (__table.count(some_name) == 1);
	}


private:		// functions


};

// Hardcoded list of built-in symbols
SymbolTable::SymbolTable()
{
}


int main(int argc, char** argv)
{
	return 0;
}

