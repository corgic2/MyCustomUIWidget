#pragma once

#include <QPushButton>
#include <QWidget>
#include "ui_TestWidget.h"
#include "DomainWidget/FilePathIconListWidget.h"

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
    void onAddTestFiles();
    void onClearAllFiles();
    void onRemoveSelectedFile();
    void onSaveToJson();
    void onLoadFromJson();
    void onMoveToTop();
    void onItemDoubleClicked(const QString& filePath);
    void onItemSelected(const QString& filePath);

private:
    void setupFileListTests();
    void createTestFiles();

private:
    Ui::TestWidgetClass* ui;
    FilePathIconListWidget* m_fileListWidget;
};

