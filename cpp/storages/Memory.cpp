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
    this->jsonToEvent(jsonObject, m_backend->getEvent());

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

void Memory::jsonToEvent(const QJsonObject &jsonObject, Event *const event) const
{
    event->clearEvent();


    { /// Phase 1
        event->setPhase(Event::Phase::First); /// thanks to my genius detached Team algorithm... ough...
        QJsonObject phase = jsonObject["first phase data"].toObject();
        this->jsonToTeams(phase["teams"].toArray(), event);
        this->jsonToMatches(phase["matches"].toArray(), event);
    }

    { /// Phase 2
        event->setPhase(Event::Phase::Second); /// thanks to my genius detached Team algorithm... ough...
        QJsonObject phase = jsonObject["second phase data"].toObject();
        this->jsonToTeams(phase["teams"].toArray(), event);
        this->jsonToMatches(phase["matches"].toArray(), event);
    }

    event->setPhase( static_cast<Event::Phase>( jsonObject["phase"].toInt() ) );
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

}

void Memory::jsonToTeams(const QJsonArray &jTeams, Event *const event) const
{
    event->blockSignals(true);

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
}

void Memory::jsonToMatches(const QJsonArray &jMatches, Event *const event) const
{
    for(int i=0; i<jMatches.size(); i++)
    {
        QJsonObject jMatch = jMatches[i].toObject();

        Match *match = event->createNewMatch(false);

        QJsonArray jMatchTeamList = jMatch["match team list"].toArray();
        if(match->getMatchTeamList().size() != jMatchTeamList.size())
        {
            W("match team list size: " + QString::number(match->getMatchTeamList().size()) + ", jMatchTeams size: " + QString::number(jMatchTeamList.size()))
            return;
        }
        for(int j=0; j<jMatchTeamList.size(); j++)
        {
            MatchTeam *matchTeam = match->getMatchTeamList()[j];
            QJsonObject jMatchTeam = jMatchTeamList[j].toObject();
            const QJsonObject jMatchType[3] = {
               jMatchTeam["triplets"].toObject(),
               jMatchTeam["dublets"].toObject(),
               jMatchTeam["singiels"].toObject()
            };
            MatchTypeBase *const matchType[3] = {
                matchTeam->getMatchType(1),
                matchTeam->getMatchType(2),
                matchTeam->getMatchType(3)
            };


            for(int h=0; h<3; h++)
            {
                this->jsonToMatchType(jMatchType[h], matchType[h]);
            }
        }

        if(!jMatch.contains("match combinations"))
            continue;

        QJsonArray jMatchCombinations = jMatch["match combinations"].toArray();
        for(int j=0; j<jMatchCombinations.size(); j++)
        {
            QJsonObject jCombination = jMatchCombinations[j].toObject();
            match->addMatchCombination(jCombination["teamIndex1"].toInt(), jCombination["teamIndex2"].toInt());
        }
    }
}

void Memory::jsonToMatchType(const QJsonObject &jMatchType, MatchTypeBase * const matchType) const
{
    if(matchType == nullptr)
    {
        W("cannot initialize match type values, because matchType variable is a null");
        return;
    }

    QJsonObject jSelection = jMatchType["selection"].toObject();
    QJsonArray jSelectionValues = jSelection["values"].toArray();
    // row and column was set in createNewMatch method;
    // just set the values

    Selection *const s = matchType->getSelection();
    for(int r=0; r<jSelectionValues.size(); r++)
    {
        QJsonArray jSelectionColumns = jSelectionValues[r].toArray();
        for(int c=0; c<jSelectionColumns.size(); c++)
        {
            bool v = jSelectionColumns[c].toBool();
            s->setValueForCell(r, c, v);
        }
    }


    QJsonObject jMatchPoints = jMatchType["match points"].toObject();
    QJsonArray jMatchPointsPoints = jMatchPoints["points"].toArray();
    // row was set in createNewMatch method;
    // just set the values

    MatchPoints *const mp = matchType->getMatchPoints();
    for(int r=0; r<jMatchPointsPoints.size(); r++)
    {
        int v = jMatchPointsPoints[r].toInt();
        mp->setPointsForGroup(r, v);
    }
}

