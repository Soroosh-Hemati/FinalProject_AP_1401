#include "Player.h"
#include "Wall.h"
#include <QKeyEvent>
Player::Player(QString path , int pos_x, int pos_y, int w, int h) : QGraphicsPixmapItem() {
    width = w;
    height = h;
    QPixmap qPixmap(path);
    qPixmap = qPixmap.scaled(w , h);
    setPos(pos_x , pos_y);
    setPixmap(qPixmap);
}

void Player::changeFrame(QString path) {
    QPixmap qPixmap(path);
    qPixmap = qPixmap.scaled(width , height);
    setPixmap(qPixmap);
}

void Player::destroyBoxScore() {
    score += 5;
}

void Player::destroyPlayerScore() {
    score += 50;
}

QString Player::getScore() {
    return QString::number(score);
}


