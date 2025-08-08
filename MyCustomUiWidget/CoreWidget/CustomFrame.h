#pragma once

#include <QFrame>
#include <QPainter>
#include <QWidget>
#include <QLayout>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/BaseDefine/BaseStyleWidgetInterface.h"
#include "CustomFrameLayoutManager.h"

/// <summary>
/// 自定义Frame控件类，提供丰富的样式和布局设置
/// 支持所有QFrame功能，包括多种边框样式和布局
/// 支持作为容器使用，可以包含其他控件
/// </summary>
class CustomUIGlobal_API CustomFrame : public QFrame, public BaseStyleWidgetInterface
{
    Q_OBJECT
    Q_PROPERTY(EM_CustomFrameFormat EM_FrameFormat READ GetFrameFormat WRITE SetFrameFormat NOTIFY ApplyFormatStyle)
    Q_PROPERTY(QString frameFormat READ GetStyleFormatStr WRITE SetStyleFormatStr)
    Q_PROPERTY(QString layoutType READ GetLayoutTypeString WRITE SetLayoutTypeString)
public:
    /// <summary>
    /// Frame格式枚举类型
    /// </summary>
    enum EM_CustomFrameFormat
    {
        EM_Normal = 0,      ///< 普通格式
        EM_Card = 1,        ///< 卡片格式
        EM_Panel = 2,       ///< 面板格式
        EM_Shadow = 3,      ///< 阴影格式
        EM_Raised = 4,      ///< 凸起格式
        EM_Sunken = 5,      ///< 凹陷格式
        EM_Line = 6,        ///< 线框格式
        EM_None = 7         ///< 无边框格式
    };
    Q_ENUM(EM_CustomFrameFormat)

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomFrame(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomFrame() override;
    
    /// <summary>
    /// 获取当前Frame格式
    /// </summary>
    EM_CustomFrameFormat GetFrameFormat() const;

    /// <summary>
    /// 设置Frame格式
    /// </summary>
    /// <param name="format">格式枚举值</param>
    void SetFrameFormat(EM_CustomFrameFormat format);
    
    /// <summary>
    /// 设置垂直布局
    /// </summary>
    void SetVerticalLayout();
    
    /// <summary>
    /// 设置水平布局
    /// </summary>
    void SetHorizontalLayout();
    
    /// <summary>
    /// 设置栅格布局
    /// </summary>
    void SetGridLayout();
    
    /// <summary>
    /// 设置表单布局
    /// </summary>
    void SetFormLayout();
    
    /// <summary>
    /// 设置堆叠布局
    /// </summary>
    void SetStackedLayout();
    
    /// <summary>
    /// 获取当前布局类型
    /// </summary>
    /// <returns>布局类型字符串</returns>
    QString GetLayoutType() const;
    
    /// <summary>
    /// 获取当前布局类型字符串
    /// </summary>
    /// <returns>布局类型字符串</returns>
    QString GetLayoutTypeString() const;
    
    /// <summary>
    /// 设置布局类型字符串
    /// </summary>
    void SetLayoutTypeString(const QString& type);
    
    /// <summary>
    /// 基类函数修改样式
    /// </summary>
    void ApplyFormatStyle() override;
protected:
    /// <summary>
    /// 基类函数链接信号
    /// </summary>
    void Connectionals() override;
    /// <summary>
    /// 基类函数初始化
    /// </summary>
    void Initilize() override;
private:
    EM_CustomFrameFormat m_frameFormat;  ///< 当前Frame格式
    CustomFrameLayoutManager* m_layoutManager; ///< 布局管理器
};

Q_DECLARE_METATYPE(CustomFrame::EM_CustomFrameFormat)
