#ifndef MATCHTEAM_H
#define MATCHTEAM_H

#include <QObject>
#include <QList>

#include "cpp/objects/MatchTriplets.h"
#include "cpp/objects/MatchDublets.h"
#include "cpp/objects/MatchSingiels.h"

class MatchTeam : public QObject
{
    Q_OBJECT
public:
    explicit MatchTeam(QObject *parent = nullptr);

    void addTriplet(uint playerID[4]);
    void addDublet(uint playerID[3]);
    void addSingiel(uint playerID);

signals:

private:
    uint m_teamID;

    QList<MatchTriplets*> m_triplets;
    QList<MatchDublets*> m_dublets;
    QList<MatchSingiels*> m_singiels;
};

typedef QList<MatchTeam*> MatchTeamList;

#endif // MATCHTEAM_H
