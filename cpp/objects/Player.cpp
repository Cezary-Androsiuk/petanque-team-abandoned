#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{}

void Player::fromOtherPlayer(const Player &player)
{
    if(this == &player)
        return;


}

// Player &Player::operator =(const Player &player)
// {
//     if(this == &player)
//         return *this;
//     return *this;
// }
