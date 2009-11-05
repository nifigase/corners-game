/*
 * logic.hpp
 *
 *  Created on: Sep 5, 2009
 *      Author: andrew
 */

#include <algorithm>
#include <functional>
#include <vector>

#include "boost/bind.hpp"
#include "boost/functional.hpp"

#include "data.hpp"
#include "moving.hpp"

#ifndef LOGIC_HPP_
#define LOGIC_HPP_

namespace cornerspp { namespace core {

bool player_won(const player& p, const board& b);

void legal_moves(const player& p, const board& b, std::vector<move>& moves);

bool move_legal(const player& p, const board& b, const move& m, move& placeholder);
bool move_legal(const player& p, const board& b, const move& m);

class move_maker {
public:

	move_maker(const player& p, const player& enemy, const board& b, const select_factor_t select_factor);

private:
	const player& p_;
	const player& enemy_;

	const board& initial_board_;
	board b_; //copy, playground

	const select_factor_t& select_factor_;

	typedef float estimate_t;

	/**
	 * Non-linear coefficient in position estimation, to make home-positions worse
	 * (to stimulate the algorithm to pull caps from home faster)
	 * The estimate of 'homest' position will be non_linear_coef_ * linear_estimate
	 */
	const static float non_linear_coef = 1.5;

	const float non_linear_coef_normalized_; //normalized coef, depends on board's DIM

	static float calculate_non_linear_coef_normalized(const board& b);

	estimate_t pos_estimate(const position& pos) const;

	/**
	 * Estimates position after move. Algorithm of arbitrary depth.
	 */
	template <int STAGE>
	estimate_t estimate(const move& m);

	template <int STAGE>
	struct compare_moves {
		move_maker& mm_;
		explicit compare_moves(move_maker& mm) : mm_(mm) {}
		bool operator()(const move& m1, const move& m2) {
			return mm_.estimate<STAGE>(m1) < mm_.estimate<STAGE>(m2);
		}
	};

	template <int STAGE, typename Iter>
	Iter filter_candidates(Iter begin, Iter end);

	// cannot use member function templates, cause partial specialization is not supported for them

	template <int STAGE>
	struct candidates_arranger;

	move propose_enemy() const;

public:
	move propose();

};

/**
 * Selects move proposed by move_maker
 */
class auto_player : public player {
public:
	auto_player(corners corner, const select_factor_t& level) : player(corner), level_(level) {}

	move make_move(const board& b) const;

private:
	const select_factor_t& level_;
};

}}

#endif
