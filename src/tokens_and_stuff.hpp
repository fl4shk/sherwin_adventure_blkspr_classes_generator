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


	// These don't really need string equivalents
	Number,
	Ident,


	// 
	Blank = -1,
};

#endif		// tokens_and_stuff_hpp
