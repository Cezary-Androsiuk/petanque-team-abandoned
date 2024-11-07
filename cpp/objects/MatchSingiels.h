#ifndef MATCHSINGIELS_H
#define MATCHSINGIELS_H

#include <QObject>

#include "cpp/support/Log.h"

class MatchSingiels : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint playerID READ getPlayerID NOTIFY playerIDChanged FINAL)
public:
    explicit MatchSingiels(QObject *parent = nullptr);

    uint getPlayerID() const;
    void setPlayerID(uint playerID);

signals:
    void playerIDChanged();

private:
    uint m_playerID;
};

#endif // MATCHSINGIELS_H
