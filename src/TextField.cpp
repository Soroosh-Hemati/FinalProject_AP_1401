#include <QFont>
#include "TextField.h"
#include <QPainter>
#include <QTextDocument>
#include <QStyleOptionGraphicsItem>
TextField::TextField(int pos_x, int pos_y, int w, int h, int size, int textWidth, QString color, QString text,
                     QString backGroundColor, QString edgeColor, bool bold) : QGraphicsTextItem() {
    height = h;
    width = w;
    this->color = color;
    this->backGroundColor = backGroundColor;
    this->edgeColor = edgeColor;
    setPos(pos_x, pos_y);
    setPlainText(text);
    setDefaultTextColor("#b3b3b3");
    QFont font;
    font.setPixelSize(size);
    font.setBold(bold);
    setFont(font);
    setTextWidth(textWidth);
    setTextInteractionFlags(Qt::TextEditorInteraction);
    document()->setDocumentMargin(10);
}


void TextField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //    QPixmap qPixmap("playersPage");
//    qPixmap = qPixmap.scaled(width , height);
    painter->setBrush(QBrush(QColor(backGroundColor)));
    painter->setPen(QPen(QColor(edgeColor)));
    painter->drawRect(QGraphicsTextItem::boundingRect());
    auto newOption = new QStyleOptionGraphicsItem(*option);
    newOption->state = QStyle::State_None;
    QGraphicsTextItem::paint(painter, newOption, widget);


}

void TextField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);
    setPlainText("");

    setDefaultTextColor(color);
}
