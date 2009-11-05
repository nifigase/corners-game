/********************************************************************************
** Form generated from reading ui file 'configdialog.ui'
**
** Created: Mon Nov 2 01:47:40 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigDialogClass
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QLabel *label_3;
    QSlider *level;
    QLabel *label_2;
    QGroupBox *horizontalGroupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *clrY;
    QRadioButton *clrG;
    QGroupBox *horizontalGroupBox1;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *cornerNW;
    QRadioButton *cornerSE;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;

    void setupUi(QDialog *ConfigDialogClass)
    {
        if (ConfigDialogClass->objectName().isEmpty())
            ConfigDialogClass->setObjectName(QString::fromUtf8("ConfigDialogClass"));
        ConfigDialogClass->setWindowModality(Qt::ApplicationModal);
        ConfigDialogClass->resize(247, 158);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigDialogClass->sizePolicy().hasHeightForWidth());
        ConfigDialogClass->setSizePolicy(sizePolicy);
        formLayoutWidget = new QWidget(ConfigDialogClass);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 231, 111));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setMargin(11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer);

        line = new QFrame(formLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setWindowModality(Qt::NonModal);
        line->setEnabled(true);
        line->setMinimumSize(QSize(160, 1));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(3, QFormLayout::FieldRole, line);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_3);

        level = new QSlider(formLayoutWidget);
        level->setObjectName(QString::fromUtf8("level"));
        level->setMinimumSize(QSize(70, 5));
        level->setAutoFillBackground(false);
        level->setMinimum(1);
        level->setMaximum(6);
        level->setPageStep(1);
        level->setOrientation(Qt::Horizontal);
        level->setTickPosition(QSlider::TicksBelow);

        formLayout->setWidget(4, QFormLayout::FieldRole, level);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        horizontalGroupBox = new QGroupBox(formLayoutWidget);
        horizontalGroupBox->setObjectName(QString::fromUtf8("horizontalGroupBox"));
        horizontalGroupBox->setMaximumSize(QSize(16777215, 20));
        horizontalGroupBox->setFlat(false);
        horizontalLayout = new QHBoxLayout(horizontalGroupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        clrY = new QRadioButton(horizontalGroupBox);
        clrY->setObjectName(QString::fromUtf8("clrY"));

        horizontalLayout->addWidget(clrY);

        clrG = new QRadioButton(horizontalGroupBox);
        clrG->setObjectName(QString::fromUtf8("clrG"));

        horizontalLayout->addWidget(clrG);


        formLayout->setWidget(0, QFormLayout::FieldRole, horizontalGroupBox);

        horizontalGroupBox1 = new QGroupBox(formLayoutWidget);
        horizontalGroupBox1->setObjectName(QString::fromUtf8("horizontalGroupBox1"));
        horizontalGroupBox1->setMaximumSize(QSize(16777215, 20));
        horizontalLayout_2 = new QHBoxLayout(horizontalGroupBox1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setMargin(1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cornerNW = new QRadioButton(horizontalGroupBox1);
        cornerNW->setObjectName(QString::fromUtf8("cornerNW"));

        horizontalLayout_2->addWidget(cornerNW);

        cornerSE = new QRadioButton(horizontalGroupBox1);
        cornerSE->setObjectName(QString::fromUtf8("cornerSE"));

        horizontalLayout_2->addWidget(cornerSE);


        formLayout->setWidget(1, QFormLayout::FieldRole, horizontalGroupBox1);

        gridLayoutWidget = new QWidget(ConfigDialogClass);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 120, 231, 31));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setMargin(11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        buttonOK = new QPushButton(gridLayoutWidget);
        buttonOK->setObjectName(QString::fromUtf8("buttonOK"));
        buttonOK->setDefault(true);

        gridLayout->addWidget(buttonOK, 0, 1, 1, 1);

        buttonCancel = new QPushButton(gridLayoutWidget);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        gridLayout->addWidget(buttonCancel, 0, 0, 1, 1);


        retranslateUi(ConfigDialogClass);

        QMetaObject::connectSlotsByName(ConfigDialogClass);
    } // setupUi

    void retranslateUi(QDialog *ConfigDialogClass)
    {
        ConfigDialogClass->setWindowTitle(QApplication::translate("ConfigDialogClass", "ConfigDialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConfigDialogClass", "my color:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ConfigDialogClass", "level:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConfigDialogClass", "my corner:", 0, QApplication::UnicodeUTF8));
        clrY->setText(QApplication::translate("ConfigDialogClass", "Y", 0, QApplication::UnicodeUTF8));
        clrG->setText(QApplication::translate("ConfigDialogClass", "G", 0, QApplication::UnicodeUTF8));
        cornerNW->setText(QApplication::translate("ConfigDialogClass", "NW", 0, QApplication::UnicodeUTF8));
        cornerSE->setText(QApplication::translate("ConfigDialogClass", "SE", 0, QApplication::UnicodeUTF8));
        buttonOK->setText(QApplication::translate("ConfigDialogClass", "OK", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("ConfigDialogClass", "cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ConfigDialogClass);
    } // retranslateUi

};

namespace Ui {
    class ConfigDialogClass: public Ui_ConfigDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
