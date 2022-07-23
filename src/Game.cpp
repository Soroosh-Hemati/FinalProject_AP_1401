#include "Game.h"
#include "Label.h"
#include "Wall.h"
#include "Box.h"
#include "Bomb.h"
#include <QTimer>
#include <QTime>
#include "AddPhoto.h"
#include "Button.h"
#include "Home.h"
#include <QKeyEvent>
#include <iostream>

Game::Game(QString player1Name, QString player2Name, QString numOfLivesToString, QString timeOfGameToString) {
    timeOfGame = timeOfGameToString.toInt();
    numOfLives = numOfLivesToString.toInt();
    timeToSecond = timeOfGame * 60;
    BOMB_EXPLODE_RANGE = 2;
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
        for (int j = 0; j < 80; j++) {
            if (random_i == iSaver[j] && random_j == jSaver[j]) {
                alreadyMade = true;
                break;
            }
        }
        if ((random_i == 0 || random_j == 0 || (random_i == 1 && random_j == 1) || (random_i == 13 && random_j == 13) ||
             random_i == 14 || random_j == 14) || (random_i == 2 && random_j == 1) ||
            (random_i == 12 && random_j == 13) || (random_i == 11 && random_j == 13) ||
            (random_i == 3 && random_j == 1) ||
            (random_i % 2 == 0 && random_j % 2 == 0) || (random_i == 4 && random_j == 1) ||
            (random_i == 10 && random_j == 13) || alreadyMade) {
            i--;
            continue;
        } else {
            auto box = new class Box((QWidget::width() / 15) * random_i, (QWidget::height() / 15) * random_j,
                                     QWidget::width() / 15, QWidget::height() / 15);
            boxes.append(box);
            scene->addItem(box);
            iSaver[i] = random_i;
            jSaver[i] = random_j;
        }
    }
    //DRAW INFORMATION PART
    auto infosBG = new AddPhoto(":/images/InfosBG", 0, (QWidget::height() * 14 / 15) - 10, 612, 58);
    scene->addItem(infosBG);
    auto p1Photo = new AddPhoto(":/images/P1_down", 0, (QWidget::height() * 14 / 15) - 10, QWidget::width() / 15,
                                QWidget::height() / 15);
    scene->addItem(p1Photo);
    auto p2Photo = new AddPhoto(":/images/P2_down", 306, (QWidget::height() * 14 / 15) - 10, QWidget::width() / 15,
                                QWidget::height() / 15);
    scene->addItem(p2Photo);
    auto p1Heart = new AddPhoto(":/images/redHeart", 204, QWidget::height() - 40, 30, 30);
    scene->addItem(p1Heart);
    auto p2Heart = new AddPhoto(":/images/blueHeart", 510, QWidget::height() - 40, 30, 30);
    scene->addItem(p2Heart);
    auto timerBG = new AddPhoto(":/images/InfosBG", 714, (QWidget::height() * 14 / 15) - 10, 102, 58);
    scene->addItem(timerBG);
    //LABELS
    auto player1Label = new Label(102, QWidget::height() - 80, "black", player1Name, 26, true);
    auto player2Label = new Label(408, QWidget::height() - 80, "black", player2Name, 26, true);
    auto timeLabel = new Label(20, 20, "black", "", 20, true);
    player1ScoreLabel = new Label(102, QWidget::height() - 40, "black", "0", 26, true);
    player2ScoreLabel = new Label(408, QWidget::height() - 40, "black", "0", 26, true);
    player1NumOfLives = new Label(234, QWidget::height() - 45, "black", QString::number(numOfLives), 26, true);
    player2NumOfLives = new Label(540, QWidget::height() - 45, "black", QString::number(numOfLives), 26, true);
    TimeLabel = new Label(738, (QWidget::height() * 14 / 15) - 10, "black", QString::number(timeToSecond), 38, true);
    pause1Label = new Label((QWidget::width() / 2) - 366, (QWidget::height() / 2) - 406, "red", "GAME PAUSED", 100,
                            true);
    pause2Label = new Label((QWidget::width() / 2) - 300, (QWidget::height() / 2) - 300, "red",
                            "   click to to continue", 50, true);
    scene->addItem(pause1Label);
    scene->addItem(pause2Label);
    pause1Label->setVisible(false);
    pause2Label->setVisible(false);
    //BUTTONS
    auto pauseButton = new Button(612, (QWidget::height() * 14 / 15) - 10, 29, 102, 19, 102, "black", "  PAUSE",
                                  "white", "black", true);
    scene->addItem(pauseButton);
    auto exitButton = new Button(612, (QWidget::height() * 14 / 15) + 26, 29, 102, 19, 102, "black", "  EXIT", "white",
                                 "black", true);
    scene->addItem(exitButton);
    connect(pauseButton, &Button::buttonPressed, this, &Game::pauseButtonPressed);
    connect(exitButton, &Button::buttonPressed, this, &Game::exitButtonPressed);
    //ADD PLAYERS
    auto player1 = new Player(":/images/P1_down", QWidget::width() / 15, (QWidget::height() / 15) + 10,
                              (QWidget::width() / 15) - 20,
                              (QWidget::height() / 15) - 20);
    auto player2 = new Player(":/images/P2_down", QWidget::width() / 15 + 1223, QWidget::height() / 15 + 680,
                              (QWidget::width() / 15) - 20, (QWidget::height() / 15) - 20);
    player1->numOfLives = numOfLives;
    player2->numOfLives = numOfLives;
    scene->addItem(player1);
    scene->addItem(player2);
    players.append(player1);
    players.append(player2);
    //ADD ITEMS TO SCENE
    scene->addItem(timeLabel);
    scene->addItem(player1Label);
    scene->addItem(player2Label);
    scene->addItem(player1ScoreLabel);
    scene->addItem(player2ScoreLabel);
    scene->addItem(player2NumOfLives);
    scene->addItem(player1NumOfLives);
    scene->addItem(TimeLabel);
    //TIMER FUNCTION
    gameTimer();
}

