#ifndef MATCHTEAM_H
#define MATCHTEAM_H

#include <QObject>
#include <QDebug>
#include <QList>

#include "cpp/objects/MatchType/MatchTriplets.h"
#include "cpp/objects/MatchType/MatchDublets.h"
#include "cpp/objects/MatchType/MatchSingiels.h"

class MatchTeam : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint teamID                  READ getTeamID      WRITE setTeamID NOTIFY teamIDChanged    FINAL)
    Q_PROPERTY(const MatchSingiels *singiels       READ getSingiels    CONSTANT FINAL)
    Q_PROPERTY(const MatchDublets *dublets         READ getDublets     CONSTANT FINAL)
    Q_PROPERTY(const MatchTriplets *triplets       READ getTriplets    CONSTANT FINAL)

public:
    explicit MatchTeam(QObject *parent = nullptr);

    uint getTeamID() const;
    const MatchSingiels *getSingiels() const;
    const MatchDublets *getDublets() const;
    const MatchTriplets *getTriplets() const;

    MatchSingiels *getSingielsRef();
    MatchDublets *getDubletsRef();
    MatchTriplets *getTripletsRef();

    void setTeamID(uint teamID);
    void setSingiels(MatchSingiels *singiels);
    void setDublets(MatchDublets *dublets);
    void setTriplets(MatchTriplets *triplets);

signals:
    void teamIDChanged();
    // void singielsChanged();
    // void dubletsChanged();
    // void tripletsChanged();

private:
    uint m_teamID;

    MatchSingiels* m_singiels;
    MatchDublets* m_dublets;
    MatchTriplets* m_triplets;
};

typedef QList<MatchTeam*> MatchTeamList;

#endif // MATCHTEAM_H
