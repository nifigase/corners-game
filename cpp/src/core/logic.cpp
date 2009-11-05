
#include <math.h>
#include <functional>
#include "core/logic.hpp"

namespace cornerspp { namespace core {

bool player_won(const player& p, const board& b) {

	corners target = opposite(p.corner());
	for (caps_iterator it = b.caps_begin(p); it != b.caps_end(p); ++it) {
		if (!b.pos_in_corner((*it).pos(), target))
			return false;
	}
	return true;
}

void legal_moves(const player& p, const board& b, std::vector<move>& moves) {
	for (caps_iterator it = b.caps_begin(p); it != b.caps_end(p); ++it) {
		cell c = *it;
		moving::add_legal_moves(b, *it, moves);
	}
	moving::unique(b, moves);
}

bool move_legal(const player& p, const board& b, const move& m) {
	move placeholder(b.get_cell(0,0));
	return move_legal(p, b, m, placeholder);
}

/**
 * In this version the resulting found move will be stored in placeholder variable
 */
bool move_legal(const player& p, const board& b, const move& m, move& placeholder) {
	std::vector<move> moves;
	legal_moves(p, b, moves);
	std::vector<move>::const_iterator it = std::find(moves.begin(), moves.end(), m);
	if (it == moves.end()) return false;
	placeholder = *it;
	return true;
}

move_maker::move_maker(const player& p, const player& enemy, const board& b, const select_factor_t select_factor) :
	p_(p), enemy_(enemy), initial_board_(b), b_(b),	select_factor_(select_factor),
	non_linear_coef_normalized_(calculate_non_linear_coef_normalized(b)) {}

/**
 * 2(DIM-1) + non_linear_coef_normalized_*((2(DIM-1)) ^ 2) = non_linear_coef_*2(DIM-1)
 */
float move_maker::calculate_non_linear_coef_normalized(const board& b) {
	size_t max_pos = b.DIM-1;
	return 2. * max_pos * (non_linear_coef - 1) / (4. * pow(max_pos, 2));
}

//will use simplest select factor for enemy, so it will not instantiate "our" maker in return
move move_maker::propose_enemy() const {
	select_factor_t enemy_select_factor;
	enemy_select_factor[0] = 1;
	enemy_select_factor[1] = 0;
	move_maker enemy_move_maker(enemy_, p_, b_, enemy_select_factor);
	return enemy_move_maker.propose();
}

/**
 * Distance to target corner. >=0. The more this value - the WORSE position is
 * TODO: add some non-linear coefficient
 */
move_maker::estimate_t
move_maker::pos_estimate(const position& pos) const {
	int dx, dy;
	if (p_.corner() == SE) {
		dx = pos.x();
		dy = pos.y();
	} else { //NW
		dx = (b_.DIM - pos.x() - 1);
		dy = (b_.DIM - pos.y() - 1);
	}
	int linear_est = dx + dy;
	if (linear_est <= 0) return static_cast<estimate_t>(0);
	return linear_est + non_linear_coef_normalized_ * pow(linear_est, 2);
}

/**
 * Estimates move by estimating position before and after it. Simple algorithm.
 * the more this value - the BETTER move is. May be < 0.
 */
template <>
move_maker::estimate_t
move_maker::estimate<1>(const move& m) {

	if (m.estimate_stage() >= 1) return m.estimate();

	estimate_t est = pos_estimate(m.first()) - pos_estimate(m.last());

	m.save_estimate(1, est);
//	std::cout << " - for " << m << "on 1: est=" << est << std::endl;
	return est;
}

/**
 * Estimates move. Complex algorithm.
 * Estimates the best possible (STAGE-1)'th legal move after this move and the best enemie's move.
 * the more this value - the BETTER move is.
 */
template <int STAGE>
move_maker::estimate_t
move_maker::estimate(const move& m) {

	if (m.estimate_stage() >= STAGE) return m.estimate();

	const estimate_t simple_est = estimate<STAGE-1>(m);
	estimate_t est = simple_est;

	b_.apply(m);

	move enemy_move = propose_enemy();
	b_.apply(enemy_move);

	std::vector<move> candidates;
	legal_moves(p_, b_, candidates);

	std::vector<move>::iterator hopped_end = std::remove_if(
			candidates.begin(), candidates.end(),
			boost::bind(boost::not2(&moving::is_hopped_through), _1, m)
	);

	if (hopped_end != candidates.begin()) { //otherwise unuseful move - will return simple est.

		std::vector<move>::iterator best = std::max_element(candidates.begin(), hopped_end, compare_moves<1>(*this)); //filter_candidates<STAGE-1> ?
		estimate_t best_est = estimate<STAGE-1>(*best);
		if (best_est > 0) est += best_est;
	}
	b_.revert(enemy_move);
	b_.revert(m);

//	std::cout << " - for " << m << "on " << STAGE << ": simple_est=" << simple_est << ", est=" << est << std::endl;

	m.save_estimate(STAGE, est);
	return est;
}

template <int STAGE>
struct move_maker::candidates_arranger {
	move_maker& mm_;
	explicit candidates_arranger(move_maker& mm) : mm_(mm) {}

