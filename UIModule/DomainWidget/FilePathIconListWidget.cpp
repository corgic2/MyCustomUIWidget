#include "FilePathIconListWidget.h"

FilePathIconListWidget::FilePathIconListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FilePathIconListWidgetClass())
{
    ui->setupUi(this);
}

FilePathIconListWidget::~FilePathIconListWidget()
{
    delete ui;
}

