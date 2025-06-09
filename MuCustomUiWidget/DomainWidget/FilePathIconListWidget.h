#pragma once
#include <QListWidget>
#include <QMenu>
#include <QWidget>
#include "FilePathIconListWidgetItem.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "ui_FilePathIconListWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FilePathIconListWidgetClass; };
QT_END_NAMESPACE

/// <summary>
/// 文件路径图标列表控件类
/// </summary>
class CustomUIGlobal_API FilePathIconListWidget : public QWidget
{
    Q_OBJECT
    /// 设置列表背景色
    Q_PROPERTY(QColor backgroundColor READ GetBackgroundColor WRITE SetBackgroundColor)
    /// 设置列表项悬停色
    Q_PROPERTY(QColor itemHoverColor READ GetItemHoverColor WRITE SetItemHoverColor)
    /// 设置列表项选中色
    Q_PROPERTY(QColor itemSelectedColor READ GetItemSelectedColor WRITE SetItemSelectedColor)
    /// 设置列表项文本色
    Q_PROPERTY(QColor itemTextColor READ GetItemTextColor WRITE SetItemTextColor)
    /// 设置列表项高度
    Q_PROPERTY(int itemHeight READ GetItemHeight WRITE SetItemHeight)
    /// 设置是否启用悬停效果
    Q_PROPERTY(bool enableHoverEffect READ GetEnableHoverEffect WRITE SetEnableHoverEffect)
    /// 设置是否启用选中效果
    Q_PROPERTY(bool enableSelectedEffect READ GetEnableSelectedEffect WRITE SetEnableSelectedEffect)
    /// 设置是否显示右键菜单
    Q_PROPERTY(bool showContextMenu READ GetShowContextMenu WRITE SetShowContextMenu)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    FilePathIconListWidget(QWidget *parent = nullptr);
    /// <summary>
    /// 析构函数
    /// </summary>
    ~FilePathIconListWidget();

    /// <summary>
    /// 添加文件项
    /// </summary>
    void AddFileItem(const FilePathIconListWidgetItem::ST_NodeInfo& nodeInfo);
    /// <summary>
    /// 清空列表
    /// </summary>
    void ClearItems();
    /// <summary>
    /// 获取当前选中项
    /// </summary>
    FilePathIconListWidgetItem* GetCurrentItem() const;
    /// <summary>
    /// 获取指定索引项
    /// </summary>
    FilePathIconListWidgetItem* GetItem(int index) const;
    /// <summary>
    /// 获取项数量
    /// </summary>
    int GetItemCount() const;

    // 属性访问方法
    QColor GetBackgroundColor() const { return m_backgroundColor; }

    void SetBackgroundColor(const QColor& color);

    QColor GetItemHoverColor() const { return m_itemHoverColor; }

    void SetItemHoverColor(const QColor& color);

    QColor GetItemSelectedColor() const { return m_itemSelectedColor; }

    void SetItemSelectedColor(const QColor& color);

    QColor GetItemTextColor() const { return m_itemTextColor; }

    void SetItemTextColor(const QColor& color);

    int GetItemHeight() const { return m_itemHeight; }

    void SetItemHeight(int height);

    bool GetEnableHoverEffect() const { return m_enableHoverEffect; }

    void SetEnableHoverEffect(bool enable);

    bool GetEnableSelectedEffect() const { return m_enableSelectedEffect; }

    void SetEnableSelectedEffect(bool enable);

    bool GetShowContextMenu() const { return m_showContextMenu; }

    void SetShowContextMenu(bool show);

signals:
    /// <summary>
    /// 文件项双击信号
    /// </summary>
    void SigItemDoubleClicked(const QString& filePath);
    /// <summary>
    /// 文件项选中信号
    /// </summary>
    void SigItemSelected(const QString& filePath);
    /// <summary>
    /// 文件项右键菜单信号
    /// </summary>
    void SigContextMenuRequested(const QString& filePath, const QPoint& pos);

protected:
    /// <summary>
    /// 右键菜单事件
    /// </summary>
    void contextMenuEvent(QContextMenuEvent* event) override;

private slots:
    /// <summary>
    /// 处理项双击
    /// </summary>
    void SlotItemDoubleClicked(QListWidgetItem* item);
    /// <summary>
    /// 处理项选中
    /// </summary>
    void SlotItemClicked(QListWidgetItem* item);
    /// <summary>
    /// 显示文件属性
    /// </summary>
    void SlotShowFileProperties();
    /// <summary>
    /// 在资源管理器中显示
    /// </summary>
    void SlotShowInExplorer();
    /// <summary>
    /// 复制文件路径
    /// </summary>
    void SlotCopyFilePath();

private:
    /// <summary>
    /// 初始化界面
    /// </summary>
    void InitializeWidget();
    /// <summary>
    /// 初始化右键菜单
    /// </summary>
    void InitializeContextMenu();
    /// <summary>
    /// 设置信号连接
    /// </summary>
    void SetupConnections();
    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

private:
    Ui::FilePathIconListWidgetClass* m_ui;
    QListWidget* m_listWidget; /// 列表控件
    QMenu* m_contextMenu; /// 右键菜单
    QColor m_backgroundColor; /// 背景色
    QColor m_itemHoverColor; /// 项悬停色
    QColor m_itemSelectedColor; /// 项选中色
    QColor m_itemTextColor; /// 项文本色
    int m_itemHeight; /// 项高度
    bool m_enableHoverEffect; /// 启用悬停效果
    bool m_enableSelectedEffect; /// 启用选中效果
    bool m_showContextMenu; /// 显示右键菜单
};

