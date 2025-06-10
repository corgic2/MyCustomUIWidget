#include "TestWidget.h"
#include <QPushButton>
#include <QVBoxLayout>

TestWidget::TestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidgetClass())
    , m_testLabel(nullptr)
    , m_testComboBox(nullptr)
    , m_testTips(nullptr)
{
    ui->setupUi(this);
    InitializeTestCases();
    CreateTestButtons();
    CreateTestLayout();
    SetupConnections();
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::InitializeTestCases()
{
    // 创建测试控件
    m_testLabel = new CustomLabel(this);
    m_testComboBox = new CustomComboBox(this);
    m_testTips = new CustomToolTips(this);

    // 初始化CustomLabel
    m_testLabel->setMinimumSize(200, 30);
    m_testLabel->SetText("Test Label");
    ui->displayLayout->addWidget(m_testLabel);

    // 初始化CustomComboBox
    m_testComboBox->setMinimumSize(200, 30);
    for(int i = 1; i <= 10; i++) {
        m_testComboBox->addItem(QString("Item %1").arg(i));
    }
    ui->displayLayout->addWidget(m_testComboBox);

    // 初始化CustomToolTips
    m_testTips->SetToolTips("Test Tips");
    m_testTips->SetToolTipsEx("Extended Tips Information");
    m_testTips->hide();
}

void TestWidget::CreateTestButtons()
{
    // CustomLabel测试按钮
    m_labelTestButtons = {
        new QPushButton("Test Font Styles", this),
        new QPushButton("Test Background Types", this),
        new QPushButton("Test Shadow & Border", this),
        new QPushButton("Test Text Elide", this),
        new QPushButton("Test Image Display", this)
    };

    // CustomComboBox测试按钮
    m_comboBoxTestButtons = {
        new QPushButton("Test Styles", this),
        new QPushButton("Test Items", this)
    };

    // CustomToolTips测试按钮
    m_tipsTestButtons = {
        new QPushButton("Test Types", this),
        new QPushButton("Test Animation", this),
        new QPushButton("Test Styles", this)
    };
}

void TestWidget::CreateTestLayout()
{
    // 添加CustomLabel测试按钮
    for(auto btn : m_labelTestButtons) {
        ui->labelTestLayout->addWidget(btn);
    }

    // 添加CustomComboBox测试按钮
    for(auto btn : m_comboBoxTestButtons) {
        ui->comboBoxTestLayout->addWidget(btn);
    }

    // 添加CustomToolTips测试按钮
    for(auto btn : m_tipsTestButtons) {
        ui->tipsTestLayout->addWidget(btn);
    }
}

void TestWidget::SetupConnections()
{
    // CustomLabel测试连接
    connect(m_labelTestButtons[0], &QPushButton::clicked, this, &TestWidget::OnTestLabelFontStyle);
    connect(m_labelTestButtons[1], &QPushButton::clicked, this, &TestWidget::OnTestLabelBackgroundType);
    connect(m_labelTestButtons[2], &QPushButton::clicked, this, &TestWidget::OnTestLabelShadowAndBorder);
    connect(m_labelTestButtons[3], &QPushButton::clicked, this, &TestWidget::OnTestLabelElide);
    connect(m_labelTestButtons[4], &QPushButton::clicked, this, &TestWidget::OnTestLabelImage);

    // CustomComboBox测试连接
    connect(m_comboBoxTestButtons[0], &QPushButton::clicked, this, &TestWidget::OnTestComboBoxStyle);
    connect(m_comboBoxTestButtons[1], &QPushButton::clicked, this, &TestWidget::OnTestComboBoxItems);

    // CustomToolTips测试连接
    connect(m_tipsTestButtons[0], &QPushButton::clicked, this, &TestWidget::OnTestToolTipsTypes);
    connect(m_tipsTestButtons[1], &QPushButton::clicked, this, &TestWidget::OnTestToolTipsAnimation);
    connect(m_tipsTestButtons[2], &QPushButton::clicked, this, &TestWidget::OnTestToolTipsStyle);
}

// CustomLabel测试用例实现
void TestWidget::OnTestLabelFontStyle()
{
    static int currentStyle = 0;
    switch(currentStyle % 4) {
        case 0:
            m_testLabel->SetFontStyle(CustomLabel::FontStyle_Normal);
            m_testLabel->SetFontSize(CustomLabel::FontSize_Normal);
            break;
        case 1:
            m_testLabel->SetFontStyle(CustomLabel::FontStyle_Bold);
            m_testLabel->SetFontSize(CustomLabel::FontSize_Large);
            break;
        case 2:
            m_testLabel->SetFontStyle(CustomLabel::FontStyle_Italic);
            m_testLabel->SetFontSize(CustomLabel::FontSize_Medium);
            break;
        case 3:
            m_testLabel->SetFontStyle(CustomLabel::FontStyle_Underline);
            m_testLabel->SetFontSize(CustomLabel::FontSize_ExtraLarge);
            break;
    }
    currentStyle++;
}

void TestWidget::OnTestLabelBackgroundType()
{
    static int currentType = 0;
    switch(currentType % 3) {
        case 0:
            m_testLabel->SetBackgroundType(CustomLabel::BackgroundType_Transparent);
            break;
        case 1:
            m_testLabel->SetBackgroundType(CustomLabel::BackgroundType_Solid);
            m_testLabel->SetBackgroundColor(QColor(200, 200, 255));
            break;
        case 2:
            m_testLabel->SetBackgroundType(CustomLabel::BackgroundType_Gradient);
            m_testLabel->SetGradientBackground(QColor(255, 200, 200), QColor(200, 255, 200));
            break;
    }
    currentType++;
}

void TestWidget::OnTestLabelShadowAndBorder()
{
    static bool hasShadow = false;
    static bool hasBorder = false;

    hasShadow = !hasShadow;
    hasBorder = !hasBorder;

    m_testLabel->EnableShadow(hasShadow);
    m_testLabel->EnableBorder(hasBorder);
}

void TestWidget::OnTestLabelElide()
{
    static bool isElided = false;
    isElided = !isElided;

    m_testLabel->SetEnableElide(isElided);
    if(isElided) {
        m_testLabel->SetText("This is a very long text that should be elided when it exceeds the width of the label");
    } else {
        m_testLabel->SetText("Normal Text");
    }
}

void TestWidget::OnTestLabelImage()
{
    static bool showImage = false;
    showImage = !showImage;

    if(showImage) {
        // 这里需要替换为实际的图片路径
        m_testLabel->SetImage(":/icons/test.png", CustomLabel::ScaleToFit);
    } else {
        m_testLabel->SetText("Test Label");
    }
}

// CustomComboBox测试用例实现
void TestWidget::OnTestComboBoxStyle()
{
    static int currentStyle = 0;
    switch(currentStyle % 3) {
        case 0:
            m_testComboBox->SetFontStyle(CustomComboBox::FontStyle_Normal);
            m_testComboBox->SetBackgroundType(CustomComboBox::BackgroundType_Transparent);
            break;
        case 1:
            m_testComboBox->SetFontStyle(CustomComboBox::FontStyle_Bold);
            m_testComboBox->SetBackgroundType(CustomComboBox::BackgroundType_Solid);
            m_testComboBox->SetBackgroundColor(QColor(200, 200, 255));
            break;
        case 2:
            m_testComboBox->SetFontStyle(CustomComboBox::FontStyle_Italic);
            m_testComboBox->SetBackgroundType(CustomComboBox::BackgroundType_Gradient);
            break;
    }
    currentStyle++;
}

void TestWidget::OnTestComboBoxItems()
{
    static int itemSet = 0;
    m_testComboBox->clear();

    switch(itemSet % 3) {
        case 0:
            for(int i = 1; i <= 5; i++) {
                m_testComboBox->addItem(QString("Short Item %1").arg(i));
            }
            break;
        case 1:
            for(int i = 1; i <= 10; i++) {
                m_testComboBox->addItem(QString("Medium Length Item %1").arg(i));
            }
            break;
        case 2:
            for(int i = 1; i <= 15; i++) {
                m_testComboBox->addItem(QString("Very Long Item Text That Should Be Handled Properly %1").arg(i));
            }
            break;
    }
    itemSet++;
}

// CustomToolTips测试用例实现
void TestWidget::OnTestToolTipsTypes()
{
    static int currentType = 0;
    switch(currentType % 5) {
        case 0:
            m_testTips->SetTipsType(CustomToolTips::Normal);
            m_testTips->SetToolTips("Normal Tip");
            m_testTips->SetToolTipsEx("This is a normal tip with default style");
            break;
        case 1:
            m_testTips->SetTipsType(CustomToolTips::Info);
            m_testTips->SetToolTips("Info Tip");
            m_testTips->SetToolTipsEx("This is an information tip");
            break;
        case 2:
            m_testTips->SetTipsType(CustomToolTips::Warning);
            m_testTips->SetToolTips("Warning Tip");
            m_testTips->SetToolTipsEx("This is a warning tip");
            break;
        case 3:
            m_testTips->SetTipsType(CustomToolTips::Error);
            m_testTips->SetToolTips("Error Tip");
            m_testTips->SetToolTipsEx("This is an error tip");
            break;
        case 4:
            m_testTips->SetTipsType(CustomToolTips::Success);
            m_testTips->SetToolTips("Success Tip");
            m_testTips->SetToolTipsEx("This is a success tip");
            break;
    }
    m_testTips->ShowTips(QCursor::pos());
    currentType++;
}

void TestWidget::OnTestToolTipsAnimation()
{
    static int currentAnimation = 0;
    switch (currentAnimation % 4)
    {
        case 0:
            m_testTips->SetToolTips("No Animation");
            m_testTips->SetToolTipsEx("Animation is disabled");
            break;
        case 1:
            m_testTips->SetAnimationDuration(500);
            m_testTips->SetToolTips("Fade Animation (Fast)");
            m_testTips->SetToolTipsEx("500ms duration");
            break;
        case 2:
            m_testTips->SetAnimationDuration(500);
            m_testTips->SetToolTips("Slide Animation (Fast)");
            m_testTips->SetToolTipsEx("500ms duration");
            break;
        case 3:
            m_testTips->SetAnimationDuration(1000);
            m_testTips->SetToolTips("Fade Animation (Slow)");
            m_testTips->SetToolTipsEx("1000ms duration");
            break;
    }
    m_testTips->ShowTips(QCursor::pos());
    currentAnimation++;
}

void TestWidget::OnTestToolTipsStyle()
{
    static int currentStyle = 0;
    switch(currentStyle % 3) {
        case 0:
            m_testTips->SetRadius(5);
            m_testTips->SetBackgroundColor(UIColorDefine::background_color::ToolTipsNormal);
            m_testTips->SetTextColor(UIColorDefine::font_color::Primary);
            m_testTips->SetToolTips("Basic Style");
            m_testTips->SetToolTipsEx("Small radius, normal colors");
            break;
        case 1:
            m_testTips->SetRadius(10);
            m_testTips->SetBackgroundColor(UIColorDefine::background_color::ToolTipsInfo);
            m_testTips->SetTextColor(UIColorDefine::font_color::Info);
            m_testTips->SetToolTips("Info Style");
            m_testTips->SetToolTipsEx("Medium radius, info colors");
            break;
        case 2:
            m_testTips->SetRadius(15);
            m_testTips->SetBackgroundColor(UIColorDefine::background_color::Success);
            m_testTips->SetTextColor(UIColorDefine::font_color::Success);
            m_testTips->SetToolTips("Success Style");
            m_testTips->SetToolTipsEx("Large radius, success colors");
            break;
    }
    m_testTips->ShowTips(QCursor::pos());
    currentStyle++;
}

