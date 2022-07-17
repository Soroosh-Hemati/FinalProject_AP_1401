#ifndef FINALPROJECT_ADDPHOTO_H
#define FINALPROJECT_ADDPHOTO_H

#include <QGraphicsPixmapItem>
class AddPhoto: public QGraphicsPixmapItem{
private:
    int width;
    int height;
public:
    AddPhoto(QString path , int pos_x , int pos_y , int w , int h);
};
#endif //FINALPROJECT_ADDPHOTO_H
