#include "CustomComboBox.h"
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

CustomComboBox::CustomComboBox(QWidget* parent)
    : QComboBox(parent)
    , m_ui(new Ui::CustomComboBoxClass())
    , m_fontColor(UIColorDefine::font_color::Primary)
    , m_fontSize(FontSize_Normal)
    , m_fontStyle(FontStyle_Normal)
    , m_backgroundType(BackgroundType_Transparent)
    , m_backgroundColor(UIColorDefine::background_color::Transparent)
    , m_itemFontColor(UIColorDefine::font_color::Primary)
    , m_itemBackgroundColor(UIColorDefine::background_color::White)
    , m_itemSpacing(2)
    , m_itemHeight(24)
    , m_searchEnabled(false)
    , m_searchBox(nullptr)
{
    InitializeComboBox();
}

CustomComboBox::~CustomComboBox()
{
    delete m_ui;
}

void CustomComboBox::InitializeComboBox()
{
    m_ui->setupUi(this);
    setView(new QListView());
    UpdateStyle();
}

void CustomComboBox::SetFontColor(const QColor& color)
{
    m_fontColor = color;
    UpdateStyle();
}

void CustomComboBox::SetFontSize(const EM_FontSize& fontSize)
{
    m_fontSize = fontSize;
    UpdateStyle();
}

void CustomComboBox::SetFontStyle(const EM_FontStyle& fontStyle)
{
    m_fontStyle = fontStyle;
    UpdateStyle();
}

void CustomComboBox::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    UpdateStyle();
}

void CustomComboBox::SetBackgroundType(const EM_BackgroundType& type)
{
    m_backgroundType = type;
    UpdateStyle();
}

void CustomComboBox::SetGradientBackground(const UIColorDefine::ST_GradientColor& gradientColor)
{
    m_gradientColor = gradientColor;
    UpdateStyle();
}

void CustomComboBox::SetItemSpacing(int spacing)
{
    m_itemSpacing = spacing;
    UpdateStyle();
}

void CustomComboBox::SetItemHeight(int height)
{
    m_itemHeight = height;
    UpdateStyle();
}

void CustomComboBox::SetItemFontColor(const QColor& color)
{
    m_itemFontColor = color;
    UpdateStyle();
}

void CustomComboBox::SetItemBackgroundColor(const QColor& color)
{
    m_itemBackgroundColor = color;
    UpdateStyle();
}

void CustomComboBox::SetEnableSearch(bool enable)
{
    if (m_searchEnabled != enable)
    {
        m_searchEnabled = enable;
        if (enable && !m_searchBox)
        {
            CreateSearchBox();
        }
        else if (!enable && m_searchBox)
        {
            delete m_searchBox;
            m_searchBox = nullptr;
        }
    }
}

void CustomComboBox::SetSearchPlaceholderText(const QString& text)
{
    if (m_searchBox)
    {
        m_searchBox->setPlaceholderText(text);
    }
}

void CustomComboBox::showPopup()
{
    if (m_searchEnabled)
    {
        if (!m_originalItems.isEmpty())
        {
            clear();
            addItems(m_originalItems);
        }
        else
        {
            m_originalItems.clear();
            for (int i = 0; i < count(); ++i)
            {
                m_originalItems << itemText(i);
            }
        }
        if (m_searchBox)
        {
            m_searchBox->clear();
            m_searchBox->setFocus();
        }
    }
    QComboBox::showPopup();
}

void CustomComboBox::hidePopup()
{
    if (m_searchEnabled && m_searchBox)
    {
        m_searchBox->clear();
    }
    QComboBox::hidePopup();
}

void CustomComboBox::OnSearchTextChanged(const QString& text)
{
    if (!m_searchEnabled || text.isEmpty())
    {
        clear();
        addItems(m_originalItems);
        return;
    }

    clear();
    for (const QString& item : m_originalItems)
    {
        if (item.contains(text, Qt::CaseInsensitive))
        {
            addItem(HighlightSearchText(item, text));
        }
    }
}

void CustomComboBox::OnStyleChanged()
{
    UpdateStyle();
}

void CustomComboBox::CreateSearchBox()
{
    if (!m_searchBox)
    {
        m_searchBox = new QLineEdit(this);
        m_searchBox->setPlaceholderText(tr("搜索..."));
        connect(m_searchBox, &QLineEdit::textChanged,
                this, &CustomComboBox::OnSearchTextChanged);
    }
}

QString CustomComboBox::HighlightSearchText(const QString& text, const QString& searchText)
{
    QString result = text;
    int index = result.indexOf(searchText, 0, Qt::CaseInsensitive);
    if (index >= 0)
    {
        result.insert(index + searchText.length(), "</span>");
        result.insert(index, "<span style='color: #0078D4;'>");
    }
    return result;
}

void CustomComboBox::UpdateStyle()
{
    QString style = "QComboBox { ";

    // 字体样式
    style += QString("color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_fontColor));
    style += QString("font-size: %1px; ").arg(m_fontSize);

    switch (m_fontStyle)
    {
        case FontStyle_Bold:
            style += "font-weight: bold; ";
            break;
        case FontStyle_Italic:
            style += "font-style: italic; ";
            break;
        case FontStyle_Underline:
            style += "text-decoration: underline; ";
            break;
        default:
            break;
    }

    // 背景样式
    switch (m_backgroundType)
    {
        case BackgroundType_Transparent:
            style += "background: transparent; ";
            break;
        case BackgroundType_Solid:
            style += QString("background: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor));
            break;
        case BackgroundType_Gradient:
            style += QString("background: %1; ").arg(UIColorDefine::color_convert::ToGradientString(m_gradientStartColor, m_gradientEndColor));
            break;
    }

    style += "} ";

    // 下拉列表样式
    style += "QComboBox QAbstractItemView { ";
    style += QString("color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_itemFontColor));
    style += QString("background: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_itemBackgroundColor));
    style += QString("spacing: %1px; ").arg(m_itemSpacing);
    style += "} ";

    // 下拉列表项样式
    style += "QComboBox::item { ";
    style += QString("height: %1px; ").arg(m_itemHeight);
    style += "} ";

    setStyleSheet(style);
}

QColor CustomComboBox::fontColor() const
{
    return m_fontColor;
}

QColor CustomComboBox::backgroundColor() const
{
    return m_backgroundColor;
}

QColor CustomComboBox::itemFontColor() const
{
    return m_itemFontColor;
}

QColor CustomComboBox::itemBackgroundColor() const
{
    return m_itemBackgroundColor;
}

CustomComboBox::EM_FontSize CustomComboBox::fontSize() const
{
    return m_fontSize;
}

CustomComboBox::EM_FontStyle CustomComboBox::fontStyle() const
{
    return m_fontStyle;
}

CustomComboBox::EM_BackgroundType CustomComboBox::backgroundType() const
{
    return m_backgroundType;
}

QColor CustomComboBox::gradientStartColor() const
{
    return m_gradientStartColor;
}

QColor CustomComboBox::gradientEndColor() const
{
    return m_gradientEndColor;
}

int CustomComboBox::itemSpacing() const
{
    return m_itemSpacing;
}

int CustomComboBox::itemHeight() const
{
    return m_itemHeight;
}

bool CustomComboBox::isSearchEnabled() const
{
    return m_searchEnabled;
}

QString CustomComboBox::searchPlaceholderText() const
{
    return m_searchPlaceholderText;
}
