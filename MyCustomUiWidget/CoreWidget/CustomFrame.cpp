#include "CustomFrame.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QStyleOption>
#include "SkinStyleLoader.h"

CustomFrame::CustomFrame(QWidget* parent)
    : QFrame(parent)
{
    AUTO_LOAD_SKIN_STYLE();
}

CustomFrame::~CustomFrame()
{
}

