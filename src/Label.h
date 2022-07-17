#ifndef FINALPROJECT_LABEL_H
#define FINALPROJECT_LABEL_H

#include <QGraphicsTextItem>
class Label: public QGraphicsTextItem{
public:
    Label(int pos_x , int pos_y , QString color , QString text ,int size , bool bold);
};



#endif //FINALPROJECT_LABEL_H
