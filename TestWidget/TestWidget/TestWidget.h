#pragma once

#include <QPushButton>
#include <QWidget>
#include "ui_TestWidget.h"
#include "CoreWidget/CustomLabel.h"
#include "CoreWidget/CustomToolButton.h"

QT_BEGIN_NAMESPACE namespace Ui
{
    class TestWidgetClass;
};
QT_END_NAMESPACE

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(QWidget* parent = nullptr);
    ~TestWidget() override;
    void SlotClicked();

private:
    Ui::TestWidgetClass* ui;
    CustomLabel* m_label;
    CustomToolButton* m_button;
    bool btrue = false;
};
