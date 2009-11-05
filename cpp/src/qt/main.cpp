
#include <QtGui>
#include <QApplication>

#include "CornersFrame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CornersFrame w;
    w.show();
    return a.exec();
}
