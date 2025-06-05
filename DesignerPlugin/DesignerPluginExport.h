#pragma once

#include <QtCore/qglobal.h>

#if defined(CUSTOMWIDGETPLUGIN_LIBRARY)
#  define CUSTOMWIDGETPLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define CUSTOMWIDGETPLUGIN_EXPORT Q_DECL_IMPORT
#endif 