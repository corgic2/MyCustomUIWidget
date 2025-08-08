#include "CustomToolBar.h"
#include <QPainter>
#include <QStyleOption>
#include <QResizeEvent>
#include "StyleSystem/SkinStyleLoader.h"

CustomToolBar::CustomToolBar(QWidget* parent)
    : QToolBar(parent)
{
    AUTO_LOAD_SKIN_STYLE();
}

CustomToolBar::~CustomToolBar()
{
}
