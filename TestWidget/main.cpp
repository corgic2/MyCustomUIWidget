#include <QApplication>
#include <QDir>
#include "StyleSystem/SkinManager.h"
#include "TestWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    // 添加皮肤配置
    SkinManager::instance()->addSkinVersionInfo("default", ":/Config/Default/skin_config.json");
    SkinManager::instance()->addQrcResource(":/CustomUiWidget/CoreWidget");
    SkinManager::instance()->addQrcResource(":/CustomUiWidget/DomainWidget");
    SkinManager::instance()->addQrcResource(":/Config/Default");
    // 设置默认皮肤
    SkinManager::instance()->setCurrentSkinId("default");
    
    TestWidget t;
    t.show();
    return app.exec();
}