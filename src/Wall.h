#ifndef FINALPROJECT_WALL_H
#define FINALPROJECT_WALL_H

#include <QGraphicsPixmapItem>
#include "Blocks.h"

class Wall: public QGraphicsPixmapItem, public Blocks{
private:
    int width;
    int height;
public:
    Wall(int pos_x , int pos_y , int w , int h);
};


#endif //FINALPROJECT_WALL_H
