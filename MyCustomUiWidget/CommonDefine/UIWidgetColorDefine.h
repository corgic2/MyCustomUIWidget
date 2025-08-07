#pragma once
#include <QColor>
#include <QMetaType>
#include <QString>
#include "UIWidgetGlobal.h"

/// <summary>
/// 颜色定义，提供所有UI组件使用的颜色定义
/// </summary>
namespace UIColorDefine
{
    /// <summary>
    /// 颜色转换函数
    /// </summary>
    namespace color_convert
    {
        /// <summary>
        /// 将QColor转换为CSS颜色字符串
        /// </summary>
        inline QString ToCssString(const QColor& color)
        {
            if (color.alpha() < 255)
            {
                return QString("rgba(%1,%2,%3,%4)")
                       .arg(color.red())
                       .arg(color.green())
                       .arg(color.blue())
                       .arg(color.alpha() / 255.0);
            }
            return QString("rgb(%1,%2,%3)")
                   .arg(color.red())
                   .arg(color.green())
                   .arg(color.blue());
        }

        /// <summary>
        /// 将两个QColor转换为CSS渐变字符串
        /// </summary>
        inline QString ToGradientString(const QColor& start, const QColor& end)
        {
            return QString("qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 %1, stop:1 %2)")
                   .arg(ToCssString(start))
                   .arg(ToCssString(end));
        }
    }
}
