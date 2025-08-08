#include "CustomComboBox.h"
#include <QPainter>
#include <QStyleOption>
#include "StyleSystem/SkinStyleLoader.h"

CustomComboBox::CustomComboBox(QWidget* parent)
    : QComboBox(parent), m_comboBoxFormat(EM_CustomComboBoxFormat::EM_Normal)
{
    AUTO_LOAD_SKIN_STYLE();
    Initilize();
    Connectionals();
}

CustomComboBox::~CustomComboBox()
{
}

CustomComboBox::EM_CustomComboBoxFormat CustomComboBox::GetComboBoxFormat() const
{
    return m_comboBoxFormat;
}

void CustomComboBox::SetComboBoxFormat(EM_CustomComboBoxFormat format)
{
    if (m_comboBoxFormat != format)
    {
        m_comboBoxFormat = format;
        ApplyFormatStyle();
    }
}

void CustomComboBox::Connectionals()
{
}

void CustomComboBox::Initilize()
{
}

void CustomComboBox::ApplyFormatStyle()
{
    QString str;
    // 根据格式设置对应的样式类
    switch (m_comboBoxFormat)
    {
        case EM_CustomComboBoxFormat::EM_Normal:
            str = "EM_Normal";
            break;
        case EM_CustomComboBoxFormat::EM_Primary:
            str = "EM_Primary";
            break;
        case EM_CustomComboBoxFormat::EM_Success:
            str = "EM_Success";
            break;
        case EM_CustomComboBoxFormat::EM_Warning:
            str = "EM_Warning";
            break;
        case EM_CustomComboBoxFormat::EM_Error:
            str = "EM_Error";
            break;
        case EM_CustomComboBoxFormat::EM_Info:
            str = "EM_Info";
            break;
        case EM_CustomComboBoxFormat::EM_Link:
            str = "EM_Link";
            break;
        case EM_CustomComboBoxFormat::EM_Disabled:
            str = "EM_Disabled";
            break;
    }
    SetStyleFormatStr(str);
    //// 重新应用样式
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}
