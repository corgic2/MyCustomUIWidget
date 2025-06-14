﻿#pragma once
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CoreWidget/CustomLabel.h"
#include "../UtilsWidget/CustomToolTips.h"
#include <QListWidgetItem>
#include <QColor>

/// <summary>
/// 文件路径图标列表项控件类，用于显示带图标和提示的文件路径项
/// </summary>
class CustomUIGlobal_API FilePathIconListWidgetItem : public QListWidgetItem
{
public:
    /// <summary>
    /// 节点类型枚举，定义列表项的不同类型
    /// </summary>
    enum EM_NodeType
    {
        Normal,     /// 普通节点
        Folder,     /// 文件夹节点
        File,       /// 文件节点
        Warning,    /// 警告节点
        Error       /// 错误节点
    };

    /// <summary>
    /// 节点信息结构体，包含列表项的完整显示信息
    /// </summary>
    struct ST_NodeInfo
    {
        QString filePath;          /// 文件路径
        QString displayName;       /// 显示名称
        QString iconPath;          /// 图标路径
        EM_NodeType type;          /// 节点类型

        ST_NodeInfo()
            : type(Normal)
        {
        }
    };

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit FilePathIconListWidgetItem(QListWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~FilePathIconListWidgetItem();

    /// <summary>
    /// 设置节点信息
    /// </summary>
    /// <param name="nodeInfo">节点信息结构体</param>
    void SetNodeInfo(const ST_NodeInfo& nodeInfo);

    /// <summary>
    /// 获取节点信息
    /// </summary>
    /// <returns>节点信息结构体</returns>
    const ST_NodeInfo& GetNodeInfo() const { return m_nodeInfo; }

    /// <summary>
    /// 获取文件路径
    /// </summary>
    /// <returns>文件路径</returns>
    QString GetFilePath() const { return m_nodeInfo.filePath; }

    /// <summary>
    /// 设置文本颜色
    /// </summary>
    void SetTextColor(const QColor& color);

    /// <summary>
    /// 设置背景颜色
    /// </summary>
    void SetBackgroundColor(const QColor& color);

    /// <summary>
    /// 设置选中颜色
    /// </summary>
    void SetSelectedColor(const QColor& color);

    /// <summary>
    /// 设置悬停颜色
    /// </summary>
    void SetHoverColor(const QColor& color);

    /// <summary>
    /// 启用悬停效果
    /// </summary>
    void EnableHoverEffect(bool enable = true);

    /// <summary>
    /// 启用选中效果
    /// </summary>
    void EnableSelectedEffect(bool enable = true);

private:
    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

private:
    ST_NodeInfo m_nodeInfo;                     /// 节点信息
    QColor m_textColor;                         /// 文本颜色
    QColor m_backgroundColor;                   /// 背景颜色
    QColor m_hoverColor;                        /// 悬停颜色
    QColor m_selectedColor;                     /// 选中颜色
    bool m_enableHover;                         /// 是否启用悬停效果
    bool m_enableSelected;                      /// 是否启用选中效果
};

