#pragma once

#include <QString>
#include <QRegularExpression>

/// <summary>
/// 验证状态枚举
/// </summary>
enum class EM_ValidationState
{
    EM_ValidationState_Invalid = 0,    // 无效
    EM_ValidationState_Valid,          // 有效
    EM_ValidationState_Empty,          // 空值
    EM_ValidationState_Partial         // 部分匹配
};

/// <summary>
/// 验证模式枚举
/// </summary>
enum class EM_ValidationMode
{
    EM_ValidationMode_ExactMatch = 0,    // 完全匹配
    EM_ValidationMode_Contains,            // 包含匹配
    EM_ValidationMode_StartWith,           // 起始匹配
    EM_ValidationMode_EndWith              // 结尾匹配
};

/// <summary>
/// 验证规则结构体
/// </summary>
struct ST_ValidationRule
{
    QString m_ruleName;                    // 规则名称
    QRegularExpression m_regularExpression; // 正则表达式
    EM_ValidationMode m_validationMode;    // 验证模式
    QString m_errorMessage;                // 错误提示信息
    QString m_successMessage;              // 成功提示信息
    bool m_isEnabled;                      // 是否启用
    
    ST_ValidationRule() : 
        m_validationMode(EM_ValidationMode::EM_ValidationMode_ExactMatch),
        m_isEnabled(true)
    {}
    
    ST_ValidationRule(const QString& name, const QString& pattern, 
                     EM_ValidationMode mode = EM_ValidationMode::EM_ValidationMode_ExactMatch,
                     const QString& errorMsg = QString(), const QString& successMsg = QString()) :
        m_ruleName(name),
        m_regularExpression(pattern),
        m_validationMode(mode),
        m_errorMessage(errorMsg),
        m_successMessage(successMsg),
        m_isEnabled(true)
    {}
};

/// <summary>
/// 验证结果结构体
/// </summary>
struct ST_ValidationResult
{
    EM_ValidationState m_validationState;  // 验证状态
    QString m_message;                     // 提示信息
    int m_matchPosition;                   // 匹配位置
    int m_matchLength;                     // 匹配长度
    
    ST_ValidationResult() : 
        m_validationState(EM_ValidationState::EM_ValidationState_Invalid),
        m_matchPosition(-1),
        m_matchLength(0)
    {}
    
    ST_ValidationResult(EM_ValidationState state, const QString& msg = QString(), 
                       int pos = -1, int len = 0) :
        m_validationState(state),
        m_message(msg),
        m_matchPosition(pos),
        m_matchLength(len)
    {}
};

/// <summary>
/// 输入范围限制结构体
/// </summary>
struct ST_InputRange
{
    int m_minLength;        // 最小长度
    int m_maxLength;        // 最大长度
    QString m_allowedChars; // 允许的字符集
    QString m_forbiddenChars; // 禁止的字符集
    
    ST_InputRange() : 
        m_minLength(0),
        m_maxLength(INT_MAX)
    {}
    
    ST_InputRange(int minLen, int maxLen, const QString& allowed = QString(), const QString& forbidden = QString()) :
        m_minLength(minLen),
        m_maxLength(maxLen),
        m_allowedChars(allowed),
        m_forbiddenChars(forbidden)
    {}
};