#include "FilePathIconListWidgetItem.h"
#include "ui_FilePathIconListWidgetItem.h"
#include <QEvent>
#include <QMouseEvent>

FilePathIconListWidgetItem::FilePathIconListWidgetItem(QWidget* parent)
    : QFrame(parent)
    , m_ui(new Ui::FilePathIconListWidgetItemClass)
    , m_tipsWidget(nullptr)
    , m_delay(700)
    , m_isSelected(false)
    , m_isHovered(false)
    , m_enableHover(true)
    , m_enableSelected(true)
{
    m_ui->setupUi(this);
    InitializeWidget();
    SetupConnections();
}

FilePathIconListWidgetItem::~FilePathIconListWidgetItem()
{
    delete m_ui;
    if (m_tipsWidget)
    {
        delete m_tipsWidget;
    }
}

void FilePathIconListWidgetItem::InitializeWidget()
{
    m_ui->setupUi(this);

    // 设置默认样式
    m_backgroundColor = UIColorDefine::background_color::Transparent;
    m_hoverColor = UIColorDefine::background_color::ToolTipsInfo;
    m_selectedColor = UIColorDefine::font_color::Info; // 浅蓝色选中背景
    m_selectedColor.setAlpha(128);
    m_textColor = UIColorDefine::font_color::Primary;

    // 配置图标标签
    m_ui->label_icon->setFixedSize(24, 24);
    m_ui->label_icon->SetEnableElide(false); // 图标不需要省略
    m_ui->label_icon->installEventFilter(this);

    // 配置内容标签
    m_ui->label_content->SetEnableElide(true); // 内容需要省略
    m_ui->label_content->setTextFormat(Qt::PlainText);
    m_ui->label_content->installEventFilter(this);

    // 设置定时器
    m_timer.setSingleShot(true);

    // 设置Tips样式
    m_tipsWidget->SetRadius(6);
    m_tipsWidget->EnableShadow(true);

    UpdateStyle();
}

void FilePathIconListWidgetItem::SetupConnections()
{
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &FilePathIconListWidgetItem::ShowToolTip);
}

void FilePathIconListWidgetItem::SetText(const QString& text)
{
    m_ui->label_content->setText(text);
}

QString FilePathIconListWidgetItem::text() const
{
    return m_ui->label_content->text();
}

void FilePathIconListWidgetItem::SetIconPath(const QString& path)
{
    m_iconPath = path;
    QPixmap pixmap(path);
    if (!pixmap.isNull())
    {
        m_ui->label_icon->setPixmap(pixmap.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

QString FilePathIconListWidgetItem::iconPath() const
{
    return m_iconPath;
}

void FilePathIconListWidgetItem::SetTextColor(const QColor& color)
{
    m_textColor = color;
    UpdateStyle();
}

QColor FilePathIconListWidgetItem::textColor() const
{
    return m_textColor;
}

void FilePathIconListWidgetItem::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    UpdateStyle();
}

QColor FilePathIconListWidgetItem::hoverColor() const
{
    return m_hoverColor;
}

QColor FilePathIconListWidgetItem::backgroundColor() const
{
    return m_backgroundColor;
}

QColor FilePathIconListWidgetItem::selectedColor() const
{
    return m_selectedColor;
}

void FilePathIconListWidgetItem::SetSelectedColor(const QColor& color)
{
    m_selectedColor = color;
    UpdateStyle();
}

void FilePathIconListWidgetItem::SetHoverColor(const QColor& color)
{
    m_hoverColor = color;
    UpdateStyle();
}

void FilePathIconListWidgetItem::SetSelected(bool selected)
{
    if (m_enableSelected && m_isSelected != selected)
    {
        m_isSelected = selected;
        UpdateStyle();
    }
}

bool FilePathIconListWidgetItem::isSelected() const
{
    return m_isSelected;
}

void FilePathIconListWidgetItem::EnableHoverEffect(bool enable)
{
    m_enableHover = enable;
    if (!enable)
    {
        m_isHovered = false;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::EnableSelectedEffect(bool enable)
{
    m_enableSelected = enable;
    if (!enable)
    {
        m_isSelected = false;
        UpdateStyle();
    }
}

const FilePathIconListWidgetItem::ST_NodeInfo& FilePathIconListWidgetItem::GetNodeInfo() const
{
    return m_info;
}

void FilePathIconListWidgetItem::SetItemNodeText(const ST_NodeInfo& nodeInfo)
{
    m_info = nodeInfo;
    SetText(nodeInfo.content);
    SetIconPath(nodeInfo.iconFilePath);

    // 创建提示框
    if (!m_tipsWidget)
    {
        m_tipsWidget = new CustomToolTips(this);
    }
    m_tipsWidget->SetToolTips(nodeInfo.toolTipsContent);
    m_tipsWidget->SetToolTipsEx(nodeInfo.toolTipsContentEx);
}

bool FilePathIconListWidgetItem::eventFilter(QObject* watched, QEvent* event)
{
    return QFrame::eventFilter(watched, event);
}

void FilePathIconListWidgetItem::enterEvent(QEvent* event)
{
    QFrame::enterEvent(event);
    if (m_enableHover)
    {
        m_isHovered = true;
        UpdateStyle();
        m_timer.start(m_delay);
    }
}

void FilePathIconListWidgetItem::leaveEvent(QEvent* event)
{
    QFrame::leaveEvent(event);
    if (m_enableHover)
    {
        m_isHovered = false;
        UpdateStyle();
        m_timer.stop();
        if (m_tipsWidget)
        {
            m_tipsWidget->HideTips();
        }
    }
}

void FilePathIconListWidgetItem::mousePressEvent(QMouseEvent* event)
{
    QFrame::mousePressEvent(event);
    if (m_enableSelected && event->button() == Qt::LeftButton)
    {
        SetSelected(!m_isSelected);
    }
}

void FilePathIconListWidgetItem::ShowToolTip()
{
    if (m_tipsWidget && !m_info.toolTipsContent.isEmpty())
    {
        QPoint pos = mapToGlobal(QPoint(0, height()));
        m_tipsWidget->ShowTips(pos);
    }
}

void FilePathIconListWidgetItem::OnStyleChanged()
{
    UpdateStyle();
}

void FilePathIconListWidgetItem::UpdateStyle()
{
    QString frameStyle = QString(
        "QFrame#frame {"
        "   background-color: %1;"
        "   border: none;"
        "   border-radius: 4px;"
        "}"
        "QLabel {"
        "   color: %2;"
        "}")
        .arg(m_isSelected ? UIColorDefine::color_convert::ToCssString(m_selectedColor) :
             m_isHovered ? UIColorDefine::color_convert::ToCssString(m_hoverColor) :
             UIColorDefine::color_convert::ToCssString(m_backgroundColor))
        .arg(UIColorDefine::color_convert::ToCssString(m_textColor));

    m_ui->frame->setStyleSheet(frameStyle);
}
