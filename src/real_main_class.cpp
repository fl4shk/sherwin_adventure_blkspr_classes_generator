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
	lex();

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

	//switch (next_char())
	//{

	//}

	//// An ident?
	//else if (isalpha(next_char()) || (next_char() == '_'))
	//{
	//}

}
