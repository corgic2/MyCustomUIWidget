#include "FilePathIconListWidget.h"
#include <QApplication>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QPainter>
#include <QPen>
#include <QProcess>
#include <QUrl>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "FileSystem/FileSystem.h"

FilePathIconListWidget::FilePathIconListWidget(QWidget* parent)
    : QListWidget(parent)
    , m_contextMenu(nullptr)
    , m_itemHeight(32)
    , m_backgroundColor(UIColorDefine::background_color::White)
    , m_itemHoverColor(UIColorDefine::background_color::HoverBackground)
    , m_itemSelectedColor(UIColorDefine::background_color::PressedBackground)
    , m_itemTextColor(UIColorDefine::font_color::Primary)
    , m_enableHoverEffect(true)
    , m_enableSelectedEffect(true)
    , m_showContextMenu(true)
    , m_borderWidth(0)
    , m_borderColor(Qt::transparent)
    , m_jsonFilePath("")
    , m_autoSaveInterval(0)
    , m_autoSaveTimer(nullptr)
{
    InitializeWidget();
    InitializeContextMenu();
    SetupConnections();
}

FilePathIconListWidget::~FilePathIconListWidget()
{
    if (m_autoSaveTimer)
    {
        m_autoSaveTimer->stop();
        SAFE_DELETE_POINTER_VALUE(m_autoSaveTimer);
    }
    SAFE_DELETE_POINTER_VALUE(m_contextMenu);
}

void FilePathIconListWidget::InitializeWidget()
{
    // 设置基本属性
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setSpacing(1);

    // 设置默认样式
    UpdateStyle();
}

void FilePathIconListWidget::InitializeContextMenu()
{
    m_contextMenu = new QMenu(this);

    // 添加菜单项
    auto propertiesAction = new QAction(tr("属性"), this);
    auto showInExplorerAction = new QAction(tr("在资源管理器中显示"), this);
    auto copyPathAction = new QAction(tr("复制文件路径"), this);

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
    connect(this, &QListWidget::itemDoubleClicked, this, &FilePathIconListWidget::SlotItemDoubleClicked);
    connect(this, &QListWidget::itemClicked, this, &FilePathIconListWidget::SlotItemClicked);
}

void FilePathIconListWidget::AddFileItem(const FilePathIconListWidgetItem::ST_NodeInfo& nodeInfo)
{
    // 确保文件路径和显示名称使用UTF-8编码
    FilePathIconListWidgetItem::ST_NodeInfo utf8NodeInfo = nodeInfo;
    
    // 如果显示名称为空，使用文件名
    if (utf8NodeInfo.displayName.isEmpty())
    {
        QFileInfo fileInfo(utf8NodeInfo.filePath);
        utf8NodeInfo.displayName = QString::fromUtf8(fileInfo.fileName().toUtf8());
    }
    else
    {
        utf8NodeInfo.displayName = QString::fromUtf8(utf8NodeInfo.displayName.toUtf8());
    }

    // 确保文件路径使用UTF-8编码
    utf8NodeInfo.filePath = QString::fromUtf8(utf8NodeInfo.filePath.toUtf8());

    auto item = new FilePathIconListWidgetItem(this);
    item->SetNodeInfo(utf8NodeInfo);
    item->SetTextColor(m_itemTextColor);
    item->SetBackgroundColor(m_backgroundColor);
    item->SetHoverColor(m_itemHoverColor);
    item->SetSelectedColor(m_itemSelectedColor);
    item->EnableHoverEffect(m_enableHoverEffect);
    item->EnableSelectedEffect(m_enableSelectedEffect);
    addItem(item);
}

