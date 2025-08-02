#pragma once

#include <QProgressBar>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
/// <summary>
/// 自定义进度条控件类，提供丰富的样式和动画效果设置
/// </summary>
class CustomUIGlobal_API CustomProgressBar : public QProgressBar
{
    Q_OBJECT

    // 使用MEMBER关键字让Qt Designer可以直接编辑这些属性
    Q_PROPERTY(EM_ProgressBarStyle progressBarStyle READ progressBarStyle WRITE SetProgressBarStyle)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE SetBackgroundColor)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE SetProgressColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE SetTextColor)
    Q_PROPERTY(bool enableGradient READ isGradientEnabled WRITE SetEnableGradient)
    Q_PROPERTY(QColor gradientStartColor READ gradientStartColor WRITE SetGradientStartColor)
    Q_PROPERTY(QColor gradientEndColor READ gradientEndColor WRITE SetGradientEndColor)
    Q_PROPERTY(bool enableAnimation READ isAnimationEnabled WRITE SetEnableAnimation)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE SetAnimationDuration)
    Q_PROPERTY(EM_TextPosition textPosition READ textPosition WRITE SetTextPosition)
    Q_PROPERTY(bool enableShadow READ isShadowEnabled WRITE SetEnableShadow)
    Q_PROPERTY(QColor shadowColor READ shadowColor WRITE SetShadowColor)
    Q_PROPERTY(bool enableBorder READ isBorderEnabled WRITE SetEnableBorder)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE SetBorderColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE SetBorderWidth)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE SetBorderRadius)
    Q_PROPERTY(bool enableStripes READ isStripesEnabled WRITE SetEnableStripes)
    Q_PROPERTY(EM_StripeDirection stripeDirection READ stripeDirection WRITE SetStripeDirection)

