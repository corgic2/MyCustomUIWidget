#include "FilePicker.h"
#include <QDir>
#include <QDirIterator>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMimeData>
#include <QTimer>
#include <QUrl>
#include <QVBoxLayout>
#include "SkinStyleLoader.h"

FilePicker::FilePicker(QWidget* parent)
    : QWidget(parent), m_pathEdit(nullptr), m_browseButton(nullptr), m_clearButton(nullptr), m_filterCombo(nullptr), m_progressBar(nullptr), m_statusLabel(nullptr), m_filePickerMode(EM_FilePickerMode::EM_FileMode), m_currentPath(""), m_defaultDirectory(""), m_dialogTitle("选择文件"), m_showClearButton(true), m_showFilterCombo(true), m_dragDropEnabled(true), m_isScanning(false), m_scanTimer(nullptr), m_dirIterator(nullptr), m_totalFiles(0), m_scannedFiles(0)
{
    AUTO_LOAD_SKIN_STYLE();
    InitUI();
    InitConnections();

    // 添加默认文件过滤器
    AddFileFilter(ST_FileFilter("所有文件", {"*"}));
    AddFileFilter(ST_FileFilter("图片文件", {"*.jpg", "*.jpeg", "*.png", "*.gif", "*.bmp"}));
    AddFileFilter(ST_FileFilter("文本文件", {"*.txt", "*.log", "*.md"}));
    AddFileFilter(ST_FileFilter("文档文件", {"*.doc", "*.docx", "*.pdf", "*.xls", "*.xlsx"}));

    UpdateFilterCombo();
    SetDefaultDirectory(QDir::homePath());
}

FilePicker::~FilePicker()
{
    if (m_scanTimer)
    {
        m_scanTimer->stop();
        delete m_scanTimer;
        m_scanTimer = nullptr;
    }

    if (m_dirIterator)
    {
        delete m_dirIterator;
        m_dirIterator = nullptr;
    }
}

EM_FilePickerMode FilePicker::GetFilePickerMode() const
{
    return m_filePickerMode;
}

void FilePicker::SetFilePickerMode(EM_FilePickerMode mode)
{
    if (m_filePickerMode != mode)
    {
        m_filePickerMode = mode;
        emit SigModeChanged(mode);

        // 更新UI显示
        if (m_filterCombo)
        {
            m_filterCombo->setVisible(m_showFilterCombo && (mode == EM_FilePickerMode::EM_FileMode || mode == EM_FilePickerMode::EM_MultiFileMode));
        }

        // 更新对话框标题
        switch (mode)
        {
            case EM_FilePickerMode::EM_FileMode:
                m_dialogTitle = "选择文件";
                break;
            case EM_FilePickerMode::EM_DirectoryMode:
                m_dialogTitle = "选择文件夹";
                break;
            case EM_FilePickerMode::EM_MultiFileMode:
                m_dialogTitle = "选择多个文件";
                break;
            case EM_FilePickerMode::EM_FileAndDirectoryMode:
                m_dialogTitle = "选择文件或文件夹";
                break;
        }
    }
}

QString FilePicker::GetCurrentPath() const
{
    return m_currentPath;
}

QStringList FilePicker::GetSelectedFiles() const
{
    return m_selectedFiles;
}

void FilePicker::SetCurrentPath(const QString& path)
{
    if (m_currentPath != path)
    {
        m_currentPath = path;
        if (m_pathEdit)
        {
            m_pathEdit->setText(path);
        }
        emit SigFilePathChanged(path);
    }
}

bool FilePicker::GetShowClearButton() const
{
    return m_showClearButton;
}

void FilePicker::SetShowClearButton(bool show)
{
    m_showClearButton = show;
    if (m_clearButton)
    {
        m_clearButton->setVisible(show && !m_currentPath.isEmpty());
    }
}

bool FilePicker::GetShowFilterCombo() const
{
    return m_showFilterCombo;
}

void FilePicker::SetShowFilterCombo(bool show)
{
    m_showFilterCombo = show;
    if (m_filterCombo)
    {
        m_filterCombo->setVisible(show && (m_filePickerMode == EM_FilePickerMode::EM_FileMode || m_filePickerMode == EM_FilePickerMode::EM_MultiFileMode));
    }
}

void FilePicker::AddFileFilter(const ST_FileFilter& filter)
{
    m_fileFilters.append(filter);
    UpdateFilterCombo();
}

void FilePicker::SetDefaultDirectory(const QString& dir)
{
    m_defaultDirectory = dir;
    if (m_defaultDirectory.isEmpty())
    {
        m_defaultDirectory = QDir::homePath();
    }
}

void FilePicker::SetDialogTitle(const QString& title)
{
    m_dialogTitle = title;
}

void FilePicker::SetDragDropEnabled(bool enabled)
{
    m_dragDropEnabled = enabled;
    setAcceptDrops(enabled);
}

void FilePicker::SlotClearSelection()
{
    SetCurrentPath("");
    m_selectedFiles.clear();
    emit SigFileListChanged(m_selectedFiles);

    if (m_clearButton)
    {
        m_clearButton->setVisible(false);
    }

    if (m_statusLabel)
    {
        m_statusLabel->clear();
    }
}

