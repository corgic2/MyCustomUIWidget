#include <QApplication>
#include "SkinManager.h"
#include "TestWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 无需手动添加qrc资源，已编译到MyCustomUiWidget库中
    // SkinManager会自动加载内置的default皮肤资源

    TestWidget t;          // 原始测试控件 
    t.show();
    return app.exec();
}