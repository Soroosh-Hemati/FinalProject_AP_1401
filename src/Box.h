#ifndef FINALPROJECT_BOX_H
#define FINALPROJECT_BOX_H

#include <QGraphicsPixmapItem>
class Box: public QGraphicsPixmapItem{
private:
    int width;
    int height;
    int pos_x;
    int pos_y;
public:
    Box(int pos_x , int pos_y , int w , int h);
    int getPosX();
    int getPosY();
};
#endif //FINALPROJECT_BOX_H
