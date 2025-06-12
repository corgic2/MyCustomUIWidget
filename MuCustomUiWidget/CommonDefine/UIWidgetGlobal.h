#pragma once

#include <QtCore/qglobal.h>
#pragma execution_character_set("utf-8")

#if defined(CUSTOMUIGLOBAL_LIBRARY)
#  define CustomUIGlobal_API Q_DECL_EXPORT
#else
#  define CustomUIGlobal_API 
#endif

#ifndef SAFE_DELETE_MACRO
// 定义一些通用的宏
#define SAFE_DELETE_POINTER_VALUE(p) if(p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY_POINTER_VALUE(p) if(p) { delete[] p; p = nullptr; }
#endif