#include "FilePathIconListWidgetItem.h"

FilePathIconListWidgetItem::FilePathIconListWidgetItem(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FilePathIconListWidgetItemClass())
{
    ui->setupUi(this);
    m_timer.setSingleShot(true);
    m_tipsWidget = new CustomToolTips;
    connect(&m_timer, &QTimer::timeout, this, &FilePathIconListWidgetItem::ShowToolTip);
    ui->label_icon->installEventFilter(this);
}

FilePathIconListWidgetItem::~FilePathIconListWidgetItem()
{
    SAFE_DELETE_POINTER_VALUE(ui);
    SAFE_DELETE_POINTER_VALUE(m_tipsWidget);
}

void FilePathIconListWidgetItem::SetItemNodeText(const ST_NodeInfo& nodeInfo)
{
    m_info = nodeInfo;
    ui->label_icon->setText(m_info.iconFilePath);
    ui->label_content->setText(m_info.content);
    m_tipsWidget->SetToolTips(m_info.toolTipsContent);
    m_tipsWidget->SetToolTipsEx(m_info.toolTipsContentEx);
}

bool FilePathIconListWidgetItem::eventFilter(QObject* obj, QEvent* event)
{
    auto* widget = qobject_cast<QWidget*>(obj);
    if (!widget && widget != ui->label_icon)
    {
        return QWidget::eventFilter(obj, event);
    }

    switch (event->type())
    {
        case QEvent::Enter:
            // 鼠标进入时启动计时器
            m_timer.start(m_delay);
            break;

        case QEvent::Leave:
        case QEvent::FocusOut:
        case QEvent::MouseButtonPress:
            // 鼠标离开或窗口失活时隐藏提示
            m_timer.stop();
            m_tipsWidget->hide();
            break;
        default:
            break;
    }
    return QObject::eventFilter(obj, event);
}

void FilePathIconListWidgetItem::ShowToolTip()
{
    QPoint globalPos = QCursor::pos();
    QPoint localPos = this->mapFromGlobal(globalPos);
    m_tipsWidget->move(globalPos.x() + 10, globalPos.y() + 4);
    m_tipsWidget->show();
}
