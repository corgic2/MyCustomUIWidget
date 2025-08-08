#include "CustomFrame.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QStackedLayout>
#include "StyleSystem/SkinStyleLoader.h"

CustomFrame::CustomFrame(QWidget* parent)
    : QFrame(parent), m_frameFormat(EM_CustomFrameFormat::EM_Normal), m_layoutManager(nullptr)
{
    AUTO_LOAD_SKIN_STYLE();
    Initilize();
    Connectionals();
    // 确保可以作为容器使用
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(false);
}

CustomFrame::~CustomFrame()
{
}

CustomFrame::EM_CustomFrameFormat CustomFrame::GetFrameFormat() const
{
    return m_frameFormat;
}

void CustomFrame::SetFrameFormat(EM_CustomFrameFormat format)
{
    if (m_frameFormat != format)
    {
        m_frameFormat = format;
        ApplyFormatStyle();
    }
}

void CustomFrame::Connectionals()
{
}

void CustomFrame::Initilize()
{
    // 确保CustomFrame可以作为容器使用
    this->setAcceptDrops(true);
    
    // 创建布局管理器
    m_layoutManager = new CustomFrameLayoutManager(this);
    
    // 设置默认布局为垂直布局
    if (!this->layout()) {
        m_layoutManager->SetLayoutType(CustomFrameLayoutManager::EM_Vertical);
    }
}

void CustomFrame::SetVerticalLayout()
{
    if (m_layoutManager) {
        m_layoutManager->SetLayoutType(CustomFrameLayoutManager::EM_Vertical);
    }
}

void CustomFrame::SetHorizontalLayout()
{
    if (m_layoutManager) {
        m_layoutManager->SetLayoutType(CustomFrameLayoutManager::EM_Horizontal);
    }
}

void CustomFrame::SetGridLayout()
{
    if (m_layoutManager) {
        m_layoutManager->SetLayoutType(CustomFrameLayoutManager::EM_Grid);
    }
}

void CustomFrame::SetFormLayout()
{
    if (m_layoutManager) {
        m_layoutManager->SetLayoutType(CustomFrameLayoutManager::EM_Form);
    }
}

void CustomFrame::SetStackedLayout()
{
    if (m_layoutManager) {
        m_layoutManager->SetLayoutType(CustomFrameLayoutManager::EM_Stacked);
    }
}

QString CustomFrame::GetLayoutType() const
{
    if (m_layoutManager) {
        return CustomFrameLayoutManager::LayoutTypeToString(m_layoutManager->GetLayoutType());
    }
    return "None";
}

QString CustomFrame::GetLayoutTypeString() const
{
    return GetLayoutType();
}

void CustomFrame::SetLayoutTypeString(const QString& type)
{
    if (m_layoutManager) {
        CustomFrameLayoutManager::EM_LayoutType layoutType = 
            CustomFrameLayoutManager::StringToLayoutType(type);
        m_layoutManager->SetLayoutType(layoutType);
    }
}

void CustomFrame::ApplyFormatStyle()
{
    QString str;
    // 根据格式设置对应的样式类
    switch (m_frameFormat)
    {
        case EM_CustomFrameFormat::EM_Normal:
            str = "EM_Normal";
            break;
        case EM_CustomFrameFormat::EM_Card:
            str = "EM_Card";
            break;
        case EM_CustomFrameFormat::EM_Panel:
            str = "EM_Panel";
            break;
        case EM_CustomFrameFormat::EM_Shadow:
            str = "EM_Shadow";
            break;
        case EM_CustomFrameFormat::EM_Raised:
            str = "EM_Raised";
            break;
        case EM_CustomFrameFormat::EM_Sunken:
            str = "EM_Sunken";
            break;
        case EM_CustomFrameFormat::EM_Line:
            str = "EM_Line";
            break;
        case EM_CustomFrameFormat::EM_None:
            str = "EM_None";
            break;
    }
    SetStyleFormatStr(str);
    //// 重新应用样式
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}