void Game::keyPressEvent(QKeyEvent *event) {
    player1MovementSpeed = 8;
    player2MovementSpeed = 8;
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

    if (event->key() == Qt::Key_S && !isGamePaused) {
        player1NewY = player1->y() + player1MovementSpeed;
        player1->changeFrame(":/images/P1_down");
    }
    if (event->key() == Qt::Key_W && !isGamePaused) {
        player1NewY = player1->y() - player1MovementSpeed;
        player1->changeFrame(":/images/P1_up");
    }
    if (event->key() == Qt::Key_A && !isGamePaused) {
        player1NewX = player1->x() - player1MovementSpeed;
        player1->changeFrame(":/images/P1_left");
    }
    if (event->key() == Qt::Key_D && !isGamePaused) {
        player1NewX = player1->x() + player1MovementSpeed;
        player1->changeFrame(":/images/P1_right");
    }
    if (event->key() == Qt::Key_8 && !isGamePaused) {
        player2NewY = player2->y() - player2MovementSpeed;
        player2->changeFrame(":/images/P2_up");
    }
    if (event->key() == Qt::Key_5 && !isGamePaused) {
        player2NewY = player2->y() + player2MovementSpeed;
        player2->changeFrame(":/images/P2_down");
    }
    if (event->key() == Qt::Key_4 && !isGamePaused) {
        player2NewX = player2->x() - player2MovementSpeed;
        player2->changeFrame(":/images/P2_left");
    }
    if (event->key() == Qt::Key_6 && !isGamePaused) {
        player2NewX = player2->x() + player2MovementSpeed;
        player2->changeFrame(":/images/P2_right");
    }

    for (const auto wall: walls) {
        if (wall->x() < player1NewX && wall->x() + wall->boundingRect().width() > player1NewX
            && wall->y() < player1NewY && wall->boundingRect().height() > player1NewY)
            return;
        if (wall->x() < player1NewX + player1Width &&
            wall->x() + wall->boundingRect().width() > player1NewX + player1Width
            && wall->y() < player1NewY && wall->y() + wall->boundingRect().height() > player1NewY)
            return;
        if (wall->x() < player1NewX + player1Width &&
            wall->x() + wall->boundingRect().width() > player1NewX + player1Width
            && wall->y() < player1NewY + player1Height &&
            wall->y() + wall->boundingRect().height() > player1NewY + player1Height)
            return;
        if (wall->x() < player1NewX && wall->x() + wall->boundingRect().width() > player1NewX
            && wall->y() < player1NewY + player1Height &&
            wall->y() + wall->boundingRect().height() > player1NewY + player1Height)
            return;
    }

    for (const auto wall: walls) {
        if (wall->x() < player2NewX && wall->x() + wall->boundingRect().width() > player2NewX
            && wall->y() < player2NewY && wall->boundingRect().height() > player2NewY)
            return;
        if (wall->x() < player2NewX + player2Width &&
            wall->x() + wall->boundingRect().width() > player2NewX + player2Width
            && wall->y() < player2NewY && wall->y() + wall->boundingRect().height() > player2NewY)
            return;
        if (wall->x() < player2NewX + player2Width &&
            wall->x() + wall->boundingRect().width() > player2NewX + player2Width
            && wall->y() < player1NewY + player1Height &&
            wall->y() + wall->boundingRect().height() > player2NewY + player2Height)
            return;
        if (wall->x() < player2NewX && wall->x() + wall->boundingRect().width() > player2NewX
            && wall->y() < player2NewY + player2Height &&
            wall->y() + wall->boundingRect().height() > player2NewY + player2Height)
            return;
    }

    for (const auto box: boxes) {
        if (box->x() < player1NewX && box->x() + box->boundingRect().width() > player1NewX
            && box->y() < player1NewY && box->boundingRect().height() > player1NewY)
            return;
        if (box->x() < player1NewX + player1Width &&
            box->x() + box->boundingRect().width() > player1NewX + player1Width
            && box->y() < player1NewY && box->y() + box->boundingRect().height() > player1NewY)
            return;
        if (box->x() < player1NewX + player1Width &&
            box->x() + box->boundingRect().width() > player1NewX + player1Width
            && box->y() < player1NewY + player1Height &&
            box->y() + box->boundingRect().height() > player1NewY + player1Height)
            return;
        if (box->x() < player1NewX && box->x() + box->boundingRect().width() > player1NewX
            && box->y() < player1NewY + player1Height &&
            box->y() + box->boundingRect().height() > player1NewY + player1Height)
            return;
    }

    for (const auto box: boxes) {
        if (box->x() < player2NewX && box->x() + box->boundingRect().width() > player2NewX
            && box->y() < player2NewY && box->boundingRect().height() > player2NewY)
            return;
        if (box->x() < player2NewX + player2Width &&
            box->x() + box->boundingRect().width() > player2NewX + player2Width
            && box->y() < player2NewY && box->y() + box->boundingRect().height() > player2NewY)
            return;
        if (box->x() < player2NewX + player2Width &&
            box->x() + box->boundingRect().width() > player2NewX + player2Width
            && box->y() < player2NewY + player2Height &&
            box->y() + box->boundingRect().height() > player2NewY + player2Height)
            return;
        if (box->x() < player2NewX && box->x() + box->boundingRect().width() > player2NewX
            && box->y() < player2NewY + player2Height &&
            box->y() + box->boundingRect().height() > player2NewY + player2Height)
            return;
    }
    //ADD SPACE AND ENTER KEY TO PLANT BOMB
    if (event->key() == Qt::Key_Space && canP1PlantBomb && !isGamePaused)
        p1bombPlanted();
    if (event->key() == Qt::Key_7 && canP2PlantBomb && !isGamePaused)
        p2bombPlanted();

    player1->setPos(player1NewX, player1NewY);
    player2->setPos(player2NewX, player2NewY);
    QGraphicsView::keyPressEvent(event);

}

