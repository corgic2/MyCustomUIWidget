#include <QApplication>
#include "TestWidget.h"
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    TestWidget t;
    t.show();
    return app.exec();
}