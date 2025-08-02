#include "FilePicker.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDir>

FilePicker::FilePicker(QWidget* parent)
    : QWidget(parent)
    , m_lineEdit(nullptr)
    , m_browseButton(nullptr)
    , m_isSaveDialog(false)
{
    Initialize();
}

FilePicker::~FilePicker()
{
}

void FilePicker::Initialize()
{
    // 创建控件
    m_lineEdit = new QLineEdit(this);
    m_browseButton = new QToolButton(this);

    // 设置默认值
    m_buttonText = tr("浏览...");
    m_dialogTitle = tr("选择文件");
    m_filter = tr("所有文件 (*.*)");
    m_placeholderText = tr("请选择文件...");
    m_startPath = QDir::currentPath();

    // 设置控件属性
    m_browseButton->setText(m_buttonText);
    m_lineEdit->setPlaceholderText(m_placeholderText);

    // 连接信号槽
    connect(m_browseButton, &QToolButton::clicked, this, &FilePicker::OnBrowseButtonClicked);
    connect(m_lineEdit, &QLineEdit::textChanged, this, &FilePicker::OnLineEditTextChanged);

    UpdateLayout();
}

void FilePicker::UpdateLayout()
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(3);
    layout->addWidget(m_lineEdit);
    layout->addWidget(m_browseButton);
}

void FilePicker::SetFilePath(const QString& path)
{
    if (m_filePath != path)
    {
        m_filePath = path;
        m_lineEdit->setText(path);
        emit SigFilePathChanged(path);
    }
}

void FilePicker::SetFilter(const QString& filter)
{
    m_filter = filter;
}

void FilePicker::SetDialogTitle(const QString& title)
{
    m_dialogTitle = title;
}

void FilePicker::SetIsSaveDialog(bool isSave)
{
    m_isSaveDialog = isSave;
}

void FilePicker::SetDefaultSuffix(const QString& suffix)
{
    m_defaultSuffix = suffix;
}

void FilePicker::SetPlaceholderText(const QString& text)
{
    m_placeholderText = text;
    m_lineEdit->setPlaceholderText(text);
}

void FilePicker::SetButtonText(const QString& text)
{
    m_buttonText = text;
    m_browseButton->setText(text);
}

void FilePicker::SetStartPath(const QString& path)
{
    m_startPath = path;
}

void FilePicker::OnBrowseButtonClicked()
{
    QString filePath;
    
    if (m_isSaveDialog)
    {
        filePath = QFileDialog::getSaveFileName(
            this,
            m_dialogTitle,
            m_startPath,
            m_filter
        );
    }
    else
    {
        filePath = QFileDialog::getOpenFileName(
            this,
            m_dialogTitle,
            m_startPath,
            m_filter
        );
    }

    if (!filePath.isEmpty())
    {
        SetFilePath(filePath);
    }
}

void FilePicker::OnLineEditTextChanged(const QString& text)
{
    if (m_filePath != text)
    {
        m_filePath = text;
        emit SigFilePathChanged(text);
    }
} 