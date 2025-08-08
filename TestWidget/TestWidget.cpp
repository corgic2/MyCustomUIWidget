#include "TestWidget.h"
#include <qDebug>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTimer>
#include <QVBoxLayout>
#include "CoreWidget/CustomProgressBar.h"
#include "CoreWidget/CustomToolButton.h"
#include "StyleSystem/SkinStyleLoader.h"

TestWidget::TestWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::TestWidgetClass())
{
    ui->setupUi(this);
    m_label = new CustomLabel("Test Label", this);
    m_label->SetLabelFormat(CustomLabel::EM_Title);
    this->layout()->addWidget(m_label);
    m_button = new CustomToolButton(this);
    m_button->setText("Test");
    this->layout()->addWidget(m_button);
    connect(m_button, &CustomToolButton::clicked, this,&TestWidget::SlotClicked);
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::SlotClicked()
{
    if (btrue)
    {
        m_label->SetLabelFormat(CustomLabel::EM_Error);
    }
    else
    {
        m_label->SetLabelFormat(CustomLabel::EM_Info);
    }
    btrue = !btrue;
}