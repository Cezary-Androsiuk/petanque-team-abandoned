#ifndef LOG_H
#define LOG_H

#include <QDebug>
#include <QString>

#include <QList>
#include <QUrl>

#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QIODevice>

//////////////////// OLD DEBUG ////////////////////
#define FUNCTION __PRETTY_FUNCTION__
// #define FUNCTION __FUNCTION__
#define DB qDebug() << qSetFieldWidth(30) << FUNCTION << qSetFieldWidth(0)
#define WR qWarning() << qSetPadChar('#') << qSetFieldWidth(30) \
<< QString(" ") + FUNCTION + " " << qSetPadChar(' ') << qSetFieldWidth(0)
//////////////////////////////////////////////////


//////////////////// NEW DEBUG ////////////////////
#define GET_MACRO(_1, _2, NAME, ...) NAME

#define I_1(x) Log::info    (__PRETTY_FUNCTION__, (x));
#define W_1(x) Log::warning (__PRETTY_FUNCTION__, (x));
#define E_1(x) Log::error   (__PRETTY_FUNCTION__, (x));
#define D_1(x) Log::debug   (__PRETTY_FUNCTION__, (x));

#define I_2(x, a) Log::info    (__PRETTY_FUNCTION__, (x), Log::Action(a));
#define W_2(x, a) Log::warning (__PRETTY_FUNCTION__, (x), Log::Action(a));
#define E_2(x, a) Log::error   (__PRETTY_FUNCTION__, (x), Log::Action(a));
#define D_2(x, a) Log::debug   (__PRETTY_FUNCTION__, (x), Log::Action(a));

#define I(...) GET_MACRO(__VA_ARGS__, I_2, I_1)(__VA_ARGS__)
#define W(...) GET_MACRO(__VA_ARGS__, W_2, W_1)(__VA_ARGS__)
#define E(...) GET_MACRO(__VA_ARGS__, E_2, E_1)(__VA_ARGS__)
#define D(...) GET_MACRO(__VA_ARGS__, D_2, D_1)(__VA_ARGS__)
//////////////////////////////////////////////////


#define LOG_FILE "Logs.log"
#define EST_FUNCTION_LENGTH 70 // estimated function name length what will be reserved while creating log
#define SHORTER_FUNCTION_FILL_CHARACTER ' ' // characters that fills area before function name to fit estimated function name length
#define CONTENT_SPACE 10 // space between function name and content
#define CONTENT_SPACE_CHARACTER ' ' // characters that fills space between function name and content
#define SPACE_BETWEEN_CONTENT_SPACE_AND_CONTENT true // creates spaces between space: "x ........ y" instead of "x........y"

class Log
{
public:
    enum Action{
        None = 0,
        Save = 1 << 0,
        Print = 1 << 1,
        Sesion = 1 << 2,
        SavePrint = Save | Print,
        SaveSesion = Save | Sesion,
        PrintSesion = Print | Sesion,
        All = Save | Print | Sesion,
    };
    static constexpr Action actionForceHighest = Action::All; // set highest ( will be compared with & sign )
    static constexpr Action actionForceLowest = Action::None;  // set lowest ( will be compared with | sign )

    static void info(QString func, QString log, Action action = Action(Action::All));
    static void warning(QString func, QString log, Action action = Action(Action::All));
    static void error(QString func, QString log, Action action = Action(Action::All));
    static void debug(QString func, QString log, Action action = Action(Action::All));

private:
    static QString time();
    static QString buildPrefix(QString type, QString func);
    static QString buildStartPrefix();

    static void log(QString content, Action action);
    static void print(QString content);
    static void saveFile(QString content);
    static void addSession(QString content);

public:
    class Convert{
    public:
        static QString listUrlToString(QList<QUrl> list);
    };

    static bool m_firstLog;
    static QString m_sessionLogs;
};

#endif // LOG_H
