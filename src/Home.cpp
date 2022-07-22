//
// Created by ASuS on 7/12/2022.
//

#include "Home.h"
#include "Button.h"
#include "Label.h"
#include "TextField.h"
#include "Game.h"
#include "AddPhoto.h"
#include <QFile>
#include <regex>
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
    auto numOfLivesLabel = new Label((QWidget::width()/2)-140 , 18, "black" , "Number of lives:" , 16 , true);
    auto player1Label = new Label((QWidget::width()/2)-536 , 675 , "#d3d3d3" , "player1 name:" , 13 , true);
    auto player2Label = new Label((QWidget::width()/2)+640-200 , 675 , "#d3d3d3" , "player2 name:" , 13 , true);
    auto setTimerLabel = new Label((QWidget::width()/2)+30 , 18, "black" , " Time of game:" , 16 , true);
    auto numOfLivesHint = new Label((QWidget::width()/2)-105 , 100 , "black" , "[1-10]" , 16 , true);
    auto timeOfGameHint = new Label((QWidget::width()/2)+55, 100 , "black" , "[1-10]" , 16 , true);
    scene->addItem(numOfLivesLabel);
    scene->addItem(player1Label);
    scene->addItem(player2Label);
    scene->addItem(setTimerLabel);
    scene->addItem(numOfLivesHint);
    scene->addItem(timeOfGameHint);
    //TEXT FIELDS
    numOfLivesTextField = new TextField((QWidget::width()/2)-100 , 50 , 40 , 20 , 20 , 40 , "black" , "3" , "white" , "white" , true);
    player1TextField = new TextField((QWidget::width()/2)-590 , 700 , 200 , 10 , 20 , 200 , "black" , "Player1" , "white" , "white" , true);
    player2TextField = new TextField((QWidget::width()/2)+390 , 700 , 200 , 10 , 20 , 200 , "black" , "Player2" , "white" , "white" ,true);
    setTimerTextField = new TextField((QWidget::width()/2)+60 , 50 , 40 , 20 , 20 , 40 , "black" , "5" , "white" , "white" , true);
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
    if(checkTextFieldInputs()){
        saveInfosInFile();
        auto game = new Game(player1TextField->toPlainText(), player2TextField->toPlainText(),
                             numOfLivesTextField->toPlainText(), setTimerTextField->toPlainText());
        game->show();
        close();
    }
}

void Home::saveInfosInFile() {
    QFile file{"playersNames.txt"};
    file.resize(0);
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
    QString line;
    if(file.open(QIODevice::ReadWrite) && file.size()!=0){
        line = file.readLine();
        line.remove('\n');
        player1TextField->setPlainText(line);
        line = file.readLine();
        line.remove('\n');
        player2TextField->setPlainText(line);
        line = file.readLine();
        line.remove('\n');
        numOfLivesTextField->setPlainText(line);
        line = file.readLine();
        line.remove('\n');
        setTimerTextField->setPlainText(line);
    }else{
        std::cerr<<"An error occurred while reading from file!"<<std::endl;
    }
}

void Home::exitButtonClicked() {
    exit(1);
}

bool Home::checkTextFieldInputs() {
    bool canStartGame1 = false;
    bool canStartGame2 = false;
    std::regex timeOfGameTF("[1-9]|10");
    if(!std::regex_match(setTimerTextField->toPlainText().toStdString() , timeOfGameTF)){
        canStartGame1 = false;
    }else{
        canStartGame1 = true;
    }
    std::regex numOfLivesTF("[1-9]|10");
    if(!std::regex_match(numOfLivesTextField->toPlainText().toStdString() , numOfLivesTF)){
        canStartGame2 = false;
    }else{
        canStartGame2 = true;
    }
    return (canStartGame1 && canStartGame2);
}
