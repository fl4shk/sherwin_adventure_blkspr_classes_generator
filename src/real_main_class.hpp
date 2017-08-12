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


#ifndef real_main_class_hpp
#define real_main_class_hpp

#include "misc_includes.hpp"


#include "symbol_table_class.hpp"

class RealMain
{
private:		// variables
	SymbolTable __sym_tbl;

	size_t __line_num = 0;

	int __next_char = ' ';
	PTok __next_tok = nullptr;
	std::string __next_sym_str;

	bool __at_start = true;
	bool __in_block = false, __in_sprite = false;

public:		// functions
	RealMain();

	int operator () ();



private:		// functions
	template<typename... ArgTypes>
	void err_suffix(ArgTypes&&... args) const
	{
		printerr(", On line ", line_num(), ":  ", args..., "\n");
		exit(1);
	}
	template<typename... ArgTypes>
	void err(ArgTypes&&... args) const
	{
		err_suffix("Error", args...);
	}

	template<typename... ArgTypes>
	void expected(ArgTypes&&... args) const
	{
		err("Expected ", args...);
	}
	void expected(PTok tok) const
	{
		expected("token of type \"", tok->str(), "\"!");
	}

	void advance();

	void lex();

	void parse();


	void handle_block();
	void handle_sprite();


	gen_getter_by_ref(sym_tbl)

	gen_getter_by_val(line_num)
	gen_getter_by_val(next_char)
	gen_getter_by_val(next_tok)
	gen_getter_by_con_ref(next_sym_str)

	gen_setter_by_val(line_num)
	gen_setter_by_val(next_char)
	gen_setter_by_val(next_tok)
	gen_setter_by_con_ref(next_sym_str)


};


#endif		// real_main_class_hpp
