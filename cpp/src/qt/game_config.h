/*
 * game_config.h
 *
 *  Created on: Oct 18, 2009
 *      Author: andrew
 */
#include "core/data.hpp"

#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_

namespace c = cornerspp::core;

enum game_status { CalculatingMove, PerformingMove, WaitingUserMove, PerformingUserMove, NotRunning };

class game_config {
public:
	game_config();

	virtual ~game_config();

	void set_level(int level);
	void set_my_corner(c::corners corner);
	void set_colors(c::colors::color_t my, c::colors::color_t enemy);

	const c::select_factor_t& level() const;
	int level_num() const;
	c::corners my_corner() const;
	c::corners enemy_corner() const;
	c::colors::color_t my_color() const;
	c::colors::color_t enemy_color() const;

	c::colors::color_t color_by_corner(c::corners c) const;

private:

	c::colors::color_t my_color_;
	c::colors::color_t enemy_color_;

	c::corners my_corner_;

	c::select_factor_t level_;
	int level_num_;
};

#endif /* GAME_CONFIG_H_ */
