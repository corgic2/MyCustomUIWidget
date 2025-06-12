#include "FilePathIconListWidgetItem.h"

#include <QFileInfo>
#include <QPainter>

FilePathIconListWidgetItem::FilePathIconListWidgetItem(QListWidget* parent)
    : QListWidgetItem(parent)
    , m_enableHover(true)
    , m_enableSelected(true)
{
    // 设置默认颜色
    m_textColor = UIColorDefine::font_color::Primary;
    m_backgroundColor = UIColorDefine::background_color::Transparent;
    m_selectedColor = UIColorDefine::background_color::PressedBackground;
    m_hoverColor = UIColorDefine::background_color::HoverBackground;

    UpdateStyle();
}

FilePathIconListWidgetItem::~FilePathIconListWidgetItem()
{
}

void FilePathIconListWidgetItem::SetNodeInfo(const ST_NodeInfo& nodeInfo)
{
    m_nodeInfo = nodeInfo;

    // 设置显示文本 - 确保使用UTF-8编码
    if (!m_nodeInfo.displayName.isEmpty())
    {
        setText(QString::fromUtf8(m_nodeInfo.displayName.toUtf8()));
    }
    else
    {
        // 如果displayName为空，使用文件路径的最后一部分作为显示名
        QFileInfo fileInfo(m_nodeInfo.filePath);
        setText(QString::fromUtf8(fileInfo.fileName().toUtf8()));
    }

    // 设置图标
    if (!m_nodeInfo.iconPath.isEmpty())
    {
        setIcon(QIcon(m_nodeInfo.iconPath));
    }

    // 设置提示文本
    setToolTip(QString::fromUtf8(m_nodeInfo.filePath.toUtf8()));

    UpdateStyle();
}

void FilePathIconListWidgetItem::SetTextColor(const QColor& color)
{
    if (m_textColor != color)
    {
        m_textColor = color;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::SetBackgroundColor(const QColor& color)
{
    if (m_backgroundColor != color)
    {
        m_backgroundColor = color;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::SetSelectedColor(const QColor& color)
{
    if (m_selectedColor != color)
    {
        m_selectedColor = color;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::SetHoverColor(const QColor& color)
{
    if (m_hoverColor != color)
    {
        m_hoverColor = color;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::EnableHoverEffect(bool enable)
{
    if (m_enableHover != enable)
    {
        m_enableHover = enable;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::EnableSelectedEffect(bool enable)
{
    if (m_enableSelected != enable)
    {
        m_enableSelected = enable;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::UpdateStyle()
{
    // 设置文本颜色
    setForeground(m_textColor);

    // 设置背景颜色
    setBackground(m_backgroundColor);

    // 设置选中状态的背景色
    if (m_enableSelected && isSelected())
    {
        setBackground(m_selectedColor);
    }

    // 设置悬停状态的背景色
    if (m_enableHover && listWidget() && listWidget()->itemAt(listWidget()->mapFromGlobal(QCursor::pos())) == this)
    {
        setBackground(m_hoverColor);
    }
}
