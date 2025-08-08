#pragma once

#include <QComboBox>
#include <QListView>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/BaseDefine/BaseStyleWidgetInterface.h"

/// <summary>
/// 自定义组合框控件类，提供丰富的样式设置
/// </summary>
class CustomUIGlobal_API CustomComboBox : public QComboBox, public BaseStyleWidgetInterface
{
    Q_OBJECT
    Q_PROPERTY(EM_CustomComboBoxFormat EM_ComboBoxFormat READ GetComboBoxFormat WRITE SetComboBoxFormat NOTIFY ApplyFormatStyle)
    Q_PROPERTY(QString comboBoxFormat READ GetStyleFormatStr WRITE SetStyleFormatStr)
public:
    /// <summary>
    /// 组合框格式枚举类型
    /// </summary>
    enum EM_CustomComboBoxFormat
    {
        EM_Normal = 0,      ///< 普通格式
        EM_Primary = 1,     ///< 主要格式
        EM_Success = 2,     ///< 成功格式
        EM_Warning = 3,     ///< 警告格式
        EM_Error = 4,       ///< 错误格式
        EM_Info = 5,        ///< 信息格式
        EM_Link = 6,        ///< 链接格式
        EM_Disabled = 7     ///< 禁用格式
    };
    Q_ENUM(EM_CustomComboBoxFormat)

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomComboBox(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomComboBox();
    
    /// <summary>
    /// 获取当前组合框格式
    /// </summary>
    EM_CustomComboBoxFormat GetComboBoxFormat() const;

    /// <summary>
    /// 设置组合框格式
    /// </summary>
    /// <param name="format">格式枚举值</param>
    void SetComboBoxFormat(EM_CustomComboBoxFormat format);
    /// <summary>
    /// 基类函数修改样式
    /// </summary>
    void ApplyFormatStyle() override;
protected:
    /// <summary>
    /// 基类函数连接信号槽
    /// </summary>
    void Connectionals() override;
    /// <summary>
    /// 基类函数初始化
    /// </summary>
    void Initilize() override;
private:
    EM_CustomComboBoxFormat m_comboBoxFormat;  ///< 当前组合框格式
};

Q_DECLARE_METATYPE(CustomComboBox::EM_CustomComboBoxFormat)
