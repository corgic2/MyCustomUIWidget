#pragma once

#include <QString>
#include <QRegularExpression>

/// <summary>
/// 正则表达式定义类，提供常用的正则表达式模式
/// </summary>
class RegexDefine
{
public:
    /// <summary>
    /// 邮箱正则表达式
    /// </summary>
    static const QString EMAIL_PATTERN;

    /// <summary>
    /// 手机号正则表达式（中国大陆）
    /// </summary>
    static const QString PHONE_PATTERN;

    /// <summary>
    /// IPv4地址正则表达式
    /// </summary>
    static const QString IPV4_PATTERN;

    /// <summary>
    /// 数字正则表达式
    /// </summary>
    static const QString NUMBER_PATTERN;

    /// <summary>
    /// 字母正则表达式
    /// </summary>
    static const QString LETTER_PATTERN;

    /// <summary>
    /// 字母和数字组合正则表达式
    /// </summary>
    static const QString ALPHANUMERIC_PATTERN;

    /// <summary>
    /// URL正则表达式
    /// </summary>
    static const QString URL_PATTERN;

    /// <summary>
    /// 日期正则表达式 (YYYY-MM-DD)
    /// </summary>
    static const QString DATE_PATTERN;

    /// <summary>
    /// 时间正则表达式 (HH:mm:ss)
    /// </summary>
    static const QString TIME_PATTERN;

    /// <summary>
    /// 密码正则表达式（至少8位，包含大小写字母和数字）
    /// </summary>
    static const QString PASSWORD_PATTERN;
}; 