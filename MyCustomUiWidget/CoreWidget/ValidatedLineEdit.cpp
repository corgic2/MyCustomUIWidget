#include "ValidatedLineEdit.h"
#include <QDebug>
#include <QFocusEvent>
#include <QStyle>
#include <QToolTip>
#include "StyleSystem/SkinStyleLoader.h"

ValidatedLineEdit::ValidatedLineEdit(QWidget* parent)
    : QLineEdit(parent), m_autoValidationEnabled(true), m_showToolTipsEnabled(true), m_isValid(false)
{
    AUTO_LOAD_SKIN_STYLE();
    InitializeDefaultRules();

    // 设置默认输入范围
    m_inputRange = ST_InputRange(0, INT_MAX);

    // 连接信号槽
    connect(this, &QLineEdit::textChanged, this, &ValidatedLineEdit::SlotOnTextChanged);
    connect(this, &QLineEdit::editingFinished, this, &ValidatedLineEdit::SlotOnEditingFinished);

    // 设置默认验证规则
    if (!m_validationRules.isEmpty())
    {
        m_currentRuleName = m_validationRules.keys().first();
    }
}

ValidatedLineEdit::~ValidatedLineEdit()
{
}

void ValidatedLineEdit::InitializeDefaultRules()
{
    // 邮箱验证规则
    ST_ValidationRule emailRule;
    emailRule.m_ruleName = "Email";
    emailRule.m_regularExpression = QRegularExpression(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    emailRule.m_validationMode = EM_ValidationMode::EM_ValidationMode_ExactMatch;
    emailRule.m_errorMessage = "请输入有效的邮箱地址";
    emailRule.m_successMessage = "邮箱格式正确";
    emailRule.m_isEnabled = true;
    m_validationRules.insert("Email", emailRule);

    // 手机号验证规则
    ST_ValidationRule phoneRule;
    phoneRule.m_ruleName = "Phone";
    phoneRule.m_regularExpression = QRegularExpression(R"(^1[3-9]\d{9}$)");
    phoneRule.m_validationMode = EM_ValidationMode::EM_ValidationMode_ExactMatch;
    phoneRule.m_errorMessage = "请输入有效的手机号码";
    phoneRule.m_successMessage = "手机号格式正确";
    phoneRule.m_isEnabled = true;
    m_validationRules.insert("Phone", phoneRule);

    // 数字验证规则
    ST_ValidationRule numberRule;
    numberRule.m_ruleName = "Number";
    numberRule.m_regularExpression = QRegularExpression(R"(^\d+$)");
    numberRule.m_validationMode = EM_ValidationMode::EM_ValidationMode_ExactMatch;
    numberRule.m_errorMessage = "请输入数字";
    numberRule.m_successMessage = "数字格式正确";
    numberRule.m_isEnabled = true;
    m_validationRules.insert("Number", numberRule);

    // URL验证规则
    ST_ValidationRule urlRule;
    urlRule.m_ruleName = "Url";
    urlRule.m_regularExpression = QRegularExpression(R"(^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$)");
    urlRule.m_validationMode = EM_ValidationMode::EM_ValidationMode_ExactMatch;
    urlRule.m_errorMessage = "请输入有效的网址";
    urlRule.m_successMessage = "网址格式正确";
    urlRule.m_isEnabled = true;
    m_validationRules.insert("Url", urlRule);

    // 密码验证规则
    ST_ValidationRule passwordRule;
    passwordRule.m_ruleName = "Password";
    passwordRule.m_regularExpression = QRegularExpression(R"(^[a-zA-Z0-9!@#$%^&*]{8,}$)");
    passwordRule.m_validationMode = EM_ValidationMode::EM_ValidationMode_ExactMatch;
    passwordRule.m_errorMessage = "密码至少8位，包含字母、数字或特殊字符";
    passwordRule.m_successMessage = "密码格式正确";
    passwordRule.m_isEnabled = true;
    m_validationRules.insert("Password", passwordRule);
}

void ValidatedLineEdit::AddValidationRule(const ST_ValidationRule& rule)
{
    m_validationRules.insert(rule.m_ruleName, rule);
    if (m_currentRuleName.isEmpty())
    {
        m_currentRuleName = rule.m_ruleName;
    }
}

void ValidatedLineEdit::RemoveValidationRule(const QString& ruleName)
{
    m_validationRules.remove(ruleName);
    if (m_currentRuleName == ruleName)
    {
        m_currentRuleName = m_validationRules.isEmpty() ? QString() : m_validationRules.keys().first();
    }
}

void ValidatedLineEdit::ClearAllRules()
{
    m_validationRules.clear();
    m_currentRuleName.clear();
}

ST_ValidationRule ValidatedLineEdit::GetValidationRule(const QString& ruleName) const
{
    return m_validationRules.value(ruleName);
}

QStringList ValidatedLineEdit::GetAllRuleNames() const
{
    return m_validationRules.keys();
}

void ValidatedLineEdit::SetCurrentRuleName(const QString& ruleName)
{
    if (m_validationRules.contains(ruleName))
    {
        m_currentRuleName = ruleName;
        // 立即验证当前输入
        SlotOnTextChanged(text());
    }
}

QString ValidatedLineEdit::GetCurrentRuleName() const
{
    return m_currentRuleName;
}

ST_ValidationResult ValidatedLineEdit::ValidateInput(const QString& input) const
{
    if (input.isEmpty())
    {
        return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Empty, "输入不能为空");
    }

    // 检查输入范围
    if (!CheckInputRange(input))
    {
        return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Invalid, QString("输入长度应在%1-%2之间").arg(m_inputRange.m_minLength).arg(m_inputRange.m_maxLength));
    }

    if (m_currentRuleName.isEmpty() || !m_validationRules.contains(m_currentRuleName))
    {
        return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Valid, "无验证规则");
    }

    const ST_ValidationRule& rule = m_validationRules.value(m_currentRuleName);
    if (!rule.m_isEnabled)
    {
        return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Valid, "规则已禁用");
    }

    QRegularExpressionMatch match = rule.m_regularExpression.match(input);

    switch (rule.m_validationMode)
    {
        case EM_ValidationMode::EM_ValidationMode_ExactMatch:
            if (match.hasMatch() && match.capturedLength() == input.length())
            {
                return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Valid, rule.m_successMessage, match.capturedStart(), match.capturedLength());
            }
            break;

        case EM_ValidationMode::EM_ValidationMode_Contains:
            if (match.hasMatch())
            {
                return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Valid, rule.m_successMessage, match.capturedStart(), match.capturedLength());
            }
            break;

        case EM_ValidationMode::EM_ValidationMode_StartWith:
            if (match.hasMatch() && match.capturedStart() == 0)
            {
                return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Valid, rule.m_successMessage, 0, match.capturedLength());
            }
            break;

        case EM_ValidationMode::EM_ValidationMode_EndWith:
            if (match.hasMatch() && (match.capturedStart() + match.capturedLength()) == input.length())
            {
                return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Valid, rule.m_successMessage, match.capturedStart(), match.capturedLength());
            }
            break;
    }

    return ST_ValidationResult(EM_ValidationState::EM_ValidationState_Invalid, rule.m_errorMessage);
}

