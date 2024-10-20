#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
    , m_age(-1)
{}

// Player &Player::operator =(const Player &player)
// {
//     if(this == &player)
//         return *this;
//     return *this;
// }

void Player::copyFromOtherPlayer(const Player &player)
{
    if(this == &player)
        return;

    this->setFname(player.getFname());
    this->setLname(player.getLname());
    this->setLicense(player.getLicense());
    this->setAge(player.getAge());
    this->setGender(player.getGender());
    this->setIsTeamCaptain(player.getIsTeamCaptain());
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

QString Player::getAge() const
{
    return QString::number(m_age);
}

Player::Genders Player::getGender() const
{
    return m_gender;
}

bool Player::getIsTeamCaptain() const
{
    return m_isTeamCaptain;
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

void Player::setAge(QString age)
{
    bool ok;
    int intAge = age.toInt(&ok);
    if(!ok)
    {
        W("cannot convert '" +age+ "' to int")
        return;
    }

    if (m_age == intAge)
        return;
    m_age = intAge;
    emit ageChanged();
}

void Player::setGender(const Player::Genders &gender)
{
    if (m_gender == gender)
        return;
    m_gender = gender;
    emit genderChanged();
}

void Player::setIsTeamCaptain(bool isTeamCaptain)
{
    if (m_isTeamCaptain == isTeamCaptain)
        return;
    m_isTeamCaptain = isTeamCaptain;
    emit isTeamCaptainChanged();
}
