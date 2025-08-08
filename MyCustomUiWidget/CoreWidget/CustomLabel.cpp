#include "CustomLabel.h"
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QVariant>
#include "StyleSystem/SkinStyleLoader.h"

CustomLabel::CustomLabel(QWidget* parent)
    : QLabel(parent), m_labelFormat(EM_CustomLabelFormat::EM_Normal)
{
    AUTO_LOAD_SKIN_STYLE();
    Initilize();
    Connectionals();
}

CustomLabel::CustomLabel(const QString& text, QWidget* parent)
    : CustomLabel(parent)
{
    setText(text);
}

CustomLabel::~CustomLabel()
{
}

CustomLabel::EM_CustomLabelFormat CustomLabel::GetLabelFormat() const
{
    return m_labelFormat;
}

void CustomLabel::SetLabelFormat(EM_CustomLabelFormat format)
{
    if (m_labelFormat != format)
    {
        m_labelFormat = format;
        ApplyFormatStyle();
    }
}

void CustomLabel::Connectionals()
{
}

void CustomLabel::Initilize()
{
}

void CustomLabel::ApplyFormatStyle()
{
    QString str;
    // 根据格式设置对应的样式类
    switch (m_labelFormat)
    {
    case EM_CustomLabelFormat::EM_Normal:
        str = "EM_Normal";
        break;
    case EM_CustomLabelFormat::EM_Title:
        str = "EM_Title";
        break;
    case EM_CustomLabelFormat::EM_SubTitle:
        str = "EM_SubTitle";
        break;
    case EM_CustomLabelFormat::EM_Description:
        str = "EM_Description";
        break;
    case EM_CustomLabelFormat::EM_Warning:
        str = "EM_Warning";
        break;
    case EM_CustomLabelFormat::EM_Error:
        str = "EM_Error";
        break;
    case EM_CustomLabelFormat::EM_Success:
        str = "EM_Success";
        break;
    case EM_CustomLabelFormat::EM_Info:
        str = "EM_Info";
        break;
    }
    SetStyleFormatStr(str);
    //// 重新应用样式
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}
