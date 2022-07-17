#ifndef FINALPROJECT_WALL_H
#define FINALPROJECT_WALL_H

#include <QGraphicsPixmapItem>
class Wall: public QGraphicsPixmapItem{
private:
    int width;
    int height;
public:
    Wall(int pos_x , int pos_y , int w , int h);
};


#endif //FINALPROJECT_WALL_H
