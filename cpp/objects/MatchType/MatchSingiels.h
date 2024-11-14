#ifndef MATCHSINGIELS_H
#define MATCHSINGIELS_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"
#include "cpp/objects/MatchType/MatchTypeBase.h"

class MatchSingiels : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchSingiels(uint playersCount, QObject *parent = nullptr);

    bool isSelectionDataValid(QString *message = nullptr) const override;
signals:

private:
};

#endif // MATCHSINGIELS_H
