#pragma once

#include <QWidget>
#include "ui_TestWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TestWidgetClass; };
QT_END_NAMESPACE

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    TestWidget(QWidget *parent = nullptr);
    ~TestWidget();

private:
    Ui::TestWidgetClass *ui;
    QWidget* m_item = nullptr;
};

