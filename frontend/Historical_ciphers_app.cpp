#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setMinimumSize(700, 400);
    window.show();

    return app.exec();
}
