#ifndef FINALPROJECT_BUTTON_H
#define FINALPROJECT_BUTTON_H

#include <iostream>
#include <QGraphicsTextItem>
class Button : public QGraphicsTextItem {
    Q_OBJECT
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int width;
    int height;
    QString backGroundColor;
    QString edgeColor;
    QString color;
public:
    Button(int pos_x , int pos_y , int w , int h , int size , int textWidth, QString color, QString text ,
           QString backGroundColor , QString edgeColor , bool bold);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    void buttonPressed();
};


#endif //FINALPROJECT_BUTTON_H
