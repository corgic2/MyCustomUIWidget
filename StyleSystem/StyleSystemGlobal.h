#ifndef STYLESYSTEMGLOBAL_H
#define STYLESYSTEMGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STYLESYSTEM_LIBRARY)
#  define STYLESYSTEM_EXPORT Q_DECL_EXPORT
#else
#  define STYLESYSTEM_EXPORT Q_DECL_IMPORT
#endif

// 皮肤系统版本信息
#define STYLESYSTEM_VERSION_MAJOR 1
#define STYLESYSTEM_VERSION_MINOR 0
#define STYLESYSTEM_VERSION_PATCH 0

// 默认配置
#define DEFAULT_SKIN_ID "default"
#define DEFAULT_RESOURCE_PATH "Resource"
#define DEFAULT_CONFIG_FILE "skin_config.json"
#define DEFAULT_STYLE_FILE "main.qss"

// 错误代码
enum class SkinError {
    NoError = 0,
    SkinNotFound,
    ResourceNotFound,
    ConfigParseError,
    StyleParseError,
    InvalidSkinStructure
};

#endif // STYLESYSTEMGLOBAL_H 