#include "SkinManager.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

// 使用示例：展示新的皮肤管理系统如何工作
void demonstrateNewSkinSystem()
{
    QApplication app(argc, argv);
    
    // 1. 添加QRC资源文件（只需添加一次）
    SkinManager::instance()->addQrcResource(":/skins/dark_skin.qrc", "dark");
    SkinManager::instance()->addQrcResource(":/skins/light_skin.qrc", "light");
    
    // 2. 创建主窗口
    QWidget mainWindow;
    mainWindow.setWindowTitle("皮肤系统使用示例");
    mainWindow.resize(400, 300);
    
    // 3. 创建组件
    QPushButton* button = new QPushButton("测试按钮", &mainWindow);
    QLabel* label = new QLabel("测试标签", &mainWindow);
    
    // 4. 为组件加载样式（一行代码搞定）
    SkinManager::instance()->loadComponentStyle(button, "QPushButton");
    SkinManager::instance()->loadComponentStyle(label, "QLabel");
    
    // 5. 设置布局
    QVBoxLayout* layout = new QVBoxLayout(&mainWindow);
    layout->addWidget(button);
    layout->addWidget(label);
    
    // 6. 切换皮肤（所有组件自动更新）
    SkinManager::instance()->setCurrentSkinId("dark");
    // 或
    // SkinManager::instance()->setCurrentSkinId("light");
    
    mainWindow.show();
    app.exec();
}

// 在自定义组件中使用示例
class MyCustomWidget : public QWidget
{
public:
    MyCustomWidget(QWidget* parent = nullptr) : QWidget(parent)
    {
        // 自动加载样式
        SkinManager::instance()->loadComponentStyle(this, "MyCustomWidget");
        
        // 启用自动重载（当皮肤切换时自动更新样式）
        SkinManager::instance()->loadComponentStyle(this, "MyCustomWidget");
        
        // 或者使用SkinStyleLoader工具类
        // SkinStyleLoader::loadStyle(this, "MyCustomWidget");
        // SkinStyleLoader::enableAutoReload(this, "MyCustomWidget");
    }
};