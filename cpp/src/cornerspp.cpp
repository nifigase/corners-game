//============================================================================
// Name        : cornerspp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "boost/function.hpp"

#include "core/data.hpp"
#include "core/logic.hpp"

#include "cli/console.hpp"

namespace c = cornerspp::core;

int main() {

	c::select_factor_t level;
	//high:
//	level[0] = 8;
//	level[1] = 5;
//	level[2] = 3;
//	level[3] = 1;

	c::select_factor_t level2;
	//medium:
	level[0] = 7;
	level[1] = 3;
	level[2] = 1;
	level[3] = 0;
	//low:
	level2[0] = 7;
	level2[1] = 1;
	level2[2] = 0;
	level2[3] = 0;

	c::board b;

//	cornerspp::console::console_player p1(c::NW);
	c::auto_player p1(c::NW, level2); //stupid
	c::auto_player p2(c::SE, level);

//	for (c::caps_iterator it = b.caps_begin(p1); it != b.caps_end(p1); ++it) {
//		c::cell cl = *it;
//		std::cerr << "cell: " << cl.pos() << std::endl;
//	}

//	std::vector<c::move> moves;
//	c::moving::add_legal_moves(b, c::cell(b.color(c::NW), 2, 1), moves);

//	c::legal_moves(p1, b, moves);

//	std::cout << "legal moves: " << std::endl;
//	std::copy(moves.begin(), moves.end(), std::ostream_iterator<c::move>(std::cout));

	for (int i = 1; ; ++i) {

		std::cout << b;

		if (c::player_won(p1, b)) {
			std::cout << "p1 WON!!! " << std::endl;
			break;
		}
		if (c::player_won(p2, b)) {
			std::cout << "p2 WON!!! " << std::endl;
			break;
		}

		c::move m1 = p1.make_move(b);
		std::cout << "p1 move " << i << ": " << m1;
		b.apply(m1);

		c::move m2 = p2.make_move(b);
		std::cout << "p2 move " << i << ": " << m2;
		b.apply(m2);
	}

	return 0;
}
