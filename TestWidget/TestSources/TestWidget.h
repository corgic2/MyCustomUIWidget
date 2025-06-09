#pragma once

#include <QPushButton>
#include <QWidget>
#include "ui_TestWidget.h"
#include "CoreWidget/CustomLabel.h"
#include "CoreWidget/CustomComboBox.h"
#include "UtilsWidget/CustomToolTips.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TestWidgetClass; };
QT_END_NAMESPACE

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    TestWidget(QWidget *parent = nullptr);
    ~TestWidget();

private slots:
    // CustomLabel测试槽函数
    void OnTestLabelFontStyle();
    void OnTestLabelBackgroundType();
    void OnTestLabelShadowAndBorder();
    void OnTestLabelElide();
    void OnTestLabelImage();

    // CustomComboBox测试槽函数
    void OnTestComboBoxStyle();
    void OnTestComboBoxItems();

    // CustomToolTips测试槽函数
    void OnTestToolTipsTypes();
    void OnTestToolTipsAnimation();
    void OnTestToolTipsStyle();

private:
    void InitializeTestCases();
    void SetupConnections();
    void CreateTestButtons();
    void CreateTestLayout();

private:
    Ui::TestWidgetClass *ui;
    
    // 测试控件
    CustomLabel* m_testLabel;
    CustomComboBox* m_testComboBox;
    CustomToolTips* m_testTips;

    // 测试用的按钮组
    QList<QPushButton*> m_labelTestButtons;
    QList<QPushButton*> m_comboBoxTestButtons;
    QList<QPushButton*> m_tipsTestButtons;
};