void FilePathIconListWidget::InsertFileItem(int index, const FilePathIconListWidgetItem::ST_NodeInfo& nodeInfo)
{
    // 确保文件路径和显示名称使用UTF-8编码
    FilePathIconListWidgetItem::ST_NodeInfo utf8NodeInfo = nodeInfo;
    
    // 如果显示名称为空，使用文件名
    if (utf8NodeInfo.displayName.isEmpty())
    {
        QFileInfo fileInfo(utf8NodeInfo.filePath);
        utf8NodeInfo.displayName = QString::fromUtf8(fileInfo.fileName().toUtf8());
    }
    else
    {
        utf8NodeInfo.displayName = QString::fromUtf8(utf8NodeInfo.displayName.toUtf8());
    }

    // 确保文件路径使用UTF-8编码
    utf8NodeInfo.filePath = QString::fromUtf8(utf8NodeInfo.filePath.toUtf8());

    auto item = new FilePathIconListWidgetItem(this);
    item->SetNodeInfo(utf8NodeInfo);
    item->SetTextColor(m_itemTextColor);
    item->SetBackgroundColor(m_backgroundColor);
    item->SetHoverColor(m_itemHoverColor);
    item->SetSelectedColor(m_itemSelectedColor);
    item->EnableHoverEffect(m_enableHoverEffect);
    item->EnableSelectedEffect(m_enableSelectedEffect);
    insertItem(index, item);
}

void FilePathIconListWidget::RemoveItemByIndex(int index)
{
    if (index >= 0 && index < count())
    {
        QListWidgetItem* item = takeItem(index);
        if (item)
        {
            delete item;
        }
    }
}

void FilePathIconListWidget::RemoveItem(FilePathIconListWidgetItem* item)
{
    if (item)
    {
        int rowIndex = row(item);
        if (rowIndex >= 0)
        {
            QListWidgetItem* removedItem = takeItem(rowIndex);
            if (removedItem)
            {
                delete removedItem;
            }
        }
    }
}

void FilePathIconListWidget::Clear()
{
    clear();
}

FilePathIconListWidgetItem* FilePathIconListWidget::GetItem(int index) const
{
    return dynamic_cast<FilePathIconListWidgetItem*>(item(index));
}

FilePathIconListWidgetItem* FilePathIconListWidget::GetCurrentItem() const
{
    return dynamic_cast<FilePathIconListWidgetItem*>(currentItem());
}

int FilePathIconListWidget::GetItemCount() const
{
    return count();
}

void FilePathIconListWidget::MoveItemToTop(FilePathIconListWidgetItem* item)
{
    if (item)
    {
        int currentRow = row(item);
        if (currentRow > 0)
        {
            QListWidgetItem* takenItem = takeItem(currentRow);
            if (takenItem)
            {
                insertItem(0, takenItem);
                setCurrentItem(takenItem);
            }
        }
    }
}

void FilePathIconListWidget::MoveItemToTop(int index)
{
    if (index > 0 && index < count())
    {
        QListWidgetItem* takenItem = takeItem(index);
        if (takenItem)
        {
            insertItem(0, takenItem);
            setCurrentItem(takenItem);
        }
    }
}

void FilePathIconListWidget::SetBackgroundColor(const QColor& color)
{
    if (m_backgroundColor != color)
    {
        m_backgroundColor = color;
        UpdateStyle();
    }
}

void FilePathIconListWidget::SetItemHoverColor(const QColor& color)
{
    if (m_itemHoverColor != color)
    {
        m_itemHoverColor = color;
        UpdateStyle();
    }
}

void FilePathIconListWidget::SetItemSelectedColor(const QColor& color)
{
    if (m_itemSelectedColor != color)
    {
        m_itemSelectedColor = color;
        UpdateStyle();
    }
}

void FilePathIconListWidget::SetItemTextColor(const QColor& color)
{
    if (m_itemTextColor != color)
    {
        m_itemTextColor = color;
        UpdateStyle();
    }
}

void FilePathIconListWidget::SetItemHeight(int height)
{
    if (m_itemHeight != height)
    {
        m_itemHeight = height;
        UpdateStyle();
    }
}

void FilePathIconListWidget::SetEnableHoverEffect(bool enable)
{
    if (m_enableHoverEffect != enable)
    {
        m_enableHoverEffect = enable;
        UpdateStyle();
    }
}

void FilePathIconListWidget::SetEnableSelectedEffect(bool enable)
{
    if (m_enableSelectedEffect != enable)
    {
        m_enableSelectedEffect = enable;
        UpdateStyle();
    }
}