void Game::mousePressEvent(QMouseEvent *event) {
    isGamePaused = false;
    qTimer_gameTimer->start();
    pause1Label->setVisible(false);
    pause2Label->setVisible(false);
    QGraphicsView::mousePressEvent(event);
}

void Game::p1bombPlanted() {
    int cellWidth = QWidget::width() / 15;
    int cellHeight = QWidget::height() / 15;

    p1bomb = new Bomb(cellWidth * qRound(players.at(0)->x() / cellWidth),
                      cellHeight * qRound(players.at(0)->y() / cellHeight),
                      QWidget::width() / 15, QWidget::height() / 15);
    scene->addItem(p1bomb);
    QTimer::singleShot(4000, this, SLOT(p1bombExploded()));
    canP1PlantBomb = false;
}

void Game::p1bombExploded() {
    scene->removeItem(p1bomb);
    p1removeBox();
    bomb1Destroys();
    canP1PlantBomb = true;
}

void Game::p1removeBox() {
    int c = 0;
    bool firstBoxFounded1 = false;
    int bomb_x1 = p1bomb->x() / 102;
    int bomb_y1 = p1bomb->y() / 57;

    for (int j = 1; j <= BOMB_EXPLODE_RANGE; j++) {
        for (int i = 0; i < boxes.length(); i++) {

            if ((boxes.at(i)->getPosX() == p1bomb->x() &&
                 boxes.at(i)->getPosY() == p1bomb->y() - (QWidget::height() / 15) * j)) {
                boxes.at(i)->setVisible(false);
                boxes.removeOne(boxes.at(i));
                firstBoxFounded1 = true;
                c += 5;
                break;
            }
        }
        if (!firstBoxFounded1 && j == 1 && bomb_x1 % 2 == 0 && (bomb_y1 - 1) % 2 == 0) {
            break;
        }
    }
    bool firstBoxFounded2 = false;
    int bomb_x2 = p1bomb->x() / 102;
    int bomb_y2 = p1bomb->y() / 57;
    for (int j = 1; j <= BOMB_EXPLODE_RANGE; ++j) {
        for (int i = 0; i < boxes.length(); i++) {

            if ((boxes.at(i)->getPosX() == p1bomb->x() &&
                 boxes.at(i)->getPosY() == p1bomb->y() + (QWidget::height() / 15) * j)) {
                boxes.at(i)->setVisible(false);
                boxes.removeOne(boxes.at(i));
                firstBoxFounded2 = true;
                c += 5;
                break;
            }
        }
        if (!firstBoxFounded2 && j == 1 && bomb_x2 % 2 == 0 && (bomb_y2 + 1) % 2 == 0) {
            break;
        }
    }
    bool firstBoxFounded3 = false;
    int bomb_x3 = p1bomb->x() / 102;
    int bomb_y3 = p1bomb->y() / 57;
    for (int j = 1; j <= BOMB_EXPLODE_RANGE; j++) {
        for (int i = 0; i < boxes.length(); i++) {

            if ((boxes.at(i)->getPosY() == p1bomb->y() &&
                 boxes.at(i)->getPosX() == p1bomb->x() + (QWidget::width() / 15) * j)) {
                boxes.at(i)->setVisible(false);
                boxes.removeOne(boxes.at(i));
                firstBoxFounded3 = true;
                c += 5;
                break;
            }
        }
        if (!firstBoxFounded3 && j == 1 && (bomb_x3 + 1) % 2 == 0 && (bomb_y3 % 2 == 0)) {
            break;
        }

    }
    bool firstBoxFounded4 = false;
    int bomb_x4 = p1bomb->x() / 102;
    int bomb_y4 = p1bomb->y() / 57;
    for (int j = 1; j <= BOMB_EXPLODE_RANGE; j++) {
        for (int i = 0; i < boxes.length(); i++) {

            if ((boxes.at(i)->getPosY() == p1bomb->y() &&
                 boxes.at(i)->getPosX() == p1bomb->x() - (QWidget::width() / 15) * j)) {
                boxes.at(i)->setVisible(false);
                boxes.removeOne(boxes.at(i));
                firstBoxFounded4 = true;
                c += 5;
                break;
            }
        }
        if (!firstBoxFounded4 && j == 1 && (bomb_x4 - 1) % 2 == 0 && (bomb_y4) % 2 == 0) {
            break;
        }
    }
    players.at(0)->score += c;
    player1ScoreLabel->setPlainText(QString::number(players.at(0)->score));
}

