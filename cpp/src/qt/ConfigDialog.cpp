
#include "qmessagebox.h"
#include "ConfigDialog.h"

#include "core/data.hpp"

namespace c = cornerspp::core;

ConfigDialog::ConfigDialog(const game_config& config, QWidget *parent)
    : QDialog(parent), config_(config) {

	ui.setupUi(this);
	connect(ui.buttonOK, SIGNAL(clicked()), this, SLOT(ok()));
	connect(ui.buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));

	//set defaults
	ui.clrG->setChecked(config_.my_color() == c::colors::green);
	ui.clrY->setChecked(config_.my_color() == c::colors::yellow);

	ui.cornerNW->setChecked(config_.my_corner() == c::NW);
	ui.cornerSE->setChecked(config_.my_corner() == c::SE);

	ui.level->setSliderPosition(config_.level_num());
}

void ConfigDialog::ok() {
	config_.set_level(ui.level->value());
	config_.set_my_corner(ui.cornerNW->isChecked() ? c::NW : c::SE);
	if (ui.clrG->isChecked()) config_.set_colors(c::colors::green, c::colors::yellow);
	if (ui.clrY->isChecked()) config_.set_colors(c::colors::yellow, c::colors::green);

	done(1);
}

void ConfigDialog::cancel() { done(0); }

ConfigDialog::~ConfigDialog() {}

