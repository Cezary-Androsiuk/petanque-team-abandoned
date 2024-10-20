#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
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
}

QString Player::getFname() const
{
    return m_fname;
}

QString Player::getLname() const
{
    return m_lname;
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
