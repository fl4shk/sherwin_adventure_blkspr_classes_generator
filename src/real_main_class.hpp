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
private:		// classes
	class Block
	{
	public:		// variables
		std::string name;
	};

	class Sprite
	{
	public:		// variables
		std::string name;
	};

private:		// variables
	SymbolTable __sym_tbl;
	std::map<std::string, Block> __blk_map;
	std::map<std::string, Sprite> __spr_map;

	size_t __line_num = 1;

	int __next_char = ' ';
	PTok __next_tok = nullptr;
	std::string __next_sym_str;
	s64 __next_num = -1;

	bool __found_set_name = false;

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
		printerr("Error");
		err_suffix(args...);
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
	void need(PTok tok);

	void advance();

	void lex();

	void parse();


	void handle_block();
	void handle_sprite();

	
	
	template<typename MapThing>
	void handle_set_name(std::map<std::string, MapThing>& some_map, 
		const std::string& debug_thing, std::string& temp_name)
	{
		if (found_set_name())
		{
			err("Can't have more than one use of the \"set_name()\" ",
				"command!");
		}
		set_found_set_name(true);

		lex();

		need(&Tok::LParen);

		if (next_tok() == &Tok::Ident)
		{
			temp_name = sym_tbl().at(next_sym_str()).name();
			lex();
		}
		else
		{
			expected(&Tok::Ident);
		}

		if (some_map.count(temp_name) != 0)
		{
			err("Can't have more than one type of ", debug_thing,
				" called \"", temp_name, "\"!");
		}

		need(&Tok::RParen);
		need(&Tok::Semicolon);

	}


	bool next_tok_is_punct() const;



	gen_getter_by_ref(sym_tbl)
	gen_getter_by_ref(blk_map)
	gen_getter_by_ref(spr_map)

	gen_getter_by_val(line_num)
	gen_getter_by_val(next_char)
	gen_getter_by_val(next_tok)
	gen_getter_by_val(next_num)
	gen_getter_by_con_ref(next_sym_str)
	gen_getter_by_val(found_set_name)


	gen_setter_by_val(line_num)
	gen_setter_by_val(next_char)
	gen_setter_by_val(next_tok)
	gen_setter_by_con_ref(next_sym_str)
	gen_setter_by_val(next_num);
	gen_setter_by_val(found_set_name)


};


#endif		// real_main_class_hpp
