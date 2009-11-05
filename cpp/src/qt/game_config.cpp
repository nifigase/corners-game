/*
 * game_config.cpp
 *
 *  Created on: Oct 18, 2009
 *      Author: andrew
 */

#include "game_config.h"

game_config::game_config() :
	my_color_(c::colors::yellow), enemy_color_(c::colors::green),
	my_corner_(c::NW), level_num_(1) {

	set_level(level_num_);
}

game_config::~game_config() {}

void game_config::set_level(int level) {
	switch (level) {
	case 1:
		level_[0] = 3;
		level_[1] = 0;
		break;
	case 2:
		level_[0] = 5;
		level_[1] = 2;
		level_[2] = 0;
		break;
	case 3:
		level_[0] = 7;
		level_[1] = 4;
		level_[2] = 2;
		level_[3] = 0;
		break;
	case 4:
		level_[0] = 7;
		level_[1] = 4;
		level_[2] = 1;
		level_[3] = 0;
		break;
	case 5:
		level_[0] = 8;
		level_[1] = 4;
		level_[2] = 2;
		level_[3] = 1;
		break;
	case 6:
		level_[0] = 8;
		level_[1] = 5;
		level_[2] = 3;
		level_[3] = 1;
		break;
	default:
		break;
	}
	level_num_ = level;
}

void game_config::set_my_corner(c::corners corner) {
	my_corner_ = corner;
}

void game_config::set_colors(c::colors::color_t my, c::colors::color_t enemy) {
	my_color_ = my;
	enemy_color_ = enemy;
}


const c::select_factor_t& game_config::level() const { return level_; }
int game_config::level_num() const { return level_num_; }
c::corners game_config::my_corner() const { return my_corner_; }
c::corners game_config::enemy_corner() const { return c::opposite(my_corner_); }
c::colors::color_t game_config::my_color() const { return my_color_; }
c::colors::color_t game_config::enemy_color() const { return enemy_color_; }
c::colors::color_t game_config::color_by_corner(c::corners corner) const {
	if (my_corner() == corner)
		return my_color();
	else
		return enemy_color();
}
