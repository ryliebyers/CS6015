#ifndef WATER_H
#define WATER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>


class water : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit water(QObject *parent = nullptr);
private slots:
    void move_droplet();
signals:
};

#endif // WATER_H
