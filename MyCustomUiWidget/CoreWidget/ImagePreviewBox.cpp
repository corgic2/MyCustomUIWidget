#include "ImagePreviewBox.h"
#include <QPainter>
#include <QFileInfo>
#include "SkinStyleLoader.h"

ImagePreviewBox::ImagePreviewBox(QWidget* parent)
    : QWidget(parent)
{
    Initialize();
    AUTO_LOAD_SKIN_STYLE();
}

ImagePreviewBox::~ImagePreviewBox()
{
}

void ImagePreviewBox::Initialize()
{
    // 设置接受拖放
    setAcceptDrops(true);

    // 初始化默认值
    m_scaleMode = ScaleToFit;
    m_enableDragDrop = true;
    m_showCropHint = false;
    m_cropSize = QSize(100, 100);
    m_borderColor = UIColorDefine::border_color::Default;
    m_borderWidth = 1;
    m_placeholderText = tr("拖拽图片到此处或点击选择");

    // 设置最小尺寸
    setMinimumSize(100, 100);

    // 设置焦点策略
    setFocusPolicy(Qt::StrongFocus);
}

void ImagePreviewBox::SetImagePath(const QString& path)
{
    if (m_imagePath != path)
    {
        m_imagePath = path;
        m_originalPixmap = QPixmap(path);
        UpdateImage();
        emit SigImageChanged(path);
    }
}

void ImagePreviewBox::SetImage(const QPixmap& pixmap)
{
    if (!pixmap.isNull())
    {
        m_originalPixmap = pixmap;
        UpdateImage();
    }
}

void ImagePreviewBox::SetScaleMode(EM_ScaleMode mode)
{
    if (m_scaleMode != mode)
    {
        m_scaleMode = mode;
        UpdateImage();
    }
}

void ImagePreviewBox::SetEnableDragDrop(bool enable)
{
    m_enableDragDrop = enable;
    setAcceptDrops(enable);
}

void ImagePreviewBox::SetShowCropHint(bool show)
{
    if (m_showCropHint != show)
    {
        m_showCropHint = show;
        update();
    }
}

void ImagePreviewBox::SetCropSize(const QSize& size)
{
    if (m_cropSize != size)
    {
        m_cropSize = size;
        if (m_showCropHint)
        {
            update();
        }
    }
}

void ImagePreviewBox::SetBorderColor(const QColor& color)
{
    if (m_borderColor != color)
    {
        m_borderColor = color;
        update();
    }
}

void ImagePreviewBox::SetBorderWidth(int width)
{
    if (m_borderWidth != width)
    {
        m_borderWidth = width;
        update();
    }
}

void ImagePreviewBox::SetPlaceholderText(const QString& text)
{
    if (m_placeholderText != text)
    {
        m_placeholderText = text;
        if (m_originalPixmap.isNull())
        {
            update();
        }
    }
}

void ImagePreviewBox::dragEnterEvent(QDragEnterEvent* event)
{
    if (!m_enableDragDrop)
    {
        event->ignore();
        return;
    }

    if (event->mimeData()->hasUrls())
    {
        QString filePath = event->mimeData()->urls().first().toLocalFile();
        QFileInfo fileInfo(filePath);
        QString suffix = fileInfo.suffix().toLower();

        // 检查是否为图片文件
        if (suffix == "jpg" || suffix == "jpeg" || suffix == "png" || suffix == "bmp" || suffix == "gif")
        {
            event->acceptProposedAction();
            return;
        }
    }
    event->ignore();
}

void ImagePreviewBox::dropEvent(QDropEvent* event)
{
    if (!m_enableDragDrop)
    {
        event->ignore();
        return;
    }

    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QString filePath = mimeData->urls().first().toLocalFile();
        SetImagePath(filePath);
        event->acceptProposedAction();
    }
}

void ImagePreviewBox::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制边框
    if (m_borderWidth > 0)
    {
        painter.setPen(QPen(m_borderColor, m_borderWidth));
        painter.drawRect(rect().adjusted(m_borderWidth/2, m_borderWidth/2, -m_borderWidth/2, -m_borderWidth/2));
    }

    if (m_originalPixmap.isNull())
    {
        // 绘制占位文本
        painter.setPen(UIColorDefine::font_color::Secondary);
        painter.drawText(rect(), Qt::AlignCenter, m_placeholderText);
    }
    else
    {
        // 绘制图片
        if (!m_scaledPixmap.isNull())
        {
            QRect targetRect = rect().adjusted(m_borderWidth, m_borderWidth, -m_borderWidth, -m_borderWidth);
            painter.drawPixmap(targetRect, m_scaledPixmap);
        }

        // 绘制裁剪提示
        if (m_showCropHint)
        {
            DrawCropHint(painter);
        }
    }
}

void ImagePreviewBox::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    UpdateImage();
}

void ImagePreviewBox::UpdateImage()
{
    if (m_originalPixmap.isNull())
    {
        m_scaledPixmap = QPixmap();
        update();
        return;
    }

    QSize availableSize = QSize(width() - m_borderWidth*2, height() - m_borderWidth*2);
    switch (m_scaleMode)
    {
        case NoScale:
            m_scaledPixmap = m_originalPixmap;
            break;
        case ScaleToFit:
            m_scaledPixmap = m_originalPixmap.scaled(availableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            break;
        case ScaleToFill:
            m_scaledPixmap = m_originalPixmap.scaled(availableSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            break;
        case ScaleKeepAspect:
            m_scaledPixmap = m_originalPixmap.scaled(availableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            break;
    }
    update();
}

void ImagePreviewBox::DrawCropHint(QPainter& painter)
{
    QRect imageRect = m_scaledPixmap.rect();
    imageRect.moveCenter(rect().center());

    // 计算裁剪框位置
    QRect cropRect(0, 0, m_cropSize.width(), m_cropSize.height());
    cropRect.moveCenter(imageRect.center());

    // 绘制半透明遮罩
    QColor maskColor(0, 0, 0, 120);
    painter.setPen(Qt::NoPen);
    painter.setBrush(maskColor);

    // 绘制四个角落的遮罩
    QPainterPath path;
    path.addRect(rect());
    path.addRect(cropRect);
    painter.drawPath(path);

    // 绘制裁剪框
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(cropRect);

    // 绘制九宫格辅助线
    int thirdWidth = cropRect.width() / 3;
    int thirdHeight = cropRect.height() / 3;
    
    painter.setPen(QPen(Qt::white, 1, Qt::DotLine));
    // 垂直线
    painter.drawLine(cropRect.left() + thirdWidth, cropRect.top(), cropRect.left() + thirdWidth, cropRect.bottom());
    painter.drawLine(cropRect.right() - thirdWidth, cropRect.top(), cropRect.right() - thirdWidth, cropRect.bottom());
    // 水平线
    painter.drawLine(cropRect.left(), cropRect.top() + thirdHeight, cropRect.right(), cropRect.top() + thirdHeight);
    painter.drawLine(cropRect.left(), cropRect.bottom() - thirdHeight, cropRect.right(), cropRect.bottom() - thirdHeight);
} 