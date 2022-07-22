#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <QGraphicsPixmapItem>
#include "Wall.h"
#include "Box.h"


class Player : public QGraphicsPixmapItem {
private:
    int width;
    int height;
public:
    Player(QString path , int pos_x , int pos_y , int w , int h);
    void changeFrame(QString path);
    void destroyBoxScore();
    void destroyPlayerScore();
    QString getScore();
    int score = 0;
    int numOfLives;
};


#endif //FINALPROJECT_PLAYER_H
