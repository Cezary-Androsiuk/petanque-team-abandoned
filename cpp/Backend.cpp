#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_event(new Event(this))
{
    this->createExampleData();
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

    QVariantMap teamNames[8] = {
        QVariantMap( {{"team name", "team 1"}} ),
        QVariantMap( {{"team name", "team 2"}} ),
        QVariantMap( {{"team name", "team 3"}} ),
        QVariantMap( {{"team name", "team 4"}} ),
        QVariantMap( {{"team name", "team 5"}} ),
        QVariantMap( {{"team name", "team 6"}} ),
        QVariantMap( {{"team name", "team 7"}} ),
        QVariantMap( {{"team name", "team 8"}} ),
    };
    QVariantMap players[8*6]={
        QVariantMap( {{"fname", "Michael"}, {"lname", "Brown"}, {"license", "L1828"}, {"age", 43}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Williams"}, {"license", "L3119"}, {"age", 23}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "John"}, {"lname", "Anderson"}, {"license", "L4000"}, {"age", 47}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Emma"}, {"lname", "Wilson"}, {"license", "L3017"}, {"age", 23}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Daniel"}, {"lname", "Davis"}, {"license", "L2472"}, {"age", 28}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "John"}, {"lname", "Brown"}, {"license", "L8923"}, {"age", 46}, {"gender", 'M'}} ),

        QVariantMap( {{"fname", "Isabella"}, {"lname", "Williams"}, {"license", "L7277"}, {"age", 38}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Emma"}, {"lname", "Thomas"}, {"license", "L1581"}, {"age", 44}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Sophia"}, {"lname", "Johnson"}, {"license", "L1022"}, {"age", 30}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Thomas"}, {"license", "L3601"}, {"age", 20}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Williams"}, {"license", "L1060"}, {"age", 18}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Sophia"}, {"lname", "Thomas"}, {"license", "L2403"}, {"age", 47}, {"gender", 'M'}} ),

        QVariantMap( {{"fname", "Emma"}, {"lname", "Williams"}, {"license", "L3286"}, {"age", 29}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "David"}, {"lname", "Davis"}, {"license", "L7003"}, {"age", 33}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Olivia"}, {"lname", "Johnson"}, {"license", "L7275"}, {"age", 41}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Miller"}, {"license", "L2834"}, {"age", 20}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "David"}, {"lname", "Brown"}, {"license", "L9907"}, {"age", 50}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Chris"}, {"lname", "Anderson"}, {"license", "L4332"}, {"age", 28}, {"gender", 'M'}} ),

        QVariantMap( {{"fname", "John"}, {"lname", "Moore"}, {"license", "L9791"}, {"age", 43}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "John"}, {"lname", "Williams"}, {"license", "L3168"}, {"age", 18}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Chris"}, {"lname", "Davis"}, {"license", "L3581"}, {"age", 46}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "John"}, {"lname", "Miller"}, {"license", "L6838"}, {"age", 21}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Sophia"}, {"lname", "Moore"}, {"license", "L4738"}, {"age", 45}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Olivia"}, {"lname", "Miller"}, {"license", "L7759"}, {"age", 30}, {"gender", 'M'}} ),

        QVariantMap( {{"fname", "Emily"}, {"lname", "Davis"}, {"license", "L9489"}, {"age", 25}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Miller"}, {"license", "L6546"}, {"age", 23}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Ava"}, {"lname", "Taylor"}, {"license", "L9274"}, {"age", 50}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Sophia"}, {"lname", "Smith"}, {"license", "L8696"}, {"age", 21}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Daniel"}, {"lname", "Smith"}, {"license", "L4830"}, {"age", 36}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Thomas"}, {"license", "L5877"}, {"age", 41}, {"gender", 'F'}} ),

        QVariantMap( {{"fname", "David"}, {"lname", "Anderson"}, {"license", "L5177"}, {"age", 38}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Olivia"}, {"lname", "Miller"}, {"license", "L9196"}, {"age", 36}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Emma"}, {"lname", "Brown"}, {"license", "L2400"}, {"age", 34}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Chris"}, {"lname", "Johnson"}, {"license", "L2216"}, {"age", 26}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Williams"}, {"license", "L8053"}, {"age", 25}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Emma"}, {"lname", "Moore"}, {"license", "L4951"}, {"age", 45}, {"gender", 'F'}} ),

        QVariantMap( {{"fname", "Daniel"}, {"lname", "Moore"}, {"license", "L3530"}, {"age", 25}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Daniel"}, {"lname", "Moore"}, {"license", "L7605"}, {"age", 45}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Brown"}, {"license", "L8251"}, {"age", 35}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "James"}, {"lname", "Brown"}, {"license", "L5737"}, {"age", 24}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Emma"}, {"lname", "Smith"}, {"license", "L5452"}, {"age", 29}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "Chris"}, {"lname", "Miller"}, {"license", "L6121"}, {"age", 24}, {"gender", 'F'}} ),

        QVariantMap( {{"fname", "Ava"}, {"lname", "Miller"}, {"license", "L5907"}, {"age", 29}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Ava"}, {"lname", "Miller"}, {"license", "L7026"}, {"age", 37}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Michael"}, {"lname", "Williams"}, {"license", "L7350"}, {"age", 35}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Ava"}, {"lname", "Smith"}, {"license", "L8990"}, {"age", 34}, {"gender", 'M'}} ),
        QVariantMap( {{"fname", "David"}, {"lname", "Johnson"}, {"license", "L1413"}, {"age", 38}, {"gender", 'F'}} ),
        QVariantMap( {{"fname", "Olivia"}, {"lname", "Thomas"}, {"license", "L4110"}, {"age", 46}, {"gender", 'F'}} ),
    };

    for(int i=0; i<8; i++)
    {
        m_event->createDetachedTeam();
        Team *dTeam = m_event->getDetachedTeam();
        dTeam->setTeamName( teamNames[i]["team name"].toString() );

        for(int j=0; j<6; j++)
        {
            dTeam->createDetachedPlayer();
            Player *dPlayer = dTeam->getDetachedPlayer();

            int h = i * 6 + j;
            dPlayer->setFname( players[h]["fname"].toString() );
            dPlayer->setLname( players[h]["lname"].toString() );
            dPlayer->setLicense( players[h]["license"].toString() );
            dPlayer->setAge( players[h]["age"].toString() );
            QChar g = players[h]["gender"].toChar();
            Player::Genders pg = g == 'M' ? Player::Genders::Male : Player::Genders::Female;
            dPlayer->setGender( pg );

            dTeam->addPlayerUsingDetachedPlayer();
        }

        m_event->addTeamUsingDetachedTeam();
    }
}

void Backend::validateData()
{
    // check if both genders belong to each team
    // check if in each team, are at least 6 players
    // check if each team choosed captain
    // (additional) check if in each team, captain was choosed only once
    // check if there are at least 8 teams (some of them could be checked as "not playing")

    emit this->dataValidatedCorrectly();
}