void Game::p2bombExploded() {
    p2bomb->setVisible(false);
    p2removeBox();
    bomb2Destroys();
    canP2PlantBomb = true;
}

void Game::p2bombPlanted() {
    int cellWidth = QWidget::width() / 15;
    int cellHeight = QWidget::height() / 15;

    p2bomb = new Bomb(cellWidth * qRound(players.at(1)->x() / cellWidth),
                      cellHeight * qRound(players.at(1)->y() / cellHeight),
                      QWidget::width() / 15, QWidget::height() / 15);

    scene->addItem(p2bomb);
    QTimer::singleShot(4000, this, SLOT(p2bombExploded()));
    canP2PlantBomb = false;
}

void Game::p2removeBox() {
    int c = 0;
    bool firstBoxFounded1 = false;
    int bomb_x1 = p2bomb->x() / 102;
    int bomb_y1 = p2bomb->y() / 57;

    for (int j = 1; j <= BOMB_EXPLODE_RANGE; j++) {
        for (int i = 0; i < boxes.length(); i++) {

            if ((boxes.at(i)->getPosX() == p2bomb->x() &&
                 boxes.at(i)->getPosY() == p2bomb->y() - (QWidget::height() / 15) * j)) {
                boxes.at(i)->setVisible(false);
                boxes.removeOne(boxes.at(i));
                firstBoxFounded1 = true;
                c += 5;
                break;
            }
        }
        if (!firstBoxFounded1 && j == 1 && bomb_x1 % 2 == 0 && (bomb_y1 - 1) % 2 == 0) {
            break;
        }
    }
    bool firstBoxFounded2 = false;
    int bomb_x2 = p2bomb->x() / 102;
    int bomb_y2 = p2bomb->y() / 57;
    for (int j = 1; j <= BOMB_EXPLODE_RANGE; ++j) {
        for (int i = 0; i < boxes.length(); i++) {

            if ((boxes.at(i)->getPosX() == p2bomb->x() &&
                 boxes.at(i)->getPosY() == p2bomb->y() + (QWidget::height() / 15) * j)) {
                boxes.at(i)->setVisible(false);
                boxes.removeOne(boxes.at(i));
                firstBoxFounded2 = true;
                c += 5;
                break;
            }
        }
        if (!firstBoxFounded2 && j == 1 && bomb_x2 % 2 == 0 && (bomb_y2 + 1) % 2 == 0) {
            break;
        }
    }
    bool firstBoxFounded3 = false;
    int bomb_x3 = p2bomb->x() / 102;
    int bomb_y3 = p2bomb->y() / 57;
    for (int j = 1; j <= BOMB_EXPLODE_RANGE; j++) {
        for (int i = 0; i < boxes.length(); i++) {

            if ((boxes.at(i)->getPosY() == p2bomb->y() &&
                 boxes.at(i)->getPosX() == p2bomb->x() + (QWidget::width() / 15) * j)) {
                boxes.at(i)->setVisible(false);
                boxes.removeOne(boxes.at(i));
                firstBoxFounded3 = true;
                c += 5;
                break;
            }
        }
        if (!firstBoxFounded3 && j == 1 && (bomb_x3 + 1) % 2 == 0 && (bomb_y3 % 2 == 0)) {
            break;
        }

    }
    bool firstBoxFounded4 = false;
    int bomb_x4 = p2bomb->x() / 102;
    int bomb_y4 = p2bomb->y() / 57;
    for (int j = 1; j <= BOMB_EXPLODE_RANGE; j++) {
        for (int i = 0; i < boxes.length(); i++) {

            if ((boxes.at(i)->getPosY() == p2bomb->y() &&
                 boxes.at(i)->getPosX() == p2bomb->x() - (QWidget::width() / 15) * j)) {
                boxes.at(i)->setVisible(false);
                boxes.removeOne(boxes.at(i));
                firstBoxFounded4 = true;
                c += 5;
                break;
            }
        }
        if (!firstBoxFounded4 && j == 1 && (bomb_x4 - 1) % 2 == 0 && (bomb_y4) % 2 == 0) {
            break;
        }
    }
    players.at(1)->score += c;
    player2ScoreLabel->setPlainText(QString::number(players.at(1)->score));
}

