#ifndef FINALPROJECT_HOME_H
#define FINALPROJECT_HOME_H

#include <QGraphicsView>
#include <QPushButton>
#include "TextField.h"

class Home : public QGraphicsView{
    Q_OBJECT
private:
    TextField *player1TextField;
    TextField *player2TextField;
    TextField *numOfLivesTextField;
    TextField *setTimerTextField;
public:
    Home();
    void saveInfosInFile();
    void readPlayersNamesInFile();
    bool checkTextFieldInputs();
public slots:
            void gameWindowOpened();
    void exitButtonClicked();


};


#endif //FINALPROJECT_HOME_H
