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
}

TestWidget::~TestWidget()
{
    delete ui;
}
