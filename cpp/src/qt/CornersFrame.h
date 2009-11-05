#ifndef CORNERSPP_H
#define CORNERSPP_H

#include <QtGui/QMainWindow>
#include <qlabel.h>
#include "ui_cornerspp.h"

#include "qt/game_config.h"
#include "qt/PlayBoard.h"

class CornersFrame : public QMainWindow
{
    Q_OBJECT

public:
    CornersFrame(QWidget *parent = 0);
    ~CornersFrame();

public slots:
    void display_game_status(game_status status);
    void display_msg(QString msg);
    void update_move_counter();
    void handle_user_player_won();
    void handle_auto_player_won();

private slots:
    void fileConfig();
    void fileNewGame();
    void helpAbout();

private:
    Ui::CornersFrameClass ui;

    game_config config_;
    PlayBoard* playBoard;

    QLabel* moveCounter;
};

#endif // CORNERSPP_H
