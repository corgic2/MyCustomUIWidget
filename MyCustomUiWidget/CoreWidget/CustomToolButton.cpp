#include "CustomToolButton.h"
#include <QEvent>
#include <QPainter>
#include <QPen>
#include "StyleSystem/SkinStyleLoader.h"
#include "SDKCommonDefine/SDKCommonDefine.h"

CustomToolButton::CustomToolButton(QWidget* parent)
    : QToolButton(parent)
{
    AUTO_LOAD_SKIN_STYLE();
}

CustomToolButton::CustomToolButton(const QString& text, QWidget* parent) : CustomToolButton(parent)
{
    setText(text);
}

CustomToolButton::~CustomToolButton()
{
}

