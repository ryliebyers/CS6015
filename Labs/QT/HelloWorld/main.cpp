

#include <QPushButton>
#include <QApplication>




int main(int argc, char **argv) {
    QApplication app (argc, argv);
    QPushButton button ("Hello world !");
    button.show();
    return app.exec();
}

