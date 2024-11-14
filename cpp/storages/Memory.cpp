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
    // I("Loading memory")
    if(!QFileInfo::exists( MEMORY_FILE ))
    {
        I("Memory file not exist");
        emit this->memoryFileNotExist();
        return;
    }

    if(m_backend == nullptr)
    {
        QString message("Backend value is NULL!");
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    m_backend->getEvent()->clearEvent();

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

    I("Memory loaded");
    emit this->memoryLoaded();
}

void Memory::save(bool reloadAfterSaved)
{
    // I("Saving memory")
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

    // m_backend->getEvent()->clearEvent();
    I("Memory saved")
    emit this->memorySaved(reloadAfterSaved);
}

void Memory::setBackendPtr(Backend *backend)
{
    m_backend = backend;
}

void Memory::eventToJson(const Event *const event, QJsonObject &jsonObject) const
{
    Event::Phase phase = event->getPhase();
    if(phase == Event::Phase::First)
    {
        QJsonObject phase1;

        QJsonArray teams;
        for(Team *team : event->getTeams())
        {
            QJsonArray players;
            for(Player *player : team->getPlayers())
            {
                QJsonObject jPlayer;
                jPlayer["playerID"] = static_cast<int>(player->getPlayerID());
                jPlayer["fname"] = player->getFname();
                jPlayer["lname"] = player->getLname();
                jPlayer["license"] = player->getLicense();
                jPlayer["age group"] = player->getAgeGroup();
                jPlayer["gender"] = player->getGender();
                jPlayer["isTeamLeader"] = player->getIsTeamLeader();

                players.append(jPlayer);
            }
            // D("saved " + QString::number(players.size()) + " players")

            QJsonObject jTeam;
            jTeam["teamID"] = static_cast<int>(team->getTeamID());
            jTeam["teamName"] = team->getTeamName();
            jTeam["players"] = players;

            teams.append(jTeam);
        }
        phase1["teams"] = teams;
        // D("saved " + QString::number(teams.size()) + " teams")

        QJsonArray jMatches;
        for(const Match *match : event->getMatches())
        {
            QJsonArray jMatchTeams;
            for(const MatchTeam *matchTeam : match->getMatchTeams())
            {
                QJsonObject jMatchTeam;
                QJsonObject jMatchTypeBase[3];
                const MatchTypeBase *const matchTeamBase[3] = {
                    matchTeam->getTriplets(),
                    matchTeam->getDublets(),
                    matchTeam->getSingiels()
                };

                for(int i=0; i<3; i++)
                {
                    QJsonArray jSelectionRows;
                    for(const auto &row : matchTeamBase[i]->getSelection())
                    {
                        QJsonArray jSelectionColumns;
                        for(bool column : row)
                            jSelectionColumns.append(column);
                        jSelectionRows.append(jSelectionColumns);
                    }

                    jMatchTypeBase[i]["selection"] = jSelectionRows;
                    jMatchTypeBase[i]["rows"] = static_cast<int>(matchTeamBase[i]->getRows());
                    jMatchTypeBase[i]["columns"] = static_cast<int>(matchTeamBase[i]->getColumns());

                }

                jMatchTeam["triplets"] = jMatchTypeBase[0];
                jMatchTeam["dublets"] = jMatchTypeBase[1];
                jMatchTeam["singiels"] = jMatchTypeBase[2];
                jMatchTeams.append(jMatchTeam);
            }
            jMatches.append(jMatchTeams);
        }
        phase1["matches"] = jMatches;

        jsonObject["phase first"] = phase1;

        jsonObject["name"] = event->getName();
        jsonObject["first phhase date"] = event->getFirstPhaseDate();
        jsonObject["second phase date"] = event->getSecondPhaseDate();
        jsonObject["competition organizer"] = event->getCompetitionOrganizer();
        jsonObject["first phase place"] = event->getFirstPhasePlace();
        jsonObject["second phase place"] = event->getSecondPhasePlace();
        QJsonArray judges;
        for(const QString &judge : event->getJudges())
            judges.append(judge);
        jsonObject["judges"] = judges;
        jsonObject["union delegate"] = event->getUnionDelegate();
        jsonObject["stage"] = event->getStage();
        jsonObject["round"] = event->getRound();
        jsonObject["round stage"] = event->getRoundStage();

        // D("saved phase " + QString::number(jsonObject["phase first"].toInt()))
        // D("saved " + QString::number(judges.size()) + " judges")
        // D("saved round " + QString::number(jsonObject["round"].toInt()))
        // D("saved round stage " + QString::number(jsonObject["round stage"].toInt()))
    }
}

