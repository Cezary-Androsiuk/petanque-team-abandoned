#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_event(new Event(this))
{
    // this->createExampleData();
}

Backend::~Backend()
{

}

Event *Backend::getEvent() const
{
    return m_event;
}

void Backend::createExampleData()
{
    m_event->clearEvent();

    const QJsonObject &exampleData = Personalization::getInstance()->getExampleData();
    QJsonArray teams = exampleData["teams"].toArray();
    int ti = 0;
    m_event->blockSignals(true);
    for(const auto &_team : teams)
    {
        QJsonObject team = _team.toObject();

        m_event->createDetachedTeam();
        Team *dTeam = m_event->getDetachedTeam();
        dTeam->setTeamName( team["team name"].toString() );

        QJsonArray players = team["players"].toArray();
        int pi = 0;
        for(const auto &_player : players)
        {
            QJsonObject player = _player.toObject();

            dTeam->createDetachedPlayer();
            Player *dPlayer = dTeam->getDetachedPlayer();

            dPlayer->setFname( player["fname"].toString() );
            dPlayer->setLname( player["lname"].toString() );
            dPlayer->setLicense( player["license"].toString() );
            dPlayer->setAgeGroup( player["age group"].toInt() );
            dPlayer->setGender( player["gender"].toInt() );
            dPlayer->setIsTeamLeader( player["isTeamLeader"].toBool() );

            dTeam->addPlayerUsingDetachedPlayer();
            D(QAPF("created player %d", ++pi));
        }

        m_event->addTeamUsingDetachedTeam();
        D(QAPF("created team %d", ++ti));
    }
    m_event->blockSignals(false);
    emit m_event->teamsChanged();
}

void Backend::validateData()
{
    /// this should be called only after starting the event

    Personalization *p = Personalization::getInstance();

    /// check if 8 teams was registered
    int teamsCount = m_event->getTeams().size();
    if(teamsCount != p->getRequiredTeamsCount())
    {
        /// less or more than 8 teams
        QString message = tr("Event requires %1 teams").arg(p->getRequiredTeamsCount());
        I(message);
        emit this->dataValidationFailed(message);
        return;
    }

    /// check data for teams:
    for(Team *team : m_event->getTeams())
    {
        /// check if team has at least 6 players
        int playersCount = team->getPlayers().size();
        if(playersCount < p->getMinimumPlayersInTeam())
        {
            /// team has least than 6 players
            QString message = tr("Team %1 has less than %2 players")
                                  .arg(team->getTeamName())
                                  .arg(p->getMinimumPlayersInTeam());
            I(message);
            emit this->dataValidationFailed(message);
            return;
        }

        /// check if team has both genders
        bool foundMale = false;
        bool foundFemale = false;
        for(Player *player : team->getPlayers())
        {
            if(player->getGender() == Player::Gender::Male)
                foundMale = true;

            if(player->getGender() == Player::Gender::Female)
                foundFemale = true;
        }
        if(!foundMale || !foundFemale)
        {
            /// one gender is missing in team
            QString message = tr("Team %1 doesn't contain players of either gender")
                                  .arg(team->getTeamName());
            I(message);
            emit this->dataValidationFailed(message);
            return;
        }

        /// check if team has junior
        if(p->getRequiresJuniors())
        {
            bool foundJunior = false;
            for(Player *player : team->getPlayers())
            {
                if(player->getAgeGroup() == Player::AgeGroup::Junior)
                {
                    foundJunior = true;
                    break;
                }
            }

            if(!foundJunior)
            {
                /// junior player is missing in team
                QString message = tr("Team %1 doesn't contain any junior player")
                                      .arg(team->getTeamName());
                I(message);
                emit this->dataValidationFailed(message);
                return;
            }
        }

        /// check if team has one leader
        int foundLeaders = 0;
        for(Player *player : team->getPlayers())
        {
            if(player->getIsTeamLeader())
                ++ foundLeaders;
        }
        if(foundLeaders == 0)
        {
            /// team missing leader
            QString message = tr("In team %1, no leader was selected")
                                  .arg(team->getTeamName());
            I(message);
            emit this->dataValidationFailed(message);
            return;
        }
        if(foundLeaders > 1)
        {
            /// team contains few leaders
            QString message = tr("Team %1 has few leaders")
                                  .arg(team->getTeamName());
            I(message);
            emit this->dataValidationFailed(message);
            return;
        }
    }


    emit this->dataValidatedCorrectly();
}

