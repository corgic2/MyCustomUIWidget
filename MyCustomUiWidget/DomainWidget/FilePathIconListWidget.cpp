#include "FilePathIconListWidget.h"
#include <QApplication>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QProcess>
#include <QUrl>
#include <QVBoxLayout>
#include "StyleSystem/SkinStyleLoader.h"
#include "FileSystem/FileSystem.h"
#include "JsonUtils/JsonUtils.h"
#include "SDKCommonDefine/SDKCommonDefine.h"

FilePathIconListWidget::FilePathIconListWidget(QWidget* parent)
    : QListWidget(parent), m_contextMenu(nullptr), m_itemHeight(32), m_showContextMenu(true), m_jsonFilePath(""), m_autoSaveTimer(nullptr), m_autoSaveInterval(1800000)
{
    InitializeWidget();
    InitializeContextMenu();
    SetupConnections();
    // 使用皮肤系统加载样式
    AUTO_LOAD_SKIN_STYLE();
}

FilePathIconListWidget::~FilePathIconListWidget()
{
    if (m_autoSaveTimer)
    {
        m_autoSaveTimer->stop();
        SAFE_DELETE_POINTER_VALUE(m_autoSaveTimer);
    }
    SaveFileListToJson();
    SAFE_DELETE_POINTER_VALUE(m_contextMenu);
}

void FilePathIconListWidget::InitializeWidget()
{
    // 设置基本属性
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setSpacing(1);
}

void FilePathIconListWidget::InitializeContextMenu()
{
    m_contextMenu = new QMenu(this);

    // 添加菜单项
    auto showInExplorerAction = new QAction(tr("在文件资源管理器中显示"), this);
    auto deleteFileAction = new QAction(tr("删除音视频文件"), this);
    auto openWithAction = new QAction(tr("打开方式..."), this);

    // 设置图标
    showInExplorerAction->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    deleteFileAction->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
    openWithAction->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon));

    m_contextMenu->addAction(showInExplorerAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(deleteFileAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(openWithAction);

    // 连接信号
    connect(showInExplorerAction, &QAction::triggered, this, &FilePathIconListWidget::SlotShowInExplorer);
    connect(deleteFileAction, &QAction::triggered, this, &FilePathIconListWidget::SlotDeleteAVFile);
    connect(openWithAction, &QAction::triggered, this, &FilePathIconListWidget::SlotOpenWith);
}

void FilePathIconListWidget::SetupConnections()
{
    connect(this, &QListWidget::itemDoubleClicked, this, &FilePathIconListWidget::SlotItemDoubleClicked);
    connect(this, &QListWidget::itemClicked, this, &FilePathIconListWidget::SlotItemClicked);
}

void FilePathIconListWidget::AddFileItem(const FilePathIconListWidgetItem::ST_NodeInfo& nodeInfo)
{
    // 确保文件路径和显示名称由上层控制
    FilePathIconListWidgetItem::ST_NodeInfo utf8NodeInfo = nodeInfo;

    // 如果显示名称为空，使用文件名
    if (utf8NodeInfo.displayName.isEmpty())
    {
        QFileInfo fileInfo(utf8NodeInfo.filePath);
        utf8NodeInfo.displayName = fileInfo.fileName();
    }
    else
    {
        utf8NodeInfo.displayName = utf8NodeInfo.displayName;
    }

    utf8NodeInfo.filePath = utf8NodeInfo.filePath;

    auto item = new FilePathIconListWidgetItem(this);
    item->SetNodeInfo(utf8NodeInfo);
    addItem(item);
}

void FilePathIconListWidget::InsertFileItem(int index, const FilePathIconListWidgetItem::ST_NodeInfo& nodeInfo)
{
    // 确保文件路径和显示名称由上层控制
    FilePathIconListWidgetItem::ST_NodeInfo utf8NodeInfo = nodeInfo;

    // 如果显示名称为空，使用文件名
    if (utf8NodeInfo.displayName.isEmpty())
    {
        QFileInfo fileInfo(utf8NodeInfo.filePath);
        utf8NodeInfo.displayName = fileInfo.fileName();
    }
    else
    {
        utf8NodeInfo.displayName = utf8NodeInfo.displayName;
    }

    utf8NodeInfo.filePath = utf8NodeInfo.filePath;

    auto item = new FilePathIconListWidgetItem(this);
    item->SetNodeInfo(utf8NodeInfo);
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

bool FilePathIconListWidget::RemoveItemByFilePath(const QString& filePath)
{
    for (int i = 0; i < count(); ++i)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(item(i));
        if (fileItem && fileItem->GetFilePath() == filePath)
        {
            RemoveItemByIndex(i);
            return true;
        }
    }
    return false;
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

void FilePathIconListWidget::SlotShowInExplorer()
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
            else
            {
                QMessageBox::warning(this, tr("文件不存在"), tr("文件 %1 不存在。").arg(filePath));
            }
        }
    }
}

