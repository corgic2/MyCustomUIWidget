#pragma once

#include <QtCore/qglobal.h>
#pragma execution_character_set("utf-8")

#define CUSTOMWIDGET_RESOURCESFILE ":/MyCustomUiWidget.qrc"

#if defined(CUSTOMUIGLOBAL_LIBRARY)
#  define CustomUIGlobal_API Q_DECL_EXPORT
#else
#  define CustomUIGlobal_API 
#endif
