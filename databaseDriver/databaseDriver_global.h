#ifndef DATABASEDRIVER_GLOBAL_H
#define DATABASEDRIVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATABASEDRIVER_LIBRARY)
#  define DATABASEDRIVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATABASEDRIVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATABASEDRIVER_GLOBAL_H