void FilePicker::SlotBrowseFiles()
{
    QStringList files;

    switch (m_filePickerMode)
    {
        case EM_FilePickerMode::EM_FileMode:
        {
            QString file = QFileDialog::getOpenFileName(this, m_dialogTitle, m_defaultDirectory, GetFileFilters());
            if (!file.isEmpty())
            {
                files.append(file);
            }
            break;
        }
        case EM_FilePickerMode::EM_DirectoryMode:
        {
            QString dir = QFileDialog::getExistingDirectory(this, m_dialogTitle, m_defaultDirectory, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
            if (!dir.isEmpty())
            {
                files.append(dir);
            }
            break;
        }
        case EM_FilePickerMode::EM_MultiFileMode:
        {
            files = QFileDialog::getOpenFileNames(this, m_dialogTitle, m_defaultDirectory, GetFileFilters());
            break;
        }
        case EM_FilePickerMode::EM_FileAndDirectoryMode:
        {
            QFileDialog dialog(this, m_dialogTitle, m_defaultDirectory);
            dialog.setFileMode(QFileDialog::AnyFile);
            dialog.setOption(QFileDialog::ReadOnly, true);

            if (dialog.exec() == QDialog::Accepted)
            {
                files = dialog.selectedFiles();
            }
            break;
        }
    }

    if (!files.isEmpty())
    {
        if (m_filePickerMode == EM_FilePickerMode::EM_DirectoryMode && files.size() == 1)
        {
            // 如果是文件夹模式，扫描文件夹
            ScanDirectory(files.first());
        }
        else
        {
            // 文件模式
            m_selectedFiles = files;
            if (!files.isEmpty())
            {
                SetCurrentPath(files.first());
                emit SigFileListChanged(m_selectedFiles);
            }
        }

        if (m_clearButton)
        {
            m_clearButton->setVisible(true);
        }
    }
}

void FilePicker::SlotFilterChanged(const QString& filter)
{
    emit SigFilterChanged(filter);
}

void FilePicker::SlotPathEditFinished()
{
    QString path = m_pathEdit->text().trimmed();
    if (ValidatePath(path))
    {
        SetCurrentPath(path);

        if (QFileInfo(path).isDir() && m_filePickerMode == EM_FilePickerMode::EM_DirectoryMode)
        {
            ScanDirectory(path);
        }
        else
        {
            m_selectedFiles.clear();
            m_selectedFiles.append(path);
            emit SigFileListChanged(m_selectedFiles);
        }
    }
}

void FilePicker::SlotScanProgress(int progress)
{
    if (m_progressBar)
    {
        m_progressBar->setValue(progress);
    }
}

void FilePicker::SlotScanProgressUpdate()
{
    if (!m_dirIterator || !m_isScanning)
    {
        return;
    }

    // 每次处理100个文件或直到完成
    int batchSize = 100;
    int processed = 0;

    while (m_dirIterator->hasNext() && processed < batchSize)
    {
        m_dirIterator->next();
        m_selectedFiles.append(m_dirIterator->filePath());
        m_scannedFiles++;
        processed++;
    }

    // 更新进度
    if (m_totalFiles > 0)
    {
        int progress = static_cast<int>((static_cast<double>(m_scannedFiles) / m_totalFiles) * 100);
        if (m_progressBar)
        {
            m_progressBar->setValue(qMin(progress, 100));
        }
    }

    // 检查是否完成
    if (!m_dirIterator->hasNext())
    {
        SlotScanFinished();
    }
}

void FilePicker::SlotScanFinished()
{
    m_isScanning = false;

    if (m_scanTimer)
    {
        m_scanTimer->stop();
    }

    if (m_dirIterator)
    {
        delete m_dirIterator;
        m_dirIterator = nullptr;
    }

    if (m_progressBar)
    {
        m_progressBar->setVisible(false);
    }

    if (m_statusLabel)
    {
        m_statusLabel->setText(QString("已选择 %1 个文件").arg(m_selectedFiles.size()));
    }

    emit SigFileListChanged(m_selectedFiles);
}

void FilePicker::InitUI()
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(4, 4, 4, 4);
    mainLayout->setSpacing(4);

    // 路径编辑框
    m_pathEdit = new QLineEdit(this);
    m_pathEdit->setPlaceholderText("选择文件或文件夹...");
    m_pathEdit->setDragEnabled(true);

    // 浏览按钮
    m_browseButton = new QToolButton(this);
    m_browseButton->setText("浏览");
    m_browseButton->setToolTip("浏览文件");

    // 清除按钮
    m_clearButton = new QToolButton(this);
    m_clearButton->setText("×");
    m_clearButton->setToolTip("清除选择");
    m_clearButton->setVisible(false);
    m_clearButton->setObjectName("clearButton");

    // 过滤器下拉框
    m_filterCombo = new QComboBox(this);
    m_filterCombo->setVisible(m_showFilterCombo);

    // 进度条
    m_progressBar = new QProgressBar(this);
    m_progressBar->setVisible(false);
    m_progressBar->setTextVisible(false);
    m_progressBar->setRange(0, 100);

    // 状态标签
    m_statusLabel = new QLabel(this);
    m_statusLabel->setObjectName("statusLabel");
    m_statusLabel->setAlignment(Qt::AlignCenter);

    // 添加到布局
    mainLayout->addWidget(m_pathEdit, 1);
    mainLayout->addWidget(m_clearButton);
    mainLayout->addWidget(m_filterCombo);
    mainLayout->addWidget(m_browseButton);

    setLayout(mainLayout);
    setAcceptDrops(m_dragDropEnabled);
}

