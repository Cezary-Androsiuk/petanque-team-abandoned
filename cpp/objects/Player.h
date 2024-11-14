#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QList>
#include <QRegularExpression>
#include <QDate>

#include "cpp/support/Log.h"

class Player : public QObject
{
public:
    enum Gender{
        Male = 0,
        Female,
        HelikopterBojowy_AH_64_Apache
    };
    Q_ENUM(Gender)

    enum AgeGroup{
        Junior = 0,
        Youth,
        Senior,
        Veteran
    };

private:
    Q_OBJECT
    Q_PROPERTY(uint playerID        READ getPlayerID                                CONSTANT                    FINAL)
    Q_PROPERTY(QString fname        READ getFname           WRITE setFname          NOTIFY fnameChanged         FINAL)
    Q_PROPERTY(QString lname        READ getLname           WRITE setLname          NOTIFY lnameChanged         FINAL)
    Q_PROPERTY(QString license      READ getLicense         WRITE setLicense        NOTIFY licenseChanged       FINAL)
    Q_PROPERTY(int ageGroup         READ getAgeGroup        WRITE setAgeGroup       NOTIFY ageGroupChanged      FINAL)
    Q_PROPERTY(int gender           READ getGender          WRITE setGender         NOTIFY genderChanged        FINAL)
    Q_PROPERTY(bool isTeamLeader    READ getIsTeamLeader    WRITE setIsTeamLeader   NOTIFY isTeamLeaderChanged  FINAL)
public:
    explicit Player(QObject *parent = nullptr);

    Q_INVOKABLE QObject *getParent() const;

    uint getPlayerID() const;
    QString getFname() const;
    QString getLname() const;
    QString getLicense() const;
    int getAgeGroup() const;
    int getGender() const;
    bool getIsTeamLeader() const;

    void setPlayerID(uint playerID);
    void setFname(const QString &fname);
    void setLname(const QString &lname);
    void setLicense(const QString &license);
    void setAgeGroup(int ageGroup);
    void setGender(const int &gender);
    void setIsTeamLeader(bool isTeamLeader);

signals:
    void fnameChanged();
    void lnameChanged();
    void licenseChanged();
    void ageGroupChanged();
    void genderChanged();
    void isTeamLeaderChanged();

private:
    uint m_playerID; // unique in team
    QString m_fname;
    QString m_lname;
    QString m_license;
    int m_ageGroup;
    int m_gender;
    bool m_isTeamLeader;
};

typedef QList<Player*> PlayerList;

#endif // PLAYER_H
