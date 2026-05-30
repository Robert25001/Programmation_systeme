#include "Recupere_info.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Recupere_info w;
    w.show();
    return a.exec();
}
