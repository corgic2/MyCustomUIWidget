#pragma once

#include <QFrame>
#include <QPainter>
#include <QWidget>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/BaseDefine/BaseStyleWidgetInterface.h"

/// <summary>
/// 自定义Frame控件类，提供丰富的样式和布局设置
/// 支持所有QFrame功能，包括多种边框样式和布局
/// </summary>
class CustomUIGlobal_API CustomFrame : public QFrame, public BaseStyleWidgetInterface
{
    Q_OBJECT
    Q_PROPERTY(EM_CustomFrameFormat EM_FrameFormat READ GetFrameFormat WRITE SetFrameFormat NOTIFY ApplyFormatStyle)
    Q_PROPERTY(QString frameFormat READ GetStyleFormatStr WRITE SetStyleFormatStr)
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
};

Q_DECLARE_METATYPE(CustomFrame::EM_CustomFrameFormat)
