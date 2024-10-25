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
    for(const auto &_team : teams)
    {
        QJsonObject team = _team.toObject();

        m_event->createDetachedTeam();
        Team *dTeam = m_event->getDetachedTeam();
        dTeam->setTeamName( team["team name"].toString() );

        QJsonArray players = team["players"].toArray();
        for(const auto &_player : players)
        {
            QJsonObject player = _player.toObject();

            dTeam->createDetachedPlayer();
            Player *dPlayer = dTeam->getDetachedPlayer();

            dPlayer->setFname( player["fname"].toString() );
            dPlayer->setLname( player["lname"].toString() );
            dPlayer->setLicense( player["license"].toString() );
            dPlayer->setAge( player["age"].toString() );
            QChar g = player["gender"].toString()[0];
            Player::Genders pg = g == 'M' ? Player::Genders::Male : Player::Genders::Female;
            dPlayer->setGender( pg );
            dPlayer->setIsTeamLeader( player["isTeamLeader"].toBool() );

            dTeam->addPlayerUsingDetachedPlayer();
        }

        m_event->addTeamUsingDetachedTeam();
    }
}

void Backend::validateData()
{
    /// this should be called only after starting the event

    /// check if 8 teams was registered
    int teamsCount = m_event->getTeams().size();
    if(teamsCount != REQUIRED_TEAMS_COUNT)
    {
        /// less or more than 8 teams
        QString message = tr("Event requires 8 teams");
        I(message);
        emit this->dataValidationFailed(message);
        return;
    }

    /// check data for teams:
    for(Team *team : m_event->getTeams())
    {
        /// check if team has at least 6 players
        int playersCount = team->getPlayers().size();
        if(playersCount < REQUIRED_PLAYERS_COUNT)
        {
            /// team has least than 6 players
            QString message = tr("Team %1 has less than %2 players")
                                  .arg(team->getTeamName())
                                  .arg(REQUIRED_PLAYERS_COUNT);
            I(message);
            emit this->dataValidationFailed(message);
            return;
        }

        /// check if team has both genders
        bool foundMale = false;
        bool foundFemale = false;
        for(Player *player : team->getPlayers())
        {
            if(player->getGender() == Player::Genders::Male)
                foundMale = true;

            if(player->getGender() == Player::Genders::Female)
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
