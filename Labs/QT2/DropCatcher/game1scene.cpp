#include "game1scene.h"
#include <QGraphicsSceneMouseEvent>
#include "bucket.h"
#include "water.h"
#include <QRandomGenerator>
#include <QLabel>
#include <QGraphicsScene>



game1scene::game1scene() {
    // Set background image
    setBackgroundBrush(QBrush(QImage(":/images/background.jpg").scaledToHeight(512).scaledToWidth(910)));
    setSceneRect(0, 0, 908, 510);

    // Create and add bucket object
    bucket *b = new bucket();
    b->setPixmap((QPixmap(":/images/bucket.png")).scaled(150, 150));
    b->setPos(400, 365); // Set initial position
    addItem(b);

    // Make bucket focusable and set focus
    b->setFlag(QGraphicsItem::ItemIsFocusable);
    b->setFocus();

    // Start timer for water droplets
    QTimer *timer_water = new QTimer(this);
    connect(timer_water, &QTimer::timeout, this, &game1scene::add_water_droplet);
    timer_water->start(1000); // Spawn water every 1 second
}

void game1scene::add_water_droplet() {
    // Create and add water droplet object
    water *w = new water();
    addItem(w);
}