void Game::bomb1Destroys() {
    for (int i = 0; i < 2; i++) {
        int c = 0;
        int n = 0;

        if (p1bomb->x() >= players.at(i)->x() &&
            p1bomb->x() - (QWidget::width() / 15) * BOMB_EXPLODE_RANGE <= players.at(i)->x() &&
            players.at(i)->y() >= p1bomb->y() && players.at(i)->y() <= p1bomb->y() + (QWidget::height() / 15)) {
            c += 50;
            players.at(i)->numOfLives--;
        } else if (p1bomb->x() <= players.at(i)->x() &&
                   p1bomb->x() + (QWidget::width() / 15) * (BOMB_EXPLODE_RANGE + 1) >= players.at(i)->x() &&
                   players.at(i)->y() >= p1bomb->y() && players.at(i)->y() <= p1bomb->y() + (QWidget::height() / 15)) {
            c += 50;
            players.at(i)->numOfLives--;
        } else if (p1bomb->x() <= players.at(i)->x() && p1bomb->x() + (QWidget::width() / 15) >= players.at(i)->x() &&
                   players.at(i)->y() <= p1bomb->y() &&
                   players.at(i)->y() >= p1bomb->y() - (QWidget::height() / 15) * BOMB_EXPLODE_RANGE) {
            c += 50;
            players.at(i)->numOfLives--;
        } else if (p1bomb->x() <= players.at(i)->x() && p1bomb->x() + (QWidget::width() / 15) >= players.at(i)->x() &&
                   players.at(i)->y() >= p1bomb->y() &&
                   players.at(i)->y() <= p1bomb->y() + (QWidget::height() / 15) * (BOMB_EXPLODE_RANGE + 1)) {
            c += 50;
            players.at(i)->numOfLives--;
        }
        if (i == 0) {
            players.at(1)->score += c;
            player2ScoreLabel->setPlainText(QString::number(players.at(1)->score));
            player1NumOfLives->setPlainText(QString::number(players.at(0)->numOfLives));
        } else if (i == 1) {
            players.at(0)->score += c;
            player1ScoreLabel->setPlainText(QString::number(players.at(0)->score));
            player2NumOfLives->setPlainText(QString::number(players.at(1)->numOfLives));
        }
    }
    //show the winner if a player lives is finished
    if (players.at(0)->numOfLives == 0) {
        auto Player2Wins = new AddPhoto(":/images/Player2wins", (QWidget::width() / 2) - 300,
                                        (QWidget::height() / 2) - 170,
                                        600, 339);
        scene->addItem(Player2Wins);
        auto returnTomHomeButton = new Button((QWidget::width() / 2) - 150, (QWidget::height() / 15) * 10, 20, 300,
                                              26, 300, "black", "     Return to home", "white", "black", true);
        scene->addItem(returnTomHomeButton);
        connect(returnTomHomeButton, &Button::buttonPressed, this, &Game::returnToHomeButtonPressed);
        isGamePaused = true;
        qTimer_gameTimer->stop();
    } else if (players.at(1)->numOfLives == 0) {
        auto Player1Wins = new AddPhoto(":/images/Player1wins", (QWidget::width() / 2) - 300,
                                        (QWidget::height() / 2) - 170,
                                        600, 339);
        scene->addItem(Player1Wins);
        auto returnTomHomeButton = new Button((QWidget::width() / 2) - 150, (QWidget::height() / 15) * 10, 20, 300,
                                              26, 300, "black", "     Return to home", "white", "black", true);
        scene->addItem(returnTomHomeButton);
        connect(returnTomHomeButton, &Button::buttonPressed, this, &Game::returnToHomeButtonPressed);
        isGamePaused = true;
        qTimer_gameTimer->stop();
    }
}