ST_ValidationResult ValidatedLineEdit::ValidateCurrentInput() const
{
    return ValidateInput(text());
}

void ValidatedLineEdit::SetInputRange(const ST_InputRange& range)
{
    m_inputRange = range;
    SlotOnTextChanged(text());
}

ST_InputRange ValidatedLineEdit::GetInputRange() const
{
    return m_inputRange;
}

void ValidatedLineEdit::SetAutoValidationEnabled(bool enabled)
{
    m_autoValidationEnabled = enabled;
}

bool ValidatedLineEdit::IsAutoValidationEnabled() const
{
    return m_autoValidationEnabled;
}

void ValidatedLineEdit::SetShowToolTipsEnabled(bool enabled)
{
    m_showToolTipsEnabled = enabled;
}

bool ValidatedLineEdit::IsShowToolTipsEnabled() const
{
    return m_showToolTipsEnabled;
}

void ValidatedLineEdit::SetEmailValidation()
{
    SetCurrentRuleName("Email");
}

void ValidatedLineEdit::SetPhoneValidation()
{
    SetCurrentRuleName("Phone");
}

void ValidatedLineEdit::SetNumberValidation()
{
    SetCurrentRuleName("Number");
}

void ValidatedLineEdit::SetUrlValidation()
{
    SetCurrentRuleName("Url");
}

void ValidatedLineEdit::SetPasswordValidation(int minLength)
{
    SetCurrentRuleName("Password");
    ST_InputRange range;
    range.m_minLength = minLength;
    range.m_maxLength = INT_MAX;
    SetInputRange(range);
}

bool ValidatedLineEdit::CheckInputRange(const QString& input) const
{
    int length = input.length();
    if (length < m_inputRange.m_minLength || length > m_inputRange.m_maxLength)
    {
        return false;
    }

    // 检查允许的字符
    if (!m_inputRange.m_allowedChars.isEmpty())
    {
        for (const QChar& ch : input)
        {
            if (!m_inputRange.m_allowedChars.contains(ch))
            {
                return false;
            }
        }
    }

    // 检查禁止的字符
    if (!m_inputRange.m_forbiddenChars.isEmpty())
    {
        for (const QChar& ch : input)
        {
            if (m_inputRange.m_forbiddenChars.contains(ch))
            {
                return false;
            }
        }
    }

    return true;
}

void ValidatedLineEdit::UpdateVisualState(const ST_ValidationResult& result)
{
    m_isValid = (result.m_validationState == EM_ValidationState::EM_ValidationState_Valid);

    // 更新样式类
    QString styleClass = "validated-lineedit-";
    switch (result.m_validationState)
    {
        case EM_ValidationState::EM_ValidationState_Valid:
            styleClass += "valid";
            break;
        case EM_ValidationState::EM_ValidationState_Invalid:
            styleClass += "invalid";
            break;
        case EM_ValidationState::EM_ValidationState_Empty:
            styleClass += "empty";
            break;
        case EM_ValidationState::EM_ValidationState_Partial:
            styleClass += "partial";
            break;
    }

    setProperty("validation-state", styleClass);
    style()->unpolish(this);
    style()->polish(this);

    // 显示提示信息
    if (m_showToolTipsEnabled && !result.m_message.isEmpty())
    {
        QToolTip::showText(mapToGlobal(rect().bottomLeft()), result.m_message, this);
    }
}

void ValidatedLineEdit::SlotOnTextChanged(const QString& text)
{
    if (!m_autoValidationEnabled)
    {
        return;
    }

    ST_ValidationResult result = ValidateInput(text);
    UpdateVisualState(result);
    emit SigValidationStateChanged(result);
}

void ValidatedLineEdit::SlotOnEditingFinished()
{
    ST_ValidationResult result = ValidateCurrentInput();

    if (result.m_validationState == EM_ValidationState::EM_ValidationState_Valid)
    {
        emit SigInputAccepted(text());
    }
    else
    {
        emit SigInputRejected(text(), result.m_message);
    }
}
