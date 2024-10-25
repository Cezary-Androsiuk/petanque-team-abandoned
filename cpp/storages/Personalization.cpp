#include "cpp/storages/Personalization.h"


Personalization::Personalization(QObject *parent)
    : QObject{parent}
{
    this->setDefault();
    this->ifNotExistSaveDefault();
    this->load();
}

Personalization::~Personalization()
{
}

void Personalization::printValues() const
{
#if PRINT_VALUES
    I("  " KEY_DARK_THEME + QString(" = ") + BOOL_TO_STR(m_darkTheme));
    /// --- ADD NEW HERE ---
#endif
}

void Personalization::addError(const QString &error)
{
    m_errors += error;
}

Personalization *const Personalization::getInstance() noexcept
{
    static Personalization p;
    return &p;
}

void Personalization::setDefault()
{

}

void Personalization::load()
{
    // I("loading personalization");

    if(!QFile(JSON_FILE).exists()){
        MARK_ERROR("file " JSON_FILE " not found");
        emit this->loadFailed();
        return;
    }

    QFile jsonFile(JSON_FILE);
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        MARK_ERROR("Can not open personalization json file: " JSON_FILE);
        emit this->loadFailed();
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonData = QJsonDocument::fromJson(jsonFile.readAll(), &jsonError);
    jsonFile.close();

    if(jsonError.error != QJsonParseError::NoError) {
        MARK_ERROR("json parse error: " + jsonError.errorString());
        emit this->loadFailed();
        return;
    }

    if(!jsonData.isObject()){
        MARK_ERROR("json file does not contains json object");
        emit this->loadFailed();
        return;
    }

    // at this point data are default

    auto jp = jsonData.object();
    QString key;

    // try to load data, but if key is missing then, notify and leave default value

    key = KEY_EXAMPLE_DATA;
    if(jp.contains(key)) m_exampleData = jp[key].toObject();
    else KEY_NOT_FOUND_MESSAGE;

    /// --- ADD NEW HERE ---

    this->printValues();
    I("personalization data loaded");

    emit this->loaded();
}

void Personalization::ifNotExistSaveDefault()
{
    if(QFileInfo::exists(JSON_FILE))
        return;
    this->save();
}

void Personalization::save()
{
    // I("save personalization starting");

    QJsonObject jsonObject;
    jsonObject[KEY_NOTE] = QString(DEFAULT_NOTE);
    // jsonObject[KEY_EXAMPLE_DATA] = this->getExampleData();
    /// --- ADD NEW HERE ---

    QJsonDocument jsonData(jsonObject);

    QFile file(JSON_FILE);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        MARK_ERROR("error while saving json file to " JSON_FILE " with error " + file.errorString());
        emit this->saveFailed();
        return;
    }

    file.write(jsonData.toJson());
    file.close();

    this->printValues();
    I("personalization data saved");

    emit this->saved();
}

const QJsonObject &Personalization::getExampleData() const
{
    return m_exampleData;
}
