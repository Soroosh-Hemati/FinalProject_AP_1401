#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem {
private:
    int width;
    int height;
    int score = 0;
public:
    Player(QString path , int pos_x , int pos_y , int w , int h);
    void changeFrame(QString path);
    void destroyBoxScore();
    void destroyPlayerScore();
    QString getScore();
};


#endif //FINALPROJECT_PLAYER_H
