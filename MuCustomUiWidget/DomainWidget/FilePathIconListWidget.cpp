#include "FilePathIconListWidget.h"
#include "ui_FilePathIconListWidget.h"
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QClipboard>
#include <QApplication>
#include <QProcess>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
FilePathIconListWidget::FilePathIconListWidget(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::FilePathIconListWidgetClass())
    , m_listWidget(nullptr)
    , m_contextMenu(nullptr)
    , m_itemHeight(32)
    , m_enableHoverEffect(true)
    , m_enableSelectedEffect(true)
    , m_showContextMenu(true)
{
    InitializeWidget();
    InitializeContextMenu();
    SetupConnections();
}

FilePathIconListWidget::~FilePathIconListWidget()
{
    SAFE_DELETE_POINTER_VALUE(m_ui);
    SAFE_DELETE_POINTER_VALUE(m_contextMenu);
}

void FilePathIconListWidget::InitializeWidget()
{
    m_ui->setupUi(this);

    // 创建列表控件
    m_listWidget = new QListWidget(this);
    m_listWidget->setFrameShape(QFrame::NoFrame);
    m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_listWidget->setSpacing(1);

    // 设置默认样式
    m_backgroundColor = UIColorDefine::background_color::Transparent;
    m_itemHoverColor = UIColorDefine::background_color::ToolTipsInfo;
    m_itemSelectedColor = UIColorDefine::font_color::Info;
    m_itemSelectedColor.setAlpha(128);
    m_itemTextColor = UIColorDefine::font_color::Primary;

    // 设置布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_listWidget);

    UpdateStyle();
}

void FilePathIconListWidget::InitializeContextMenu()
{
    m_contextMenu = new QMenu(this);
    
    // 添加菜单项
    QAction* propertiesAction = new QAction(tr("属性"), this);
    QAction* showInExplorerAction = new QAction(tr("在资源管理器中显示"), this);
    QAction* copyPathAction = new QAction(tr("复制文件路径"), this);

    m_contextMenu->addAction(propertiesAction);
    m_contextMenu->addAction(showInExplorerAction);
    m_contextMenu->addAction(copyPathAction);

    // 连接信号
    connect(propertiesAction, &QAction::triggered, this, &FilePathIconListWidget::SlotShowFileProperties);
    connect(showInExplorerAction, &QAction::triggered, this, &FilePathIconListWidget::SlotShowInExplorer);
    connect(copyPathAction, &QAction::triggered, this, &FilePathIconListWidget::SlotCopyFilePath);
}

void FilePathIconListWidget::SetupConnections()
{
    connect(m_listWidget, &QListWidget::itemDoubleClicked, this, &FilePathIconListWidget::SlotItemDoubleClicked);
    connect(m_listWidget, &QListWidget::itemClicked, this, &FilePathIconListWidget::SlotItemClicked);
}

void FilePathIconListWidget::AddFileItem(const FilePathIconListWidgetItem::ST_NodeInfo& nodeInfo)
{
    QListWidgetItem* item = new QListWidgetItem(m_listWidget);
    FilePathIconListWidgetItem* widget = new FilePathIconListWidgetItem(m_listWidget);
    
    widget->SetItemNodeText(nodeInfo);
    widget->SetTextColor(m_itemTextColor);
    widget->SetBackgroundColor(m_backgroundColor);
    widget->SetHoverColor(m_itemHoverColor);
    widget->SetSelectedColor(m_itemSelectedColor);
    widget->EnableHoverEffect(m_enableHoverEffect);
    widget->EnableSelectedEffect(m_enableSelectedEffect);
    
    item->setSizeHint(QSize(m_listWidget->width(), m_itemHeight));
    m_listWidget->addItem(item);
    m_listWidget->setItemWidget(item, widget);
}

void FilePathIconListWidget::ClearItems()
{
    m_listWidget->clear();
}

FilePathIconListWidgetItem* FilePathIconListWidget::GetCurrentItem() const
{
    QListWidgetItem* item = m_listWidget->currentItem();
    if (item)
    {
        return qobject_cast<FilePathIconListWidgetItem*>(m_listWidget->itemWidget(item));
    }
    return nullptr;
}

