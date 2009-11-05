/*
 * PlayBoard.cpp
 *
 *  Created on: Oct 18, 2009
 *      Author: andrew
 */

#include <iostream> //TODO REMOVE me
#include <QtGui>
#include "PlayBoard.h"

PlayBoard::PlayBoard(const game_config& config, QWidget *parent) :
	QWidget(parent),
	status_(WaitingUserMove),
	session_(new game_session(config)),
	not_sel(c::position(0, session_->board().DIM)),
	selected_(not_sel),
	moveTimer_(new QTimer(this)),
	cur_move_(not_sel), cur_move_it_(cur_move_.end()) {

	moveTimer_->setSingleShot(true);
	connect(moveTimer_, SIGNAL(timeout()), this, SLOT(applyMove()));

	connect(this, SIGNAL(user_move_entered()), this, SLOT(perform_user_move()));
	connect(this, SIGNAL(move_performed()), this, SLOT(handle_move_performed()));
	connect(this, SIGNAL(user_player_won()), this, SLOT(handle_win()));
	connect(this, SIGNAL(auto_player_won()), this, SLOT(handle_win()));
}

PlayBoard::~PlayBoard() {}

void PlayBoard::reinit(const game_config& config) {

	session_.reset(new game_session(config));
	not_sel = c::position(0, session_->board().DIM);
	selected_ = not_sel;

	update();
	setStatus(WaitingUserMove);
}

void PlayBoard::setStatus(game_status status) {
	if (status == status_) return;
	status_ = status;
	emit game_status_changed(status_);
}

bool PlayBoard::game_in_process() const {
	if (status_ == NotRunning) return false;
	if (status_ == WaitingUserMove && session_->cur_move() == 1) return false;
	return true;
}

void PlayBoard::resizeEvent (QResizeEvent * event) {
	side_ = qMin(event->size().width(), event->size().height());
	capSize_ = side_ / session_->board().DIM;
}

void PlayBoard::mouseReleaseEvent (QMouseEvent * event) {
	if (event->button() != Qt::LeftButton) return;
	if (status_ != WaitingUserMove) return;

	if (event->pos().x() > side_ || event->pos().y() > side_) return;

	c::position eventPos(event->pos().x() * session_->board().DIM / side_, event->pos().y() * session_->board().DIM / side_);
	c::cell_data_t content = session_->board()[eventPos];

	if (content == session_->board().color(session_->user_p().corner())) {
		select(eventPos);
		return;
	}

	if (content != c::cell::no_caps) return;

	c::move m(selected_, eventPos);
	if (!c::move_legal(session_->user_p(), session_->board(), m, cur_move_)) {
		emit message_generated(tr("Move illegal"));
		return;
	}

	emit user_move_entered();
}

void PlayBoard::perform_user_move() {

	//animate move
	setStatus(PerformingUserMove);

	cur_move_it_ = cur_move_.begin();

	moveTimer_->start(300);
}

void PlayBoard::handle_move_performed() {

	deselect();
	if (status_ == PerformingUserMove) {
		if (c::player_won(session_->user_p(), session_->board())) {
			emit user_player_won();
			return;
		}
		makeMove();
		return;
	}
	if (status_ == PerformingMove) {
		if (c::player_won(session_->auto_p(), session_->board())) {
			emit auto_player_won();
			return;
		}
		session_->inc_cur_move();
		setStatus(WaitingUserMove);
		return;
	}
}

void PlayBoard::handle_win() {
	setStatus(NotRunning);
}

void PlayBoard::applyMove() {
	if (cur_move_it_ == cur_move_.end() || cur_move_it_+1 == cur_move_.end()) return;

	session_->board().applyPartial(*cur_move_it_, *(cur_move_it_+1));
	selected_ = *(cur_move_it_+1);

	repaintPos(*cur_move_it_);
	repaintPos(*(cur_move_it_+1));

	++cur_move_it_;
	if (cur_move_it_+1 == cur_move_.end()) {
		emit move_performed();
	} else {
		moveTimer_->start(nextMoveElemTimeout);
	}
}

void PlayBoard::makeMove() {

	setStatus(CalculatingMove);
	cur_move_ = session_->auto_p().make_move(session_->board());

	setStatus(PerformingMove);
	cur_move_it_ = cur_move_.begin();
	select(*cur_move_it_);

	moveTimer_->start(firstMoveElemTimeout);
}

void PlayBoard::deselect() {

	if (selected_ == not_sel) return;
	c::position prevSelected = selected_;
	selected_ = not_sel;
	repaintPos(prevSelected);
}

void PlayBoard::select(const c::position& pos) {

	c::position prevSelected = selected_;
	if (selected_ == pos) {
		selected_ = not_sel;
	} else {
		selected_ = pos;
		repaintPos(selected_);
	}
	if (prevSelected != not_sel)
		repaintPos(prevSelected);
}

void PlayBoard::repaintPos(const c::position& pos) {
	repaint(capSize_ * pos.x(), capSize_ * pos.y(), capSize_, capSize_);
}

void PlayBoard::paintEvent(QPaintEvent* /*event*/) {

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(0, 0);
	//painter.scale(static_cast<qreal>(width())/height(), 1);//static_cast<qreal>(height())/width());

	QColor bg(205,192,178);
	painter.fillRect(0, 0, width(), height(), bg);

	for (size_t r = 0; r < session_->board().DIM; ++r) {
		for (size_t c = 0; c < session_->board().DIM; ++c) {
			drawCell(painter, c::position(c, r));
		}
	}
}

void PlayBoard::drawCell(QPainter& painter, const c::position& pos) const {

	c::cell_data_t content = session_->board()[pos];

	int side = qMin(width(), height());
	int capSize = side / session_->board().DIM;
	int gap = capSize / 5;

	std::cout << "sz: " << capSize << ", pos.x = " << pos.x() << ", pos.y = " << pos.y() << std::endl;

	QColor yellowColor(255, 255, 0);
	QColor greenColor(94, 204, 91);
	QColor selColor(30, 30, 219);

	QColor divColor(162, 162, 162);

	QPen pen;
	QBrush brush(Qt::SolidPattern);

	switch(content) {
	case c::colors::green:
		pen.setColor(greenColor);
		brush.setColor(greenColor);
		break;
	case c::colors::yellow:
		pen.setColor(yellowColor);
		brush.setColor(yellowColor);
		break;
	case c::cell::no_caps:
		pen.setColor(painter.background().color());
		brush.setColor(painter.background().color());
		break;
	}

	if (pos == selected_)
		pen.setColor(selColor);

	painter.setPen(pen);
	painter.setBrush(brush);

	QRect rect(pos.x() * capSize + gap, pos.y() * capSize + gap, capSize - 2*gap, capSize - 2*gap);
	painter.drawEllipse(rect);
}
