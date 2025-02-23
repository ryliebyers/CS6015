#include "water.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QRandomGenerator>
water::water(QObject *parent)
    : QObject{parent}
{


    setPixmap((QPixmap(":/images/water.gif")).scaled(30, 30));
    QTimer *timer_drop = new QTimer(this);
    connect(timer_drop, &QTimer::timeout, this, &water::move_droplet);
    int randomX = QRandomGenerator::global()->bounded(0, 908);
    setPos(randomX,0);
    timer_drop->start(20); // Move droplet every 20 milliseconds

}
void water::move_droplet() {
    QPointF currentPos = scenePos();


    setPos(currentPos.x(), currentPos.y() + 5);
    if((y()>510)  || (y()<0) ||(!(scene()->collidingItems(this).isEmpty()))){
        scene()->removeItem(this);
        delete this;

    }

}
