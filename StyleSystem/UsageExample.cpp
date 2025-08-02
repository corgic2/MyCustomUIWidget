#include "SkinManager.h"
#include "SkinStyleLoader.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

// 示例1：使用SkinStyleLoader的自动加载
class MyCustomButton : public QPushButton
{
    Q_OBJECT

public:
    explicit MyCustomButton(const QString& text = QString(), QWidget* parent = nullptr)
        : QPushButton(text, parent)
    {
        // 方法1：使用SkinStyleLoader自动加载
        SkinStyleLoader::loadStyle(this);
        SkinStyleLoader::enableAutoReload(this);
        
        // 或者使用方法2：使用宏简化
        // AUTO_LOAD_SKIN_STYLE();
        
        // 或者使用方法3：指定样式名
        // AUTO_LOAD_SKIN_STYLE_NAME("CustomButton");
    }
};

// 示例2：使用宏的简洁方式
class MyCustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyCustomWidget(QWidget* parent = nullptr) : QWidget(parent)
    {
        // 一行代码搞定自动加载和重载
        AUTO_LOAD_SKIN_STYLE();
    }
};

// 示例3：使用指定样式名
class MyComplexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyComplexWidget(QWidget* parent = nullptr) : QWidget(parent)
    {
        // 指定样式文件名（不依赖类名）
        AUTO_LOAD_SKIN_STYLE_NAME("ComplexWidgetStyle");
    }
};

// 示例4：高级用法 - 子控件自动加载
class MyCompositeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyCompositeWidget(QWidget* parent = nullptr) : QWidget(parent)
    {
        // 主控件自动加载
        AUTO_LOAD_SKIN_STYLE_NAME("CompositeWidget");
        
        // 子控件自动加载
        m_button = new QPushButton("子按钮", this);
        m_label = new QLabel("子标签", this);
        
        SkinStyleLoader::loadStyle(m_button, "CompositeButton");
        SkinStyleLoader::enableAutoReload(m_button, "CompositeButton");
        
        SkinStyleLoader::loadStyle(m_label, "CompositeLabel");
        SkinStyleLoader::enableAutoReload(m_label, "CompositeLabel");
    }

private:
    QPushButton* m_button;
    QLabel* m_label;
};

// 使用示例：展示新的自动加载系统
void demonstrateAutoSkinLoading()
{
    QApplication app(argc, argv);
    
    // 1. 添加QRC资源文件（只需添加一次）
    SkinManager::instance()->addQrcResource(":/skins/dark_skin.qrc", "dark");
    SkinManager::instance()->addQrcResource(":/skins/light_skin.qrc", "light");
    
    // 2. 创建主窗口
    QWidget mainWindow;
    mainWindow.setWindowTitle("自动皮肤加载系统示例");
    mainWindow.resize(500, 400);
    
    // 3. 创建自动加载样式的组件
    MyCustomButton* autoButton = new MyCustomButton("自动按钮", &mainWindow);
    MyCustomWidget* autoWidget = new MyCustomWidget(&mainWindow);
    MyComplexWidget* complexWidget = new MyComplexWidget(&mainWindow);
    MyCompositeWidget* compositeWidget = new MyCompositeWidget(&mainWindow);
    
    // 4. 创建普通组件（需要手动加载，对比用）
    QPushButton* manualButton = new QPushButton("手动按钮", &mainWindow);
    QLabel* manualLabel = new QLabel("手动标签", &mainWindow);
    
    // 5. 手动加载样式（对比）
    SkinManager::instance()->loadComponentStyle(manualButton, "QPushButton");
    SkinManager::instance()->loadComponentStyle(manualLabel, "QLabel");
    
    // 6. 设置布局
    QVBoxLayout* layout = new QVBoxLayout(&mainWindow);
    layout->addWidget(new QLabel("=== 自动加载的组件 ===", &mainWindow));
    layout->addWidget(autoButton);
    layout->addWidget(autoWidget);
    layout->addWidget(complexWidget);
    layout->addWidget(compositeWidget);
    layout->addWidget(new QLabel("=== 手动加载的组件 ===", &mainWindow));
    layout->addWidget(manualButton);
    layout->addWidget(manualLabel);
    
    // 7. 演示皮肤切换（所有自动加载的组件会自动更新）
    QPushButton* switchButton = new QPushButton("切换皮肤", &mainWindow);
    QObject::connect(switchButton, &QPushButton::clicked, []() {
        static bool isDark = true;
        if (isDark) {
            SkinManager::instance()->setCurrentSkinId("light");
        } else {
            SkinManager::instance()->setCurrentSkinId("dark");
        }
        isDark = !isDark;
    });
    layout->addWidget(switchButton);
    
    mainWindow.show();
    app.exec();
}

// 使用指南
/*
使用方式：

1. 创建自定义组件时，在构造函数中添加自动加载代码：

   // 方法1：使用宏（推荐）
   class MyWidget : public QWidget {
       MyWidget() {
           AUTO_LOAD_SKIN_STYLE();  // 使用类名作为样式名
           // 或
           AUTO_LOAD_SKIN_STYLE_NAME("MyWidgetStyle");  // 指定样式名
       }
   };

2. 只需在QRC中放置对应的QSS文件：
   - 如果使用类名：MyWidget.qss
   - 如果指定样式名：MyWidgetStyle.qss

3. 无需外部调用load接口，组件会自动加载样式
4. 皮肤切换时，组件会自动重新加载对应样式

优势：
- 零外部依赖：组件内部完成所有样式加载
- 即插即用：添加组件到UI无需额外代码
- 动态更新：皮肤切换时自动重载样式
- 灵活命名：支持类名或自定义样式名
- 向后兼容：不影响现有手动加载方式
*/