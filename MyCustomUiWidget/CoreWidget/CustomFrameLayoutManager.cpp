#include "CustomFrameLayoutManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QStackedLayout>

CustomFrameLayoutManager::CustomFrameLayoutManager(QWidget* parent)
    : QObject(parent)
    , m_parentWidget(parent)
    , m_currentType(EM_Vertical)
{
}

void CustomFrameLayoutManager::SetLayoutType(EM_LayoutType type)
{
    if (m_currentType == type || !m_parentWidget) {
        return;
    }

    // 保存现有子控件
    QList<QWidget*> children = SaveChildren();
    
    // 删除旧布局
    QLayout* oldLayout = m_parentWidget->layout();
    if (oldLayout) {
        delete oldLayout;
    }

    // 创建新布局
    QLayout* newLayout = nullptr;
    switch (type) {
    case EM_Vertical:
        newLayout = new QVBoxLayout(m_parentWidget);
        break;
    case EM_Horizontal:
        newLayout = new QHBoxLayout(m_parentWidget);
        break;
    case EM_Grid:
        newLayout = new QGridLayout(m_parentWidget);
        break;
    case EM_Form:
        newLayout = new QFormLayout(m_parentWidget);
        break;
    case EM_Stacked:
        newLayout = new QStackedLayout(m_parentWidget);
        break;
    case EM_None:
        newLayout = nullptr;
        break;
    }

    if (newLayout) {
        newLayout->setContentsMargins(4, 4, 4, 4);
        if (type != EM_Stacked) {
            newLayout->setSpacing(2);
        }
        RestoreChildren(children, newLayout);
    }

    m_currentType = type;
}

CustomFrameLayoutManager::EM_LayoutType CustomFrameLayoutManager::GetLayoutType() const
{
    return m_currentType;
}

QString CustomFrameLayoutManager::LayoutTypeToString(EM_LayoutType type)
{
    switch (type) {
    case EM_Vertical: return "Vertical";
    case EM_Horizontal: return "Horizontal";
    case EM_Grid: return "Grid";
    case EM_Form: return "Form";
    case EM_Stacked: return "Stacked";
    case EM_None: return "None";
    default: return "Unknown";
    }
}

CustomFrameLayoutManager::EM_LayoutType CustomFrameLayoutManager::StringToLayoutType(const QString& str)
{
    QString lowerStr = str.toLower();
    if (lowerStr == "vertical") return EM_Vertical;
    if (lowerStr == "horizontal") return EM_Horizontal;
    if (lowerStr == "grid") return EM_Grid;
    if (lowerStr == "form") return EM_Form;
    if (lowerStr == "stacked") return EM_Stacked;
    if (lowerStr == "none") return EM_None;
    return EM_Vertical;
}

QLayout* CustomFrameLayoutManager::GetCurrentLayout() const
{
    return m_parentWidget ? m_parentWidget->layout() : nullptr;
}

QList<QWidget*> CustomFrameLayoutManager::SaveChildren()
{
    QList<QWidget*> children;
    if (!m_parentWidget) {
        return children;
    }

    QLayout* layout = m_parentWidget->layout();
    if (layout) {
        while (layout->count() > 0) {
            QLayoutItem* item = layout->takeAt(0);
            if (item->widget()) {
                children.append(item->widget());
            }
            delete item;
        }
    }
    return children;
}

void CustomFrameLayoutManager::RestoreChildren(const QList<QWidget*>& children, QLayout* layout)
{
    if (!layout) {
        return;
    }

    QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(layout);
    QHBoxLayout* hLayout = qobject_cast<QHBoxLayout*>(layout);
    QGridLayout* gLayout = qobject_cast<QGridLayout*>(layout);
    QFormLayout* fLayout = qobject_cast<QFormLayout*>(layout);
    QStackedLayout* sLayout = qobject_cast<QStackedLayout*>(layout);

    if (vLayout || hLayout || sLayout) {
        // 垂直、水平、堆叠布局直接添加
        for (QWidget* child : children) {
            if (vLayout) vLayout->addWidget(child);
            else if (hLayout) hLayout->addWidget(child);
            else if (sLayout) sLayout->addWidget(child);
        }
    } else if (gLayout) {
        // 栅格布局按行列添加
        for (int i = 0; i < children.size(); ++i) {
            int row = i / 2;
            int col = i % 2;
            gLayout->addWidget(children[i], row, col);
        }
    } else if (fLayout) {
        // 表单布局成对添加
        for (int i = 0; i < children.size(); i += 2) {
            if (i + 1 < children.size()) {
                fLayout->addRow(children[i], children[i + 1]);
            } else {
                fLayout->addRow(children[i]);
            }
        }
    }
}