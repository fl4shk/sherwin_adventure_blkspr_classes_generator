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

	return 0;
}

void RealMain::need(PTok tok)
{
	if (next_tok() == tok)
	{
		printout("need(), before lex():  ", next_tok()->str(), "\n");
		lex();
		printout("need(), after lex():  ", next_tok()->str(), "\n");
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
	//printout("start of lex():  next_char():  ", (char)next_char(), "\n");
	//advance();
	//printout("lex():  next_char():  ", (char)next_char(), "\n");

	while (isspace(next_char()))
	{
		//printout("Advancing...\n");
		//printout("lex():  next_char():  ", (char)next_char(), "\n");
		advance();
	}

	//printout("lex() before if (next_char() == EOF):  next_char():  ", 
	//	(char)next_char(), "\n");
	if (next_char() == EOF)
	{
		set_next_tok(&Tok::Blank);
		return;
	}

	std::string next_str;
	next_str += next_char();

	//printout("lex() before if (next_str == \"\"):  next_str, ",
	//	"next_char():  ", next_str, ", ", (char)next_char(), "\n");
	if (next_str == "")
	{
	}

	#define VARNAME(some_tok) \
		else if (next_str == Tok::some_tok.str()) \
		{ \
			/*
			if (next_tok() != nullptr) \
			{ \
				printout("lex():  Setting next_tok:  \"", \
					next_tok()->str(), "\" \"", next_str, "\"\n"); \
			}
			*/ \
			set_next_tok(&Tok::some_tok); \
			advance(); \
			/*
			printout("lex() after punct:  next_char():  \"", \
				(char)next_char(), "\"\n"); \
			*/ \
			return; \
		}
	#define VALUE(some_str)


	LIST_OF_PUNCT_TOKENS(VARNAME, VALUE)

	#undef VARNAME

	//printout("lex() before An ident?:  ", (char)next_char(), ", ", 
	//	isalpha(next_char()), ", ", (next_char() == '_'), "\n");

	// An ident?
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
			printout("Creating a new symbol....\n");
			Symbol to_insert(next_str, &Tok::Ident);

			sym_tbl().at(next_str) = to_insert;
		}


		set_next_tok(&Tok::Ident);
		set_next_sym_str(next_str);

		return;
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
	set_found_set_name(false);

	need(&Tok::LBrace);

	Block to_insert;

	while ((next_tok() != &Tok::RBrace) && (next_tok() != &Tok::Blank))
	{
		if (next_tok() == &Tok::SetName)
		{
			std::string temp_name;
			handle_set_name(temp_name);
			to_insert.name = std::move(temp_name);
		}
	}


	need(&Tok::RBrace);

	blk_map()[to_insert.name] = to_insert;


	if (!found_set_name())
	{
		expected("an instance of \"set_name\"");
	}
}

void RealMain::handle_sprite()
{
	set_found_set_name(false);

	need(&Tok::LBrace);

	Sprite to_insert;

	while ((next_tok() != &Tok::RBrace) && (next_tok() != &Tok::Blank))
	{
		if (next_tok() == &Tok::SetName)
		{
			std::string temp_name;
			handle_set_name(temp_name);
			to_insert.name = std::move(temp_name);
		}
	}

	need(&Tok::RBrace);

	spr_map()[to_insert.name] = to_insert;


	if (!found_set_name())
	{
		expected("an instance of \"set_name\"");
	}
}


void RealMain::handle_set_name(std::string& temp_name)
{
	set_found_set_name(true);

	printout("handle_set_name():  ", next_tok()->str(), "\n");

	lex();
	printout("handle_set_name(), before need():  ", next_tok()->str(), 
		"\n");

	need(&Tok::LParen);

	printout("handle_set_name(), after need():  ", next_tok()->str(), 
		"\n");

	if (next_tok() == &Tok::Ident)
	{
		printout("I found an identifier for set_name()!\n");
		lex();
	}
	else
	{
		expected(&Tok::Ident);
	}


	need(&Tok::RParen);
	printout("handle_set_name():  ", next_tok()->str(), "\n");
	need(&Tok::Semicolon);

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