void FilePicker::InitConnections()
{
    connect(m_browseButton, &QToolButton::clicked, this, &FilePicker::SlotBrowseFiles);
    connect(m_clearButton, &QToolButton::clicked, this, &FilePicker::SlotClearSelection);
    connect(m_filterCombo, &QComboBox::currentTextChanged, this, &FilePicker::SlotFilterChanged);
    connect(m_pathEdit, &QLineEdit::editingFinished, this, &FilePicker::SlotPathEditFinished);

    // 初始化扫描定时器
    m_scanTimer = new QTimer(this);
    m_scanTimer->setSingleShot(false);
    connect(m_scanTimer, &QTimer::timeout, this, &FilePicker::SlotScanProgressUpdate);
}

void FilePicker::UpdateFilterCombo()
{
    if (!m_filterCombo)
    {
        return;
    }

    m_filterCombo->clear();

    for (const ST_FileFilter& filter : m_fileFilters)
    {
        QString filterText = filter.m_filterName;
        if (!filter.m_extensions.isEmpty())
        {
            filterText += QString(" (%1)").arg(filter.m_extensions.join(" "));
        }
        m_filterCombo->addItem(filterText);
    }
}

QString FilePicker::GetFileFilters() const
{
    QStringList filters;

    for (const ST_FileFilter& filter : m_fileFilters)
    {
        if (!filter.m_extensions.isEmpty())
        {
            filters.append(QString("%1 (%2)").arg(filter.m_filterName).arg(filter.m_extensions.join(" ")));
        }
    }

    return filters.join(";;");
}

void FilePicker::ScanDirectory(const QString& dirPath)
{
    if (m_isScanning)
    {
        return;
    }

    m_isScanning = true;
    m_selectedFiles.clear();
    m_scannedFiles = 0;
    m_totalFiles = 0;

    // 清理之前的迭代器
    if (m_dirIterator)
    {
        delete m_dirIterator;
        m_dirIterator = nullptr;
    }

    if (m_progressBar)
    {
        m_progressBar->setVisible(true);
        m_progressBar->setValue(0);
    }

    if (m_statusLabel)
    {
        m_statusLabel->setText("正在扫描文件夹...");
    }

    // 创建新的目录迭代器
    m_dirIterator = new QDirIterator(dirPath, QDir::Files, QDirIterator::Subdirectories);

    // 估算总文件数（快速遍历一次）
    QDirIterator countIt(dirPath, QDir::Files, QDirIterator::Subdirectories);
    while (countIt.hasNext())
    {
        countIt.next();
        m_totalFiles++;
    }

    // 重新创建迭代器用于实际扫描
    delete m_dirIterator;
    m_dirIterator = new QDirIterator(dirPath, QDir::Files, QDirIterator::Subdirectories);

    // 启动定时器进行非阻塞扫描
    m_scanTimer->start(10); // 每10毫秒处理一批文件

    SetCurrentPath(dirPath);
}

bool FilePicker::ValidatePath(const QString& path) const
{
    if (path.isEmpty())
    {
        return false;
    }

    QFileInfo info(path);
    return info.exists();
}

void FilePicker::dragEnterEvent(QDragEnterEvent* event)
{
    if (!m_dragDropEnabled)
    {
        return;
    }

    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
        setProperty("drag", true);
        style()->unpolish(this);
        style()->polish(this);
    }
}

void FilePicker::dragMoveEvent(QDragMoveEvent* event)
{
    if (!m_dragDropEnabled)
    {
        return;
    }

    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void FilePicker::dropEvent(QDropEvent* event)
{
    if (!m_dragDropEnabled)
    {
        return;
    }

    setProperty("drag", false);
    style()->unpolish(this);
    style()->polish(this);

    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return;
    }

    QStringList files;
    for (const QUrl& url : urls)
    {
        QString path = url.toLocalFile();
        if (!path.isEmpty())
        {
            files.append(path);
        }
    }

    if (!files.isEmpty())
    {
        if (m_filePickerMode == EM_FilePickerMode::EM_DirectoryMode && files.size() == 1)
        {
            ScanDirectory(files.first());
        }
        else
        {
            m_selectedFiles = files;
            if (!files.isEmpty())
            {
                SetCurrentPath(files.first());
                emit SigFileListChanged(m_selectedFiles);
            }
        }

        if (m_clearButton)
        {
            m_clearButton->setVisible(true);
        }
    }
}
