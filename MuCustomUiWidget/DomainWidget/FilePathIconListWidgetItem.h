#pragma once
#include "UIWidgetGlobal.h"
#include "../CoreWidget/CustomLabel.h"
#include "../UtilsWidget/CustomToolTips.h"
#include "ui_FilePathIconListWidgetItem.h"
#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class FilePathIconListWidgetItemClass; };
QT_END_NAMESPACE

/// <summary>
/// 文件路径图标列表项控件类，用于显示带图标和提示的文件路径项
/// </summary>
class CustomUIGlobal_API FilePathIconListWidgetItem : public QWidget
{
    Q_OBJECT

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
        QString iconFilePath;      /// 图标路径
        QString content;           /// 显示内容
        QString toolTipsContent;   /// 提示内容
        QString toolTipsContentEx; /// 扩展提示内容
        EM_NodeType nodeType = Normal;   /// 节点类型
    };

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    FilePathIconListWidgetItem(QWidget *parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~FilePathIconListWidgetItem();

    /// <summary>
    /// 设置节点文本信息
    /// </summary>
    /// <param name="nodeInfo">节点信息结构体</param>
    void SetItemNodeText(const ST_NodeInfo& nodeInfo);
    
    /// <summary>
    /// 设置背景颜色
    /// </summary>
    /// <param name="color">RGBA颜色值</param>
    void SetBackgroundColor(const UIColorDefine::ST_ColorRgba& color);

    /// <summary>
    /// 设置悬停颜色
    /// </summary>
    /// <param name="color">RGBA颜色值</param>
    void SetHoverColor(const UIColorDefine::ST_ColorRgba& color);

    /// <summary>
    /// 设置选中颜色
    /// </summary>
    /// <param name="color">RGBA颜色值</param>
    void SetSelectedColor(const UIColorDefine::ST_ColorRgba& color);

    /// <summary>
    /// 设置文本颜色
    /// </summary>
    /// <param name="color">RGB颜色值</param>
    void SetTextColor(const UIColorDefine::ST_ColorRgb& color);

    /// <summary>
    /// 启用悬停效果
    /// </summary>
    /// <param name="enable">是否启用</param>
    void EnableHoverEffect(bool enable = true);

    /// <summary>
    /// 启用选中效果
    /// </summary>
    /// <param name="enable">是否启用</param>
    void EnableSelectedEffect(bool enable = true);

    /// <summary>
    /// 获取节点信息
    /// </summary>
    /// <returns>节点信息结构体的常量引用</returns>
    const ST_NodeInfo& GetNodeInfo() const { return m_info; }

protected:
    /// <summary>
    /// 事件过滤器
    /// </summary>
    bool eventFilter(QObject* watched, QEvent* event) override;

    /// <summary>
    /// 鼠标进入事件
    /// </summary>
    void enterEvent(QEvent* event) override;

    /// <summary>
    /// 鼠标离开事件
    /// </summary>
    void leaveEvent(QEvent* event) override;

    /// <summary>
    /// 鼠标按下事件
    /// </summary>
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    /// <summary>
    /// 显示工具提示
    /// </summary>
    void ShowToolTip();

    /// <summary>
    /// 样式变化槽函数
    /// </summary>
    void OnStyleChanged();

private:
    /// <summary>
    /// 初始化UI
    /// </summary>
    void InitializeUI();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

    /// <summary>
    /// 设置信号连接
    /// </summary>
    void SetupConnections();

private:
    Ui::FilePathIconListWidgetItemClass* m_ui;  /// UI对象指针
    ST_NodeInfo m_info;                         /// 节点信息
    QTimer m_timer;                             /// 提示显示定时器
    CustomToolTips* m_tipsWidget = nullptr;               /// 提示框控件
    int m_delay = 700;                                /// 提示显示延时

    UIColorDefine::ST_ColorRgba m_backgroundColor;  /// 背景颜色
    UIColorDefine::ST_ColorRgba m_hoverColor;      /// 悬停颜色
    UIColorDefine::ST_ColorRgba m_selectedColor;   /// 选中颜色
    UIColorDefine::ST_ColorRgb m_textColor;        /// 文本颜色
    bool m_isHovered;                              /// 是否处于悬停状态
    bool m_isSelected = false;                             /// 是否处于选中状态
    bool m_enableHover = true;                            /// 是否启用悬停效果
    bool m_enableSelected = true;                         /// 是否启用选中效果    , m_isHovered(false)
};

