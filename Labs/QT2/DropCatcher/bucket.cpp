#include "bucket.h"
#include <QKeyEvent>


bucket::bucket(QObject *parent)
    : QObject{parent}
{
}
void bucket::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Right) {
        setPos(x() + 10, y()); // Move right
    } else if (event->key() == Qt::Key_Left) {
        setPos(x() - 10, y()); // Move left
    }

//keep bucket on screen

        if((x()>800)){
                   setPos(800,365);
               }
        if((x()<-50)){
            setPos(-50,365);

        }



}
