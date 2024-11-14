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
    Q_PROPERTY(uint teamID                  READ getTeamID      WRITE setTeamID NOTIFY teamIDChanged    FINAL)
    Q_PROPERTY(const MatchTriplets *triplets       READ getTriplets    CONSTANT FINAL)
    Q_PROPERTY(const MatchDublets *dublets         READ getDublets     CONSTANT FINAL)
    Q_PROPERTY(const MatchSingiels *singiels       READ getSingiels    CONSTANT FINAL)

public:
    explicit MatchTeam(QObject *parent = nullptr);

    uint getTeamID() const;
    const MatchTriplets *getTriplets() const;
    const MatchDublets *getDublets() const;
    const MatchSingiels *getSingiels() const;

    void setTeamID(uint teamID);
    void setTriplets(MatchTriplets *triplets);
    void setDublets(MatchDublets *dublets);
    void setSingiels(MatchSingiels *singiels);

signals:
    void teamIDChanged();
    // void tripletsChanged();
    // void dubletsChanged();
    // void singielsChanged();

private:
    uint m_teamID;

    MatchTriplets* m_triplets;
    MatchDublets* m_dublets;
    MatchSingiels* m_singiels;
};

typedef QList<MatchTeam*> MatchTeamList;

#endif // MATCHTEAM_H
