#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"

class Player : public QObject
{
public:
    enum Genders{
        Male = 0,
        Female,
        HelikopterBojowy_AH_64_Apache
    };

private:
    Q_OBJECT
    Q_PROPERTY(QString fname        READ getFname           WRITE setFname          NOTIFY fnameChanged         FINAL)
    Q_PROPERTY(QString lname        READ getLname           WRITE setLname          NOTIFY lnameChanged         FINAL)
    Q_PROPERTY(QString license      READ getLicense         WRITE setLicense        NOTIFY licenseChanged       FINAL)
    Q_PROPERTY(QString age          READ getAge             WRITE setAge            NOTIFY ageChanged           FINAL)
    Q_PROPERTY(Genders gender       READ getGender          WRITE setGender         NOTIFY genderChanged        FINAL)
    Q_PROPERTY(bool isTeamLeader    READ getIsTeamLeader    WRITE setIsTeamLeader   NOTIFY isTeamLeaderChanged  FINAL)
public:
    explicit Player(QObject *parent = nullptr);
    // Player &operator = (const Player &player);
    void copyFromOtherPlayer(const Player &player);

    uint getPlayerID() const;
    QString getFname() const;
    QString getLname() const;
    QString getLicense() const;
    QString getAge() const;
    Genders getGender() const;
    bool getIsTeamLeader() const;

    void setPlayerID(uint playerID);
    void setFname(const QString &fname);
    void setLname(const QString &lname);
    void setLicense(const QString &license);
    void setAge(QString age);
    void setGender(const Genders &gender);
    void setIsTeamLeader(bool isTeamLeader);


signals:
    void fnameChanged();
    void lnameChanged();
    void licenseChanged();
    void ageChanged();
    void genderChanged();
    void isTeamLeaderChanged();

private:
    uint m_playerID; // unique in team
    QString m_fname;
    QString m_lname;
    QString m_license;
    int m_age;
    Genders m_gender;
    bool m_isTeamLeader;
};

typedef QList<Player*> PlayerList;

#endif // PLAYER_H
