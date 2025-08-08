#pragma once

#include <QLineEdit>
#include <QMap>
#include <QRegularExpression>
#include "../CommonDefine/RegexDefine.h"
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/ValidatedLineEditDefine.h"

/// <summary>
/// 带验证功能的输入框控件
/// </summary>
class CustomUIGlobal_API ValidatedLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit ValidatedLineEdit(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~ValidatedLineEdit() override;

    // 规则管理
    void AddValidationRule(const ST_ValidationRule& rule);
    void RemoveValidationRule(const QString& ruleName);
    void ClearAllRules();
    ST_ValidationRule GetValidationRule(const QString& ruleName) const;
    QStringList GetAllRuleNames() const;

    // 当前规则设置
    void SetCurrentRuleName(const QString& ruleName);
    QString GetCurrentRuleName() const;

    // 验证功能
    ST_ValidationResult ValidateInput(const QString& input) const;
    ST_ValidationResult ValidateCurrentInput() const;

    // 范围限制
    void SetInputRange(const ST_InputRange& range);
    ST_InputRange GetInputRange() const;

    // 配置选项
    void SetAutoValidationEnabled(bool enabled);
    bool IsAutoValidationEnabled() const;

    void SetShowToolTipsEnabled(bool enabled);
    bool IsShowToolTipsEnabled() const;

    // 快速设置常用验证
    void SetEmailValidation();
    void SetPhoneValidation();
    void SetNumberValidation();
    void SetUrlValidation();
    void SetPasswordValidation(int minLength = 8);

signals:
    void SigValidationStateChanged(const ST_ValidationResult& result);
    void SigInputAccepted(const QString& text);
    void SigInputRejected(const QString& text, const QString& reason);

protected slots:
    void SlotOnTextChanged(const QString& text);
    void SlotOnEditingFinished();

private:
    void InitializeDefaultRules();
    void UpdateVisualState(const ST_ValidationResult& result);
    bool CheckInputRange(const QString& input) const;

private:
    QMap<QString, ST_ValidationRule> m_validationRules;
    QString m_currentRuleName;
    ST_InputRange m_inputRange;
    bool m_autoValidationEnabled;
    bool m_showToolTipsEnabled;
    bool m_isValid;
};
