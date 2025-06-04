#pragma once

#include <QEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QToolTip>
#include <QWidget>
#include "UIWidgetColorDefine.h"
#include "UIWidgetGlobal.h"
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
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    /// <summary>
    /// Tips显示位置枚举，定义提示框相对于目标的显示位置
    /// </summary>
    enum EM_TipsPosition
    {
        TopLeft,     /// 目标左上方
        Top,         /// 目标正上方
        TopRight,    /// 目标右上方
        Left,        /// 目标左侧
        Right,       /// 目标右侧
        BottomLeft,  /// 目标左下方
        Bottom,      /// 目标正下方
        BottomRight  /// 目标右下方
    };

    /// <summary>
    /// Tips类型枚举，定义不同类型的提示框样式
    /// </summary>
    enum EM_TipsType
    {
        Normal,   /// 普通提示
        Info,     /// 信息提示
        Warning,  /// 警告提示
        Error,    /// 错误提示
        Success   /// 成功提示
    };

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    CustomToolTips(QWidget* parent = Q_NULLPTR);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomToolTips() override;

    /// <summary>
    /// 设置提示文本
    /// </summary>
    /// <param name="str">提示文本内容</param>
    void SetToolTips(const QString& str);

    /// <summary>
    /// 设置扩展提示文本
    /// </summary>
    /// <param name="str">扩展提示文本内容</param>
    void SetToolTipsEx(const QString& str);

    /// <summary>
    /// 设置提示框类型
    /// </summary>
    /// <param name="type">提示框类型枚举值</param>
    void SetTipsType(EM_TipsType type);

    /// <summary>
    /// 设置显示位置
    /// </summary>
    /// <param name="position">显示位置枚举值</param>
    void SetPosition(EM_TipsPosition position);

    /// <summary>
    /// 设置显示持续时间
    /// </summary>
    /// <param name="msecs">持续时间(毫秒)</param>
    void SetShowDuration(int msecs);

    /// <summary>
    /// 设置动画持续时间
    /// </summary>
    /// <param name="msecs">动画时间(毫秒)</param>
    void SetAnimationDuration(int msecs);

    /// <summary>
    /// 设置背景颜色
    /// </summary>
    /// <param name="color">RGBA颜色值</param>
    void SetBackgroundColor(const UIColorDefine::ST_ColorRgba& color);

    /// <summary>
    /// 设置文本颜色
    /// </summary>
    /// <param name="color">RGB颜色值</param>
    void SetTextColor(const UIColorDefine::ST_ColorRgb& color);

    /// <summary>
    /// 设置字体大小
    /// </summary>
    /// <param name="size">字体大小</param>
    void SetFontSize(int size);

    /// <summary>
    /// 设置圆角半径
    /// </summary>
    /// <param name="radius">圆角半径值</param>
    void SetRadius(int radius);

    /// <summary>
    /// 启用阴影效果
    /// </summary>
    /// <param name="enable">是否启用</param>
    void EnableShadow(bool enable = true);

    /// <summary>
    /// 显示提示框
    /// </summary>
    /// <param name="pos">显示位置</param>
    void ShowTips(const QPoint& pos);

    /// <summary>
    /// 为指定控件显示提示框
    /// </summary>
    /// <param name="widget">目标控件</param>
    /// <param name="offset">位置偏移量</param>
    void ShowTipsForWidget(QWidget* widget, const QPoint& offset = QPoint(0, 0));

    /// <summary>
    /// 隐藏提示框
    /// </summary>
    void HideTips();

protected:
    void enterEvent(QEvent* event) override;    /// 鼠标进入事件
    void leaveEvent(QEvent* event) override;    /// 鼠标离开事件
    void paintEvent(QPaintEvent* event) override;  /// 绘制事件

private:
    /// <summary>
    /// 初始化UI
    /// </summary>
    void InitializeUI();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

    /// <summary>
    /// 设置动画
    /// </summary>
    void SetupAnimation();

    /// <summary>
    /// 计算显示位置
    /// </summary>
    /// <param name="targetPos">目标位置</param>
    /// <param name="targetSize">目标大小</param>
    /// <returns>计算后的显示位置</returns>
    QPoint CalculatePosition(const QPoint& targetPos, const QSize& targetSize);

    /// <summary>
    /// 获取当前透明度
    /// </summary>
    qreal opacity() const { return m_opacity; }

    /// <summary>
    /// 设置透明度
    /// </summary>
    void setOpacity(qreal opacity);

public slots:
    /// <summary>
    /// 隐藏动画完成槽函数
    /// </summary>
    void OnHideAnimationFinished();

signals:
    void ToolTipsHidden();  /// 提示框隐藏信号
    void ToolTipsShown();   /// 提示框显示信号

private:
    Ui::CustomToolTipsClass* m_ui;              /// UI对象指针
    bool m_isAnimating;                         /// 是否正在动画中
    QPoint m_targetPosition;                    /// 目标位置
    QTimer* m_hideTimer;                        /// 隐藏定时器
    QPropertyAnimation* m_opacityAnimation;     /// 透明度动画
    EM_TipsPosition m_position;                 /// 显示位置
    EM_TipsType m_tipsType;                    /// 提示框类型

    UIColorDefine::ST_ColorRgba m_backgroundColor;  /// 背景颜色
    UIColorDefine::ST_ColorRgb m_textColor;        /// 文本颜色
    int m_fontSize;                                 /// 字体大小
    int m_radius;                                  /// 圆角半径
    bool m_hasShadow;                              /// 是否有阴影
    qreal m_opacity;                               /// 透明度值

    int m_showDuration;                            /// 显示持续时间
    int m_animationDuration;                       /// 动画持续时间
};

/// <summary>
/// 全局提示框管理器
/// </summary>
class CustomToolTipsManager
{
public:
    /// <summary>
    /// 获取全局实例
    /// </summary>
    static CustomToolTips* GetInstance();

    /// <summary>
    /// 显示提示框
    /// </summary>
    /// <param name="text">提示文本</param>
    /// <param name="widget">目标控件</param>
    /// <param name="type">提示框类型</param>
    static void ShowTips(const QString& text, QWidget* widget,
                        CustomToolTips::EM_TipsType type = CustomToolTips::Normal);
private:
    static CustomToolTips* s_instance;  /// 全局单例指针
};
