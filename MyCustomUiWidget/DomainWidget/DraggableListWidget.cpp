#include "DraggableListWidget.h"
#include <QPainter>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>

DraggableListWidget::DraggableListWidget(QWidget* parent)
    : QListWidget(parent)
    , m_dragEnabled(true)
    , m_dropIndicatorVisible(true)
    , m_dropIndicatorColor(UIColorDefine::theme_color::Primary)
    , m_dropIndicatorWidth(2)
{
    Initialize();
}

DraggableListWidget::~DraggableListWidget()
{
}

void DraggableListWidget::Initialize()
{
    // 设置拖放模式
    setDragDropMode(QAbstractItemView::InternalMove);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setDefaultDropAction(Qt::MoveAction);
    
    // 启用交替行颜色
    setAlternatingRowColors(true);
    
    // 设置样式
    setStyleSheet(QString(R"(
        QListWidget {
            background-color: %1;
            border: 1px solid %2;
            border-radius: 4px;
        }
        QListWidget::item {
            padding: 4px;
            border-bottom: 1px solid %2;
        }
        QListWidget::item:selected {
            background-color: %3;
            color: %4;
        }
        QListWidget::item:hover {
            background-color: %5;
        }
    )")
    .arg(UIColorDefine::color_convert::ToCssString(UIColorDefine::background_color::White))
    .arg(UIColorDefine::color_convert::ToCssString(UIColorDefine::border_color::Default))
    .arg(UIColorDefine::color_convert::ToCssString(UIColorDefine::theme_color::Primary))
    .arg(UIColorDefine::color_convert::ToCssString(UIColorDefine::font_color::White))
    .arg(UIColorDefine::color_convert::ToCssString(UIColorDefine::background_color::HoverBackground)));
}

void DraggableListWidget::SetDragEnabled(bool enable)
{
    m_dragEnabled = enable;
    setDragEnabled(enable);
    setAcceptDrops(enable);
}

void DraggableListWidget::SetDropIndicatorVisible(bool visible)
{
    m_dropIndicatorVisible = visible;
    update();
}

void DraggableListWidget::SetDropIndicatorColor(const QColor& color)
{
    m_dropIndicatorColor = color;
    update();
}

void DraggableListWidget::SetDropIndicatorWidth(int width)
{
    m_dropIndicatorWidth = width;
    update();
}

void DraggableListWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->source() == this)
    {
        event->acceptProposedAction();
    }
}

void DraggableListWidget::dragMoveEvent(QDragMoveEvent* event)
{
    if (event->source() == this)
    {
        m_dropIndicatorPos = event->pos();
        event->acceptProposedAction();
        update();
    }
}

void DraggableListWidget::dropEvent(QDropEvent* event)
{
    QListWidget::dropEvent(event);
    m_dropIndicatorPos = QPoint();
    update();
    emit SigOrderChanged();
}

void DraggableListWidget::paintEvent(QPaintEvent* event)
{
    QListWidget::paintEvent(event);

    if (m_dragEnabled && m_dropIndicatorVisible && !m_dropIndicatorPos.isNull())
    {
        QPainter painter(viewport());
        DrawDropIndicator(painter, m_dropIndicatorPos);
    }
}

void DraggableListWidget::DrawDropIndicator(QPainter& painter, const QPoint& pos)
{
    QRect rect = visualItemRect(itemAt(pos));
    if (!rect.isValid())
    {
        return;
    }

    // 计算指示器位置
    bool drawOnTop = pos.y() < (rect.top() + rect.height() / 2);
    int y = drawOnTop ? rect.top() : rect.bottom();

    // 设置画笔
    QPen pen(m_dropIndicatorColor, m_dropIndicatorWidth);
    painter.setPen(pen);

    // 绘制指示器线条
    painter.drawLine(0, y, width(), y);

    // 绘制指示器三角形
    const int triangleSize = 6;
    QPolygon triangle;
    if (drawOnTop)
    {
        triangle << QPoint(-triangleSize, y - triangleSize)
                << QPoint(0, y)
                << QPoint(-triangleSize, y + triangleSize);
    }
    else
    {
        triangle << QPoint(-triangleSize, y - triangleSize)
                << QPoint(0, y)
                << QPoint(-triangleSize, y + triangleSize);
    }

    painter.setBrush(m_dropIndicatorColor);
    painter.drawPolygon(triangle);
} 