void Memory::eventToJson(Event *const event, QJsonObject &jsonObject) const
{
    jsonObject["phase"] = event->getPhase();

    { /// Phase 1
        QJsonObject phase;

        QJsonArray jTeams;
        this->teamsToJson(event->getTeamsP1(), jTeams);
        phase["teams"] = jTeams;

        QJsonArray jMatches;
        this->matchesToJson(event->getMatchesP1(), jMatches);
        phase["matches"] = jMatches;

        jsonObject["first phase data"] = phase;
    }

    { /// Phase 2
        QJsonObject phase;

        QJsonArray jTeams;
        this->teamsToJson(event->getTeamsP2(), jTeams);
        phase["teams"] = jTeams;

        QJsonArray jMatches;
        this->matchesToJson(event->getMatchesP2(), jMatches);
        phase["matches"] = jMatches;

        jsonObject["second phase data"] = phase;
    }

    /// move following to the phases
    jsonObject["name"] = event->getName();
    jsonObject["date phase 1"] = event->getFirstPhaseDate();
    jsonObject["date phase 2"] = event->getSecondPhaseDate();
    jsonObject["competition organizer"] = event->getCompetitionOrganizer();
    jsonObject["place phase 1"] = event->getFirstPhasePlace();
    jsonObject["place phase 2"] = event->getSecondPhasePlace();
    QJsonArray judges;
    for(const QString &judge : event->getJudges())
        judges.append(judge);
    jsonObject["judges"] = judges;
    jsonObject["union delegate"] = event->getUnionDelegate();
    jsonObject["stage"] = event->getStage();
    jsonObject["round"] = event->getRound();
    jsonObject["round stage"] = event->getRoundStage();
}

void Memory::teamsToJson(TeamList &teamList, QJsonArray &jTeams) const
{
    for(Team *team : teamList)
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

        QJsonObject jTeam;
        jTeam["teamID"] = static_cast<int>(team->getTeamID());
        jTeam["teamName"] = team->getTeamName();
        jTeam["players"] = players;

        jTeams.append(jTeam);
    }
}

void Memory::matchesToJson(MatchList &matchList, QJsonArray &jMatches) const
{
    for(Match *match : matchList)
    {
        QJsonObject jMatch;
        QJsonArray jMatchTeamList;
        for(MatchTeam *matchTeam : match->getMatchTeamList())
        {
            QJsonObject jMatchTeam;
            QJsonObject jMatchType[3];
            MatchTypeBase *const matchType[3] = {
                matchTeam->getMatchType(1),
                matchTeam->getMatchType(2),
                matchTeam->getMatchType(3)
            };

            for(int i=0; i<3; i++)
            {
                this->matchTypeToJson(matchType[i], jMatchType[i]);
            }

            jMatchTeam["triplets"] = jMatchType[0];
            jMatchTeam["dublets"] = jMatchType[1];
            jMatchTeam["singiels"] = jMatchType[2];
            jMatchTeamList.append(jMatchTeam);
        }
        jMatch["match team list"] = jMatchTeamList;

        QJsonArray jMatchCombinations;
        for(auto &[teamIndex1, teamIndex2] : match->getMatchCombinations())
        {
            QJsonObject jCombination;
            jCombination["teamIndex1"] = teamIndex1;
            jCombination["teamIndex2"] = teamIndex2;
            jMatchCombinations.append(jCombination);
        }
        jMatch["match combinations"] = jMatchCombinations;

        jMatches.append(jMatch);
    }
}

void Memory::matchTypeToJson(MatchTypeBase * const matchType, QJsonObject &jMatchType) const
{
    if(matchType == nullptr)
    {
        W("cannot read match type values, because matchType variable is a null");
        return;
    }

    QJsonObject jSelection;
    {
        Selection *s = matchType->getSelection();
        QJsonArray jSelectionValues;
        for(auto &row : s->getValues())
        {
            QJsonArray jSelectionValuesColumns;
            for(bool value : row)
            {
                jSelectionValuesColumns.append(value);
            }
            jSelectionValues.append(jSelectionValuesColumns);
        }

        jSelection["values"] = jSelectionValues;
        // jSelection["rows"] = static_cast<int>(s->getPlayersCount());
        // jSelection["columns"] = static_cast<int>(s->getGroupsCount());
    }
    jMatchType["selection"] = jSelection;

    QJsonObject jMatchPoints;
    {
        MatchPoints *mp = matchType->getMatchPoints();
        QJsonArray jMatchPointsPoints;
        for(int playerPoints : mp->getPoints())
        {
            jMatchPointsPoints.append(playerPoints);
        }
        jMatchPoints["points"] = jMatchPointsPoints;
        // jMatchPoints["rows"] = static_cast<int>(mp->getGroupsCount());
    }

    jMatchType["match points"] = jMatchPoints;
}
