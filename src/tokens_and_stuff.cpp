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

#include "tokens_and_stuff.hpp"

#define VARNAME(some_tok) \
	Tok::some_tok
#define VALUE(some_str) \
	(some_str),

const Tok LIST_OF_TOKENS(VARNAME, VALUE) Tok::Dummy;

#undef VARNAME
#undef VALUE



#define VARNAME(some_tok) \
	&Tok::some_tok,
#define VALUE(some_str)


const std::vector<PTok> Tok::tok_vec
({
	LIST_OF_TOKENS(VARNAME, VALUE)
});


#undef VARNAME
#undef VALUE
