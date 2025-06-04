#pragma once
#include <QString>

/// <summary>
/// 颜色定义命名空间，提供所有UI组件使用的颜色定义
/// </summary>
namespace UIColorDefine
{
    /// <summary>
    /// RGB颜色结构体
    /// </summary>
    struct ST_ColorRgb
    {
        int r;  /// 红色分量(0-255)
        int g;  /// 绿色分量(0-255)
        int b;  /// 蓝色分量(0-255)

        /// <summary>
        /// 转换为Qt样式表可用的颜色字符串
        /// </summary>
        /// <returns>十六进制颜色字符串，例如"#FF0000"</returns>
        QString ToQString() const
        {
            return QString("#%1%2%3")
                   .arg(r, 2, 16, QChar('0'))
                   .arg(g, 2, 16, QChar('0'))
                   .arg(b, 2, 16, QChar('0'));
        }
    };

    /// <summary>
    /// RGBA颜色结构体，支持透明度
    /// </summary>
    struct ST_ColorRgba
    {
        int r;  /// 红色分量(0-255)
        int g;  /// 绿色分量(0-255)
        int b;  /// 蓝色分量(0-255)
        int a;  /// 透明度(0-255)

        /// <summary>
        /// 转换为Qt样式表可用的颜色字符串
        /// </summary>
        /// <returns>RGBA格式颜色字符串，例如"rgba(255,0,0,1.0)"</returns>
        QString ToQString() const
        {
            return QString("rgba(%1, %2, %3, %4)")
                   .arg(r).arg(g).arg(b).arg(static_cast<float>(a) / 255.0);
        }
    };

    /// <summary>
    /// 主题色定义命名空间
    /// </summary>
    namespace theme_color
    {
        /// <summary>
        /// 主要主题颜色
        /// </summary>
        const ST_ColorRgb Primary = {51, 122, 183};     /// 主题色
        const ST_ColorRgb Success = {92, 184, 92};      /// 成功色
        const ST_ColorRgb Info = {91, 192, 222};        /// 信息色
        const ST_ColorRgb Warning = {240, 173, 78};     /// 警告色
        const ST_ColorRgb Error = {217, 83, 79};        /// 错误色
    }

    /// <summary>
    /// 文本颜色命名空间
    /// </summary>
    namespace font_color
    {
        /// <summary>
        /// 主要文本颜色定义
        /// </summary>
        const ST_ColorRgb Primary = {51, 51, 51};       /// 主要文本
        const ST_ColorRgb Secondary = {102, 102, 102};  /// 次要文本
        const ST_ColorRgb Disabled = {153, 153, 153};   /// 禁用文本
        const ST_ColorRgb White = {255, 255, 255};      /// 白色文本
        const ST_ColorRgb Link = {51, 122, 183};        /// 链接文本

        /// <summary>
        /// 状态文本颜色定义
        /// </summary>
        const ST_ColorRgb Success = {92, 184, 92};      /// 成功文本
        const ST_ColorRgb Info = {91, 192, 222};        /// 信息文本
        const ST_ColorRgb Warning = {240, 173, 78};     /// 警告文本
        const ST_ColorRgb Error = {217, 83, 79};        /// 错误文本
    }

    /// <summary>
    /// 背景颜色命名空间
    /// </summary>
    namespace background_color
    {
        /// <summary>
        /// 基础背景色定义
        /// </summary>
        const ST_ColorRgba Transparent = {0, 0, 0, 0};        /// 透明背景
        const ST_ColorRgba White = {255, 255, 255, 255};      /// 白色背景
        const ST_ColorRgba Light = {248, 249, 250, 255};      /// 浅色背景
        const ST_ColorRgba Dark = {52, 58, 64, 255};          /// 深色背景

        /// <summary>
        /// 状态背景色定义
        /// </summary>
        const ST_ColorRgba Success = {242, 255, 242, 255};    /// 成功状态背景
        const ST_ColorRgba Info = {240, 248, 255, 255};       /// 信息状态背景
        const ST_ColorRgba Warning = {255, 248, 220, 255};    /// 警告状态背景
        const ST_ColorRgba Error = {255, 235, 235, 255};      /// 错误状态背景

        /// <summary>
        /// 提示框背景色定义
        /// </summary>
        const ST_ColorRgba ToolTipsNormal = {250, 250, 250, 250};  /// 普通提示框背景
        const ST_ColorRgba ToolTipsInfo = {236, 246, 255, 250};    /// 信息提示框背景
        const ST_ColorRgba ToolTipsWarning = {255, 248, 220, 250}; /// 警告提示框背景
        const ST_ColorRgba ToolTipsError = {255, 235, 235, 250};   /// 错误提示框背景
        const ST_ColorRgba ToolTipsSuccess = {242, 255, 242, 250}; /// 成功提示框背景
    }

    /// <summary>
    /// 边框颜色命名空间 
    /// </summary>
    namespace border_color
    {
        const ST_ColorRgb Default = {229, 229, 229};    /// 默认边框颜色
        const ST_ColorRgb Primary = {51, 122, 183};     /// 主要边框颜色
        const ST_ColorRgb Success = {92, 184, 92};      /// 成功边框颜色
        const ST_ColorRgb Info = {91, 192, 222};        /// 信息边框颜色
        const ST_ColorRgb Warning = {240, 173, 78};     /// 警告边框颜色
        const ST_ColorRgb Error = {217, 83, 79};        /// 错误边框颜色
    }

    /// <summary>
    /// 阴影颜色命名空间
    /// </summary>
    namespace shadow_color
    {
        const ST_ColorRgba Light = {0, 0, 0, 40};    /// 浅色阴影
        const ST_ColorRgba Default = {0, 0, 0, 80};  /// 默认阴影
        const ST_ColorRgba Dark = {0, 0, 0, 120};    /// 深色阴影
    }

    /// <summary>
    /// 渐变色结构体定义
    /// </summary>
    struct ST_GradientColor
    {
        ST_ColorRgb start;  /// 渐变起始颜色
        ST_ColorRgb end;    /// 渐变结束颜色
    };

    /// <summary>
    /// 渐变色命名空间
    /// </summary>
    namespace gradient_color
    {
        const ST_GradientColor Primary = {            /// 主要渐变色
            {71, 142, 203},
            {51, 122, 183}
        };
        
        const ST_GradientColor Success = {            /// 成功渐变色
            {102, 194, 102},
            {92, 184, 92}
        };

        const ST_GradientColor Info = {               /// 信息渐变色
            {101, 202, 232},
            {91, 192, 222}
        };

        const ST_GradientColor Warning = {            /// 警告渐变色
            {250, 183, 88},
            {240, 173, 78}
        };

        const ST_GradientColor Error = {              /// 错误渐变色
            {227, 93, 89},
            {217, 83, 79}
        };
    }

    /// <summary>
    /// 通用尺寸定义命名空间
    /// </summary>
    namespace size
    {
        const int TipsRadius = 6;                    /// 提示框圆角半径
        const int TipsFontSize = 12;                /// 提示框字体大小
        const int TipsAnimationDuration = 200;      /// 提示框动画持续时间(ms)
        const int TipsShowDuration = 3000;          /// 提示框显示持续时间(ms)
        
        const int DefaultBorderWidth = 1;           /// 默认边框宽度
        const int DefaultShadowRadius = 5;          /// 默认阴影半径
        const int DefaultShadowOffset = 2;          /// 默认阴影偏移
    }
}
