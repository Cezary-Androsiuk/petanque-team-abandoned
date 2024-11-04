#ifndef MATCHTEAM_H
#define MATCHTEAM_H

#include <QObject>
#include <QDebug>
#include <QList>

#include "cpp/objects/MatchTriplets.h"
#include "cpp/objects/MatchDublets.h"
#include "cpp/objects/MatchSingiels.h"

class MatchTeam : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint teamID READ getTeamID WRITE setTeamID NOTIFY teamIDChanged FINAL)

public:
    explicit MatchTeam(QObject *parent = nullptr);

    void addTriplet(uint playerID[4]);
    void addDublet(uint playerID[3]);
    void addSingiel(uint playerID);

    uint getTeamID() const;
    void setTeamID(uint teamID);

signals:
    void teamIDChanged();

private:
    uint m_teamID;

    QList<MatchTriplets*> m_triplets;
    QList<MatchDublets*> m_dublets;
    QList<MatchSingiels*> m_singiels;
};

typedef QList<MatchTeam*> MatchTeamList;

#endif // MATCHTEAM_H
