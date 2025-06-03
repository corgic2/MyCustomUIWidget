#pragma once
#include "UIWidgetGlobal.h"
#include <QString>
#include <QTimer>
#include <QToolTip>
#include <QWidget>
#include "../UtilsWidget/CustomToolTips.h"
#include "ui_FilePathIconListWidgetItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FilePathIconListWidgetItemClass; };
QT_END_NAMESPACE

class CustomUIGlobal_API FilePathIconListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    struct ST_NodeInfo
    {
        QString filePath;
        QString iconFilePath;
        QString content;
        QString toolTipsContent;
        QString toolTipsContentEx = QString();
    };
    FilePathIconListWidgetItem(QWidget *parent = nullptr);
    ~FilePathIconListWidgetItem();
    /// <summary>
    /// 添加节点信息
    /// </summary>
    /// <param name="nodeInfo"></param>
    void SetItemNodeText(const ST_NodeInfo& nodeInfo);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    /// <summary>
    /// 显示tips
    /// </summary>
    void ShowToolTip();

private:
    Ui::FilePathIconListWidgetItemClass *ui;
    ST_NodeInfo m_info;
    QTimer m_timer;
    int m_delay = 700; // 延迟时间(ms)
    /// <summary>
    /// tipsWidget
    /// </summary>
    CustomToolTips* m_tipsWidget = nullptr;
};

