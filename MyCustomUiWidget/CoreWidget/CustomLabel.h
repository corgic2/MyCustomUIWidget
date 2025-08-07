#pragma once

#include <QLabel>
#include <QWidget>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"

/// <summary>
/// 自定义标签控件类，提供丰富的样式和特效设置
/// </summary>
class CustomUIGlobal_API CustomLabel : public QLabel
{
    Q_OBJECT public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomLabel(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomLabel() override;
};
