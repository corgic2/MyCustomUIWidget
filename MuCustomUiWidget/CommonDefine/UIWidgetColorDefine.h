#pragma once
#include <QColor>
#include <QMetaType>
#include <QString>
#include "UIWidgetGlobal.h"

/// <summary>
/// 颜色定义命名空间，提供所有UI组件使用的颜色定义
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

    /// <summary>
    /// 主题色定义命名空间
    /// </summary>
    namespace theme_color
    {
        /// <summary>
        /// 主要主题颜色
        /// </summary>
        const QColor Primary(51, 122, 183); /// 主题色
        const QColor Success(92, 184, 92); /// 成功色
        const QColor Info(91, 192, 222); /// 信息色
        const QColor Warning(240, 173, 78); /// 警告色
        const QColor Error(217, 83, 79); /// 错误色
    }

    /// <summary>
    /// 文本颜色命名空间
    /// </summary>
    namespace font_color
    {
        /// <summary>
        /// 主要文本颜色定义
        /// </summary>
        const QColor Primary(51, 51, 51); /// 主要文本
        const QColor Secondary(102, 102, 102); /// 次要文本
        const QColor Disabled(153, 153, 153); /// 禁用文本
        const QColor White(255, 255, 255); /// 白色文本
        const QColor Link(51, 122, 183); /// 链接文本

        /// <summary>
        /// 状态文本颜色定义
        /// </summary>
        const QColor Success(92, 184, 92); /// 成功文本
        const QColor Info(91, 192, 222); /// 信息文本
        const QColor Warning(240, 173, 78); /// 警告文本
        const QColor Error(217, 83, 79); /// 错误文本
    }

    /// <summary>
    /// 背景颜色命名空间
    /// </summary>
    namespace background_color
    {
        /// <summary>
        /// 基础背景色定义
        /// </summary>
        const QColor Transparent(0, 0, 0, 0); /// 透明背景
        const QColor White(255, 255, 255); /// 白色背景
        const QColor Light(248, 249, 250); /// 浅色背景
        const QColor Dark(52, 58, 64); /// 深色背景

        /// <summary>
        /// 交互状态背景色定义
        /// </summary>
        const QColor HoverBackground(240, 240, 240); /// 悬停状态背景
        const QColor PressedBackground(230, 230, 230); /// 按下状态背景

        /// <summary>
        /// 状态背景色定义
        /// </summary>
        const QColor Success(242, 255, 242); /// 成功状态背景
        const QColor Info(240, 248, 255); /// 信息状态背景
        const QColor Warning(255, 248, 220); /// 警告状态背景
        const QColor Error(255, 235, 235); /// 错误状态背景

        /// <summary>
        /// 提示框背景色定义
        /// </summary>
        const QColor ToolTipsNormal(197, 245, 251, 255); /// 普通提示框背景
        const QColor ToolTipsInfo(236, 246, 255, 255); /// 信息提示框背景
        const QColor ToolTipsWarning(255, 248, 220, 255); /// 警告提示框背景
        const QColor ToolTipsError(255, 235, 235, 255); /// 错误提示框背景
        const QColor ToolTipsSuccess(242, 255, 242, 255); /// 成功提示框背景
    }

    /// <summary>
    /// 边框颜色命名空间 
    /// </summary>
    namespace border_color
    {
        const QColor Default(229, 229, 229); /// 默认边框颜色
        const QColor Primary(51, 122, 183); /// 主要边框颜色
        const QColor Success(92, 184, 92); /// 成功边框颜色
        const QColor Info(91, 192, 222); /// 信息边框颜色
        const QColor Warning(240, 173, 78); /// 警告边框颜色
        const QColor Error(217, 83, 79); /// 错误边框颜色
    }

    /// <summary>
    /// 阴影颜色命名空间
    /// </summary>
    namespace shadow_color
    {
        const QColor Light(0, 0, 0, 40); /// 浅色阴影
        const QColor Default(0, 0, 0, 80); /// 默认阴影
        const QColor Dark(0, 0, 0, 120); /// 深色阴影
    }

    /// <summary>
    /// 渐变色结构体定义
    /// </summary>
    struct ST_GradientColor
    {
        ST_GradientColor()
        {
        }

        ST_GradientColor(const QColor& startColor, const QColor& endColor)
            : start(startColor), end(endColor)
        {
        }

        QColor start; /// 起始颜色
        QColor end; /// 结束颜色

        /// <summary>
        /// 转换为CSS渐变字符串
        /// </summary>
        QString ToString() const 
        {
            return color_convert::ToGradientString(start, end); 
        }

        /// <summary>
        /// 从两个QColor创建渐变色
        /// </summary>
        static ST_GradientColor FromQColors(const QColor& startColor, const QColor& endColor)
        {
            return ST_GradientColor(startColor, endColor);
        }
    };

    /// <summary>
    /// 渐变色命名空间
    /// </summary>
    namespace gradient_color
    {
        const ST_GradientColor Primary = {
            /// 主要渐变色
            {71, 142, 203},
            {51, 122, 183}
        };

        const ST_GradientColor Success = {
            /// 成功渐变色
            {102, 194, 102},
            {92, 184, 92}
        };

        const ST_GradientColor Info = {
            /// 信息渐变色
            {101, 202, 232},
            {91, 192, 222}
        };

        const ST_GradientColor Warning = {
            /// 警告渐变色
            {250, 183, 88},
            {240, 173, 78}
        };

        const ST_GradientColor Error = {
            /// 错误渐变色
            {227, 93, 89},
            {217, 83, 79}
        };
    }

    /// <summary>
    /// 通用尺寸定义命名空间
    /// </summary>
    namespace size
    {
        const int TipsRadius = 4; /// 提示框圆角半径
        const int TipsFontSize = 12; /// 提示框字体大小
        const int TipsAnimationDuration = 200; /// 提示框动画持续时间(毫秒)
        const int TipsShowDuration = 3000; /// 提示框显示持续时间(毫秒)

        const int DefaultBorderWidth = 1; /// 默认边框宽度
        const int DefaultShadowRadius = 5; /// 默认阴影半径
        const int DefaultShadowOffset = 2; /// 默认阴影偏移
    }
}

Q_DECLARE_METATYPE(UIColorDefine::ST_GradientColor)
