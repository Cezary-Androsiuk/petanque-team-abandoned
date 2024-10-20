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
    Q_PROPERTY(bool isTeamCaptain   READ getIsTeamCaptain   WRITE setIsTeamCaptain  NOTIFY isTeamCaptainChanged FINAL)
public:
    explicit Player(QObject *parent = nullptr);
    // Player &operator = (const Player &player);
    void copyFromOtherPlayer(const Player &player);

    QString getFname() const;
    QString getLname() const;
    QString getLicense() const;
    QString getAge() const;
    Genders getGender() const;
    bool getIsTeamCaptain() const;

    void setFname(const QString &fname);
    void setLname(const QString &lname);
    void setLicense(const QString &license);
    void setAge(QString age);
    void setGender(const Genders &gender);
    void setIsTeamCaptain(bool isTeamCaptain);

signals:
    void fnameChanged();
    void lnameChanged();
    void licenseChanged();
    void ageChanged();
    void genderChanged();
    void isTeamCaptainChanged();

private:
    QString m_fname;
    QString m_lname;
    QString m_license;
    int m_age;
    Genders m_gender;
    bool m_isTeamCaptain;
};

typedef QList<Player*> PlayerList;

#endif // PLAYER_H
