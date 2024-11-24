#ifndef MATCHTEAM_H
#define MATCHTEAM_H

#include <QObject>
#include <QDebug>
#include <QList>

#include "cpp/objects/MatchType/MatchTypeBase.h"
#include "cpp/objects/MatchType/MatchTriplets.h"
#include "cpp/objects/MatchType/MatchDublets.h"
#include "cpp/objects/MatchType/MatchSingiels.h"

class MatchTeam : public QObject
{
    Q_OBJECT

public:
    explicit MatchTeam(QObject *parent = nullptr);

    /// here the getter and the setter works differently - getter return original value
    Q_INVOKABLE MatchTypeBase *getMatchType(int type) const;
    Q_INVOKABLE MatchTypeBase *getMatchType(int type);
    void setMatchType(MatchTypeBase *matchTypeBase);

private:
    MatchTypeBase *_getMatchType(int type) const;

private:
    MatchSingiels* m_singiels;
    MatchDublets* m_dublets;
    MatchTriplets* m_triplets;
};

typedef QList<MatchTeam*> MatchTeamList;

#endif // MATCHTEAM_H
