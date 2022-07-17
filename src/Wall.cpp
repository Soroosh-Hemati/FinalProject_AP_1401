#include "Wall.h"

Wall::Wall(int pos_x , int pos_y , int w , int h) : QGraphicsPixmapItem() {
    width = w;
    height = h;
    QPixmap qPixmap(":/images/wall");
    qPixmap = qPixmap.scaled(w , h);
    setPos(pos_x , pos_y);
    setPixmap(qPixmap);
}
