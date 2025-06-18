#pragma once

#include <QLineEdit>
#include <QRegularExpression>
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/RegexDefine.h"

/// <summary>
/// 带验证功能的输入框控件
/// </summary>
class CustomUIGlobal_API ValidatedLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString m_pattern READ GetPattern WRITE SetPattern)
    Q_PROPERTY(bool m_isValid READ IsValid)
    Q_PROPERTY(QString m_errorMessage READ GetErrorMessage WRITE SetErrorMessage)
    Q_PROPERTY(bool m_showErrorMessage READ GetShowErrorMessage WRITE SetShowErrorMessage)
    Q_PROPERTY(QColor m_errorBorderColor READ GetErrorBorderColor WRITE SetErrorBorderColor)
    Q_PROPERTY(QColor m_normalBorderColor READ GetNormalBorderColor WRITE SetNormalBorderColor)
    Q_PROPERTY(ValidationType m_validationType READ GetValidationType WRITE SetValidationType)

public:
    /// <summary>
    /// 验证类型枚举
    /// </summary>
    enum ValidationType
    {
        Custom = 0,     /// 自定义正则表达式
        Email,          /// 邮箱
        Phone,          /// 手机号
        IPV4,           /// IPv4地址
        Number,         /// 数字
        Letter,         /// 字母
        AlphaNum,       /// 字母和数字
        URL,            /// URL
        Date,           /// 日期
        Time,           /// 时间
        Password        /// 密码
    };
    Q_ENUM(ValidationType)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit ValidatedLineEdit(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~ValidatedLineEdit();

    /// <summary>
    /// 设置验证类型
    /// </summary>
    /// <param name="type">验证类型</param>
    void SetValidationType(ValidationType type);

    /// <summary>
    /// 设置自定义正则表达式
    /// </summary>
    /// <param name="pattern">正则表达式</param>
    void SetPattern(const QString& pattern);

    /// <summary>
    /// 设置错误提示信息
    /// </summary>
    /// <param name="message">错误信息</param>
    void SetErrorMessage(const QString& message);

    /// <summary>
    /// 设置是否显示错误提示
    /// </summary>
    /// <param name="show">是否显示</param>
    void SetShowErrorMessage(bool show);

    /// <summary>
    /// 设置错误状态下的边框颜色
    /// </summary>
    /// <param name="color">颜色</param>
    void SetErrorBorderColor(const QColor& color);

    /// <summary>
    /// 设置正常状态下的边框颜色
    /// </summary>
    /// <param name="color">颜色</param>
    void SetNormalBorderColor(const QColor& color);

    // Getters
    QString GetPattern() const { return m_pattern; }
    bool IsValid() const { return m_isValid; }
    QString GetErrorMessage() const { return m_errorMessage; }
    bool GetShowErrorMessage() const { return m_showErrorMessage; }
    QColor GetErrorBorderColor() const { return m_errorBorderColor; }
    QColor GetNormalBorderColor() const { return m_normalBorderColor; }
    ValidationType GetValidationType() const { return m_validationType; }

protected:
    /// <summary>
    /// 焦点离开事件
    /// </summary>
    void focusOutEvent(QFocusEvent* event) override;

    /// <summary>
    /// 焦点进入事件
    /// </summary>
    void focusInEvent(QFocusEvent* event) override;

private slots:
    /// <summary>
    /// 文本改变槽函数
    /// </summary>
    /// <param name="text">改变后的文本</param>
    void OnTextChanged(const QString& text);

private:
    /// <summary>
    /// 初始化控件
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

    /// <summary>
    /// 验证输入
    /// </summary>
    void ValidateInput();

private:
    QString m_pattern;                /// 正则表达式
    bool m_isValid;                  /// 是否有效
    QString m_errorMessage;          /// 错误提示信息
    bool m_showErrorMessage;         /// 是否显示错误提示
    QColor m_errorBorderColor;       /// 错误状态边框颜色
    QColor m_normalBorderColor;      /// 正常状态边框颜色
    ValidationType m_validationType; /// 验证类型
};

Q_DECLARE_METATYPE(ValidatedLineEdit::ValidationType) 