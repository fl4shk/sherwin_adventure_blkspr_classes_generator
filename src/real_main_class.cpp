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
	advance();
	lex();
	while (next_tok() != &Tok::Blank)
	{
		parse();
	}

	for (auto& block_iter : blk_map())
	{
		printout("Block with name, filename_stuff:  \"", 
			block_iter.second.name, "\", \"", 
			block_iter.second.filename_stuff, "\"\n");

		if (block_iter.second.cvec.vec.size() == 0)
		{
			continue;
		}

		printout("And constants\n");

		for (auto& citer : block_iter.second.cvec.vec)
		{
			citer.print_const_type();
			printout(" \"", citer.name, "\" = ", citer.value, "\n");
		}
	}

	for (auto& sprite_iter : spr_map())
	{
		printout("Sprite with name, filename_stuff:  \"", 
			sprite_iter.second.name, "\", \"", 
			sprite_iter.second.filename_stuff, "\"\n");

		if (sprite_iter.second.cvec.vec.size() == 0)
		{
			continue;
		}

		printout("And constants\n");

		for (auto& citer : sprite_iter.second.cvec.vec)
		{
			citer.print_const_type();
			printout(" \"", citer.name, "\" = ", citer.value, "\n");
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
	LIST_OF_SINGLE_CHAR_OPERATOR_TOKENS(VARNAME, VALUE)

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

		return;

	}

	// BitLsl
	if (next_char() == '<')
	{
		advance();

		if (next_char() == '<')
		{
			advance();
			set_next_tok(&Tok::BitLsl);
		}
		else
		{
			expected("\"<<\" but got \"", next_str, "\"!");
		}

		return;
	}

	// BitLsr or BitAsr
	if (next_char() == '>')
	{
		advance();

		if (next_char() == '>')
		{
			advance();

			if (next_char() == '>')
			{
				advance();
				set_next_tok(&Tok::BitAsr);
			}
			else
			{
				set_next_tok(&Tok::BitLsr);
			}
		}
		else
		{
			expected("\">>\" or \">>>\" but got \"", next_str, "\"!");
		}
		
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
	handle_block_or_sprite(blk_map(), "block", 
		&RealMain::handle_block_specifics);

}

void RealMain::handle_sprite()
{
	handle_block_or_sprite(spr_map(), "sprite", 
		&RealMain::handle_sprite_specifics);
}



void RealMain::handle_const(BlkSprBase& some_blkspr)
{
	lex();

	ConstType some_const_type;

	if (next_tok() == nullptr)
	{
	}


	#define VARNAME(some_tok) \
		else if (next_tok() == &Tok::some_tok) \
		{ \
			some_const_type = ConstType::some_tok; \
		}
	#define VALUE(some_str) 

	LIST_OF_CONST_TYPE_TOKENS(VARNAME, VALUE)

	#undef VARNAME
	#undef VALUE

	else
	{
		expected("token of type \"size_t\", \"u32\", \"s32\", etc.!");
	}
	

	for (;;)
	{
		printout("handle_const():  ", next_tok()->str(), "\n");
		handle_const_contents(some_blkspr, some_const_type);

		//lex();

		printout("handle_const():  ", next_tok()->str(), "\n");

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

void RealMain::handle_const_contents(BlkSprBase& some_blkspr,
	ConstType some_const_type)
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

	need(&Tok::Equals);

	//if (some_cvec.count(temp_name) != 0)
	if (some_blkspr.cvec.contains(temp_name))
	{
		err("In one block or sprite, can't have more than one constant ",
			"with the identifer \"", temp_name, "\"!");
	}


	//if (next_tok() == &Tok::Number)
	//{
	//	Constant to_insert;
	//	to_insert.type = some_const_type;
	//	to_insert.value = next_num();
	//	some_cvec[temp_name] = to_insert;
	//}
	//else
	//{
	//	expected(&Tok::Number);
	//}

	Constant to_insert;
	to_insert.name = temp_name;
	to_insert.type = some_const_type;
	to_insert.value = handle_expr(some_blkspr.cvec);
	some_blkspr.cvec.vec.push_back(std::move(to_insert));
}


s64 RealMain::handle_term(ConstVec& some_cvec)
{
	s64 ret = handle_factor(some_cvec);

	//const auto old_next_tok = next_tok();

	while ((next_tok() == &Tok::Mult) || (next_tok() == &Tok::Div))
	{
		const auto old_next_tok = next_tok();
		lex();

		if (old_next_tok == &Tok::Mult)
		{
			ret *= handle_factor(some_cvec);
		}
		else // if (old_next_tok == &Tok::Div)
		{
			ret /= handle_factor(some_cvec);
		}
	}

	//if (next_tok() == &Tok::Mult)
	//{
	//	ret *= handle_expr(some_cvec);
	//}
	//else if (next_tok() == &Tok::Div)
	//{
	//	ret /= handle_expr(some_cvec);
	//}
	
	return ret;
}

s64 RealMain::handle_factor(ConstVec& some_cvec)
{
	if (next_tok() == &Tok::Number)
	{
		s64 ret = next_num();
		lex();
		return ret;
	}
	else if (next_tok() == &Tok::Ident)
	{
		size_t index;
		if (some_cvec.contains(next_sym_str(), index))
		{
			s64 ret = some_cvec.vec.at(index).value;
			lex();
			return ret;
		}
		else
		{
			expected("existing constant of name \"", next_sym_str(),
				"\"!");
		}
	}

	s64 ret;

	if (next_tok() != &Tok::LParen)
	{
		expected("token of type \"Number\" or \"Ident\" or \"(\"!");
	}

	need(&Tok::LParen);

	ret = handle_expr(some_cvec);

	need(&Tok::RParen);

	return ret;
}

s64 RealMain::handle_expr(ConstVec& some_cvec)
{
	const auto old_next_tok = next_tok();

	s64 ret;

	if ((old_next_tok == &Tok::Plus) || (old_next_tok == &Tok::Minus))
	{
		lex();

		if (old_next_tok == &Tok::Plus)
		{
			ret = handle_term(some_cvec);
		}
		else // if (old_next_tok == &Tok::Minus)
		{
			ret = -handle_term(some_cvec);
		}
	}
	else
	{
		ret = handle_term(some_cvec);
	}

	if ((next_tok() == &Tok::Plus) || (next_tok() == &Tok::Minus))
	{
		ret += handle_expr(some_cvec);
	}

	return ret;

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

