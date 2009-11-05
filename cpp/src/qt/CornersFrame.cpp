#include "qt/CornersFrame.h"
#include "qt/ConfigDialog.h"
#include "qmessagebox.h"

CornersFrame::CornersFrame(QWidget *parent)
    : QMainWindow(parent), config_()
{
	ui.setupUi(this);

	playBoard = new PlayBoard(config_, this);
	moveCounter = new QLabel(statusBar());

	setCentralWidget(playBoard);
	statusBar()->addPermanentWidget(moveCounter, 0);

	connect(ui.actionNew_game, SIGNAL(triggered()), this, SLOT(fileNewGame()));
	connect(ui.actionConfig, SIGNAL(triggered()), this, SLOT(fileConfig()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(helpAbout()));

	connect(playBoard, SIGNAL(game_status_changed(game_status)), this, SLOT(display_game_status(game_status)));
	connect(playBoard, SIGNAL(message_generated(QString)), this, SLOT(display_msg(QString)));

	connect(playBoard, SIGNAL(move_performed()), this, SLOT(update_move_counter()));
	connect(playBoard, SIGNAL(user_player_won()), this, SLOT(handle_user_player_won()));
	connect(playBoard, SIGNAL(auto_player_won()), this, SLOT(handle_auto_player_won()));

	display_game_status(playBoard->get_game_status());
	update_move_counter();
}

void CornersFrame::handle_user_player_won() {
	QMessageBox::information(this, tr("You Win!"),
			tr("<p align=center><b>Congratulations!</b><br/>"
				"Now you may heighten the level and try again"));
}

void CornersFrame::handle_auto_player_won() {
	QMessageBox::information(this, tr("You Loose :("),
			tr("<p align=center><b>You must admit that...</b><br/>"
				"computer does some things much better then you, and playing corners is just another such thing.<br/>"
				"May be you should just try again..."));
}

void CornersFrame::update_move_counter() {
	moveCounter->setText(tr("Move: %1").arg(playBoard->session().cur_move()));
}

void CornersFrame::display_msg(QString msg) {
	statusBar()->showMessage(msg);
}

void CornersFrame::display_game_status(game_status status) {

	QString msg;

	switch (status) {
	case CalculatingMove:
		msg = tr("Calculating move, please wait...");
		break;
	case PerformingMove:
		msg = tr("Performing move: you can see it");
		break;
	case WaitingUserMove:
		msg = tr("Make a move");
		break;
	case PerformingUserMove:
		msg = tr("Performing your move: you can see it");
		break;
	case NotRunning:
		msg = tr("Game over. You may start a new one");
		break;
	}
	statusBar()->showMessage(msg);
}

void CornersFrame::fileConfig() {

	if (playBoard->game_in_process()) {
		if (QMessageBox::question(this, tr("Game in process"),
				tr("If you change config values the game will restart. Continue?"),
				QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Cancel)
				return;
	}

	ConfigDialog cd(config_, this);
	int ret = cd.exec();
	if (ret != 0) {
		config_ = cd.config(); //save copy
		playBoard->reinit(config_);
		update_move_counter();
	}
}

void CornersFrame::fileNewGame() {
	playBoard->reinit(config_);
	update_move_counter();
}

void CornersFrame::helpAbout() {
	QMessageBox::about(
		this, tr("About Corners"),
		tr("<p align=center><b>Corners</b> is a strategy game.<br/>"
			"Your mission is to move all your caps to the opposite corner.<br/>"
			"In file -> config you may set your color, corner, board size, level, etc.<br/>"
			"Enjoy! (c) Andrew, 2009</p>"
		));
}

CornersFrame::~CornersFrame()
{

}
