#include "CustomLabel.h"
#include <QGraphicsDropShadowEffect>
#include "SkinStyleLoader.h"

CustomLabel::CustomLabel(QWidget* parent)
    : QLabel(parent)
{
    AUTO_LOAD_SKIN_STYLE();
}

CustomLabel::~CustomLabel()
{
}
