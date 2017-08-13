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
		ConstType type;
		s64 value;

	public:		// functions
		inline void print_const_type()
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
	};



	class Block
	{
	public:		// variables
		std::string name, filename_stuff;

		std::map<std::string, Constant> cmap;
	};

	class Sprite
	{
	public:		// variables
		std::string name, filename_stuff;

		std::map<std::string, Constant> cmap;
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

	bool __found_set_name = false, __found_set_filename_stuff = false;

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
	void handle_block_or_sprite(std::map<std::string, MapThing>& some_map,
		const std::string& debug_thing, 
		void (RealMain::* extras_func)(MapThing& to_insert))
	{
		set_found_set_name(false);
		set_found_set_filename_stuff(false);

		need(&Tok::LBrace);

		MapThing to_insert;

		while ((next_tok() != &Tok::RBrace) && (next_tok() != &Tok::Blank))
		{
			if (next_tok() == &Tok::SetName)
			{
				std::string temp_name;
				//handle_set_name(blk_map(), "block", temp_name);
				handle_set_name(some_map, debug_thing, temp_name);
				to_insert.name = std::move(temp_name);
			}
			else if (next_tok() == &Tok::SetFilenameStuff)
			{
				std::string temp_filename_stuff;

				handle_set_filename_stuff(some_map, debug_thing,
					temp_filename_stuff);
				to_insert.filename_stuff = std::move(temp_filename_stuff);
			}
			else if (next_tok() == &Tok::Const)
			{
				handle_const(to_insert.cmap);
			}
			else
			{
				((*this).*extras_func)(to_insert);
			}
		}

		need(&Tok::RBrace);

		some_map[to_insert.name] = to_insert;

		if (!found_set_name())
		{
			expected("an instance of \"set_name\"");
		}
		if (!found_set_filename_stuff())
		{
			expected("an instance of \"set_filename_stuff\"");
		}
	}


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

	template<typename MapThing>
	void handle_set_filename_stuff
		(std::map<std::string, MapThing>& some_map, 
		const std::string& debug_thing, std::string& temp_filename_stuff)
	{
		if (found_set_filename_stuff())
		{
			err("Can't have more than one use of the ",
				"\"set_filename_stuff()\" command!");
		}

		set_found_set_filename_stuff(true);

		lex();

		need(&Tok::LParen);

		if (next_tok() == &Tok::Ident)
		{
			temp_filename_stuff = sym_tbl().at(next_sym_str()).name();
			lex();
		}
		else
		{
			expected(&Tok::Ident);
		}

		for (auto& iter : some_map)
		{
			if (iter.second.filename_stuff == temp_filename_stuff)
			{
				err("Can't have more than one type of ", debug_thing,
					" called \"", temp_filename_stuff, "\"!");
			}
		}

		need(&Tok::RParen);
		need(&Tok::Semicolon);

	}



	void handle_const(std::map<std::string, Constant>& some_cmap);
	void handle_const_contents(std::map<std::string, Constant>& some_cmap,
		ConstType some_const_type);

	void handle_block_specifics(Block& to_insert);
	void handle_sprite_specifics(Sprite& to_insert);

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
	gen_getter_by_val(found_set_filename_stuff)


	gen_setter_by_val(line_num)
	gen_setter_by_val(next_char)
	gen_setter_by_val(next_tok)
	gen_setter_by_con_ref(next_sym_str)
	gen_setter_by_val(next_num);
	gen_setter_by_val(found_set_name)
	gen_setter_by_val(found_set_filename_stuff)


};


#endif		// real_main_class_hpp
