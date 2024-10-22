#include "cpp/support/Log.h"

bool Log::m_firstLog = true;
QString Log::m_sessionLogs = QString();

void Log::info(QString func, QString log, Log::Action action)
{
    Log::log( Log::buildPrefix("I", func) + log, action);
}

void Log::warning(QString func, QString log, Log::Action action)
{
    Log::log( Log::buildPrefix("W", func) + log, action);
}

void Log::error(QString func, QString log, Log::Action action)
{
    Log::log( Log::buildPrefix("E", func) + log, action);
}

void Log::debug(QString func, QString log, Log::Action action)
{
    Log::log( Log::buildPrefix("D", func) + log, action);
}

QString Log::time()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    return currentDateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
}

QString Log::buildPrefix(QString type, QString func)
{
    QString prefix;
    // set time
    prefix = "[" + Log::time() +  "]" + " ";
    // set type
    prefix += type + " ";

    // set function name
    if(func.length() >= EST_FUNCTION_LENGTH)
        prefix += func;
    else
    {
        size_t fill = EST_FUNCTION_LENGTH - func.length();
        prefix += QString(SHORTER_FUNCTION_FILL_CHARACTER).repeated(fill);
        prefix += func;
    }

#if SPACE_BETWEEN_CONTENT_SPACE_AND_CONTENT
    prefix += " ";
#endif

    // set space between content
    prefix += QString(CONTENT_SPACE_CHARACTER).repeated(CONTENT_SPACE);

#if SPACE_BETWEEN_CONTENT_SPACE_AND_CONTENT
    prefix += " ";
#endif

    return prefix;
}

QString Log::buildStartPrefix()
{
    QString prefix;
    // set time
    prefix = "[" + Log::time() +  "]" + "   ";

    return prefix + "--- [APPLICATION STARTED] ---";
}

void Log::log(QString content, Log::Action action)
{
    if(action & Action::Print)
        Log::print(content);

    if(action & Action::Save)
        Log::saveFile(content);

    if(action & Action::Sesion)
        Log::addSession(content);
}

void Log::print(QString content)
{
    qDebug() << content.toStdString().c_str();
}

void Log::saveFile(QString content)
{
    QFile file(LOG_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        WR << "Error while creating info log!";
        return;
    }

    QTextStream out(&file);
    if(m_firstLog)
    {
        out << Log::buildStartPrefix() << "\n";
        m_firstLog = false;
    }
    out << content << "\n";
    file.close();
}

void Log::addSession(QString content)
{
    Log::m_sessionLogs += content + "\n";
}

QString Log::Convert::listUrlToString(QList<QUrl> list)
{
    QString str("[");
    for(const auto &i : list)
        str += "\"" + i.toLocalFile() + "\", ";
    return str + "\b\b]";
}
