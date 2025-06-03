#include "TestWidget.h"
#include "DomainWidget/FilePathIconListWidgetItem.h"
TestWidget::TestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWidgetClass())
{
    ui->setupUi(this);
    m_item = new FilePathIconListWidgetItem;
    ui->verticalLayout_2->addWidget(m_item);
    FilePathIconListWidgetItem::ST_NodeInfo info;
    info.filePath = "FilePAth : ";
    info.content = "1234567";
    info.iconFilePath = "IconFilePAth: ";
    info.toolTipsContent = "ToolTipsContent: ";
    info.toolTipsContentEx = "ToolTipsContentEx: ";
    auto item = dynamic_cast<FilePathIconListWidgetItem*>(m_item);
    item->SetItemNodeText(info);
    setFixedSize(item->size());
}

TestWidget::~TestWidget()
{
    SAFE_DELETE_POINTER_VALUE(ui);
    SAFE_DELETE_POINTER_VALUE(m_item);
}

