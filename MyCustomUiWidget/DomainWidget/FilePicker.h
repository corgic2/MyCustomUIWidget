#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QComboBox>
#include <QProgressBar>
#include <QLabel>
#include <QFileDialog>
#include "../CommonDefine/UIWidgetGlobal.h"

/// <summary>
/// 文件选择器模式枚举
/// </summary>
enum class EM_FilePickerMode
{
    EM_FileMode,          ///< 选择文件
    EM_DirectoryMode,     ///< 选择文件夹
    EM_MultiFileMode,     ///< 选择多个文件
    EM_FileAndDirectoryMode ///< 选择文件或文件夹
};

/// <summary>
/// 文件过滤器结构体
/// </summary>
struct ST_FileFilter
{
    QString m_filterName;    ///< 过滤器名称
    QStringList m_extensions; ///< 支持的扩展名
    
    ST_FileFilter() = default;
    ST_FileFilter(const QString& name, const QStringList& exts)
        : m_filterName(name), m_extensions(exts) {}
};

/// <summary>
/// 文件选择器控件
/// 支持文件/文件夹选择，多格式过滤，文件夹遍历等功能
/// </summary>
class CustomUIGlobal_API FilePicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(EM_FilePickerMode m_filePickerMode READ GetFilePickerMode WRITE SetFilePickerMode)
    Q_PROPERTY(QString m_currentPath READ GetCurrentPath WRITE SetCurrentPath)
    Q_PROPERTY(bool m_showClearButton READ GetShowClearButton WRITE SetShowClearButton)
    Q_PROPERTY(bool m_showFilterCombo READ GetShowFilterCombo WRITE SetShowFilterCombo)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit FilePicker(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~FilePicker();

    /// <summary>
    /// 获取当前选择模式
    /// </summary>
    EM_FilePickerMode GetFilePickerMode() const;

    /// <summary>
    /// 设置选择模式
    /// </summary>
    void SetFilePickerMode(EM_FilePickerMode mode);

    /// <summary>
    /// 获取当前路径
    /// </summary>
    QString GetCurrentPath() const;

    /// <summary>
    /// 获取所有选择的文件路径（多选模式）
    /// </summary>
    QStringList GetSelectedFiles() const;

    /// <summary>
    /// 设置当前路径
    /// </summary>
    void SetCurrentPath(const QString& path);

    /// <summary>
    /// 获取是否显示清除按钮
    /// </summary>
    bool GetShowClearButton() const;

    /// <summary>
    /// 设置是否显示清除按钮
    /// </summary>
    void SetShowClearButton(bool show);

    /// <summary>
    /// 获取是否显示过滤器下拉框
    /// </summary>
    bool GetShowFilterCombo() const;

    /// <summary>
    /// 设置是否显示过滤器下拉框
    /// </summary>
    void SetShowFilterCombo(bool show);

    /// <summary>
    /// 添加文件过滤器
    /// </summary>
    void AddFileFilter(const ST_FileFilter& filter);

    /// <summary>
    /// 设置默认目录
    /// </summary>
    void SetDefaultDirectory(const QString& dir);

    /// <summary>
    /// 设置对话框标题
    /// </summary>
    void SetDialogTitle(const QString& title);

    /// <summary>
    /// 启用/禁用拖拽功能
    /// </summary>
    void SetDragDropEnabled(bool enabled);

public slots:
    /// <summary>
    /// 清除选择
    /// </summary>
    void SlotClearSelection();

    /// <summary>
    /// 浏览文件
    /// </summary>
    void SlotBrowseFiles();

signals:
    /// <summary>
    /// 文件路径改变信号
    /// </summary>
    void SigFilePathChanged(const QString& path);

    /// <summary>
    /// 文件列表改变信号（多选模式）
    /// </summary>
    void SigFileListChanged(const QStringList& files);

    /// <summary>
    /// 选择模式改变信号
    /// </summary>
    void SigModeChanged(EM_FilePickerMode mode);

    /// <summary>
    /// 文件过滤器改变信号
    /// </summary>
    void SigFilterChanged(const QString& filter);

protected:
    /// <summary>
    /// 拖拽进入事件
    /// </summary>
    void dragEnterEvent(QDragEnterEvent* event) override;

    /// <summary>
    /// 拖拽移动事件
    /// </summary>
    void dragMoveEvent(QDragMoveEvent* event) override;

    /// <summary>
    /// 拖拽释放事件
    /// </summary>
    void dropEvent(QDropEvent* event) override;

private slots:
    /// <summary>
    /// 过滤器改变槽函数
    /// </summary>
    void SlotFilterChanged(const QString& filter);

    /// <summary>
    /// 路径编辑完成槽函数
    /// </summary>
    void SlotPathEditFinished();

    /// <summary>
    /// 扫描文件夹进度更新（QtConcurrent版本，已废弃）
    /// </summary>
    void SlotScanProgress(int progress);

    /// <summary>
    /// 扫描文件夹完成
    /// </summary>
    void SlotScanFinished();
    
    /// <summary>
    /// 扫描文件夹进度更新（定时器版本）
    /// </summary>
    void SlotScanProgressUpdate();

private:
    /// <summary>
    /// 初始化UI
    /// </summary>
    void InitUI();

    /// <summary>
    /// 初始化连接
    /// </summary>
    void InitConnections();

    /// <summary>
    /// 更新过滤器下拉框
    /// </summary>
    void UpdateFilterCombo();

    /// <summary>
    /// 获取文件过滤器字符串
    /// </summary>
    QString GetFileFilters() const;

    /// <summary>
    /// 遍历文件夹获取文件
    /// </summary>
    void ScanDirectory(const QString& dirPath);

    /// <summary>
    /// 验证文件路径
    /// </summary>
    bool ValidatePath(const QString& path) const;

private:
    QLineEdit* m_pathEdit;              ///< 路径编辑框
    QToolButton* m_browseButton;        ///< 浏览按钮
    QToolButton* m_clearButton;         ///< 清除按钮
    QComboBox* m_filterCombo;           ///< 过滤器下拉框
    QProgressBar* m_progressBar;        ///< 进度条
    QLabel* m_statusLabel;              ///< 状态标签
    
    EM_FilePickerMode m_filePickerMode;  ///< 选择模式
    QString m_currentPath;              ///< 当前路径
    QStringList m_selectedFiles;        ///< 选择的文件列表
    QString m_defaultDirectory;         ///< 默认目录
    QString m_dialogTitle;              ///< 对话框标题
    QList<ST_FileFilter> m_fileFilters;  ///< 文件过滤器
    bool m_showClearButton;             ///< 是否显示清除按钮
    bool m_showFilterCombo;             ///< 是否显示过滤器下拉框
    bool m_dragDropEnabled;             ///< 是否启用拖拽
    bool m_isScanning;                  ///< 是否正在扫描
    
    // 文件夹扫描相关成员
    QTimer* m_scanTimer;                ///< 扫描定时器
    QDirIterator* m_dirIterator;      ///< 目录迭代器
    int m_totalFiles;                 ///< 总文件数（估算）
    int m_scannedFiles;               ///< 已扫描文件数
};
