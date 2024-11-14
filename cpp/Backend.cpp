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
    m_event->blockSignals(true);

    QJsonArray jTeams = Personalization::getInstance()->getExampleData()["teams"].toArray();
    for(int i=0; i<jTeams.size(); i++)
    {
        QJsonObject jTeam = jTeams[i].toObject();

        m_event->createDetachedTeam();
        Team *team = m_event->getDetachedTeam();
        team->blockSignals(true);

        team->setTeamName( jTeam["team name"].toString() );

        QJsonArray jPlayers = jTeam["players"].toArray();
        for(int j=0; j<jPlayers.size(); j++)
        {
            QJsonObject jPlayer = jPlayers[j].toObject();

            team->createDetachedPlayer();
            Player *player = team->getDetachedPlayer();

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

        m_event->addTeamUsingDetachedTeam();
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
