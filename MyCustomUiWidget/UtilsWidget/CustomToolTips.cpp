#include "CustomToolTips.h"
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>
#include <QScreen>

CustomToolTips::CustomToolTips(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::CustomToolTipsClass)
{
    m_ui->setupUi(this);
}

CustomToolTips::~CustomToolTips()
{
}
