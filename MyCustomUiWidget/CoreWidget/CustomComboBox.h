#pragma once

#include <QComboBox>
#include <QListView>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"

/// <summary>
/// 自定义组合框控件类，提供丰富的样式设置
/// </summary>
class CustomUIGlobal_API CustomComboBox : public QComboBox
{
    Q_OBJECT public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomComboBox(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomComboBox();
};
