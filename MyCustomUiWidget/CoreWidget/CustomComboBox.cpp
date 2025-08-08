#include "CustomComboBox.h"
#include <QPainter>
#include <QStyleOption>
#include "StyleSystem/SkinStyleLoader.h"

CustomComboBox::CustomComboBox(QWidget* parent)
    : QComboBox(parent)
{
    AUTO_LOAD_SKIN_STYLE();
}

CustomComboBox::~CustomComboBox()
{
}

