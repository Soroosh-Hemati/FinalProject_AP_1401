#include <QFont>
#include <QTextDocument>
#include "Label.h"

Label::Label(int pos_x , int pos_y , QString color , QString text , int size , bool bold) {
    setPos(pos_x , pos_y);
    setPlainText(text);
    setDefaultTextColor(color);
    QFont font;
    font.setPixelSize(size);
    font.setBold(bold);
    setFont(font);
    document()->setDocumentMargin(4);
}