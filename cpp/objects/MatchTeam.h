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
    Q_PROPERTY(uint teamID                      READ getTeamID      WRITE setTeamID NOTIFY teamIDChanged    FINAL)
    Q_PROPERTY(QList<MatchTriplets*> triplets   READ getTriplets                    NOTIFY tripletsChanged  FINAL)
    Q_PROPERTY(QList<MatchDublets*> dublets     READ getDublets                     NOTIFY dubletsChanged   FINAL)
    Q_PROPERTY(QList<MatchSingiels*> singiels   READ getSingiels                    NOTIFY singielsChanged  FINAL)

public:
    explicit MatchTeam(QObject *parent = nullptr);

    void addTriplet(uint playerID[4]);
    void addDublet(uint playerID[3]);
    void addSingiel(uint playerID);

    uint getTeamID() const;
    const QList<MatchTriplets*> &getTriplets() const;
    const QList<MatchDublets*> &getDublets() const;
    const QList<MatchSingiels*> &getSingiels() const;

    void setTeamID(uint teamID);

signals:
    void teamIDChanged();
    void tripletsChanged();
    void dubletsChanged();
    void singielsChanged();

private:
    uint m_teamID;

    QList<MatchTriplets*> m_triplets;
    QList<MatchDublets*> m_dublets;
    QList<MatchSingiels*> m_singiels;
};

typedef QList<MatchTeam*> MatchTeamList;

#endif // MATCHTEAM_H
