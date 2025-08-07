#pragma once

#include <QEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QToolTip>
#include <QWidget>
#include <QScreen>
#include <QGuiApplication>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "ui_CustomToolTips.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class CustomToolTipsClass;
};

QT_END_NAMESPACE

/// <summary>
/// 自定义提示框控件类，提供美观的提示框效果和丰富的自定义选项
/// </summary>
class CustomUIGlobal_API CustomToolTips : public QWidget
{
    Q_OBJECT public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    CustomToolTips(QWidget* parent = Q_NULLPTR);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomToolTips() override;

private:
    Ui::CustomToolTipsClass* m_ui; /// UI对象指针
};
