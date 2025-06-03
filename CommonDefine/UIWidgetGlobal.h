#pragma once
#pragma once
#define CostomUIGlobal_DLL
#ifdef CostomUIGlobal_DLL
#define CustomUIGlobal_API __declspec(dllexport)
#else
#define CustomUIGlobal_API __declspec(dllimport)
#endif

#define SAFE_DELETE_POINTER_VALUE(p) {if(p) {delete p; p = nullptr;}}
#define SAFE_DELETE_POINTER_ARRAY(p) {if(p) {delete []p; p = nullptr;}}
