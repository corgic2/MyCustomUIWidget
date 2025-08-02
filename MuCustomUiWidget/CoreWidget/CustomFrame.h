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
    // 使用MEMBER关键字让Qt Designer可以直接编辑这些属性
    Q_PROPERTY(QColor m_backgroundColor READ GetBackgroundColor WRITE SetBackgroundColor)
    Q_PROPERTY(bool m_leftBorder READ HasLeftBorder WRITE EnableLeftBorder)
    Q_PROPERTY(bool m_topBorder READ HasTopBorder WRITE EnableTopBorder)
    Q_PROPERTY(bool m_rightBorder READ HasRightBorder WRITE EnableRightBorder)
    Q_PROPERTY(bool m_bottomBorder READ HasBottomBorder WRITE EnableBottomBorder)
    Q_PROPERTY(QColor m_borderColor READ GetBorderColor WRITE SetBorderColor)
    Q_PROPERTY(int m_borderWidth READ GetBorderWidth WRITE SetBorderWidth)
    Q_PROPERTY(int m_padding READ GetPadding WRITE SetPadding)
    Q_PROPERTY(EM_BackgroundType m_backgroundType READ GetBackgroundType WRITE SetBackgroundType)

public:
    /// <summary>
    /// 背景类型枚举，定义Frame的背景显示方式
    /// </summary>
    enum EM_BackgroundType
    {
        BackgroundType_Transparent, /// 透明背景
        BackgroundType_Solid, /// 纯色背景
        BackgroundType_Gradient /// 渐变背景
    };

    Q_ENUM(EM_BackgroundType)

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

    /// <summary>
    /// 设置背景颜色
    /// </summary>
    /// <param name="color">RGB颜色值</param>
    void SetBackgroundColor(const QColor& color);

    /// <summary>
    /// 设置背景类型
    /// </summary>
    /// <param name="type">背景类型枚举值</param>
    void SetBackgroundType(const EM_BackgroundType& type);

    /// <summary>
    /// 设置渐变背景
    /// </summary>
    /// <param name="startColor">起始颜色</param>
    /// <param name="endColor">结束颜色</param>
    void SetGradientBackground(const QColor& startColor, const QColor& endColor);

    /// <summary>
    /// 启用左边框
    /// </summary>
    /// <param name="enable">是否启用</param>
    void EnableLeftBorder(bool enable = true);

    /// <summary>
    /// 启用上边框
    /// </summary>
    /// <param name="enable">是否启用</param>
    void EnableTopBorder(bool enable = true);

    /// <summary>
    /// 启用右边框
    /// </summary>
    /// <param name="enable">是否启用</param>
    void EnableRightBorder(bool enable = true);

    /// <summary>
    /// 启用下边框
    /// </summary>
    /// <param name="enable">是否启用</param>
    void EnableBottomBorder(bool enable = true);

    /// <summary>
    /// 设置内边距
    /// </summary>
    /// <param name="padding">内边距大小</param>
    void SetPadding(int padding);

    /// <summary>
    /// 设置边框宽度
    /// </summary>
    /// <param name="width">边框宽度</param>
    void SetBorderWidth(int width);

    /// <summary>
    /// 设置边框颜色
    /// </summary>
    /// <param name="color">边框颜色</param>
    void SetBorderColor(const QColor& color);


    // Getters
    QColor GetBackgroundColor() const { return m_backgroundColor; }

    bool HasLeftBorder() const { return m_hasLeftBorder; }

    bool HasTopBorder() const { return m_hasTopBorder; }

    bool HasRightBorder() const { return m_hasRightBorder; }

    bool HasBottomBorder() const { return m_hasBottomBorder; }

    QColor GetBorderColor() const { return m_borderColor; }

    int GetBorderWidth() const { return m_borderWidth; }

    int GetPadding() const { return m_padding; }

    EM_BackgroundType GetBackgroundType() const { return m_backgroundType; }

protected:
    /// <summary>
    /// 绘制事件
    /// </summary>
    void paintEvent(QPaintEvent* event) override;

private:
    /// <summary>
    /// 初始化Frame
    /// </summary>
    void InitializeFrame();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

private:
    QString m_styleSheet; /// 样式表字符串
    QColor m_backgroundColor; /// 背景颜色
    QColor m_gradientStartColor; /// 渐变起始颜色
    QColor m_gradientEndColor; /// 渐变结束颜色
    bool m_hasLeftBorder; /// 是否有左边框
    bool m_hasTopBorder; /// 是否有上边框
    bool m_hasRightBorder; /// 是否有右边框
    bool m_hasBottomBorder; /// 是否有下边框
    QColor m_borderColor; /// 边框颜色
    int m_borderWidth; /// 边框宽度
    int m_padding; /// 内边距
    EM_BackgroundType m_backgroundType; /// 背景类型
};

Q_DECLARE_METATYPE(CustomFrame::EM_BackgroundType)
