#pragma once

#include <QFrame>
#include <QPainter>
#include <QWidget>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"

/// <summary>
/// 自定义Frame控件类，提供丰富的样式和布局设置
/// 支持所有QFrame功能，包括多种边框样式和布局
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

    // 继承QFrame的所有功能，确保在QtDesigner中完全兼容
    // QFrame已经提供了以下功能：
    // - 多种边框样式（NoFrame, Box, Panel, StyledPanel, HLine, VLine, WinPanel）
    // - 线条宽度设置
    // -  margins设置
    // -  layout支持
    // -  自动适应内容大小
};