bool Memory::jsonToEvent(QJsonObject &jsonObject, Event *const event, QString &errorMessage) const
{
    Event::Phase phase;
    if(jsonObject.contains("phase second"))
    {
        phase = Event::Phase::Second;
        // QJsonObject phase2 = jsonObject["phase second"].toObject();
        // if(!this->jsonToPhase2(phase2, event, errorMessage))
        //     return false;
    }
    else if(jsonObject.contains("phase first"))
    {
        phase = Event::Phase::First;
        QJsonObject phase1 = jsonObject["phase first"].toObject();
        if(!this->jsonToPhase1(phase1, event, errorMessage))
            return false;
    }
    else
    {
        errorMessage = "No phase was found";
        return false;
    }

    event->setPhase(phase);

    event->setName( jsonObject["name"].toString() );
    event->setFirstPhaseDate( jsonObject["first phhase date"].toString() );
    event->setSecondPhaseDate( jsonObject["second phase date"].toString() );
    event->setCompetitionOrganizer( jsonObject["competition organizer"].toString() );
    event->setFirstPhasePlace( jsonObject["first phase place"].toString() );
    event->setSecondPhasePlace( jsonObject["second phase place"].toString() );
    QJsonArray jsonJudges = jsonObject["judges"].toArray();
    QStringList judges;
    for(auto jJudge : jsonJudges)
        judges.append( jJudge.toString() );
    event->setJudges( judges );
    event->setUnionDelegate( jsonObject["union delegate"].toString() );
    event->setStage( static_cast<Event::Stage>( jsonObject["stage"].toInt() ) );
    event->setRound( jsonObject["round"].toInt() );
    event->setRoundStage( static_cast<Event::RoundStage>( jsonObject["round stage"].toInt() ) );


    // D("loaded phase " + QString::number(event->getPhase()))
    // D("loaded " + QString::number(judges.size()) + " judges")
    // D("loaded round " + QString::number(event->getRound()))
    // D("loaded round stage " + QString::number(event->getRoundStage()))

    return true;
}

bool Memory::jsonToPhase1(QJsonObject &phase1, Event *const event, QString &errorMessage) const
{
    event->clearEvent();
    event->blockSignals(true);

    QJsonArray jTeams = phase1["teams"].toArray();
    for(int i=0; i<jTeams.size(); i++)
    {
        QJsonObject jTeam = jTeams[i].toObject();

        event->createDetachedTeam();
        Team *team = event->getDetachedTeam();
        team->blockSignals(true);

        team->setTeamName( jTeam["teamName"].toString() );
        team->setTeamID( static_cast<uint>(jTeam["teamID"].toInt()) );

        QJsonArray jPlayers = jTeam["players"].toArray();
        for(int j=0; j<jPlayers.size(); j++)
        {
            QJsonObject jPlayer = jPlayers[j].toObject();

            team->createDetachedPlayer();
            Player *player = team->getDetachedPlayer();
            player->setPlayerID( static_cast<uint>(jPlayer["playerID"].toInt()) );
            player->setFname( jPlayer["fname"].toString() );
            player->setLname( jPlayer["lname"].toString() );
            player->setLicense( jPlayer["license"].toString() );
            player->setAgeGroup( jPlayer["age group"].toInt() );
            player->setGender( jPlayer["gender"].toInt() );
            player->setIsTeamLeader( jPlayer["isTeamLeader"].toBool() );

            team->addPlayerUsingDetachedPlayer();
        }

        team->blockSignals(false);
        emit team->playersChanged();

        event->addTeamUsingDetachedTeam();
    }

    event->blockSignals(false);
    emit event->teamsChanged();

    // D("loaded " + QString::number(event->getTeams().size()) + " teams")
    return true;
}