void Game::gameTimer() {
    qTimer_gameTimer = new QTimer(this);
    connect(qTimer_gameTimer, &QTimer::timeout, this, &Game::printTime);
    qTimer_gameTimer->start(1000);
}

void Game::printTime() {
    timeToSecond--;
    TimeLabel->setPlainText(QString::number(timeToSecond));
    if (timeToSecond == 0) {
        disconnect(qTimer_gameTimer, &QTimer::timeout, this, &Game::printTime);
        qTimer_gameTimer->stop();
        if (players.at(0)->score > players.at(1)->score) {
            auto Player1Wins = new AddPhoto(":/images/Player1wins", (QWidget::width() / 2) - 300,
                                            (QWidget::height() / 2) - 170,
                                            600, 339);
            scene->addItem(Player1Wins);
            auto returnTomHomeButton = new Button((QWidget::width() / 2) - 150, (QWidget::height() / 15) * 10, 20, 300,
                                                  26, 300, "black", "     Return to home", "white", "black", true);
            scene->addItem(returnTomHomeButton);
            connect(returnTomHomeButton, &Button::buttonPressed, this, &Game::returnToHomeButtonPressed);
            isGamePaused = true;
        } else if (players.at(0)->score < players.at(1)->score) {
            auto Player2Wins = new AddPhoto(":/images/Player2wins", (QWidget::width() / 2) - 300,
                                            (QWidget::height() / 2) - 170,
                                            600, 339);
            scene->addItem(Player2Wins);
            auto returnTomHomeButton = new Button((QWidget::width() / 2) - 150, (QWidget::height() / 15) * 10, 20, 300,
                                                  26, 300, "black", "     Return to home", "white", "black", true);
            scene->addItem(returnTomHomeButton);
            connect(returnTomHomeButton, &Button::buttonPressed, this, &Game::returnToHomeButtonPressed);
            isGamePaused = true;
        } else if (players.at(0)->score == players.at(1)->score) {
            auto Tie = new AddPhoto(":/images/Tie", (QWidget::width() / 2) - 300,
                                    (QWidget::height() / 2) - 170,
                                    600, 339);
            scene->addItem(Tie);
            auto returnTomHomeButton = new Button((QWidget::width() / 2) - 150, (QWidget::height() / 15) * 10, 20, 300,
                                                  26, 300, "black", "     Return to home", "white", "black", true);
            scene->addItem(returnTomHomeButton);
            connect(returnTomHomeButton, &Button::buttonPressed, this, &Game::returnToHomeButtonPressed);
            isGamePaused = true;
        }
    }
}

