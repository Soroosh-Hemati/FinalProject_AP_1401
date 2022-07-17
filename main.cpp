#include <QApplication>
#include "src/Home.h"
#include <QAbstractButton>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto h = new Home;
    h->show();
    return QApplication::exec();
}
