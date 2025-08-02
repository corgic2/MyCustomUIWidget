# 新版皮肤管理系统使用指南

## 概述

新版皮肤管理系统简化了组件样式加载流程，只需一行代码即可为组件加载样式，无需复杂的注册和管理过程。

## 核心特性

1. **简化API**：只需调用`loadComponentStyle`即可加载样式
2. **QRC自动发现**：自动从QRC文件中查找组件对应的QSS样式
3. **颜色变量支持**：支持通过JSON配置文件定义颜色变量
4. **自动重载**：皮肤切换时组件自动更新样式

## 使用步骤

### 1. 添加QRC资源

```cpp
// 只需添加一次QRC文件路径
SkinManager::instance()->addQrcResource(":/skins/dark_skin.qrc", "dark");
SkinManager::instance()->addQrcResource(":/skins/light_skin.qrc", "light");
```

### 2. 为组件加载样式

**方法1：直接调用**
```cpp
// 在组件构造函数中
MyWidget::MyWidget(QWidget* parent) : QWidget(parent)
{
    // 自动从QRC中查找MyWidget.qss并应用
    SkinManager::instance()->loadComponentStyle(this);
}
```

**方法2：使用SkinStyleLoader工具类**
```cpp
#include "CommonDefine/SkinStyleLoader.h"

MyWidget::MyWidget(QWidget* parent) : QWidget(parent)
{
    // 加载样式
    SkinStyleLoader::loadStyle(this);
    
    // 启用自动重载（皮肤切换时自动更新）
    SkinStyleLoader::enableAutoReload(this);
}
```

### 3. QRC文件结构要求

皮肤QRC文件应包含以下结构：

```
:/skin_name/
├── MyWidget.qss          # 组件样式文件（自动查找）
├── components/
│   ├── MyWidget.qss      # 备选路径
│   └── Button.qss
├── styles/
│   └── MyWidget.qss      # 备选路径
└── colors.json           # 颜色变量配置（可选）
```

### 4. 颜色变量配置

在colors.json中定义颜色变量：

```json
{
    "primaryColor": "#0078d4",
    "secondaryColor": "#106ebe",
    "backgroundColor": "#ffffff",
    "textColor": "#323130"
}
```

在QSS文件中使用：

```css
MyWidget {
    background-color: {{primaryColor}};
    color: {{textColor}};
}
```

### 5. 切换皮肤

```cpp
// 全局切换皮肤，所有启用自动重载的组件会自动更新
SkinManager::instance()->setCurrentSkinId("dark");
```

## 完整示例

```cpp
#include <QApplication>
#include "StyleSystem/SkinManager.h"
#include "CommonDefine/SkinStyleLoader.h"

class MyButton : public QPushButton
{
public:
    MyButton(const QString& text, QWidget* parent = nullptr) 
        : QPushButton(text, parent)
    {
        // 加载样式
        SkinStyleLoader::loadStyle(this, "MyButton");
        
        // 启用自动重载
        SkinStyleLoader::enableAutoReload(this, "MyButton");
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 添加皮肤资源
    SkinManager::instance()->addQrcResource(":/skins/dark.qrc");
    SkinManager::instance()->addQrcResource(":/skins/light.qrc");
    
    // 创建界面
    QWidget window;
    MyButton* button = new MyButton("测试按钮", &window);
    
    window.show();
    return app.exec();
}
```

## 文件命名规则

- 组件样式文件应以组件类名命名
- 支持以下查找顺序：
  1. `:/skin_name/ComponentName.qss`
  2. `:/skin_name/components/ComponentName.qss`
  3. `:/skin_name/styles/ComponentName.qss`

## 注意事项

1. QRC文件必须在编译前添加到项目
2. 样式文件必须使用UTF-8编码
3. 颜色变量区分大小写
4. 组件类名可以通过第二个参数手动指定