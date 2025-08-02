# MuCustomUiWidget 资源文件使用指南

## 资源文件结构

### QSS样式文件位置
```
MuCustomUiWidget/Resources/
├── CustomFrame.qss          # 自定义框架样式
├── CustomComboBox.qss       # 自定义下拉框样式
├── CustomLabel.qss          # 自定义标签样式
├── CustomProgressBar.qss    # 自定义进度条样式
├── CustomToolButton.qss     # 自定义工具按钮样式
├── CustomToolBar.qss        # 自定义工具栏样式
├── CustomButton.qss         # 自定义按钮样式
├── ValidatedLineEdit.qss    # 验证输入框样式
├── FilePicker.qss           # 文件选择器样式
├── ImagePreviewBox.qss      # 图片预览框样式
├── CommonStyles.qss         # 通用样式定义
└── CMakeLists.txt           # 资源构建配置
```

### Qt资源文件
```
MuCustomUiWidget.qrc        # 主资源文件
```

## CMake集成配置

### 已完成的配置
1. **CMakeLists.txt已更新**：包含所有QSS和QRC文件
2. **资源路径配置**：正确设置了Resources目录的搜索路径
3. **Qt资源系统**：启用了`qt5_add_resources`处理QRC文件
4. **构建目标**：所有资源文件都被包含在构建过程中

### 使用方法

#### 1. 添加新的QSS文件
```bash
# 在Resources目录下创建新的QSS文件
touch Resources/NewComponent.qss
```

#### 2. 更新资源文件
编辑`MuCustomUiWidget.qrc`文件，添加新的QSS文件：
```xml
<file>Resources/NewComponent.qss</file>
```

#### 3. 重新构建项目
```bash
# 清理并重新构建
cmake --build . --clean-first
```

#### 4. 在代码中使用资源
```cpp
// 使用资源路径加载样式
QString stylePath = ":/MuCustomUiWidget/Resources/CustomFrame.qss";
QFile file(stylePath);
if (file.open(QIODevice::ReadOnly)) {
    QString styleSheet = file.readAll();
    widget->setStyleSheet(styleSheet);
}
```

## 变量化样式系统

### 支持的CSS变量
所有QSS文件都支持以下变量替换：

#### 颜色变量
- `@primaryColor` - 主色调
- `@secondaryColor` - 次要色调
- `@backgroundColor` - 背景色
- `@fontColor` - 字体颜色
- `@borderColor` - 边框颜色
- `@hoverColor` - 悬停状态色
- `@disabledColor` - 禁用状态色

#### 尺寸变量
- `@borderWidth` - 边框宽度
- `@borderRadius` - 圆角半径
- `@padding` - 内边距
- `@fontSize` - 字体大小

#### 状态变量
- `@successColor` - 成功状态色
- `@warningColor` - 警告状态色
- `@errorColor` - 错误状态色

### 动态样式切换
系统支持运行时样式切换，通过SkinManager实现：

```cpp
// 获取组件样式
SkinManager* manager = SkinManager::instance();
QString style = manager->getComponentStyleSheet("CustomFrame");

// 应用样式到组件
manager->applyComponentStyle(customFrame, "CustomFrame");
```

## 构建验证

### 检查资源包含
运行以下命令验证资源是否正确包含：
```bash
# 检查构建输出
ls build/MuCustomUiWidget_resources_*.cpp

# 验证资源内容
rcc -list MuCustomUiWidget.qrc
```

### 调试资源加载
```cpp
// 检查资源是否存在
QFileInfo fileInfo(":/MuCustomUiWidget/Resources/CustomFrame.qss");
qDebug() << "Resource exists:" << fileInfo.exists();
```

## 最佳实践

1. **命名规范**：组件样式文件名与组件类名保持一致
2. **变量使用**：优先使用CSS变量，便于主题切换
3. **模块化**：通用样式放在CommonStyles.qss中
4. **测试**：为每个新组件创建独立的QSS文件
5. **版本控制**：所有资源文件都应纳入版本控制

## 故障排除

### 常见问题
1. **资源未找到**：检查QRC文件中的路径是否正确
2. **样式未应用**：确认QSS文件语法正确且变量已定义
3. **构建错误**：清理构建目录后重新构建

### 调试工具
```cpp
// 启用资源调试
qputenv("QT_DEBUG_PLUGINS", "1");
```