void FilePathIconListWidget::SlotDeleteAVFile()
{
    QListWidgetItem* tmpCurrentItem = currentItem();
    if (tmpCurrentItem)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(tmpCurrentItem);
        if (fileItem)
        {
            QString filePath = fileItem->GetFilePath();
            QFileInfo fileInfo(filePath);

            if (!fileInfo.exists())
            {
                QMessageBox::warning(this, tr("文件不存在"), tr("文件 %1 不存在。").arg(filePath));
                return;
            }

            int result = QMessageBox::question(this, tr("删除文件"), tr("确定要删除文件列表的 %1 吗？\n此操作不可撤销。").arg(fileInfo.fileName()), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

            if (result == QMessageBox::Yes)
            {
                // 发送删除信号，让外部处理具体的删除逻辑
                emit SigDeleteFileRequested(filePath);

                // 从列表中移除该项
                RemoveItemByFilePath(filePath);
            }
        }
    }
}

void FilePathIconListWidget::SlotOpenWith()
{
    QListWidgetItem* tmpCurrentItem = currentItem();
    if (tmpCurrentItem)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(tmpCurrentItem);
        if (fileItem)
        {
            QString filePath = fileItem->GetFilePath();
            QFileInfo fileInfo(filePath);

            if (!fileInfo.exists())
            {
                QMessageBox::warning(this, tr("文件不存在"), tr("文件 %1 不存在。").arg(filePath));
                return;
            }

            // 弹出文件选择对话框，选择要用来打开文件的程序
            QString selectedProgram = QFileDialog::getOpenFileName(this, tr("选择打开程序"), QString(), tr("可执行文件 (*.exe);;所有文件 (*.*)"));

            if (!selectedProgram.isEmpty())
            {
                QFileInfo programInfo(selectedProgram);
                if (programInfo.exists() && programInfo.isExecutable())
                {
                    // 使用选择的程序打开文件
                    QStringList arguments;
                    arguments << QDir::toNativeSeparators(filePath);

                    bool success = QProcess::startDetached(selectedProgram, arguments);
                    if (!success)
                    {
                        QMessageBox::warning(this, tr("打开失败"), tr("无法使用 %1 打开文件 %2").arg(programInfo.fileName()).arg(fileInfo.fileName()));
                    }
                }
                else
                {
                    QMessageBox::warning(this, tr("程序无效"), tr("选择的程序 %1 不存在或不可执行。").arg(selectedProgram));
                }
            }

            // 发送打开方式信号
            emit SigOpenWithRequested(filePath);
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
    
    // 确保文件存在
    if (!my_sdk::FileSystem::Exists(m_jsonFilePath.toStdString()))
    {
        my_sdk::FileSystem::WriteStringToFile(m_jsonFilePath.toStdString(), "{}");
    }
    
    // 使用新的JsonUtils读取JSON文件
    my_sdk::pt::ptree rootTree;
    my_sdk::EM_JsonOperationResult result = my_sdk::JsonUtils::ReadJsonTreeFromFile(m_jsonFilePath.toStdString(), rootTree);
    
    if (result == my_sdk::EM_JsonOperationResult::Success)
    {
        try
        {
            // 清空现有列表
            Clear();
            
            // 遍历JSON树
            for (const auto& item : rootTree)
            {
                const auto& fileObject = item.second;
                
                std::string filePath = fileObject.get<std::string>("filePath", "");
                std::string displayName = fileObject.get<std::string>("displayName", "");
                std::string iconPath = fileObject.get<std::string>("iconPath", "");
                
                if (!filePath.empty())
                {
                    // 标准化路径
                    filePath = my_sdk::FileSystem::NormalizePath(filePath);
                    
                    // 检查文件是否存在
                    if (my_sdk::FileSystem::Exists(filePath))
                    {
                        FilePathIconListWidgetItem::ST_NodeInfo nodeInfo;
                        nodeInfo.filePath = QString::fromStdString(filePath);
                        nodeInfo.displayName = QString::fromStdString(displayName);
                        nodeInfo.iconPath = QString::fromStdString(iconPath);
                        
                        // 添加到列表
                        AddFileItem(nodeInfo);
                    }
                }
            }
            emit SigFileListLoaded();
            return true;
        }
        catch (const std::exception&)
        {
            return false;
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

    my_sdk::pt::ptree rootTree;

    for (int i = 0; i < count(); ++i)
    {
        auto fileItem = dynamic_cast<FilePathIconListWidgetItem*>(item(i));
        if (fileItem)
        {
            my_sdk::pt::ptree fileTree;
            const auto& nodeInfo = fileItem->GetNodeInfo();
            
            fileTree.put("filePath", nodeInfo.filePath.toStdString());
            fileTree.put("displayName", nodeInfo.displayName.toStdString());
            fileTree.put("iconPath", nodeInfo.iconPath.toStdString());
            
            rootTree.add_child(std::to_string(i), fileTree);
        }
    }

    // 使用新的JsonUtils保存JSON
    my_sdk::EM_JsonOperationResult result = my_sdk::JsonUtils::WriteJsonTreeToFile(m_jsonFilePath.toStdString(), rootTree, true);

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
