#include "TestWidget.h"
#include <qDebug>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardPaths>
#include "SkinStyleLoader.h"

TestWidget::TestWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::TestWidgetClass()), m_fileListWidget(nullptr)
{
    ui->setupUi(this);
    setupFileListTests();
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::setupFileListTests()
{
    // 创建文件列表控件
    m_fileListWidget = new FilePathIconListWidget(this);
    m_fileListWidget->setMinimumHeight(200);

    // 创建测试按钮
    auto addButton = new QPushButton("添加测试文件", this);
    auto clearButton = new QPushButton("清除所有", this);
    auto removeButton = new QPushButton("移除选中", this);
    auto saveButton = new QPushButton("保存到JSON", this);
    auto loadButton = new QPushButton("从JSON加载", this);
    auto moveTopButton = new QPushButton("移到顶部", this);

    // 连接信号
    connect(addButton, &QPushButton::clicked, this, &TestWidget::onAddTestFiles);
    connect(clearButton, &QPushButton::clicked, this, &TestWidget::onClearAllFiles);
    connect(removeButton, &QPushButton::clicked, this, &TestWidget::onRemoveSelectedFile);
    connect(saveButton, &QPushButton::clicked, this, &TestWidget::onSaveToJson);
    connect(loadButton, &QPushButton::clicked, this, &TestWidget::onLoadFromJson);
    connect(moveTopButton, &QPushButton::clicked, this, &TestWidget::onMoveToTop);
    //connect(m_fileListWidget, &FilePathIconListWidget::SigItemDoubleClicked, this, &TestWidget::onItemDoubleClicked);
    //connect(m_fileListWidget, &FilePathIconListWidget::SigItemSelected, this, &TestWidget::onItemSelected);

    // 创建按钮布局
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(moveTopButton);

    // 创建主布局
    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(m_fileListWidget);

    // 添加到测试组
    auto testLayout = qobject_cast<QVBoxLayout*>(ui->fileListTestGroup->layout());
    if (testLayout)
    {
        testLayout->addLayout(mainLayout);
    }

    // 设置JSON文件路径
    QString jsonPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/test_file_list.json";
    m_fileListWidget->SetJsonFilePath(jsonPath);

    // 启用自动保存（5秒）
    m_fileListWidget->SetAutoSaveInterval(5000);
    m_fileListWidget->EnableAutoSave(true);
}

void TestWidget::onAddTestFiles()
{
    createTestFiles();
}

void TestWidget::onClearAllFiles()
{
    m_fileListWidget->Clear();
    qDebug() << "所有文件已清除";
}

void TestWidget::onRemoveSelectedFile()
{
    FilePathIconListWidgetItem* currentItem = m_fileListWidget->GetCurrentItem();
    if (currentItem)
    {
        QString filePath = currentItem->GetFilePath();
        m_fileListWidget->RemoveItemByFilePath(filePath);
        qDebug() << "已移除文件:" << filePath;
    }
    else
    {
        QMessageBox::information(this, "提示", "请先选择要移除的文件");
    }
}

void TestWidget::onSaveToJson()
{
    if (m_fileListWidget->SaveFileListToJson())
    {
        QMessageBox::information(this, "成功", "文件列表已保存到JSON");
        qDebug() << "文件列表已保存到:" << m_fileListWidget->GetJsonFilePath();
    }
    else
    {
        QMessageBox::warning(this, "失败", "保存文件列表到JSON失败");
    }
}

void TestWidget::onLoadFromJson()
{
    if (m_fileListWidget->LoadFileListFromJson())
    {
        QMessageBox::information(this, "成功", "文件列表已从JSON加载");
        qDebug() << "已从JSON加载文件列表，共" << m_fileListWidget->GetItemCount() << "个文件";
    }
    else
    {
        QMessageBox::warning(this, "失败", "从JSON加载文件列表失败");
    }
}

void TestWidget::onMoveToTop()
{
    FilePathIconListWidgetItem* currentItem = m_fileListWidget->GetCurrentItem();
    if (currentItem)
    {
        m_fileListWidget->MoveItemToTop(currentItem);
        qDebug() << "已将文件移到顶部:" << currentItem->GetFilePath();
    }
    else
    {
        QMessageBox::information(this, "提示", "请先选择要移到顶部的文件");
    }
}

void TestWidget::onItemDoubleClicked(const QString& filePath)
{
    qDebug() << "文件被双击:" << filePath;
    QMessageBox::information(this, "文件双击", "您双击了文件:\n" + filePath);
}

void TestWidget::onItemSelected(const QString& filePath)
{
    qDebug() << "文件被选中:" << filePath;
}

void TestWidget::createTestFiles()
{
    // 创建一些测试文件路径
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QList<FilePathIconListWidgetItem::ST_NodeInfo> testFiles;

    // 测试文件1
    FilePathIconListWidgetItem::ST_NodeInfo file1;
    file1.filePath = desktopPath + "/test_document.txt";
    file1.displayName = "测试文档";
    file1.type = FilePathIconListWidgetItem::File;
    testFiles.append(file1);

    // 测试文件2
    FilePathIconListWidgetItem::ST_NodeInfo file2;
    file2.filePath = documentsPath + "/project_folder";
    file2.displayName = "项目文件夹";
    file2.type = FilePathIconListWidgetItem::Folder;
    testFiles.append(file2);

    // 测试文件3
    FilePathIconListWidgetItem::ST_NodeInfo file3;
    file3.filePath = desktopPath + "/image.jpg";
    file3.displayName = "示例图片";
    file3.type = FilePathIconListWidgetItem::File;
    testFiles.append(file3);

    // 测试文件4
    FilePathIconListWidgetItem::ST_NodeInfo file4;
    file4.filePath = documentsPath + "/video.mp4";
    file4.displayName = "示例视频";
    file4.type = FilePathIconListWidgetItem::File;
    testFiles.append(file4);

    // 添加测试文件到列表
    for (const auto& file : testFiles)
    {
        m_fileListWidget->AddFileItem(file);
    }

    qDebug() << "已添加" << testFiles.size() << "个测试文件";
}
