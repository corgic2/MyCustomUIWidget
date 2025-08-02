#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QFileDialog>
#include "../CommonDefine/UIWidgetGlobal.h"
/// <summary>
/// 文件选择器控件
/// </summary>
class CustomUIGlobal_API FilePicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString m_filePath READ GetFilePath WRITE SetFilePath NOTIFY SigFilePathChanged)
    Q_PROPERTY(QString m_filter READ GetFilter WRITE SetFilter)
    Q_PROPERTY(QString m_dialogTitle READ GetDialogTitle WRITE SetDialogTitle)
    Q_PROPERTY(bool m_isSaveDialog READ IsSaveDialog WRITE SetIsSaveDialog)
    Q_PROPERTY(QString m_defaultSuffix READ GetDefaultSuffix WRITE SetDefaultSuffix)
    Q_PROPERTY(QString m_placeholderText READ GetPlaceholderText WRITE SetPlaceholderText)
    Q_PROPERTY(QString m_buttonText READ GetButtonText WRITE SetButtonText)
    Q_PROPERTY(QString m_startPath READ GetStartPath WRITE SetStartPath)

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
    /// 设置文件路径
    /// </summary>
    /// <param name="path">文件路径</param>
    void SetFilePath(const QString& path);

    /// <summary>
    /// 设置文件过滤器
    /// </summary>
    /// <param name="filter">过滤器字符串，如"Images (*.png *.jpg);;All Files (*.*)"</param>
    void SetFilter(const QString& filter);

    /// <summary>
    /// 设置对话框标题
    /// </summary>
    /// <param name="title">标题</param>
    void SetDialogTitle(const QString& title);

    /// <summary>
    /// 设置是否为保存对话框
    /// </summary>
    /// <param name="isSave">是否为保存对话框</param>
    void SetIsSaveDialog(bool isSave);

    /// <summary>
    /// 设置默认文件后缀（保存对话框使用）
    /// </summary>
    /// <param name="suffix">默认后缀，不包含点号</param>
    void SetDefaultSuffix(const QString& suffix);

    /// <summary>
    /// 设置输入框占位文本
    /// </summary>
    /// <param name="text">占位文本</param>
    void SetPlaceholderText(const QString& text);

    /// <summary>
    /// 设置按钮文本
    /// </summary>
    /// <param name="text">按钮文本</param>
    void SetButtonText(const QString& text);

    /// <summary>
    /// 设置起始路径
    /// </summary>
    /// <param name="path">起始路径</param>
    void SetStartPath(const QString& path);

    // Getters
    QString GetFilePath() const { return m_filePath; }
    QString GetFilter() const { return m_filter; }
    QString GetDialogTitle() const { return m_dialogTitle; }
    bool IsSaveDialog() const { return m_isSaveDialog; }
    QString GetDefaultSuffix() const { return m_defaultSuffix; }
    QString GetPlaceholderText() const { return m_placeholderText; }
    QString GetButtonText() const { return m_buttonText; }
    QString GetStartPath() const { return m_startPath; }

signals:
    /// <summary>
    /// 文件路径改变信号
    /// </summary>
    /// <param name="path">新的文件路径</param>
    void SigFilePathChanged(const QString& path);

private slots:
    /// <summary>
    /// 浏览按钮点击槽函数
    /// </summary>
    void OnBrowseButtonClicked();

    /// <summary>
    /// 输入框文本改变槽函数
    /// </summary>
    /// <param name="text">新的文本</param>
    void OnLineEditTextChanged(const QString& text);

private:
    /// <summary>
    /// 初始化控件
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新布局
    /// </summary>
    void UpdateLayout();

private:
    QLineEdit* m_lineEdit;           /// 路径输入框
    QToolButton* m_browseButton;     /// 浏览按钮
    QString m_filePath;              /// 文件路径
    QString m_filter;                /// 文件过滤器
    QString m_dialogTitle;           /// 对话框标题
    bool m_isSaveDialog;             /// 是否为保存对话框
    QString m_defaultSuffix;         /// 默认文件后缀
    QString m_placeholderText;       /// 输入框占位文本
    QString m_buttonText;            /// 按钮文本
    QString m_startPath;             /// 起始路径
}; 