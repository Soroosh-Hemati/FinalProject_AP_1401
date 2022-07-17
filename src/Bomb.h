#ifndef FINALPROJECT_BOMB_H
#define FINALPROJECT_BOMB_H

#include <QGraphicsPixmapItem>

class Bomb : public QGraphicsPixmapItem{

private:
    int width;
    int height;
    int pos_x;
    int pos_y;
public:
    Bomb(int pos_x , int pos_y , int w , int h);
    void fireDrawer(Bomb *bomb);
    int getPosX();
    int getPosY();
};


#endif //FINALPROJECT_BOMB_H
