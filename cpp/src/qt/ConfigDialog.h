#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui/QDialog>
#include "qt/ui/ui_configdialog.h"
#include "qt/game_config.h"

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog(const game_config& config, QWidget *parent = 0);
    ~ConfigDialog();

    const game_config& config() const { return config_; }

private slots:
	void ok();
	void cancel();

private:
    Ui::ConfigDialogClass ui;

    game_config config_;
};

#endif // CONFIGDIALOG_H
