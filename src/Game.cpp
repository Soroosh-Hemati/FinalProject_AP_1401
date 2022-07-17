#include "Game.h"
#include "Label.h"
#include "Wall.h"
#include "Box.h"
#include "Bomb.h"
#include <QTimer>
#include <QTime>
#include "AddPhoto.h"
#include <QKeyEvent>
#include <iostream>
Game::Game(QString player1Name, QString player2Name, QString numOfLivesToString, QString timeOfGameToString) {
    timeOfGame = timeOfGameToString.toInt();
    numOfLives = numOfLivesToString.toInt();
    //WINDOW OPTIONS
    showFullScreen();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //SCENE
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, QWidget::width(), QWidget::height());
    scene->setBackgroundBrush(QBrush("#3F5E5A"));
    setScene(scene);
    //DRAW BLOCKS(WALLS)
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (i != 0 && j != 0 && i != 14 && j != 14 && (i % 2 != 0 || j % 2 != 0)) { continue; }
            auto wall = new Wall((QWidget::width() / 15) * i, (QWidget::height() / 15) * j,
                                 QWidget::width() / 15, QWidget::height() / 15);
            walls.append(wall);
            scene->addItem(wall);
        }
    }
    //DRAW BLOCKS(BOX)
    int *iSaver = new int[80];
    int *jSaver = new int[80];
    bool alreadyMade = false;
    for (int i = 0; i < 80; i++) {
        alreadyMade = false;
        int random_i = rand() % 15;
        int random_j = rand() % 15;
        for(int j = 0 ; j<80 ; j++){
            if(random_i == iSaver[j] && random_j == jSaver[j]){
                alreadyMade = true;
                break;
            }
        }
        if ((random_i == 0 || random_j == 0 || (random_i == 1 && random_j == 1) || (random_i == 13 && random_j == 13) ||
             random_i == 14 || random_j == 14) || (random_i == 2 && random_j == 1) ||
            (random_i == 12 && random_j == 13) || (random_i == 11 && random_j == 13) ||
            (random_i == 3 && random_j == 1) ||
            (random_i % 2 == 0 && random_j % 2 == 0) || alreadyMade) {
            i--;
            continue;
        }else {
            auto box = new class Box((QWidget::width() / 15) * random_i, (QWidget::height() / 15) * random_j,
                                     QWidget::width() / 15, QWidget::height() / 15);
            boxes.append(box);
            scene->addItem(box);
            iSaver[i] = random_i;
            jSaver[i] = random_j;
        }
    }
    //DRAW INFORMATION PART
    auto  infosBG = new AddPhoto(":/images/InfosBG" , 0 , (QWidget::height()*14/15)-10 , 612 , 58);
    scene->addItem(infosBG);
    auto p1Photo = new AddPhoto(":/images/P1_down" , 0 , (QWidget::height()*14/15)-10 , QWidget::width()/15 , QWidget::height()/15);
    scene->addItem(p1Photo);
    auto p2Photo = new AddPhoto(":/images/P2_down" , 306 , (QWidget::height()*14/15)-10 , QWidget::width()/15 , QWidget::height()/15);
    scene->addItem(p2Photo);
    //LABELS
    auto player1Label = new Label(102, QWidget::height() - 80, "black", player1Name, 26, true);
    auto player2Label = new Label(408, QWidget::height() - 80, "black", player2Name, 26, true);
    auto timeLabel = new Label(20, 20, "black", "", 20, true);
    //ADD PLAYERS
    auto player1 = new Player(":/images/P1_down", QWidget::width() / 15, QWidget::height() / 15, (QWidget::width() / 15)-20,
                              (QWidget::height() / 15)-20);
    auto player2 = new Player(":/images/P2_down", QWidget::width() / 15 + 1223, QWidget::height() / 15 + 680,
                              (QWidget::width() / 15)-20, (QWidget::height() / 15)-20);
    scene->addItem(player1);
    scene->addItem(player2);
    players.append(player1);
    players.append(player2);
    //ADD ITEMS TO SCENE
    scene->addItem(timeLabel);
    scene->addItem(player1Label);
    scene->addItem(player2Label);
    //TIMER FUNCTION
    countDown();
}

