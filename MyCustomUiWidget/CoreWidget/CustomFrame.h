#pragma once

#include <QFrame>
#include <QPainter>
#include <QWidget>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
/// <summary>
/// 自定义Frame控件类，提供丰富的样式和布局设置
/// </summary>
class CustomUIGlobal_API CustomFrame : public QFrame
{
    Q_OBJECT

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomFrame(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomFrame() override;
};
