#pragma once

#include <QLabel>
#include <QWidget>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/BaseDefine/BaseStyleWidgetInterface.h"


/// <summary>
/// 自定义标签控件类，提供丰富的样式和特效设置
/// 支持多种预设格式，通过枚举切换实现样式快速变更
/// </summary>
class CustomUIGlobal_API CustomLabel : public QLabel, public BaseStyleWidgetInterface
{
    Q_OBJECT
    Q_PROPERTY(EM_CustomLabelFormat EM_LabelFormat READ GetLabelFormat WRITE SetLabelFormat NOTIFY ApplyFormatStyle)
    Q_PROPERTY(QString labelFormat READ GetStyleFormatStr WRITE SetStyleFormatStr)
public:
    /// <summary>
    /// 标签格式枚举类型
    /// </summary>
    enum EM_CustomLabelFormat
    {
        EM_Normal = 0,      ///< 普通格式
        EM_Title = 1,       ///< 标题格式
        EM_SubTitle = 2,    ///< 副标题格式
        EM_Description = 3, ///< 描述格式
        EM_Warning = 4,     ///< 警告格式
        EM_Error = 5,       ///< 错误格式
        EM_Success = 6,     ///< 成功格式
        EM_Info = 7         ///< 信息格式
    };
    Q_ENUM(EM_CustomLabelFormat)

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomLabel(QWidget* parent = nullptr);
    
    /// <summary>
    /// 委托构造
    /// </summary>
    /// <param name="text">标签文本</param>
    /// <param name="parent">父窗口指针</param>
    CustomLabel(const QString& text, QWidget* parent);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomLabel() override;
    /// <summary>
    /// 获取当前标签格式
    /// </summary>
    EM_CustomLabelFormat GetLabelFormat() const;

    /// <summary>
    /// 设置标签格式
    /// </summary>
    /// <param name="format">格式枚举值</param>
    void SetLabelFormat(EM_CustomLabelFormat format);
    /// <summary>
    /// 基类函数修改样式
    /// </summary>
    void ApplyFormatStyle() override;
protected:
    /// <summary>
    /// 信号槽连接
    /// </summary>
    void Connectionals() override;
    /// <summary>
    /// 初始化
    /// </summary>
    void Initilize() override;
private:
    EM_CustomLabelFormat m_labelFormat;  ///< 当前标签格式
};

Q_DECLARE_METATYPE(CustomLabel::EM_CustomLabelFormat)