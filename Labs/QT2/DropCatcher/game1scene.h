#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include "bucket.h"
//#include "water.h"

class game1scene : public QGraphicsScene
{
    Q_OBJECT
public:
     game1scene();
    bucket *b;
    QTimer *dropletTimer;
private slots:
    void add_water_droplet();

signals:
};

#endif // GAME1SCENE_H
