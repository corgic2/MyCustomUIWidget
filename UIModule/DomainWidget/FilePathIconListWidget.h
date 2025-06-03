#pragma once
#include <QWidget>
#include "UIWidgetGlobal.h"
#include "ui_FilePathIconListWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FilePathIconListWidgetClass; };
QT_END_NAMESPACE

class CustomUIGlobal_API FilePathIconListWidget : public QWidget
{
    Q_OBJECT

public:
    FilePathIconListWidget(QWidget *parent = nullptr);
    ~FilePathIconListWidget();

private:
    Ui::FilePathIconListWidgetClass *ui;
};

