#include "CustomToolBar.h"
#include <QPainter>
#include <QStyleOption>
#include <QResizeEvent>
#include "SkinStyleLoader.h"

CustomToolBar::CustomToolBar(QWidget* parent)
    : QToolBar(parent)
    , m_iconSize(24)
    , m_spacing(8)
    , m_hasShadow(true)
    , m_shadowSize(4)
{
    InitializeWidget();
    AUTO_LOAD_SKIN_STYLE();
}

CustomToolBar::~CustomToolBar()
{
}

void CustomToolBar::InitializeWidget()
{
    // 设置基本属性
    setMovable(false);
    setIconSize(QSize(m_iconSize, m_iconSize));
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setAllowedAreas(Qt::TopToolBarArea);

    // 设置默认颜色
    m_backgroundColor = UIColorDefine::background_color::White;
    m_borderColor = UIColorDefine::border_color::Default;
    m_hoverColor = UIColorDefine::background_color::HoverBackground;
    m_pressedColor = UIColorDefine::background_color::PressedBackground;
    m_shadowColor = UIColorDefine::shadow_color::Light;

    // 更新样式表
    UpdateStyleSheet();
}

void CustomToolBar::UpdateStyleSheet()
{
    QString styleSheet = QString(R"(
        QToolBar {
            background-color: %1;
            border: 1px solid %2;
            border-top: none;
            spacing: %3px;
            padding: 4px;
        }

        QToolButton {
            background-color: transparent;
            border: none;
            border-radius: 4px;
            padding: 6px;
            margin: 0px;
            color: %4;
        }

        QToolButton:hover {
            background-color: %5;
        }

        QToolButton:pressed {
            background-color: %6;
        }

        QToolButton::menu-button {
            width: 16px;
            border: none;
        }
    )")
    .arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor))
    .arg(UIColorDefine::color_convert::ToCssString(m_borderColor))
    .arg(m_spacing)
    .arg(UIColorDefine::color_convert::ToCssString(UIColorDefine::font_color::Primary))
    .arg(UIColorDefine::color_convert::ToCssString(m_hoverColor))
    .arg(UIColorDefine::color_convert::ToCssString(m_pressedColor));

    setStyleSheet(styleSheet);
}

QAction* CustomToolBar::AddCustomAction(const QString& text, const QIcon& icon, const QString& tip)
{
    QAction* action = addAction(icon, text);
    if (!tip.isEmpty())
    {
        action->setToolTip(tip);
    }
    return action;
}

void CustomToolBar::SetIconSize(int size)
{
    if (m_iconSize != size)
    {
        m_iconSize = size;
        setIconSize(QSize(m_iconSize, m_iconSize));
    }
}

void CustomToolBar::SetSpacing(int spacing)
{
    if (m_spacing != spacing)
    {
        m_spacing = spacing;
        UpdateStyleSheet();
    }
}

void CustomToolBar::SetBackgroundColor(const QColor& color)
{
    if (m_backgroundColor != color)
    {
        m_backgroundColor = color;
        UpdateStyleSheet();
    }
}

void CustomToolBar::SetBorderColor(const QColor& color)
{
    if (m_borderColor != color)
    {
        m_borderColor = color;
        UpdateStyleSheet();
    }
}

void CustomToolBar::SetHoverColor(const QColor& color)
{
    if (m_hoverColor != color)
    {
        m_hoverColor = color;
        UpdateStyleSheet();
    }
}

void CustomToolBar::SetPressedColor(const QColor& color)
{
    if (m_pressedColor != color)
    {
        m_pressedColor = color;
        UpdateStyleSheet();
    }
}

void CustomToolBar::SetHasShadow(bool hasShadow)
{
    if (m_hasShadow != hasShadow)
    {
        m_hasShadow = hasShadow;
        update();
    }
}

void CustomToolBar::SetShadowSize(int size)
{
    if (m_shadowSize != size)
    {
        m_shadowSize = size;
        update();
    }
}

void CustomToolBar::SetShadowColor(const QColor& color)
{
    if (m_shadowColor != color)
    {
        m_shadowColor = color;
        update();
    }
}

void CustomToolBar::paintEvent(QPaintEvent* event)
{
    QToolBar::paintEvent(event);

    if (m_hasShadow)
    {
        // 绘制底部阴影
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QLinearGradient gradient(0, height() - m_shadowSize, 0, height());
        gradient.setColorAt(0, QColor(m_shadowColor.red(), m_shadowColor.green(), m_shadowColor.blue(), 0));
        gradient.setColorAt(1, m_shadowColor);

        painter.fillRect(QRect(0, height() - m_shadowSize, width(), m_shadowSize), gradient);
    }
}

void CustomToolBar::resizeEvent(QResizeEvent* event)
{
    QToolBar::resizeEvent(event);
    update(); // 确保阴影效果正确重绘
} 