void FilePathIconListWidget::SetShowContextMenu(bool show)
{
    m_showContextMenu = show;
}

void FilePathIconListWidget::SetMargins(int left, int top, int right, int bottom)
{
    setContentsMargins(left, top, right, bottom);
    update();
}

void FilePathIconListWidget::SetBorderWidth(int width)
{
    m_borderWidth = width;
    update();
}

void FilePathIconListWidget::SetBorderColor(const QColor& color)
{
    m_borderColor = color;
    update();
}

void FilePathIconListWidget::contextMenuEvent(QContextMenuEvent* event)
{
    if (!m_showContextMenu)
    {
        return;
    }

    QListWidgetItem* currentItem = itemAt(event->pos());
    if (currentItem)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(currentItem);
        if (fileItem)
        {
            QString filePath = fileItem->GetFilePath();
            emit SigContextMenuRequested(filePath, event->globalPos());
            m_contextMenu->exec(event->globalPos());
        }
    }
}

void FilePathIconListWidget::SlotItemDoubleClicked(QListWidgetItem* item)
{
    if (item)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(item);
        if (fileItem)
        {
            QString filePath = fileItem->GetFilePath();
            emit SigItemDoubleClicked(filePath);
        }
    }
}

void FilePathIconListWidget::SlotItemClicked(QListWidgetItem* item)
{
    if (item)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(item);
        if (fileItem)
        {
            QString filePath = fileItem->GetFilePath();
            emit SigItemSelected(filePath);
        }
    }
}

void FilePathIconListWidget::SlotShowFileProperties(bool clicked)
{
    QListWidgetItem* tmpCurrentItem = currentItem();
    if (tmpCurrentItem)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(tmpCurrentItem);
        if (fileItem)
        {
            QString filePath = fileItem->GetFilePath();
            QFileInfo fileInfo(filePath);
            if (fileInfo.exists())
            {
                // TODO: 显示文件属性对话框
            }
        }
    }
}

void FilePathIconListWidget::SlotShowInExplorer(bool bClicked)
{
    QListWidgetItem* tmpCurrentItem = currentItem();
    if (tmpCurrentItem)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(tmpCurrentItem);
        if (fileItem)
        {
            QString filePath = fileItem->GetFilePath();
            QFileInfo fileInfo(filePath);
            if (fileInfo.exists())
            {
                QString argument = QString("/select,\"%1\"").arg(QDir::toNativeSeparators(filePath));
                QProcess::startDetached("explorer.exe", QStringList(argument));
            }
        }
    }
}

void FilePathIconListWidget::SlotCopyFilePath(bool bClicked)
{
    QListWidgetItem* tmpCurrentItem = currentItem();
    if (tmpCurrentItem)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(tmpCurrentItem);
        if (fileItem)
        {
            QString filePath = fileItem->GetFilePath();
            QClipboard* clipboard = QApplication::clipboard();
            clipboard->setText(filePath);
        }
    }
}

void FilePathIconListWidget::UpdateStyle()
{
    QString styleSheet = QString(R"(
        QListWidget {
            background-color: %1;
            border: none;
        }
        QListWidget::item {
            height: %2px;
        }
    )").arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor))
       .arg(m_itemHeight);

    setStyleSheet(styleSheet);

    // 更新所有项的样式
    for (int i = 0; i < count(); ++i)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(item(i));
        if (fileItem)
        {
            fileItem->SetTextColor(m_itemTextColor);
            fileItem->SetBackgroundColor(m_backgroundColor);
            fileItem->SetHoverColor(m_itemHoverColor);
            fileItem->SetSelectedColor(m_itemSelectedColor);
            fileItem->EnableHoverEffect(m_enableHoverEffect);
            fileItem->EnableSelectedEffect(m_enableSelectedEffect);
        }
    }
}

void FilePathIconListWidget::SetJsonFilePath(const QString& jsonFilePath)
{
    m_jsonFilePath = jsonFilePath;
}