FilePathIconListWidgetItem* FilePathIconListWidget::GetItem(int index) const
{
    QListWidgetItem* item = m_listWidget->item(index);
    if (item)
    {
        return qobject_cast<FilePathIconListWidgetItem*>(m_listWidget->itemWidget(item));
    }
    return nullptr;
}

int FilePathIconListWidget::GetItemCount() const
{
    return m_listWidget->count();
}

void FilePathIconListWidget::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    UpdateStyle();
}

void FilePathIconListWidget::SetItemHoverColor(const QColor& color)
{
    m_itemHoverColor = color;
    UpdateStyle();
}

void FilePathIconListWidget::SetItemSelectedColor(const QColor& color)
{
    m_itemSelectedColor = color;
    UpdateStyle();
}

void FilePathIconListWidget::SetItemTextColor(const QColor& color)
{
    m_itemTextColor = color;
    UpdateStyle();
}

void FilePathIconListWidget::SetItemHeight(int height)
{
    m_itemHeight = height;
    for (int i = 0; i < m_listWidget->count(); ++i)
    {
        QListWidgetItem* item = m_listWidget->item(i);
        item->setSizeHint(QSize(m_listWidget->width(), height));
    }
}

void FilePathIconListWidget::SetEnableHoverEffect(bool enable)
{
    m_enableHoverEffect = enable;
    for (int i = 0; i < m_listWidget->count(); ++i)
    {
        if (auto widget = GetItem(i))
        {
            widget->EnableHoverEffect(enable);
        }
    }
}

void FilePathIconListWidget::SetEnableSelectedEffect(bool enable)
{
    m_enableSelectedEffect = enable;
    for (int i = 0; i < m_listWidget->count(); ++i)
    {
        if (auto widget = GetItem(i))
        {
            widget->EnableSelectedEffect(enable);
        }
    }
}

void FilePathIconListWidget::SetShowContextMenu(bool show)
{
    m_showContextMenu = show;
}

void FilePathIconListWidget::contextMenuEvent(QContextMenuEvent* event)
{
    if (m_showContextMenu && GetCurrentItem())
    {
        m_contextMenu->exec(event->globalPos());
    }
}

void FilePathIconListWidget::SlotItemDoubleClicked(QListWidgetItem* item)
{
    if (auto widget = qobject_cast<FilePathIconListWidgetItem*>(m_listWidget->itemWidget(item)))
    {
        emit SigItemDoubleClicked(widget->GetNodeInfo().filePath);
    }
}

void FilePathIconListWidget::SlotItemClicked(QListWidgetItem* item)
{
    if (auto widget = qobject_cast<FilePathIconListWidgetItem*>(m_listWidget->itemWidget(item)))
    {
        emit SigItemSelected(widget->GetNodeInfo().filePath);
    }
}

void FilePathIconListWidget::SlotShowFileProperties()
{
    if (auto currentItem = GetCurrentItem())
    {
        QString filePath = currentItem->GetNodeInfo().filePath;
#ifdef Q_OS_WIN
        QStringList args;
        args << "/select," << QDir::toNativeSeparators(filePath);
        QProcess::startDetached("explorer.exe", args);
#else
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(filePath).absolutePath()));
#endif
    }
}

void FilePathIconListWidget::SlotShowInExplorer()
{
    if (auto currentItem = GetCurrentItem())
    {
        QString filePath = currentItem->GetNodeInfo().filePath;
        QFileInfo fileInfo(filePath);
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absolutePath()));
    }
}

void FilePathIconListWidget::SlotCopyFilePath()
{
    if (auto currentItem = GetCurrentItem())
    {
        QString filePath = currentItem->GetNodeInfo().filePath;
        QApplication::clipboard()->setText(filePath);
    }
}

void FilePathIconListWidget::UpdateStyle()
{
    QString listStyle = QString(
        "QListWidget {"
        "    background-color: %1;"
        "    border: none;"
        "}")
        .arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor));

    m_listWidget->setStyleSheet(listStyle);

    // 更新所有项的样式
    for (int i = 0; i < m_listWidget->count(); ++i)
    {
        if (auto widget = GetItem(i))
        {
            widget->SetTextColor(m_itemTextColor);
            widget->SetBackgroundColor(m_backgroundColor);
            widget->SetHoverColor(m_itemHoverColor);
            widget->SetSelectedColor(m_itemSelectedColor);
        }
    }
}

