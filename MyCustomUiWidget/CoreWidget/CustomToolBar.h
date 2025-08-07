#pragma once

#include <QToolBar>
#include <QWidget>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"

/// <summary>
/// 自定义工具栏控件类，提供丰富的样式和布局设置
/// </summary>
class CustomUIGlobal_API CustomToolBar : public QToolBar
{
    Q_OBJECT

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomToolBar(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomToolBar() override;
};
