#include "CustomLabel.h"
#include <QGraphicsDropShadowEffect>
#include "StyleSystem/SkinStyleLoader.h"

CustomLabel::CustomLabel(QWidget* parent)
    : QLabel(parent)
{
    AUTO_LOAD_SKIN_STYLE();
}
CustomLabel::CustomLabel(const QString& text, QWidget* parent)
    : QLabel(text, parent)
{
    AUTO_LOAD_SKIN_STYLE();
}
CustomLabel::~CustomLabel()
{
}
