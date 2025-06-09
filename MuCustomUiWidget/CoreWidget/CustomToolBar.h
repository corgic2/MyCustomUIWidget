#pragma once

#include <QToolBar>
#include <QAction>
#include <QColor>
#include <QPainter>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"

/// <summary>
/// 自定义工具栏类，提供现代化UI风格和丰富的样式设置
/// </summary>
class CustomUIGlobal_API CustomToolBar : public QToolBar
{
    Q_OBJECT

        Q_PROPERTY(int iconSize READ GetIconSize WRITE SetIconSize)
        Q_PROPERTY(int spacing READ GetSpacing WRITE SetSpacing)
        Q_PROPERTY(QColor backgroundColor READ GetBackgroundColor WRITE SetBackgroundColor)
        Q_PROPERTY(QColor borderColor READ GetBorderColor WRITE SetBorderColor)
        Q_PROPERTY(QColor hoverColor READ GetHoverColor WRITE SetHoverColor)
        Q_PROPERTY(QColor pressedColor READ GetPressedColor WRITE SetPressedColor)
        Q_PROPERTY(bool hasShadow READ GetHasShadow WRITE SetHasShadow)
        Q_PROPERTY(int shadowSize READ GetShadowSize WRITE SetShadowSize)
        Q_PROPERTY(QColor shadowColor READ GetShadowColor WRITE SetShadowColor)

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

    /// <summary>
    /// 添加自定义动作
    /// </summary>
    /// <param name="text">动作文本</param>
    /// <param name="icon">动作图标</param>
    /// <param name="tip">提示文本</param>
    /// <returns>创建的动作指针</returns>
    QAction* AddCustomAction(const QString& text, const QIcon& icon, const QString& tip = "");

    int GetIconSize() const { return m_iconSize; }

    int GetSpacing() const { return m_spacing; }

    QColor GetBackgroundColor() const { return m_backgroundColor; }

    QColor GetBorderColor() const { return m_borderColor; }

    QColor GetHoverColor() const { return m_hoverColor; }

    QColor GetPressedColor() const { return m_pressedColor; }

    bool GetHasShadow() const { return m_hasShadow; }

    int GetShadowSize() const { return m_shadowSize; }

    QColor GetShadowColor() const { return m_shadowColor; }

    void SetIconSize(int size);
    void SetSpacing(int spacing);
    void SetBackgroundColor(const QColor& color);
    void SetBorderColor(const QColor& color);
    void SetHoverColor(const QColor& color);
    void SetPressedColor(const QColor& color);
    void SetHasShadow(bool hasShadow);
    void SetShadowSize(int size);
    void SetShadowColor(const QColor& color);

protected:
    /// <summary>
    /// 绘制事件
    /// </summary>
    void paintEvent(QPaintEvent* event) override;

    /// <summary>
    /// 调整大小事件
    /// </summary>
    void resizeEvent(QResizeEvent* event) override;

private:
    /// <summary>
    /// 初始化界面
    /// </summary>
    void InitializeWidget();

    /// <summary>
    /// 更新样式表
    /// </summary>
    void UpdateStyleSheet();

private:
    int m_iconSize;            /// 图标大小
    int m_spacing;             /// 间距
    QColor m_backgroundColor;  /// 背景色
    QColor m_borderColor;      /// 边框色
    QColor m_hoverColor;       /// 悬停色
    QColor m_pressedColor;     /// 按下色
    bool m_hasShadow;         /// 是否显示阴影
    int m_shadowSize;         /// 阴影大小
    QColor m_shadowColor;     /// 阴影颜色
}; 