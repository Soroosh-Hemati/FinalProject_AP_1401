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
    int BOMB_EXPLODE_RANGE;
    int timeOfGame;
    int numOfLives;
    int timeToSecond;
    int player1MovementSpeed;
    int player2MovementSpeed;
    Bomb *p1bomb;
    Bomb *p2bomb;
    Label *player1ScoreLabel;
    Label *player2ScoreLabel;
    Label *player1NumOfLives;
    Label *player2NumOfLives;
    Label *pause1Label;
    Label *pause2Label;
    Label *TimeLabel;
    bool canP1PlantBomb = true;
    bool canP2PlantBomb = true;
    QTimer *qTimer_gameTimer;
    bool isGamePaused = false;

public:
    Game(QString player1Name, QString player2Name, QString numOfLivesToString, QString timeOfGameToString);

    QList<Player *> players{};
    QList<Wall *> walls{};
    QList<class Box *> boxes{};
    QList<Bomb *> bombs{};

    void p1bombPlanted();

    void p2bombPlanted();

    void keyPressEvent(QKeyEvent *event) override;

    void p1removeBox();

    void p2removeBox();

    void bomb1Destroys();

    void bomb2Destroys();

    void gameTimer();

public slots:

    void pauseButtonPressed();

    void exitButtonPressed();

    void printTime();

    void p1bombExploded();

    void p2bombExploded();

    void returnToHomeButtonPressed();


};


#endif //FINALPROJECT_GAME_H
