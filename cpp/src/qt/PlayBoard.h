/*
 * PlayBoard.h
 *
 *  Created on: Oct 18, 2009
 *      Author: andrew
 */

#include <memory>

#include <QtGui/QWidget>
#include "qt/game_config.h"
#include "qt/game_session.hpp"

#include "core/data.hpp"
#include "core/logic.hpp"

#ifndef PLAYBOARD_H_
#define PLAYBOARD_H_

class PlayBoard : public QWidget
{
    Q_OBJECT

public:
    PlayBoard(const game_config& config, QWidget *parent = 0);
    ~PlayBoard();

    /**
     * init new game
     */
    void reinit(const game_config& config);

    game_status get_game_status() const { return status_; }
    bool game_in_process() const;

    const game_session& session() const { return *session_; }

signals:
	/**
	 * Fired when game becomes in_process or not in_process
	 */
	void game_status_changed(game_status status);
	void message_generated(QString msg);

protected:
	void paintEvent(QPaintEvent *event);
	int heightForWidth (int w) const { return w; }

	void mouseReleaseEvent (QMouseEvent * event);
	void resizeEvent (QResizeEvent * event);

private slots:
	void applyMove();

signals:
	void user_move_entered();
	void move_performed();
	void user_player_won();
	void auto_player_won();

private slots:
	void perform_user_move();
	void handle_move_performed();
	void handle_win();

private:
	void drawCell(QPainter& painter, const c::position& pos) const;

	void repaintPos(const c::position& pos);
	void select(const c::position& pos);
	void deselect();
	void setStatus(game_status status);

	void makeMove();

	static const int firstMoveElemTimeout = 500;
	static const int nextMoveElemTimeout = 700;

    game_status status_;
    std::auto_ptr<game_session> session_;

    c::position not_sel;
    c::position selected_;

    bool isSelected() const {
    	return selected_ != not_sel;
    }

    //size-dependent cache
    int side_, capSize_;

    QTimer* moveTimer_;
    c::move cur_move_; //move which is currently being performed
    c::move::path_iter_t cur_move_it_;
};

#endif /* PLAYBOARD_H_ */
