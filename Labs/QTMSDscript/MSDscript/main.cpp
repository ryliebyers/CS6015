#include <QApplication>
#include "msdqt.h"
#include "Env.h"
#include "expr.h"
#include "parse.hpp"
#include "val.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MSDQT msdqt;
    msdqt.setWindowTitle("Expression Evaluator");
    msdqt.show();

    return app.exec();
}