void Game::countDown() {
    auto qTimer = new QTimer(this);
    connect(qTimer, &QTimer::timeout, this, &Game::timeIsUp);
    qTimer->start(timeOfGame * 60000);

}

void Game::timeIsUp() {
    auto timeIsUpPic = new AddPhoto(":/images/timeIsUp", (QWidget::width() / 2) - 250, (QWidget::height() / 2) - 333,
                                    500, 666);
    scene->addItem(timeIsUpPic);
    setDisabled(scene);
}

void Game::keyPressEvent(QKeyEvent *event) {
    QGraphicsView::keyPressEvent(event);

    auto player1 = players.at(0);
    auto player2 = players.at(1);

    auto player1Width = player1->boundingRect().width();
    auto player1Height = player1->boundingRect().height();

    auto player2Width = player2->boundingRect().width();
    auto player2Height = player2->boundingRect().height();

    auto player1NewX = player1->x();
    auto player1NewY = player1->y();

    auto player2NewX = player2->x();
    auto player2NewY = player2->y();

    if (event->key() == Qt::Key_S) {
        player1NewY = player1->y() + 8;
        player1->changeFrame(":/images/P1_down");
    }
    if (event->key() == Qt::Key_W) {
        player1NewY = player1->y() - 8;
        player1->changeFrame(":/images/P1_up");
    }
    if (event->key() == Qt::Key_A) {
        player1NewX = player1->x() - 8;
        player1->changeFrame(":/images/P1_left");
    }
    if (event->key() == Qt::Key_D) {
        player1NewX = player1->x() + 8;
        player1->changeFrame(":/images/P1_right");
    }
    if (event->key() == Qt::Key_8) {
        player2NewY = player2->y() - 8;
        player2->changeFrame(":/images/P2_up");
    }
    if (event->key() == Qt::Key_5) {
        player2NewY = player2->y() + 8;
        player2->changeFrame(":/images/P2_down");
    }
    if (event->key() == Qt::Key_4) {
        player2NewX = player2->x() - 8;
        player2->changeFrame(":/images/P2_left");
    }
    if (event->key() == Qt::Key_6) {
        player2NewX = player2->x() + 8;
        player2->changeFrame(":/images/P2_right");
    }
    //ADD SPACE AND ENTER KEY TO PLANT BOMB
    if (event->key() == Qt::Key_Space)
        p1bombPlanted();
    if(event->key() == Qt::Key_7)
        p2bombPlanted();

    player1->setPos(player1NewX, player1NewY);
    player2->setPos(player2NewX, player2NewY);

}

void Game::p1bombPlanted() {
    int cellWidth = QWidget::width() / 15;
    int cellHeight = QWidget::height() / 15;

    p1bomb = new Bomb(cellWidth * qRound(players.at(0)->x() / cellWidth), cellHeight * qRound(players.at(0)->y() / cellHeight),
                    QWidget::width() / 15, QWidget::height() / 15);
    scene->addItem(p1bomb);
    auto qTimer = new QTimer(this);
    connect(qTimer, &QTimer::timeout, this, &Game::p1bombExploded);
    qTimer->start(4000);
}

void Game::p1bombExploded() {
    p1bomb->setVisible(false);
    p1removeBox();
    //fireDrawer();

}

void Game::fireDrawer() {
//    if (bomb->x() - (QWidget::height() / 15) > QWidget::height() / 15 &&
//        (bomb->x() - (QWidget::height() / 15) % 2) != 0) {
//        auto fire_negative_x = new AddPhoto(":/images/Fire_x", bomb->x() - (QWidget::width() / 15), bomb->y(),
//                                            (QWidget::width() / 15)-20,
//                                            QWidget::height() / 15);
//        scene->addItem(fire_negative_x);
//    }
//    if (bomb->x() + 15 != 0 && (bomb->x() + 15 % 2) != 0) {
//        auto fire_x = new AddPhoto(":/images/Fire_x", bomb->x() + (QWidget::width() / 15), bomb->y(),
//                                   (QWidget::width() / 15)-20,
//                                   QWidget::height() / 15);
//        scene->addItem(fire_x);
//    }
//    if (bomb->y() - 15 != 0 && (bomb->y() - 15 % 2) != 0) {
//        auto fire_negative_y = new AddPhoto(":/images/Fire_y", bomb->x(), bomb->y() - (QWidget::height() / 15),
//                                            QWidget::width() / 15,
//                                            (QWidget::height() / 15)-20);
//        scene->addItem(fire_negative_y);
//    }
//    if (bomb->y() + 15 != 0 && (bomb->y() + 15 % 2) != 0) {
//        auto fire_y = new AddPhoto(":/images/Fire_y", bomb->x(), bomb->y() + (QWidget::height() / 15),
//                                   QWidget::width() / 15,
//                                   (QWidget::height() / 15)-20);
//        scene->addItem(fire_y);
//    }
}

