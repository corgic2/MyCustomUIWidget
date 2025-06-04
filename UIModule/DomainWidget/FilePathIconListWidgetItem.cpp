#include "FilePathIconListWidgetItem.h"
#include <QStyle>

FilePathIconListWidgetItem::FilePathIconListWidgetItem(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::FilePathIconListWidgetItemClass())
    , m_tipsWidget(new CustomToolTips(this))

{
    InitializeUI();
    SetupConnections();
}

FilePathIconListWidgetItem::~FilePathIconListWidgetItem()
{
    SAFE_DELETE_POINTER_VALUE(m_ui);
}

void FilePathIconListWidgetItem::InitializeUI()
{
    m_ui->setupUi(this);
    
    // 设置默认样式
    m_backgroundColor = UIColorDefine::background_color::Transparent;
    m_hoverColor = UIColorDefine::background_color::Light;
    m_selectedColor = {230, 244, 255, 255}; // 浅蓝色选中背景
    m_textColor = UIColorDefine::font_color::Primary;

    // 配置图标标签
    m_ui->label_icon->setFixedSize(24, 24);
    m_ui->label_icon->EnableElide(false);  // 图标不需要省略
    m_ui->label_icon->installEventFilter(this);

    // 配置内容标签
    m_ui->label_content->EnableElide(true); // 内容需要省略
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
    connect(&m_timer, &QTimer::timeout, this, &FilePathIconListWidgetItem::ShowToolTip);
}

void FilePathIconListWidgetItem::SetItemNodeText(const ST_NodeInfo& nodeInfo)
{
    m_info = nodeInfo;
    
    // 设置图标
    if (!m_info.iconFilePath.isEmpty())
    {
        m_ui->label_icon->SetImage(m_info.iconFilePath, CustomLabel::ScaleToFit);
    }
    
    // 设置内容
    m_ui->label_content->SetText(m_info.content);
    // 设置提示信息
    m_tipsWidget->SetToolTips(m_info.toolTipsContent);
    if (!m_info.toolTipsContentEx.isEmpty())
    {
        m_tipsWidget->SetToolTipsEx(m_info.toolTipsContentEx);
    }

    // 根据节点类型设置样式
    switch (m_info.nodeType)
    {
        case Warning:
            m_tipsWidget->SetTipsType(CustomToolTips::Warning);
            break;
        case Error:
            m_tipsWidget->SetTipsType(CustomToolTips::Error);
            break;
        case Folder:
            m_ui->label_content->setProperty("type", "folder");
            break;
        case File:
            m_ui->label_content->setProperty("type", "file");
            break;
        default:
            m_tipsWidget->SetTipsType(CustomToolTips::Normal);
            break;
    }

    UpdateStyle();
}

void FilePathIconListWidgetItem::SetBackgroundColor(const UIColorDefine::ST_ColorRgba& color)
{
    m_backgroundColor = color;
    UpdateStyle();
}

void FilePathIconListWidgetItem::SetHoverColor(const UIColorDefine::ST_ColorRgba& color)
{
    m_hoverColor = color;
    if (m_isHovered)
    {
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::SetSelectedColor(const UIColorDefine::ST_ColorRgba& color)
{
    m_selectedColor = color;
    if (m_isSelected)
    {
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::SetTextColor(const UIColorDefine::ST_ColorRgb& color)
{
    m_textColor = color;
    UpdateStyle();
}

void FilePathIconListWidgetItem::EnableHoverEffect(bool enable)
{
    m_enableHover = enable;
    if (!enable && m_isHovered)
    {
        m_isHovered = false;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::EnableSelectedEffect(bool enable)
{
    m_enableSelected = enable;
    if (!enable && m_isSelected)
    {
        m_isSelected = false;
        UpdateStyle();
    }
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
        .arg(m_isSelected ? m_selectedColor.ToQString() :
             m_isHovered ? m_hoverColor.ToQString() :
             m_backgroundColor.ToQString())
        .arg(m_textColor.ToQString());

    m_ui->frame->setStyleSheet(frameStyle);
}

bool FilePathIconListWidgetItem::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_ui->label_icon || watched == m_ui->label_content)
    {
        switch (event->type())
        {
            case QEvent::Enter:
                if (m_enableHover)
                {
                    m_timer.start(m_delay);
                }
                break;
            case QEvent::Leave:
            case QEvent::MouseButtonPress:
                m_timer.stop();
                m_tipsWidget->hide();
                break;
            default:
                break;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void FilePathIconListWidgetItem::enterEvent(QEvent* event)
{
    QWidget::enterEvent(event);
    if (m_enableHover)
    {
        m_isHovered = true;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    if (m_enableHover)
    {
        m_isHovered = false;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    if (m_enableSelected)
    {
        m_isSelected = !m_isSelected;
        UpdateStyle();
    }
}

void FilePathIconListWidgetItem::ShowToolTip()
{
    if (!m_info.toolTipsContent.isEmpty())
    {
        QPoint globalPos = QCursor::pos();
        m_tipsWidget->move(globalPos.x() + 10, globalPos.y() + 4);
        m_tipsWidget->show();
    }
}

void FilePathIconListWidgetItem::OnStyleChanged()
{
}
