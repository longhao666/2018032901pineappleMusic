#ifndef LLLL_GLOBAL_H
#define LLLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LLLL_LIBRARY)
#  define LLLLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LLLLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LLLL_GLOBAL_H
