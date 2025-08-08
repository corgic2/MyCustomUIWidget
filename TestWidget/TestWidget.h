#pragma once

#include <QPushButton>
#include <QWidget>
#include "ui_TestWidget.h"

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
private:
    Ui::TestWidgetClass* ui;
};
