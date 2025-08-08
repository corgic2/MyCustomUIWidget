#pragma once

#include <QtWidgets/QToolButton>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../UtilsWidget/CustomToolTips.h"
/// <summary>
/// 自定义工具按钮类，提供丰富的样式设置和提示功能
/// </summary>
class CustomUIGlobal_API CustomToolButton : public QToolButton
{
    Q_OBJECT
public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomToolButton(QWidget* parent = nullptr);
    CustomToolButton(const QString& text, QWidget* parent = nullptr);
    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomToolButton();
};
