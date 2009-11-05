/*
 * detail.hpp
 *
 *  Created on: Sep 7, 2009
 *      Author: andrew
 */
#include <vector>
#include "core/data.hpp"

#ifndef DETAIL_HPP_
#define DETAIL_HPP_

namespace cornerspp { namespace core { namespace moving {

using ::cornerspp::core::board;
using ::cornerspp::core::position;
using ::cornerspp::core::cell;
using ::cornerspp::core::move;

void add_legal_moves(const board& b, const cell& c, std::vector<move>& moves);

bool has_locked_caps(const board& b, const player& p);

void unique(const board& b, std::vector<move>& moves);

/**
 * Is move m is hopped through last position of move target
 */
bool is_hopped_through(const move& m, const move& target);

}}}

#endif /* DETAIL_HPP_ */
