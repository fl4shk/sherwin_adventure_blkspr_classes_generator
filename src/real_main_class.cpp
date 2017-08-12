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
	while (next_char() != EOF)
	{
		parse();
	}

	return 0;
}


void RealMain::advance()
{
	if (next_char() == EOF)
	{
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
			return; \
		}
	#define VALUE(some_str)

	LIST_OF_PUNCT_TOKENS(VARNAME, VALUE)

	// An ident?
	else if (isalpha(next_char()) || (next_char() == '_'))
	{
		advance();

		while (isalnum(next_char()) || (next_char() == '_'))
		{
			next_str += next_char();
			advance();
		}

		if (next_str == "")
		{
		}
		

		LIST_OF_IDENT_LIKE_TOKENS(VARNAME, VALUE)

		#undef VARNAME
		#undef VALUE


		// If we haven't seen a symbol like this before...
		if (!sym_tbl().contains(next_str))
		{
			// ...Then create a new symbol
			Symbol to_insert(next_str, &Tok::Ident);

			sym_tbl().at(next_str) = to_insert;
		}


		set_next_sym_str(next_str);

		return;
	}

}

void RealMain::parse()
{
	const bool at_start = __at_start;
	__at_start = false;


	lex();

	if (at_start)
	{

		return;
	}
	
}