bool Backend::debugMemoryFileExist()
{
    QString memoryFile("./memory/PetanqueMemory.json");
    return QFileInfo::exists(memoryFile);
}

void Backend::debugDeleteMemory()
{
    QString memoryFile("./memory/PetanqueMemory.json");
    QFile::remove(memoryFile);
}

// QString Backend::isSelectionDataValid(QVariantList data, int groupSize, int groupsCount)
// {
//     int rowIndex = 0;
//     constexpr int maxGroupsCount = 6;
//     int playersCountInGroups[maxGroupsCount] = {0};
//     QString messageError("");

//     for(const QVariant &qv : data)
//     {
//         /// assign values from data to variable local
//         int containsTrueCount = 0;
//         QVariantMap qvmap = qv.toMap();
//         for(int i=0; i<groupsCount; i++)
//         {
//             int dataRow = qvmap[ QString::number(i+1) ].toBool() ?1:0;
//             /// and add to row counter
//             containsTrueCount += dataRow;
//             /// add values to column counter
//             playersCountInGroups[i] += dataRow;
//         }

//         /// i don't trust qml
//         /// test if in each row, has 0 or 1 radio buttons selected
//         if(containsTrueCount > 1)
//         {
//             messageError = "To much radio buttons selected in " + QString::number(rowIndex++) + " row index";
//             W(messageError)
//             return messageError;
//         }
//     }

//     /// test if each column contains required count of choosed players
//     if(groupSize == 3)
//     {
//         /// test if in each column, 3 or 4 players were selected for triplets
//         constexpr int requiredPlayers = 3;
//         for(int i=0; i<groupsCount; i++)
//         {
//             int playersCountInGroup = playersCountInGroups[i];
//             if(playersCountInGroup == requiredPlayers || playersCountInGroup == requiredPlayers+1)
//                 continue;

//             messageError = "in group " + QString::number(i+1) + ", " + QString::number(playersCountInGroup) +
//                            " players where selected, but " + QString::number(requiredPlayers) + " or " +
//                            QString::number(requiredPlayers+1) + " were expected";
//             I(messageError);
//             return messageError;
//         }
//     }
//     else
//     if(groupSize == 2)
//     {
//         /// test if in each column, 2 or 3 players were selected for triplets
//         constexpr int requiredPlayers = 2;
//         for(int i=0; i<groupsCount; i++)
//         {
//             int playersCountInGroup = playersCountInGroups[i];
//             if(playersCountInGroup == requiredPlayers || playersCountInGroup == requiredPlayers+1)
//                 continue;

//             messageError = "in group " + QString::number(i+1) + ", " + QString::number(playersCountInGroup) +
//                            " players where selected, but " + QString::number(requiredPlayers) + " or " +
//                            QString::number(requiredPlayers+1) + " were expected";
//             I(messageError);
//             return messageError;
//         }
//     }
//     else
//     // groupSize == 1
//     {
//         /// test if in each column, 1 player was selected for singiels
//         constexpr int requiredPlayers = 1;
//         for(int i=0; i<groupsCount; i++)
//         {
//             int playersCountInGroup = playersCountInGroups[i];
//             if(playersCountInGroup == requiredPlayers)
//                 continue;

//             messageError = "in group " + QString::number(i+1) + ", " +
//                            QString::number(playersCountInGroup) +
//                            " players where selected, but 1 was expected";
//             I(messageError);
//             return messageError;
//         }
//     }

//     return messageError;
// }
