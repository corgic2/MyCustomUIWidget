#include "CustomToolTips.h"

CustomToolTips::CustomToolTips(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomToolTipsClass())
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

CustomToolTips::~CustomToolTips()
{
    SAFE_DELETE_POINTER_VALUE(ui);
}

void CustomToolTips::SetToolTips(const QString& str)
{
    ui->label->setText(str);
}

void CustomToolTips::SetToolTipsEx(const QString& str)
{
    ui->label_2->setText(str);
}

