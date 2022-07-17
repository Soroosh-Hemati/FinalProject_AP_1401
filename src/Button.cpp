#include "Button.h"
#include <QFont>
#include <QTextDocument>
#include <QPainter>
Button::Button(int pos_x , int pos_y , int w , int h , int size , int textWidth, QString color, QString text,
               QString backGroundColor , QString edgeColor , bool bold) : QGraphicsTextItem() {
    height = h;
    width = w;
    this->color = color;
    this->backGroundColor = backGroundColor;
    this->edgeColor = edgeColor;
    setPos(pos_x , pos_y);
    setPlainText(text);
    setDefaultTextColor(color);
    QFont font;
    font.setPixelSize(size);
    font.setBold(bold);
    setFont(font);
    setTextWidth(textWidth);

}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    QPixmap qPixmap("playersPage");
//    qPixmap = qPixmap.scaled(width , height);
    painter->setBrush(QBrush(QColor(backGroundColor)));
    painter->setPen(QPen(QColor(edgeColor)));
    painter->drawRect(QGraphicsTextItem::boundingRect());
    QGraphicsTextItem::paint(painter, option, widget);
}



void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);
    emit buttonPressed();


}



