/*
 * console.hpp
 *
 *  Created on: Oct 12, 2009
 *      Author: andrew
 */

#include <iostream>
#include "core/data.hpp"

#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

namespace cornerspp { namespace core {

std::ostream& operator<< (std::ostream& os, const position& pos) {
	return os << "[" << pos.x() << "," << pos.y() << "]";
}

std::ostream& operator<< (std::ostream& os, const move& m) {
	os << "move: ";
	std::copy(m.begin(), m.end(), std::ostream_iterator<position>(os, ", "));
	return os << std::endl;
}

std::ostream& operator<< (std::ostream& os, const board& b) {

	os << '*';
	for (size_t x = 0; x < b.DIM; ++x) os << x;
	os << std::endl;

	for (size_t y = 0; y < b.DIM; ++y) {
		os << y;
		for (size_t x = 0; x < b.DIM; ++x) {
			os << b[y][x];
		}
		os << std::endl;
	}
	return os;
}

} //NS core

namespace console {

namespace core = ::cornerspp::core;
using core::player;
using core::board;
using core::corners;
using core::move;
using core::position;

/**
 * Selects move proposed by move_maker
 */
class console_player : public player {
public:
	console_player(corners corner) : player(corner) {}

	move make_move(const board& b) const {
		while (true) {
			std::cout << "> enter move: x1 y1 x2 y2" << std::endl;

			size_t x1,y1,x2,y2;
			std::cin >> x1 >> y1 >> x2 >> y2;
			//TODO check for bounds

			std::vector<move> moves;
			core::legal_moves(*this, b, moves);

//			std::cout << "legal moves: " << std::endl;
//			std::copy(moves.begin(), moves.end(), std::ostream_iterator<move>(std::cout));

			move m(position(x1,y1), position(x2, y2));
			if (!core::move_legal(*this, b, m)) {
				std::cerr << "Move illegal" << std::endl;
				std::cout << b;
				continue;
			}

			return m;
		}
	}
};


}}
#endif /* CONSOLE_HPP_ */
