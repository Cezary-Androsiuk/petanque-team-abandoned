#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"
#include "cpp/objects/MatchType/MatchData/Selection.h"
#include "cpp/objects/MatchType/MatchData/MatchPoints.h"

class MatchTypeBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Selection *selection READ getSelection CONSTANT FINAL)
    Q_PROPERTY(MatchPoints *matchPoints READ getMatchPoints CONSTANT FINAL)

public:
    explicit MatchTypeBase(uint playersCount, uint groupsCount, QObject *parent = nullptr);

    virtual bool isSelectionDataValid(QString *message = nullptr) const = 0;
    virtual bool isMatchPointsDataValid(QString *message = nullptr) const = 0;

protected:
    bool _isSelectionDataValid(const int rangeOfPlayersCountInGroup[2], QString *message) const;
    bool _isMatchPointsDataValid(QString *message) const;

public slots:
    void computePlayersUsed(const PlayerList &players); /// should be used after selection

public:
    Selection *getSelection() const;
    MatchPoints *getMatchPoints() const;

protected:
    Selection *m_selection;
    MatchPoints *m_matchPoints;
};

#endif // MATCHTYPEBASE_H
