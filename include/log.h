#ifndef LOG_H
#define LOG_H

#include <QDebug>

#define LOG_EXIT(msg, val) \
    { \
        qDebug() << __FUNCTION__ << __LINE__ << msg; \
        return val; \
    }


#endif // LOG_H
