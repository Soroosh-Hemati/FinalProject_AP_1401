#include "Home.h"
#include "Home.h"
#include "Button.h"
#include "Label.h"
#include "TextField.h"
#include "Game.h"
#include "AddPhoto.h"
#include <QFile>
Home::Home() {
    //WINDOW OPTIONS
    showFullScreen();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //SCENE
    auto scene = new QGraphicsScene(this);
    scene->setSceneRect(0 , 0 , QWidget::width() , QWidget::height());
    scene->setBackgroundBrush(QBrush("#2a3d45"));
    setScene(scene);
    //SET BACKGROUND
    auto background = new AddPhoto( ":/images/gameBG", 0 , 0 , QWidget::width(), QWidget::height());
    scene->addItem(background);
    //BUTTONS
    auto startGameButton = new Button( (QWidget::width()/2)-60, 740  , 120 , 50 , 16 , 120 , "black" , " START GAME", "white" ,"a7f542" ,true);
    auto exitButton = new Button( (QWidget::width()/2)-60, 780  , 120 , 50 , 16 , 120 , "black" , "         EXIT", "white" ,"a7f542" ,true);
    scene->addItem(startGameButton);
    scene->addItem(exitButton);
    //LABELS
    auto numOfLivesLabel = new Label((QWidget::width()/2)-62 , 40, "black" , "Number of lives:" , 16 , true);
    auto player1Label = new Label((QWidget::width()/2)-536 , 675 , "#d3d3d3" , "player1 name:" , 13 , true);
    auto player2Label = new Label((QWidget::width()/2)+640-200 , 675 , "#d3d3d3" , "player2 name:" , 13 , true);
    auto setTimerLabel = new Label((QWidget::width()/2)-62 , 40, "black" , " Time of game:" , 16 , true);
    scene->addItem(numOfLivesLabel);
    scene->addItem(player1Label);
    scene->addItem(player2Label);
    scene->addItem(setTimerLabel);
    //TEXT FIELDS
    numOfLivesTextField = new TextField((QWidget::width()/2)-100 , 50 , 40 , 20 , 20 , 40 , "black" , "" , "white" , "white" , true);
    player1TextField = new TextField((QWidget::width()/2)-590 , 700 , 200 , 10 , 20 , 200 , "black" , "Player1" , "white" , "white" , true);
    player2TextField = new TextField((QWidget::width()/2)+390 , 700 , 200 , 10 , 20 , 200 , "black" , "Player2" , "white" , "white" ,true);
    setTimerTextField = new TextField((QWidget::width()/2)+100 , 50 , 40 , 20 , 20 , 40 , "black" , "5" , "white" , "white" , true);
    scene->addItem(numOfLivesTextField);
    scene->addItem(player1TextField);
    scene->addItem(player2TextField);
    scene->addItem(setTimerTextField);
    //READ PLAYERS NAMES FROM FILE
    readPlayersNamesInFile();
    //CONNECT SIGNALS AND SLOTS
    connect(startGameButton , &Button::buttonPressed , this , &Home::gameWindowOpened);
    connect(exitButton , &Button::buttonPressed , this , &Home::exitButtonClicked);
}

void Home::gameWindowOpened() {
    saveInfosInFile();
    auto game = new Game(player1TextField->toPlainText() , player2TextField->toPlainText() ,
                         numOfLivesTextField->toPlainText() , setTimerTextField->toPlainText());
    game->show();
    close();
}

void Home::saveInfosInFile() {
    QFile file{"playersNames.txt"};
    if(file.open(QIODevice::ReadWrite)){
        QTextStream out(&file);
        out<<player1TextField->toPlainText()<<'\n'<<player2TextField->toPlainText()<<'\n'<<numOfLivesTextField->toPlainText()<<'\n';
        out<<setTimerTextField->toPlainText()<<'\n';
    }else{
        std::cerr<<"An error occurred while writing in file!"<<std::endl;
    }
}

void Home::readPlayersNamesInFile() {
    QFile file{"playersNames.txt"};
    if(file.open(QIODevice::ReadOnly) && file.size()!=0){
        player1TextField->setPlainText(file.readLine());
        player2TextField->setPlainText(file.readLine());
        numOfLivesTextField->setPlainText(file.readLine());
        setTimerTextField->setPlainText(file.readLine());
    }else{
        std::cerr<<"An error occurred while reading from file!"<<std::endl;
    }
}

void Home::exitButtonClicked() {
    exit(1);
}