void Game::pauseButtonPressed() {
    pause1Label->setVisible(true);
    pause2Label->setVisible(true);
    qTimer_gameTimer->stop();
    isGamePaused = true;
}

void Game::exitButtonPressed() {
    auto home = new Home;
    home->show();
    close();
}

void Game::returnToHomeButtonPressed() {
    auto home = new Home;
    home->show();
    close();

}

void Game::bomb2Destroys() {
    for (int i = 0; i < 2; i++) {
        int c = 0;
        int n = 0;
        if (p2bomb->x() >= players.at(i)->x() &&
            p2bomb->x() - (QWidget::width() / 15) * BOMB_EXPLODE_RANGE <= players.at(i)->x() &&
            players.at(i)->y() >= p2bomb->y() && players.at(i)->y() <= p2bomb->y() + (QWidget::height() / 15)) {
            c += 50;
            players.at(i)->numOfLives--;
        } else if (p2bomb->x() <= players.at(i)->x() &&
                   p2bomb->x() + (QWidget::width() / 15) * (BOMB_EXPLODE_RANGE + 1) >= players.at(i)->x() &&
                   players.at(i)->y() >= p2bomb->y() && players.at(i)->y() <= p2bomb->y() + (QWidget::height() / 15)) {
            c += 50;
            players.at(i)->numOfLives--;
        } else if (p2bomb->x() <= players.at(i)->x() && p2bomb->x() + (QWidget::width() / 15) >= players.at(i)->x() &&
                   players.at(i)->y() <= p2bomb->y() &&
                   players.at(i)->y() >= p2bomb->y() - (QWidget::height() / 15) * BOMB_EXPLODE_RANGE) {
            c += 50;
            players.at(i)->numOfLives--;
        } else if (p2bomb->x() <= players.at(i)->x() && p2bomb->x() + (QWidget::width() / 15) >= players.at(i)->x() &&
                   players.at(i)->y() >= p2bomb->y() &&
                   players.at(i)->y() <= p2bomb->y() + (QWidget::height() / 15) * (BOMB_EXPLODE_RANGE + 1)) {
            c += 50;
            players.at(i)->numOfLives--;
        }
        if (i == 0) {
            players.at(1)->score += c;
            player2ScoreLabel->setPlainText(QString::number(players.at(1)->score));
            player1NumOfLives->setPlainText(QString::number(players.at(0)->numOfLives));
        } else if (i == 1) {
            players.at(0)->score += c;
            player1ScoreLabel->setPlainText(QString::number(players.at(0)->score));
            player2NumOfLives->setPlainText(QString::number(players.at(1)->numOfLives));
        }
    }
//show the winner if a player lives is finished
    if (players.at(0)->numOfLives == 0) {
        auto Player2Wins = new AddPhoto(":/images/Player2wins", (QWidget::width() / 2) - 300,
                                        (QWidget::height() / 2) - 170,
                                        600, 339);
        scene->addItem(Player2Wins);
        auto returnTomHomeButton = new Button((QWidget::width() / 2) - 150, (QWidget::height() / 15) * 10, 20, 300,
                                              26, 300, "black", "     Return to home", "white", "black", true);
        scene->addItem(returnTomHomeButton);
        connect(returnTomHomeButton, &Button::buttonPressed, this, &Game::returnToHomeButtonPressed);
        isGamePaused = true;
        qTimer_gameTimer->stop();
    } else if (players.at(1)->numOfLives == 0) {
        auto Player1Wins = new AddPhoto(":/images/Player1wins", (QWidget::width() / 2) - 300,
                                        (QWidget::height() / 2) - 170,
                                        600, 339);
        scene->addItem(Player1Wins);
        auto returnTomHomeButton = new Button((QWidget::width() / 2) - 150, (QWidget::height() / 15) * 10, 20, 300,
                                              26, 300, "black", "     Return to home", "white", "black", true);
        scene->addItem(returnTomHomeButton);
        connect(returnTomHomeButton, &Button::buttonPressed, this, &Game::returnToHomeButtonPressed);
        isGamePaused = true;
        qTimer_gameTimer->stop();
    }
}
