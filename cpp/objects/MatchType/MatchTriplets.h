#ifndef MATCHTRIPLETS_H
#define MATCHTRIPLETS_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"
#include "cpp/objects/MatchType/MatchTypeBase.h"

class MatchTriplets : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchTriplets(uint playersCount, QObject *parent = nullptr);

    bool isSelectionDataValid(QString *message = nullptr) const override;
signals:

private:
};

#endif // MATCHTRIPLETS_H