void Game::p1removeBox() {
    for(int i = 0 ; i<boxes.length() ; i++){

        if((boxes.at(i)->getPosX()== p1bomb->x() && boxes.at(i)->getPosY() == p1bomb->y()-(QWidget::height()/15))){
            boxes.at(i)->setVisible(false);
        }
        if((boxes.at(i)->getPosX()== p1bomb->x() && boxes.at(i)->getPosY() == p1bomb->y()+(QWidget::height()/15))){
            boxes.at(i)->setVisible(false);
        }
        if((boxes.at(i)->getPosY()== p1bomb->y() && boxes.at(i)->getPosX() == p1bomb->x()+(QWidget::width()/15))){
            boxes.at(i)->setVisible(false);
        }
        if((boxes.at(i)->getPosY()== p1bomb->y() && boxes.at(i)->getPosX() == p1bomb->x()-(QWidget::width()/15))){
            boxes.at(i)->setVisible(false);
        }
    }

}

void Game::p2bombExploded() {
    p2bomb->setVisible(false);
    p2removeBox();
    //fireDrawer();
}

void Game::p2bombPlanted() {
    int cellWidth = QWidget::width() / 15;
    int cellHeight = QWidget::height() / 15;

    p2bomb = new Bomb(cellWidth * qRound(players.at(1)->x() / cellWidth), cellHeight * qRound(players.at(1)->y() / cellHeight),
                      QWidget::width() / 15, QWidget::height() / 15);
    scene->addItem(p2bomb);
    auto qTimer = new QTimer(this);
    connect(qTimer, &QTimer::timeout, this, &Game::p2bombExploded);
    qTimer->start(4000);
}

void Game::p2removeBox() {
int c = 0;
    for(int i = 0 ; i<boxes.length() ; i++) {

        if ((boxes.at(i)->getPosX() == p2bomb->x() &&
             boxes.at(i)->getPosY() == p2bomb->y() - (QWidget::height() / 15))) {
             boxes.at(i)->setVisible(false);
             players.at(1)->score += 5;
             c++;
             break;
        }
    }
//    for(int i = 0 ; i<boxes.length() ; i++) {
//        if ((boxes.at(i)->getPosX() == p2bomb->x() &&
//             boxes.at(i)->getPosY() == p2bomb->y() + (QWidget::height() / 15))) {
//            boxes.at(i)->setVisible(false);
//        }
//        if(b2){
//            players.at(1)->destroyBoxScore();
//            b2 = false;
//            qInfo()<<"+";
//        }
//    }
//    for(int i = 0 ; i<boxes.length() ; i++) {
//        if ((boxes.at(i)->getPosY() == p2bomb->y() &&
//             boxes.at(i)->getPosX() == p2bomb->x() + (QWidget::width() / 15))) {
//            boxes.at(i)->setVisible(false);
//        }
//        if(b3){
//            players.at(1)->destroyBoxScore();
//            b3 = false;
//            qInfo()<<"+";
//        }
//    }
//    for(int i = 0 ; i<boxes.length() ; i++){
//        if((boxes.at(i)->getPosY()== p2bomb->y() && boxes.at(i)->getPosX() == p2bomb->x()-(QWidget::width()/15))){
//            boxes.at(i)->setVisible(false);
//        }
//        if(b4){
//            players.at(1)->destroyBoxScore();
//            b4 = false;
//            qInfo()<<"+";
//        }
//    }
std::cout<<c;
}

void Game::mousePressEvent(QMouseEvent *event) {
    std::cout<<players.at(1)->getScore().toInt()<<std::endl;
    QGraphicsView::mousePressEvent(event);
}
