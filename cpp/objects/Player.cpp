#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
    , m_playerID(0)
    , m_isTeamLeader(false)
{}

void Player::copyFromOtherPlayer(const Player &sourcePlayer)
{
    if(this == &sourcePlayer)
        return;

    m_playerID = sourcePlayer.m_playerID;
    m_fname = sourcePlayer.m_fname;
    m_lname = sourcePlayer.m_lname;
    m_license = sourcePlayer.m_license;
    m_ageGroup = sourcePlayer.m_ageGroup;
    m_gender = sourcePlayer.m_gender;
    m_isTeamLeader = sourcePlayer.m_isTeamLeader;

    emit this->fnameChanged();
    emit this->lnameChanged();
    emit this->licenseChanged();
    emit this->ageGroupChanged();
    emit this->genderChanged();
    emit this->isTeamLeaderChanged();
}

QObject *Player::getParent() const
{
    return this->parent();
}

uint Player::getPlayerID() const
{
    return m_playerID;
}

QString Player::getFname() const
{
    return m_fname;
}

QString Player::getLname() const
{
    return m_lname;
}

QString Player::getLicense() const
{
    return m_license;
}

int Player::getAgeGroup() const
{
    return m_ageGroup;
}

int Player::getGender() const
{
    return m_gender;
}

bool Player::getIsTeamLeader() const
{
    return m_isTeamLeader;
}

void Player::setPlayerID(uint playerID)
{
    if(m_playerID == playerID)
        return;

    m_playerID = playerID;
}

void Player::setFname(const QString &fname)
{
    if (m_fname == fname)
        return;
    m_fname = fname;
    emit fnameChanged();
}

void Player::setLname(const QString &lname)
{
    if (m_lname == lname)
        return;
    m_lname = lname;
    emit lnameChanged();
}

void Player::setLicense(const QString &license)
{
    if (m_license == license)
        return;
    m_license = license;
    emit licenseChanged();
}

void Player::setAgeGroup(int ageGroup)
{
    if (m_ageGroup == ageGroup)
        return;
    m_ageGroup = ageGroup;
    emit ageGroupChanged();
}

void Player::setGender(const int &gender)
{
    if (m_gender == gender)
        return;
    m_gender = gender;
    emit genderChanged();
}

void Player::setIsTeamLeader(bool isTeamLeader)
{
    if (m_isTeamLeader == isTeamLeader)
        return;
    m_isTeamLeader = isTeamLeader;
    emit isTeamLeaderChanged();
}
