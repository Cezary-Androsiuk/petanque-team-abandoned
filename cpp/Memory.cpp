#include "Memory.h"

Memory::Memory(QObject *parent)
    : QObject{parent}
    , m_backend(nullptr)
{

#if DELETE_MEMORY_AT_START
    D("removed memory file at start with status: " + BOOL_TO_STR(QFile::remove(MEMORY_FILE)));
#endif

}

void Memory::load()
{
    if(m_backend == nullptr)
    {
        QString message("Backend value is NULL!");
        E(message);
        emit this->memoryLoadError(message);
        return;
    }
    if(m_backend->getEvent() == nullptr)
    {
        QString message("Event value is NULL!");
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    if(!QFile( MEMORY_FILE ).exists())
    {
        QString message("Memory file not exist");
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    QFile file( MEMORY_FILE );
    if(!file.open(QIODevice::OpenModeFlag::ReadOnly | QIODevice::OpenModeFlag::Text))
    {
        QString message = "Failed to create memory file: " + file.errorString();
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    file.close();

    if(jsonParseError.error != QJsonParseError::ParseError::NoError)
    {
        QString message = "Failed to parse file to json: " + jsonParseError.errorString();
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    if(!jsonDocument.isObject()){
        QString message = "Json in file is not a json object";
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    QJsonObject jsonObject = jsonDocument.object();
    QString errorMessage;
    if(!this->jsonToEvent(jsonObject, m_backend->getEvent(), errorMessage))
    {
        QString message = "Failed while saving json to events variable: " + errorMessage;
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    emit this->memoryLoaded();
}

void Memory::save()
{

    if(m_backend == nullptr)
    {
        QString message("Backend value is NULL!");
        E(message);
        emit this->memorySaveError(message);
        return;
    }
    if(m_backend->getEvent() == nullptr)
    {
        QString message("Event value is NULL!");
        E(message);
        emit this->memorySaveError(message);
        return;
    }

    if(!QFileInfo::exists( MEMORY_DIR ))
    {
        if(!QDir().mkdir( MEMORY_DIR ))
        {
            E("Failed to create directory: " MEMORY_DIR );
        }
    }

    QFile file( MEMORY_FILE );
    if(!file.open(QIODevice::OpenModeFlag::WriteOnly | QIODevice::OpenModeFlag::Text))
    {
        QString message = "Failed to create memory file: " + file.errorString();
        E(message);
        emit this->memorySaveError(message);
        return;
    }

    QJsonObject jsonObject;
    this->eventToJson(m_backend->getEvent(), jsonObject);

    file.write(QJsonDocument(jsonObject).toJson());
    file.close();

    emit this->memorySaved();
}

bool Memory::memoryFileExist() const
{
    return QFileInfo::exists( MEMORY_FILE );
}

void Memory::setBackendPtr(Backend *backend)
{
    m_backend = backend;
}

void Memory::eventToJson(const Event *const event, QJsonObject &jsonObject) const
{
    int phase = event->getPhase();
    if(phase == 1)
    {
        QJsonArray teams;
        for(Team *team : event->getTeams())
        {
            QJsonArray players;
            for(Player *player : team->getPlayers())
            {
                QJsonObject jPlayer;
                jPlayer["fname"] = player->getFname();
                jPlayer["lname"] = player->getLname();
                jPlayer["license"] = player->getLicense();
                jPlayer["age"] = player->getAge();
                jPlayer["gender"] = player->getGender();
                jPlayer["isTeamLeader"] = player->getIsTeamLeader();

                players.append(jPlayer);
            }

            QJsonObject jTeam;
            jTeam["team name"] = team->getTeamName();
            jTeam["players"] = players;

            teams.append(jTeam);
        }

        QJsonObject phase1;
        phase1["teams"] = teams;

        jsonObject["phase 1"] = phase1;
    }
}

bool Memory::jsonToEvent(QJsonObject &jsonObject, Event *const event, QString &errorMessage) const
{
    int phase;
    if(jsonObject.contains("phase 2"))
    {
        phase = 2;
        QJsonObject phase1 = jsonObject["phase 2"].toObject();
        if(!this->jsonToPhase1(phase1, event, errorMessage))
            return false;
    }
    else if(jsonObject.contains("phase 1"))
    {
        phase = 1;
        QJsonObject phase1 = jsonObject["phase 1"].toObject();
        if(!this->jsonToPhase1(phase1, event, errorMessage))
            return false;
    }
    else
    {
        errorMessage = "";
        return false;
    }

    event->setPhase(phase);

    return true;
}

bool Memory::jsonToPhase1(QJsonObject &phase1, Event *const event, QString &errorMessage) const
{
    QJsonArray teams = phase1["teams"].toArray();

    for(auto _jTeam : teams)
    {
        QJsonObject jTeam = _jTeam.toObject();

        event->createDetachedTeam();
        Team *team = event->getDetachedTeam();
        team->setTeamName( jTeam["team name"].toString() );

        if(!this->jsonToPlayer(jTeam, team, errorMessage))
        {
            team->deleteDetachedPlayer();
            return false;
        }

        event->addTeamUsingDetachedTeam();
    }
    return true;
}

bool Memory::jsonToPlayer(QJsonObject &jTeam, Team *const team, QString &errorMessage) const
{
    QJsonArray players = jTeam["players"].toArray();

    for(auto _jPlayer : players)
    {
        QJsonObject jPlayer = _jPlayer.toObject();

        team->createDetachedPlayer();
        Player *player = team->getDetachedPlayer();
        player->setFname( jPlayer["fname"].toString() );
        player->setLname( jPlayer["lname"].toString() );
        player->setLicense( jPlayer["license"].toString() );
        player->setAge( jPlayer["age"].toString() );
        Player::Genders pg = jPlayer["gender"].toInt() ? Player::Genders::Female : Player::Genders::Male;
        player->setGender( pg );
        player->setIsTeamLeader( jPlayer["isTeamLeader"].toBool() );

        team->addPlayerUsingDetachedPlayer();
    }

    return true;
}