QString FilePathIconListWidget::GetJsonFilePath() const
{
    return m_jsonFilePath;
}

bool FilePathIconListWidget::LoadFileListFromJson()
{
    if (m_jsonFilePath.isEmpty())
    {
        return false;
    }

    std::string jsonStr;
    my_sdk::EM_JsonOperationResult result = my_sdk::FileSystem::ReadJsonFromFile(m_jsonFilePath.toStdString(), jsonStr);

    if (result == my_sdk::EM_JsonOperationResult::Success && my_sdk::FileSystem::ValidateJsonString(jsonStr))
    {
        // 使用Qt的JSON解析功能解析数据
        QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(jsonStr).toUtf8());
        if (document.isObject())
        {
            QJsonObject rootObject = document.object();
            // 遍历根对象的所有子对象
            for (auto it = rootObject.begin(); it != rootObject.end(); ++it)
            {
                QJsonObject fileObject = it.value().toObject();
                if (!fileObject.isEmpty())
                {
                    std::string filePath = my_sdk::FileSystem::QtPathToStdPath(fileObject["filePath"].toString().toStdString());
                    QString qtFilePath = QString::fromStdString(my_sdk::FileSystem::StdPathToQtPath(filePath));

                    // 使用FileSystem API检查文件是否存在
                    if (my_sdk::FileSystem::Exists(filePath))
                    {
                        FilePathIconListWidgetItem::ST_NodeInfo nodeInfo;
                        nodeInfo.filePath = qtFilePath;
                        nodeInfo.displayName = fileObject["displayName"].toString();
                        nodeInfo.iconPath = fileObject["iconPath"].toString();

                        // 添加到列表
                        AddFileItem(nodeInfo);
                    }
                }
            }
            emit SigFileListLoaded();
            return true;
        }
    }
    return false;
}

bool FilePathIconListWidget::SaveFileListToJson()
{
    if (m_jsonFilePath.isEmpty())
    {
        return false;
    }

    QJsonObject rootObject;

    for (int i = 0; i < count(); ++i)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(item(i));
        if (fileItem)
        {
            QJsonObject fileObject;
            fileObject["filePath"] = fileItem->GetNodeInfo().filePath;
            fileObject["displayName"] = fileItem->GetNodeInfo().displayName;
            fileObject["iconPath"] = fileItem->GetNodeInfo().iconPath;

            rootObject[QString::number(i)] = fileObject;
        }
    }

    QJsonDocument doc(rootObject);
    QString jsonQStr = doc.toJson(QJsonDocument::Indented);
    std::string jsonStr = jsonQStr.toUtf8().constData();

    // 使用FileSystem API保存JSON
    my_sdk::EM_JsonOperationResult result = my_sdk::FileSystem::WriteJsonToFile(m_jsonFilePath.toStdString(), jsonStr, true);

    if (result == my_sdk::EM_JsonOperationResult::Success)
    {
        emit SigFileListSaved();
        return true;
    }
    return false;
}

void FilePathIconListWidget::SetAutoSaveInterval(int interval)
{
    m_autoSaveInterval = interval;
    if (m_autoSaveTimer)
    {
        if (interval > 0)
        {
            m_autoSaveTimer->setInterval(interval);
            m_autoSaveTimer->start();
        }
        else
        {
            m_autoSaveTimer->stop();
        }
    }
}

int FilePathIconListWidget::GetAutoSaveInterval() const
{
    return m_autoSaveInterval;
}

void FilePathIconListWidget::EnableAutoSave(bool enable)
{
    if (enable)
    {
        if (!m_autoSaveTimer)
        {
            m_autoSaveTimer = new QTimer(this);
            m_autoSaveTimer->setInterval(m_autoSaveInterval);
            connect(m_autoSaveTimer, &QTimer::timeout, this, &FilePathIconListWidget::SlotAutoSave);
        }
        m_autoSaveTimer->start();
    }
    else if (m_autoSaveTimer)
    {
        m_autoSaveTimer->stop();
    }
}

void FilePathIconListWidget::SlotAutoSave()
{
    SaveFileListToJson();
}