	template <typename Iter>
	void operator()(Iter begin, Iter end) {

		if (mm_.select_factor_[STAGE-1] == 0) return;

		Iter lim = mm_.filter_candidates<STAGE>(begin, end);

//		std::cout << "On " << STAGE << " selected: " << std::distance(lim, end) << ": ";
//		std::copy(lim, end, std::ostream_iterator<move>(std::cout));

		if (std::distance(lim, end) > 1) {
			candidates_arranger<STAGE+1> next_arr(mm_);
			next_arr(lim, end);
		}
	}
};

template <>
struct move_maker::candidates_arranger<MAX_STAGES+1> {
	explicit candidates_arranger(move_maker& ) {}

	template <typename Iter>
	void operator()(Iter, Iter) {}
};

template <int STAGE, typename Iter>
Iter move_maker::filter_candidates(Iter begin, Iter end) {

	size_t to_select = select_factor_[STAGE-1];
	Iter middle = begin;
	size_t len = std::distance(begin, end);
	if (to_select < len) {
		std::advance(middle, len - to_select);
		std::nth_element(begin, middle, end, compare_moves<STAGE>(*this));
	}

//	std::cout << "filtered on stage " << STAGE << ": " << std::distance(middle, end) << " out of " << len;
//	std::copy(middle, end, std::ostream_iterator<move>(std::cout));

	return middle;
}

move move_maker::propose() {

	std::vector<move> candidates;
	legal_moves(p_, b_, candidates);

	typedef std::vector<move>::const_iterator citer_t;
	typedef std::vector<move>::iterator iter_t;

	citer_t beg = candidates.begin();
	citer_t end = candidates.end();

	//check for winning moves
	for (citer_t it = beg; it != end; ++it) {
		b_.apply(*it);
		bool won = player_won(p_, b_);
		b_.revert(*it);
		if (won) return *it;
	}

	//check for unlocking moves
	if (moving::has_locked_caps(b_, enemy_)) {
		for (citer_t it = beg; it != end; ++it) {
			bool has_locked = false;
			b_.apply(*it);
			has_locked = moving::has_locked_caps(b_, enemy_);
			b_.revert(*it);
			if (!has_locked) return *it;
		}
		//still locked!
	}

	//check for situation (happens at end of game) where ALL moves estimate (at first stage) to <= 0.
	//we need to mangle select coefs to force algorithm to consider ALL zero-moves at 1st stage and
	//perform 2nd stage (have select_factor_[1] > 0)
	std::unary_function<estimate_t, bool> positive = boost::bind(std::greater<estimate_t>, _1, .0);
	std::unary_function<estimate_t, bool> is_zero = boost::bind(std::equal_to<estimate_t>, _1, .0);

	//find positive, count 0s
	if (std::find_if(beg, end, positive) == end) {
		size_t zeros = std::count_if(beg, end, is_zero);

		//strip constantness from select_factor_, mangle it. Mangle back when done
	}

	//normal processing
	candidates_arranger<1> arranger(*this);
	arranger(candidates.begin(), candidates.end());

	return candidates.back();
}

move auto_player::make_move(const board& b) const {

	auto_player enemy(opposite(corner()), level_);
	move_maker maker(*this, enemy, b, level_);
	return maker.propose();
}

}} //NS
