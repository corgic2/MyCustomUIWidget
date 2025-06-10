#pragma once
#include <QListWidget>
#include <QMenu>
#include <QWidget>
#include "FilePathIconListWidgetItem.h"
#include "ui_FilePathIconListWidget.h"
#include "../CommonDefine/UIWidgetGlobal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FilePathIconListWidgetClass; };
QT_END_NAMESPACE

/// <summary>
/// 文件路径图标列表控件类
/// </summary>
class CustomUIGlobal_API FilePathIconListWidget : public QListWidget
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
    /// <param name="parent">父窗口指针</param>
    explicit FilePathIconListWidget(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~FilePathIconListWidget() override;

    /// <summary>
    /// 添加文件项
    /// </summary>
    void AddFileItem(const FilePathIconListWidgetItem::ST_NodeInfo& nodeInfo);

    /// <summary>
    /// 在指定位置插入文件项
    /// </summary>
    /// <param name="index">插入位置的索引</param>
    /// <param name="nodeInfo">节点信息</param>
    void InsertFileItem(int index, const FilePathIconListWidgetItem::ST_NodeInfo& nodeInfo);

    /// <summary>
    /// 移除指定索引的文件项
    /// </summary>
    /// <param name="index">要移除的文件项索引</param>
    void RemoveItemByIndex(int index);

    /// <summary>
    /// 移除指定的文件项
    /// </summary>
    /// <param name="item">要移除的文件项指针</param>
    void RemoveItem(FilePathIconListWidgetItem* item);

    /// <summary>
    /// 清空列表
    /// </summary>
    void Clear();

    /// <summary>
    /// 获取指定索引的列表项
    /// </summary>
    /// <param name="index">索引</param>
    /// <returns>列表项指针</returns>
    FilePathIconListWidgetItem* GetItem(int index) const;

    /// <summary>
    /// 获取当前选中的列表项
    /// </summary>
    /// <returns>当前选中的列表项指针</returns>
    FilePathIconListWidgetItem* GetCurrentItem() const;

    /// <summary>
    /// 获取列表项数量
    /// </summary>
    /// <returns>列表项数量</returns>
    int GetItemCount() const;

    /// <summary>
    /// 将指定文件项移动到顶部
    /// </summary>
    /// <param name="item">要移动的文件项指针</param>
    void MoveItemToTop(FilePathIconListWidgetItem* item);

    /// <summary>
    /// 将指定索引的文件项移动到顶部
    /// </summary>
    /// <param name="index">要移动的文件项索引</param>
    void MoveItemToTop(int index);

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

    /// <summary>
    /// 设置边距
    /// </summary>
    /// <param name="left">左边距</param>
    /// <param name="top">上边距</param>
    /// <param name="right">右边距</param>
    /// <param name="bottom">下边距</param>
    void SetMargins(int left, int top, int right, int bottom);

    /// <summary>
    /// 设置边框宽度
    /// </summary>
    /// <param name="width">边框宽度</param>
    void SetBorderWidth(int width);

    /// <summary>
    /// 设置边框颜色
    /// </summary>
    /// <param name="color">边框颜色</param>
    void SetBorderColor(const QColor& color);

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
    /// 右键菜单请求信号
    /// </summary>
    void SigContextMenuRequested(const QString& filePath, const QPoint& pos);

protected:
    /// <summary>
    /// 上下文菜单事件
    /// </summary>
    void contextMenuEvent(QContextMenuEvent* event) override;

private slots:
    /// <summary>
    /// 列表项双击槽函数
    /// </summary>
    void SlotItemDoubleClicked(QListWidgetItem* item);

    /// <summary>
    /// 列表项点击槽函数
    /// </summary>
    void SlotItemClicked(QListWidgetItem* item);

    /// <summary>
    /// 显示文件属性槽函数
    /// </summary>
    void SlotShowFileProperties(bool clicked);

    /// <summary>
    /// 在资源管理器中显示槽函数
    /// </summary>
    void SlotShowInExplorer(bool bClicked);

    /// <summary>
    /// 复制文件路径槽函数
    /// </summary>
    void SlotCopyFilePath(bool bClicked);

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
    /// 初始化信号连接
    /// </summary>
    void SetupConnections();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

private:
    QMenu* m_contextMenu; /// 右键菜单
    int m_itemHeight; /// 列表项高度
    QColor m_backgroundColor; /// 背景色
    QColor m_itemHoverColor; /// 悬停色
    QColor m_itemSelectedColor; /// 选中色
    QColor m_itemTextColor; /// 文本色
    bool m_enableHoverEffect; /// 是否启用悬停效果
    bool m_enableSelectedEffect; /// 是否启用选中效果
    bool m_showContextMenu; /// 是否显示右键菜单
    int m_borderWidth; /// 边框宽度
    QColor m_borderColor; /// 边框颜色
};

