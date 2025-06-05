# Custom Widget Designer Plugin

这个项目实现了一组Qt Designer插件，允许在Qt Designer中使用自定义控件。

## 支持的控件

- CustomLabel: 增强型标签控件
- CustomToolTips: 自定义提示框控件
- FilePathIconListWidgetItem: 文件路径图标列表项控件

## 构建说明

1. 确保已安装Qt开发环境和Qt Designer
2. 在项目根目录下执行：
   ```bash
   qmake
   make (或 nmake 如果使用MSVC)
   make install (或 nmake install)
   ```

## 安装说明

1. 编译完成后，插件将自动安装到Qt Designer的插件目录
2. 重启Qt Designer
3. 在Qt Designer的控件面板中，可以找到"Custom Widgets"分组下的自定义控件

## 使用说明

1. 打开Qt Designer
2. 在控件面板中找到"Custom Widgets"分组
3. 将需要的控件拖放到设计界面
4. 在属性编辑器中设置控件属性

## 属性说明

### CustomLabel
- 字体颜色
- 字体大小
- 背景颜色
- 文本省略
- 阴影效果
- 边框样式

### CustomToolTips
- 提示类型
- 显示位置
- 背景颜色
- 文本颜色
- 显示动画

### FilePathIconListWidgetItem
- 图标
- 文本内容
- 提示信息
- 悬停效果
- 选中效果

## 注意事项

1. 确保CustomUIWidget库已经正确编译并安装
2. 插件依赖于CustomUIWidget库，请确保库文件在系统可以找到的位置
3. 如果Qt Designer找不到插件，检查插件是否已正确安装到插件目录 