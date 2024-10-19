#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "cpp/support/Log.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    // Player &operator = (const Player &player);
    void fromOtherPlayer(const Player &player);

signals:


};

#endif // PLAYER_H
