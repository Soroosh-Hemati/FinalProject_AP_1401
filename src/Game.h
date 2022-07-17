#ifndef FINALPROJECT_GAME_H
#define FINALPROJECT_GAME_H

#include <QGraphicsView>
#include "Label.h"
#include "Player.h"
#include "Bomb.h"
#include "Wall.h"
#include "Box.h"

class Game : public QGraphicsView {
Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QGraphicsScene *scene;
    int timeOfGame;
    int numOfLives;
    Bomb *p1bomb;
    Bomb *p2bomb;
public:
    Game(QString player1Name, QString player2Name, QString numOfLivesToString, QString timeOfGameToString);

    void countDown();

    void p1bombPlanted();
    void p2bombPlanted();

    QList<Player *> players{};
    QList<Wall *> walls{};
    QList<class Box*> boxes{};
    QList<Bomb *> bombs{};

    void keyPressEvent(QKeyEvent *event) override;

    void fireDrawer();

    void p1removeBox();
    void p2removeBox();
public slots:

    void timeIsUp();

    void p1bombExploded();
    void p2bombExploded();



};


#endif //FINALPROJECT_GAME_H
