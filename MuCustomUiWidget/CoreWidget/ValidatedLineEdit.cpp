#include "ValidatedLineEdit.h"
#include <QFocusEvent>
#include <QToolTip>

ValidatedLineEdit::ValidatedLineEdit(QWidget* parent)
    : QLineEdit(parent)
    , m_isValid(true)
    , m_showErrorMessage(true)
    , m_validationType(Custom)
{
    Initialize();
}

ValidatedLineEdit::~ValidatedLineEdit()
{
}

void ValidatedLineEdit::Initialize()
{
    // 初始化默认值
    m_errorBorderColor = UIColorDefine::border_color::Error;
    m_normalBorderColor = UIColorDefine::border_color::Default;
    m_errorMessage = "输入格式不正确";

    // 连接信号槽
    connect(this, &QLineEdit::textChanged, this, &ValidatedLineEdit::OnTextChanged);

    // 设置初始样式
    UpdateStyle();
}

void ValidatedLineEdit::SetValidationType(ValidationType type)
{
    m_validationType = type;
    switch (type)
    {
        case Email:
            m_pattern = RegexDefine::EMAIL_PATTERN;
            m_errorMessage = "请输入正确的邮箱地址";
            break;
        case Phone:
            m_pattern = RegexDefine::PHONE_PATTERN;
            m_errorMessage = "请输入正确的手机号码";
            break;
        case IPV4:
            m_pattern = RegexDefine::IPV4_PATTERN;
            m_errorMessage = "请输入正确的IPv4地址";
            break;
        case Number:
            m_pattern = RegexDefine::NUMBER_PATTERN;
            m_errorMessage = "请输入数字";
            break;
        case Letter:
            m_pattern = RegexDefine::LETTER_PATTERN;
            m_errorMessage = "请输入字母";
            break;
        case AlphaNum:
            m_pattern = RegexDefine::ALPHANUMERIC_PATTERN;
            m_errorMessage = "请输入字母或数字";
            break;
        case URL:
            m_pattern = RegexDefine::URL_PATTERN;
            m_errorMessage = "请输入正确的URL地址";
            break;
        case Date:
            m_pattern = RegexDefine::DATE_PATTERN;
            m_errorMessage = "请输入正确的日期格式(YYYY-MM-DD)";
            break;
        case Time:
            m_pattern = RegexDefine::TIME_PATTERN;
            m_errorMessage = "请输入正确的时间格式(HH:mm:ss)";
            break;
        case Password:
            m_pattern = RegexDefine::PASSWORD_PATTERN;
            m_errorMessage = "密码必须包含大小写字母和数字，且长度不少于8位";
            break;
        default:
            break;
    }
    ValidateInput();
}

void ValidatedLineEdit::SetPattern(const QString& pattern)
{
    m_pattern = pattern;
    m_validationType = Custom;
    ValidateInput();
}

void ValidatedLineEdit::SetErrorMessage(const QString& message)
{
    m_errorMessage = message;
}

void ValidatedLineEdit::SetShowErrorMessage(bool show)
{
    m_showErrorMessage = show;
}

void ValidatedLineEdit::SetErrorBorderColor(const QColor& color)
{
    m_errorBorderColor = color;
    UpdateStyle();
}

void ValidatedLineEdit::SetNormalBorderColor(const QColor& color)
{
    m_normalBorderColor = color;
    UpdateStyle();
}

void ValidatedLineEdit::OnTextChanged(const QString& text)
{
    ValidateInput();
}

void ValidatedLineEdit::focusOutEvent(QFocusEvent* event)
{
    QLineEdit::focusOutEvent(event);
    if (!m_isValid && m_showErrorMessage)
    {
        QToolTip::hideText();
    }
}

void ValidatedLineEdit::focusInEvent(QFocusEvent* event)
{
    QLineEdit::focusInEvent(event);
    if (!m_isValid && m_showErrorMessage)
    {
        QPoint pos = mapToGlobal(QPoint(0, height()));
        QToolTip::showText(pos, m_errorMessage);
    }
}

void ValidatedLineEdit::ValidateInput()
{
    if (text().isEmpty() || m_pattern.isEmpty())
    {
        m_isValid = true;
        UpdateStyle();
        return;
    }

    QRegularExpression regex(m_pattern);
    QRegularExpressionMatch match = regex.match(text());
    m_isValid = match.hasMatch();
    UpdateStyle();

    if (!m_isValid && m_showErrorMessage && hasFocus())
    {
        QPoint pos = mapToGlobal(QPoint(0, height()));
        QToolTip::showText(pos, m_errorMessage);
    }
}

void ValidatedLineEdit::UpdateStyle()
{
    QString styleSheet = QString(
        "QLineEdit {"
        "    border: 1px solid %1;"
        "    border-radius: 3px;"
        "    padding: 2px 4px;"
        "}"
    ).arg(UIColorDefine::color_convert::ToCssString(m_isValid ? m_normalBorderColor : m_errorBorderColor));

    setStyleSheet(styleSheet);
} 