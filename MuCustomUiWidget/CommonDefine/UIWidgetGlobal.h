#pragma once

#include <QtCore/qglobal.h>

#if defined(CUSTOMUIGLOBAL_LIBRARY)
#  define CustomUIGlobal_API Q_DECL_EXPORT
#else
#  define CustomUIGlobal_API Q_DECL_IMPORT
#endif

// 定义一些通用的宏
#define SAFE_DELETE_POINTER_VALUE(p) if(p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY_POINTER_VALUE(p) if(p) { delete[] p; p = nullptr; }
