#ifndef FINALPROJECT_TEXTFIELD_H
#define FINALPROJECT_TEXTFIELD_H

#include <QGraphicsTextItem>
class TextField : public QGraphicsTextItem{
private:
    int width;
    int height;
    QString backGroundColor;
    QString edgeColor;
    QString color;
public:
    TextField(int pos_x , int pos_y , int w , int h , int size , int textWidth, QString color, QString text,
              QString backGroundColor , QString edgeColor , bool bold);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif //FINALPROJECT_TEXTFIELD_H
