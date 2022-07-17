#include "Box.h"

Box::Box(int pos_x, int pos_y, int w, int h): QGraphicsPixmapItem() {
    width = w;
    height = h;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    QPixmap qPixmap(":/images/box");
    qPixmap = qPixmap.scaled(w , h);
    setPos(pos_x , pos_y);
    setPixmap(qPixmap);
}

int Box::getPosX() {
    return pos_x;
}

int Box::getPosY() {
    return pos_y;
}
