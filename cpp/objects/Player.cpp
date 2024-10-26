#include "Player.h"

const QRegularExpression Player::m_birthDateRegex(R"(\d{4}-\d{2}-\d{2})");

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
    m_birthDate = sourcePlayer.m_birthDate;
    m_gender = sourcePlayer.m_gender;
    m_isTeamLeader = sourcePlayer.m_isTeamLeader;

    emit this->fnameChanged();
    emit this->lnameChanged();
    emit this->licenseChanged();
    emit this->birthDateChanged();
    emit this->genderChanged();
    emit this->isTeamLeaderChanged();
}

QObject *Player::getParent() const
{
    return this->parent();
}

int Player::birthDateIsValid() const
{
    QRegularExpressionMatch rMatch = m_birthDateRegex.match(m_birthDate);
    bool matchLength = rMatch.capturedLength() == m_birthDate.length();
    bool match = rMatch.hasMatch() && matchLength;
    if(!match)
        return 1;

    QDate date = this->getBirthDateAsDate();
    if(!date.isValid())
        return 2;

    if(date >= QDate::currentDate() || date < QDate(1800, 01, 01))
        return 3;

    return 0;
}

QDate Player::getBirthDateAsDate() const
{
    QStringList timeValues = m_birthDate.split('-');
    int year = timeValues[0].toInt();
    int month = timeValues[1].toInt();
    int day = timeValues[2].toInt();
    return QDate(year, month, day);
}

int Player::getAgeInYears() const
{
    QDate birthDate = this->getBirthDateAsDate();
    QDate currentDate = QDate::currentDate();
    int age = currentDate.year() - birthDate.year();

    /// the "birthday this year has not happened yet" case
    bool beforeMonth = currentDate.month() < birthDate.month();
    bool beforeDay = currentDate.month() == birthDate.month() && currentDate.day() < birthDate.day();
    if(beforeMonth || beforeDay)
        age --;

    return age;
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

QString Player::getBirthDate() const
{
    return m_birthDate;
}

Player::Genders Player::getGender() const
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

void Player::setBirthDate(QString birthDate)
{
    if (m_birthDate == birthDate)
        return;
    m_birthDate = birthDate;
    emit birthDateChanged();
}

void Player::setGender(const Player::Genders &gender)
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
