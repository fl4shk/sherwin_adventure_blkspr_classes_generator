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

#include "real_main_class.hpp"


RealMain::RealMain()
{
}

int RealMain::operator () ()
{
	//while (next_char() != EOF)
	advance();
	lex();
	while (next_tok() != &Tok::Blank)
	{
		parse();
	}

	for (auto& block_iter : blk_map())
	{
		printout("Block with name \"", block_iter.second.name, "\"\n");

		if (block_iter.second.cmap.size() == 0)
		{
			continue;
		}

		printout("And constants\n");

		for (auto& citer : block_iter.second.cmap)
		{
			printout("\"", citer.first, "\" = ", citer.second, "\n");
		}
	}

	for (auto& sprite_iter : spr_map())
	{
		printout("Sprite with name \"", sprite_iter.second.name, "\"\n");
		
		if (sprite_iter.second.cmap.size() == 0)
		{
			continue;
		}

		printout("And constants\n");

		for (auto& citer : sprite_iter.second.cmap)
		{
			printout("\"", citer.first, "\" = ", citer.second, "\n");
		}
	}

	return 0;
}

void RealMain::need(PTok tok)
{
	if (next_tok() == tok)
	{
		//printout("need(), before lex():  ", next_tok()->str(), "\n");
		lex();
		//printout("need(), after lex():  ", next_tok()->str(), "\n");
	}
	else
	{
		printerr("need():  ");
		expected(tok);
	}
}

void RealMain::advance()
{
	if (next_char() == EOF)
	{
		set_next_tok(&Tok::Blank);
		return;
	}

	set_next_char(getchar());

	if (next_char() == '\n')
	{
		++__line_num;
	}
}



void RealMain::lex()
{
	while (isspace(next_char()))
	{
		advance();
	}

	if (next_char() == EOF)
	{
		set_next_tok(&Tok::Blank);
		return;
	}

	std::string next_str;
	next_str += next_char();

	if (next_str == "")
	{
	}

	#define VARNAME(some_tok) \
		else if (next_str == Tok::some_tok.str()) \
		{ \
			set_next_tok(&Tok::some_tok); \
			advance(); \
			return; \
		}
	#define VALUE(some_str)


	LIST_OF_PUNCT_TOKENS(VARNAME, VALUE)

	#undef VARNAME

	// Find an identifier
	if (isalpha(next_char()) || (next_char() == '_'))
	{
		//printout("lex():  An ident?\n");
		next_str = "";
		next_str += next_char();
		advance();

		while (isalnum(next_char()) || (next_char() == '_'))
		{
			next_str += next_char();
			advance();
		}

		//printout("lex():  next_str, next_char():  ", next_str, ", ",
		//	(char)next_char(), "\n");

		if (next_str == "")
		{
		}
		
		#define VARNAME(some_tok) \
			else if (next_str == Tok::some_tok.str()) \
			{ \
				set_next_tok(&Tok::some_tok); \
				return; \
			}

		LIST_OF_IDENT_LIKE_TOKENS(VARNAME, VALUE)

		#undef VARNAME
		#undef VALUE


		// If we haven't seen a symbol like this before...
		if (!sym_tbl().contains(next_str))
		{
			// ...Then create a new symbol
			//printout("Creating a new symbol....\n");
			Symbol to_insert(next_str, &Tok::Ident);

			sym_tbl().at(next_str) = to_insert;
		}


		set_next_tok(&Tok::Ident);
		set_next_sym_str(next_str);

		return;
	}

	// Find a constant number
	if (isdigit(next_char()))
	{
		set_next_num(0);

		do
		{
			set_next_num((next_num() * 10) + (next_char() - '0'));
			advance();
		} while (isdigit(next_char()));

		set_next_tok(&Tok::Number);

	}

}

void RealMain::parse()
{
	printout("parse():  ", next_tok()->str(), "\n");

	if (next_tok() == &Tok::Block)
	{
		//printout("I found a \"block\" token!\n");
		lex();
		handle_block();
	}

	else if (next_tok() == &Tok::Sprite)
	{
		//printout("I found a \"sprite\" token!\n");
		lex();
		handle_sprite();
	}

	else if (next_tok() == &Tok::Blank)
	{
		printout("Done.\n");
	}

	else
	{
		expected("token of type \"block\" or \"sprite\"!");
	}
	
}

void RealMain::handle_block()
{
	handle_block_or_sprite(blk_map(), "block", 
		&RealMain::handle_block_specifics);

}

void RealMain::handle_sprite()
{
	handle_block_or_sprite(spr_map(), "sprite", 
		&RealMain::handle_sprite_specifics);
}



void RealMain::handle_const(std::map<std::string, s64>& some_cmap)
{
	for (;;)
	{
		handle_const_contents(some_cmap);

		lex();

		if (next_tok() == &Tok::Semicolon)
		{
			break;
		}
		else if (next_tok() == &Tok::Comma)
		{
			continue;
		}
		else
		{
			expected("token of type \";\" or \",\"!");
		}
	}
	lex();

}

void RealMain::handle_const_contents(std::map<std::string, s64>& some_cmap)
{
	lex();

	std::string temp_name;

	if (next_tok() == &Tok::Ident)
	{
		temp_name = sym_tbl().at(next_sym_str()).name();
		lex();
	}
	else
	{
		expected(&Tok::Ident);
	}

	if (some_cmap.count(temp_name) != 0)
	{
		err("In one block or sprite, can't have more than one constant ",
			"with the identifer \"", temp_name, "\"!");
	}

	need(&Tok::Equals);

	if (next_tok() == &Tok::Number)
	{
		some_cmap[temp_name] = next_num();
	}
	else
	{
		expected(&Tok::Number);
	}
}

void RealMain::handle_block_specifics(Block& to_insert)
{
	printout("handle_block_specifics()\n");
	printout(line_num(), "\t\t");
	printout(next_tok()->str(), " ");
	lex();
	printout("\t\t", line_num(), "\t\t");
	printout(next_tok()->str(), "\n");
}
void RealMain::handle_sprite_specifics(Sprite& to_insert)
{
	printout("handle_sprite_specifics()\n");
	printout(line_num(), "\t\t");
	printout(next_tok()->str(), " ");
	lex();
	printout("\t\t", line_num(), "\t\t");
	printout(next_tok()->str(), "\n");

}



bool RealMain::next_tok_is_punct() const
{
	if (next_tok() == nullptr)
	{
	}
	
	#define VARNAME(some_tok) \
		else if (next_tok() == &Tok::some_tok) \
		{ \
			return true; \
		}
	#define VALUE(some_str) 
	
	LIST_OF_PUNCT_TOKENS(VARNAME, VALUE)

	#undef VARNAME
	#undef VALUE


	return false;
}

