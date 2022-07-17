#include "Bomb.h"
#include <QTimer>
Bomb::Bomb(int pos_x, int pos_y, int w, int h) : QGraphicsPixmapItem() {
    width = w;
    height = h;
    QPixmap qPixmap(":/images/bomb");
    qPixmap = qPixmap.scaled(w , h);
    setPos(pos_x , pos_y);
    setPixmap(qPixmap);
}

void Bomb::fireDrawer(Bomb *bomb) {



}

int Bomb::getPosX() {
    return pos_x;
}

int Bomb::getPosY() {
    return pos_y;
}
