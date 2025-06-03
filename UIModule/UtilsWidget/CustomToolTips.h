#pragma once

#include <QTimer>
#include <QToolTip>
#include <QWidget>
#include "UIWidgetGlobal.h"
#include "ui_CustomToolTips.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CustomToolTipsClass; };
QT_END_NAMESPACE

class CustomUIGlobal_API CustomToolTips : public QWidget
{
    Q_OBJECT

public:
    CustomToolTips(QWidget* parent = Q_NULLPTR);
    ~CustomToolTips() override;

    void SetToolTips(const QString& str);
    void SetToolTipsEx(const QString& str);
private:
    Ui::CustomToolTipsClass *ui;
};

