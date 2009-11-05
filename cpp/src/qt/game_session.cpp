
#include <stdexcept>

#include "qt/game_session.hpp"

game_session::user_player::user_player(c::corners corner) : c::player(corner) {}

c::move game_session::user_player::make_move(const c::board& b) const {
	throw std::logic_error("user_player::make_move must not be called");
}

game_session::game_session(const game_config& config) :
	board_(config.color_by_corner(c::NW), config.color_by_corner(c::SE)),
	auto_p_(config.enemy_corner(), config.level()),
	user_p_(config.my_corner()),
	cur_move_(1) {}
