# MuCustomUiWidget 皮肤系统使用指南

## 概述

本项目已经实现了基于组件的皮肤管理系统，支持为每个自定义组件创建独立的QSS样式文件。

## 目录结构

```
MuCustomUiWidget/
├── Resources/              # 组件样式文件目录
│   ├── CustomFrame.qss
│   ├── CustomComboBox.qss
│   ├── CustomLabel.qss
│   ├── CustomProgressBar.qss
│   ├── CustomToolButton.qss
│   ├── CustomToolBar.qss
│   ├── ValidatedLineEdit.qss
│   ├── FilePicker.qss
│   └── ImagePreviewBox.qss
├── MuCustomUiWidget.qrc    # 资源文件
├── CommonDefine/
│   ├── ComponentStyleManager.h/.cpp  # 组件样式管理器
│   └── SkinIntegration.h/.cpp        # 皮肤集成工具
└── CoreWidget/            # 自定义组件
```

## 使用方法

### 1. 自动样式应用

所有自定义组件在创建时会自动应用对应的样式文件：
- 组件类名与QSS文件名自动匹配
- 支持皮肤切换时自动更新样式

### 2. 手动注册组件

对于非自定义组件或特殊情况，可以手动注册：

```cpp
#include "CommonDefine/SkinIntegration.h"

// 方法1：使用工具类
SkinIntegrationHelper::registerWidget(myWidget, "MyWidgetClass");

// 方法2：使用宏
REGISTER_COMPONENT_STYLE(MyWidgetClass);

// 方法3：直接调用管理器
ComponentStyleManager::instance()->registerComponent(myWidget, "MyWidgetClass");
ComponentStyleManager::instance()->applyStyle(myWidget);
```

### 3. 皮肤切换

```cpp
// 切换皮肤时，所有组件样式会自动更新
SkinManager::instance()->applySkin("dark");

// 或者手动刷新所有组件
ComponentStyleManager::instance()->applyStylesToAllComponents("dark");
```

### 4. 创建新组件样式

1. 在 `Resources/` 目录下创建新的QSS文件
2. 文件名必须与组件类名相同（如 `MyNewWidget.qss`）
3. 在 `MuCustomUiWidget.qrc` 中添加文件引用
4. 在组件构造函数中添加注册代码

### 5. 样式变量支持

QSS文件支持使用颜色变量：
- `@backgroundColor` - 背景色
- `@primaryColor` - 主色调
- `@fontColor` - 字体颜色
- `@borderColor` - 边框颜色
- `@hoverColor` - 悬停颜色
- `@selectedColor` - 选中颜色
- `@disabledColor` - 禁用颜色

## 示例

### 创建自定义组件样式

1. 创建 `Resources/MyCustomWidget.qss`：
```css
MyCustomWidget {
    background-color: @backgroundColor;
    border: 2px solid @borderColor;
    border-radius: 4px;
}

MyCustomWidget:hover {
    border-color: @hoverColor;
}
```

2. 在组件构造函数中：
```cpp
MyCustomWidget::MyCustomWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化代码...
    REGISTER_COMPONENT_STYLE(MyCustomWidget);
}
```

## 注意事项

1. 确保QSS文件名与组件类名完全一致（区分大小写）
2. 使用 `MuCustomUiWidget.qrc` 管理所有资源文件
3. 皮肤切换时会自动应用新样式，无需手动刷新
4. 组件销毁时会自动从管理器中注销

## 调试技巧

- 检查控制台输出是否有样式文件加载错误
- 使用 `ComponentStyleManager::instance()->getComponentClassName(widget)` 验证类名
- 通过 `SkinManager::instance()->getComponentStyleSheet("ClassName")` 获取样式内容