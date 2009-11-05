
#include "qt/game_config.h"

#include "core/data.hpp"
#include "core/logic.hpp"

#ifndef GAME_SESSION_H_
#define GAME_SESSION_H_


class game_session {

private:
	class user_player : public c::player {
	public:
		user_player(c::corners corner);

		c::move make_move(const c::board& b) const;
	};

public:
	game_session(const game_config& config);

	const c::board& board() const { return board_; }
	c::board& board() { return board_; }
    const c::auto_player& auto_p() const { return auto_p_; }
    const c::player& user_p() const { return user_p_; }

    int cur_move() const { return cur_move_; }
    void inc_cur_move() { ++cur_move_; }

//    void reset(const game_config& config);
private:

	c::board board_;
	c::auto_player auto_p_;
	user_player user_p_;
	int cur_move_;
};

#endif
