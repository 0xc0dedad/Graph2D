#ifndef LOG_H
#define LOG_H

#include <QDebug>

#define LOG_EXIT(msg, val) \
    { \
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << msg; \
        return val; \
    }

#define LOG_DEBUG(msg) \
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << msg;


#endif // LOG_H
