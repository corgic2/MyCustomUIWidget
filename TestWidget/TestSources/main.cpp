#include <QApplication>
#include "TestWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    TestWidget t;          // 原始测试控件
    t.show();
    return app.exec();
}