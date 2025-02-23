#ifndef BUCKET_H
#define BUCKET_H

#include <QObject>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class bucket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit bucket(QObject *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
signals:
};

#endif // BUCKET_H
