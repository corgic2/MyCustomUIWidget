#pragma once

#if defined(CUSTOMUIGLOBAL_LIBRARY)
#  define CustomUIGlobal_API Q_DECL_EXPORT
#else
#  define CustomUIGlobal_API Q_DECL_IMPORT
#endif 

#define SAFE_DELETE_POINTER_VALUE(p) {if(p) {delete p; p = nullptr;}}
#define SAFE_DELETE_POINTER_ARRAY(p) {if(p) {delete []p; p = nullptr;}}