public:
    /// <summary>
    /// 进度条样式枚举，定义不同的外观风格
    /// </summary>
    enum EM_ProgressBarStyle
    {
        ProgressBarStyle_Default,   /// 默认样式
        ProgressBarStyle_Flat,      /// 扁平样式
        ProgressBarStyle_Rounded,   /// 圆角样式
        ProgressBarStyle_Gradient,  /// 渐变样式
        ProgressBarStyle_Stripe     /// 条纹样式
    };
    Q_ENUM(EM_ProgressBarStyle)

    /// <summary>
    /// 文本位置枚举，定义进度文本的显示位置
    /// </summary>
    enum EM_TextPosition
    {
        TextPosition_Center,   /// 居中显示
        TextPosition_Left,     /// 左侧显示
        TextPosition_Right,    /// 右侧显示
        TextPosition_Outside,  /// 外部显示
        TextPosition_Hidden    /// 隐藏文本
    };
    Q_ENUM(EM_TextPosition)

    /// <summary>
    /// 条纹方向枚举，定义条纹样式的方向
    /// </summary>
    enum EM_StripeDirection
    {
        StripeDirection_LeftToRight,  /// 从左到右
        StripeDirection_RightToLeft,  /// 从右到左
        StripeDirection_Diagonal      /// 对角线
    };
    Q_ENUM(EM_StripeDirection)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomProgressBar(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomProgressBar() override;

    /// <summary>
    /// 设置进度条样式
    /// </summary>
    /// <param name="style">样式枚举值</param>
    void SetProgressBarStyle(EM_ProgressBarStyle style);

    /// <summary>
    /// 获取进度条样式
    /// </summary>
    EM_ProgressBarStyle progressBarStyle() const;

    /// <summary>
    /// 设置背景颜色
    /// </summary>
    /// <param name="color">背景颜色</param>
    void SetBackgroundColor(const QColor& color);

    /// <summary>
    /// 获取背景颜色
    /// </summary>
    QColor backgroundColor() const;

    /// <summary>
    /// 设置进度颜色
    /// </summary>
    /// <param name="color">进度颜色</param>
    void SetProgressColor(const QColor& color);

    /// <summary>
    /// 获取进度颜色
    /// </summary>
    QColor progressColor() const;

    /// <summary>
    /// 设置文本颜色
    /// </summary>
    /// <param name="color">文本颜色</param>
    void SetTextColor(const QColor& color);

    /// <summary>
    /// 获取文本颜色
    /// </summary>
    QColor textColor() const;

    /// <summary>
    /// 设置是否启用渐变
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetEnableGradient(bool enable);

    /// <summary>
    /// 获取是否启用渐变
    /// </summary>
    bool isGradientEnabled() const;

    /// <summary>
    /// 设置渐变起始颜色
    /// </summary>
    /// <param name="color">起始颜色</param>
    void SetGradientStartColor(const QColor& color);

    /// <summary>
    /// 获取渐变起始颜色
    /// </summary>
    QColor gradientStartColor() const;

    /// <summary>
    /// 设置渐变结束颜色
    /// </summary>
    /// <param name="color">结束颜色</param>
    void SetGradientEndColor(const QColor& color);

    /// <summary>
    /// 获取渐变结束颜色
    /// </summary>
    QColor gradientEndColor() const;

    /// <summary>
    /// 设置是否启用动画
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetEnableAnimation(bool enable);

    /// <summary>
    /// 获取是否启用动画
    /// </summary>
    bool isAnimationEnabled() const;

    /// <summary>
    /// 设置动画持续时间
    /// </summary>
    /// <param name="duration">持续时间（毫秒）</param>
    void SetAnimationDuration(int duration);

    /// <summary>
    /// 获取动画持续时间
    /// </summary>
    int animationDuration() const;

    /// <summary>
    /// 设置文本位置
    /// </summary>
    /// <param name="position">文本位置枚举值</param>
    void SetTextPosition(EM_TextPosition position);

    /// <summary>
    /// 获取文本位置
    /// </summary>
    EM_TextPosition textPosition() const;

    /// <summary>
    /// 设置是否启用阴影
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetEnableShadow(bool enable);

    /// <summary>
    /// 获取是否启用阴影
    /// </summary>
    bool isShadowEnabled() const;

    /// <summary>
    /// 设置阴影颜色
    /// </summary>
    /// <param name="color">阴影颜色</param>
    void SetShadowColor(const QColor& color);

    /// <summary>
    /// 获取阴影颜色
    /// </summary>
    QColor shadowColor() const;

    /// <summary>
    /// 设置是否启用边框
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetEnableBorder(bool enable);

    /// <summary>
    /// 获取是否启用边框
    /// </summary>
    bool isBorderEnabled() const;

    /// <summary>
    /// 设置边框颜色
    /// </summary>
    /// <param name="color">边框颜色</param>
    void SetBorderColor(const QColor& color);

    /// <summary>
    /// 获取边框颜色
    /// </summary>
    QColor borderColor() const;

    /// <summary>
    /// 设置边框宽度
    /// </summary>
    /// <param name="width">边框宽度</param>
    void SetBorderWidth(int width);

    /// <summary>
    /// 获取边框宽度
    /// </summary>
    int borderWidth() const;

    /// <summary>
    /// 设置边框圆角半径
    /// </summary>
    /// <param name="radius">圆角半径</param>
    void SetBorderRadius(int radius);

    /// <summary>
    /// 获取边框圆角半径
    /// </summary>
    int borderRadius() const;

    /// <summary>
    /// 设置是否启用条纹
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetEnableStripes(bool enable);

    /// <summary>
    /// 获取是否启用条纹
    /// </summary>
    bool isStripesEnabled() const;

    /// <summary>
    /// 设置条纹方向
    /// </summary>
    /// <param name="direction">条纹方向枚举值</param>
    void SetStripeDirection(EM_StripeDirection direction);

    /// <summary>
    /// 获取条纹方向
    /// </summary>
    EM_StripeDirection stripeDirection() const;

    /// <summary>
    /// 动画设置进度值
    /// </summary>
    /// <param name="value">目标进度值</param>
    void SetValueWithAnimation(int value);

    /// <summary>
    /// 重置进度条到初始状态
    /// </summary>
    void Reset();

public slots:
    /// <summary>
    /// 启动条纹动画槽函数
    /// </summary>
    void SlotStartStripeAnimation();

    /// <summary>
    /// 停止条纹动画槽函数
    /// </summary>
    void SlotStopStripeAnimation();

signals:
    /// <summary>
    /// 进度值改变信号
    /// </summary>
    /// <param name="value">新的进度值</param>
    void SigValueChanged(int value);

    /// <summary>
    /// 动画完成信号
    /// </summary>
    void SigAnimationFinished();

protected:
    /// <summary>
    /// 重写绘制事件
    /// </summary>
    /// <param name="event">绘制事件指针</param>
    void paintEvent(QPaintEvent* event) override;

    /// <summary>
    /// 重写值改变事件
    /// </summary>
    /// <param name="value">新的值</param>
    void valueChanged(int value);

private slots:
    /// <summary>
    /// 动画完成槽函数
    /// </summary>
    void SlotAnimationFinished();

    /// <summary>
    /// 条纹动画更新槽函数
    /// </summary>
    void SlotUpdateStripeAnimation();

private:
    /// <summary>
    /// 初始化进度条
    /// </summary>
    void InitializeProgressBar();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

    /// <summary>
    /// 绘制背景
    /// </summary>
    /// <param name="painter">绘制器指针</param>
    /// <param name="rect">绘制区域</param>
    void DrawBackground(QPainter* painter, const QRect& rect);

    /// <summary>
    /// 绘制进度
    /// </summary>
    /// <param name="painter">绘制器指针</param>
    /// <param name="rect">绘制区域</param>
    void DrawProgress(QPainter* painter, const QRect& rect);

    /// <summary>
    /// 绘制条纹
    /// </summary>
    /// <param name="painter">绘制器指针</param>
    /// <param name="rect">绘制区域</param>
    void DrawStripes(QPainter* painter, const QRect& rect);

    /// <summary>
    /// 绘制文本
    /// </summary>
    /// <param name="painter">绘制器指针</param>
    /// <param name="rect">绘制区域</param>
    void DrawText(QPainter* painter, const QRect& rect);

    /// <summary>
    /// 获取进度区域
    /// </summary>
    /// <param name="rect">总区域</param>
    /// <returns>进度区域</returns>
    QRect GetProgressRect(const QRect& rect) const;

private:
    EM_ProgressBarStyle m_progressBarStyle;        /// 进度条样式
    QColor m_backgroundColor;                      /// 背景颜色
    QColor m_progressColor;                        /// 进度颜色
    QColor m_textColor;                           /// 文本颜色
    bool m_enableGradient;                        /// 是否启用渐变
    QColor m_gradientStartColor;                  /// 渐变起始颜色
    QColor m_gradientEndColor;                    /// 渐变结束颜色
    bool m_enableAnimation;                       /// 是否启用动画
    int m_animationDuration;                      /// 动画持续时间
    EM_TextPosition m_textPosition;               /// 文本位置
    bool m_enableShadow;                          /// 是否启用阴影
    QColor m_shadowColor;                         /// 阴影颜色
    bool m_enableBorder;                          /// 是否启用边框
    QColor m_borderColor;                         /// 边框颜色
    int m_borderWidth;                            /// 边框宽度
    int m_borderRadius;                           /// 边框圆角半径
    bool m_enableStripes;                         /// 是否启用条纹
    EM_StripeDirection m_stripeDirection;         /// 条纹方向
    
    QPropertyAnimation* m_animation;              /// 进度动画
    QTimer* m_stripeTimer;                        /// 条纹动画定时器
    int m_stripeOffset;                           /// 条纹偏移量
    QString m_styleSheet;                         /// 样式表字符串
};

Q_DECLARE_METATYPE(CustomProgressBar::EM_ProgressBarStyle)
Q_DECLARE_METATYPE(CustomProgressBar::EM_TextPosition)
Q_DECLARE_METATYPE(CustomProgressBar::EM_StripeDirection)