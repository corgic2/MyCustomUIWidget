#include "FilePathIconListWidgetItem.h"
#include <QFileInfo>
#include <QPainter>
#include "StyleSystem/SkinStyleLoader.h"

FilePathIconListWidgetItem::FilePathIconListWidgetItem(QListWidget* parent)
    : QListWidgetItem(parent)
{
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
        setText(m_nodeInfo.displayName);
    }
    else
    {
        // 如果displayName为空，使用文件路径的最后一部分作为显示名
        QFileInfo fileInfo(m_nodeInfo.filePath);
        setText(fileInfo.fileName());
    }

    // 设置图标
    if (!m_nodeInfo.iconPath.isEmpty())
    {
        setIcon(QIcon(m_nodeInfo.iconPath));
    }

    // 设置提示文本
    setToolTip(m_nodeInfo.filePath);
}

