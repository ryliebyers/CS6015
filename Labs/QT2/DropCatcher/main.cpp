#include <QApplication>
#include "game1scene.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    game1scene *scene1 = new game1scene();

    // Add view to visualize the scene
    QGraphicsView *view_obj = new QGraphicsView(scene1);
    view_obj->setScene(scene1);
    view_obj->show();

    // Fix window size and disable scrollbars
    view_obj->setFixedSize(910, 512);
    view_obj->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_obj->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    return app.exec();
}
