#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QList>
#include <QRandomGenerator>

#include "cpp/support/Log.h"
#include "cpp/objects/Team.h"
#include "cpp/objects/Match.h"
#include "cpp/storages/Personalization.h"

class Event : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TeamList teams       READ getTeams                               NOTIFY teamsChanged             FINAL)
    Q_PROPERTY(Team* detachedTeam   READ getDetachedTeam                        NOTIFY detachedTeamChanged      FINAL)

    Q_PROPERTY(Phase phase                  READ getPhase                       WRITE setPhase                  NOTIFY phaseChanged                 FINAL)
    Q_PROPERTY(QString name                 READ getName                        WRITE setName                   NOTIFY nameChanged                  FINAL)
    Q_PROPERTY(QString firstPhaseDate       READ getFirstPhaseDate              WRITE setFirstPhaseDate         NOTIFY firstPhaseDateChanged        FINAL)
    Q_PROPERTY(QString secondPhaseDate      READ getSecondPhaseDate             WRITE setSecondPhaseDate        NOTIFY secondPhaseDateChanged       FINAL)
    Q_PROPERTY(QString competitionOrganizer READ getCompetitionOrganizer        WRITE setCompetitionOrganizer   NOTIFY competitionOrganizerChanged  FINAL)
    Q_PROPERTY(QString firstPhasePlace      READ getFirstPhasePlace             WRITE setFirstPhasePlace        NOTIFY firstPhasePlaceChanged       FINAL)
    Q_PROPERTY(QString secondPhasePlace     READ getSecondPhasePlace            WRITE setSecondPhasePlace       NOTIFY secondPhasePlaceChanged      FINAL)
    Q_PROPERTY(QStringList judges           READ getJudges                      WRITE setJudges                 NOTIFY judgesChanged                FINAL)
    Q_PROPERTY(QString unionDelegate        READ getUnionDelegate               WRITE setUnionDelegate          NOTIFY unionDelegateChanged         FINAL)

    Q_PROPERTY(Stage stage          READ getStage                               NOTIFY stageChanged             FINAL)
    Q_PROPERTY(int round            READ getRound           WRITE setRound      NOTIFY roundChanged             FINAL)
    Q_PROPERTY(int roundStage       READ getRoundStage      WRITE setRoundStage NOTIFY roundStageChanged        FINAL)
    Q_PROPERTY(Match *match         READ getMatch                               NOTIFY matchesChanged           FINAL)

    Q_PROPERTY(bool hasNextRoundStage READ hasNextRoundStage NOTIFY roundStageChanged FINAL)
    Q_PROPERTY(bool hasPrevRoundStage READ hasPrevRoundStage NOTIFY roundStageChanged FINAL)

public:
    explicit Event(QObject *parent = nullptr);
    ~Event();
    void clearTeams();
    void clearEvent();

    enum Phase{
        First = 0,
        Second = 1,
    };
    enum Stage{
        None = 0,
        Configure = 1,
        Continue = 2,
        Finish = 3,
    };
    enum RoundStage{
        Selection = 0,
        Triplets,
        Dublets,
        Singiels,
    };
    static constexpr RoundStage firstRoundStage = RoundStage::Selection;
    static constexpr RoundStage lastRoundStage = RoundStage::Singiels;

public slots:
    void createDetachedTeam();
    void deleteDetachedTeam();

    void addTeamUsingDetachedTeam();
    void deleteTeam(const Team *const team);

    void addJudge();
    void deleteJudge(int index);
    void setJudge(int index, QString judge);

    // void overwriteMatch(QVariantList selectionData);
    // void createMatch(QVariantList selectionData);

    void goToNextStage();
    void goToPrevStage();

    void goToNextRoundStage();
    void goToPrevRoundStage();

    void createMatchIfNotExist();
    void verifyCurrentRoundStage();

public:
    bool hasNextRoundStage() const;
    bool hasPrevRoundStage() const;

signals:
    void matchWasCreated();
    void matchAlreadyExist();
    void currentRoundStageVerified();
    void currentRoundStageVerificationFailed(QString message);

private:
    // static void createMatch(Match *match, const TeamList &teams, const QVariantList &selectionData);
    uint generateUniqueTeamID() const;
    bool isTeamIDUniqueInTeamssList(uint id) const;

public:
    TeamList getTeams() const;
    Team *getDetachedTeam() const;

    Phase getPhase() const;
    QString getName() const;
    QString getFirstPhaseDate() const;
    QString getSecondPhaseDate() const;
    QString getCompetitionOrganizer() const;
    QString getFirstPhasePlace() const;
    QString getSecondPhasePlace() const;
    QStringList getJudges() const;
    QString getUnionDelegate() const;

    Stage getStage() const;
    int getRound() const;
    int getRoundStage() const;
    Match* getMatch() const;
    MatchList getMatches() const;


    void setPhase(Phase phase);
    void setName(const QString &name);
    void setFirstPhaseDate(const QString &firstPhaseDate);
    void setSecondPhaseDate(const QString &secondPhaseDate);
    void setCompetitionOrganizer(const QString &competitionOrganizer);
    void setFirstPhasePlace(const QString &firstPhasePlace);
    void setSecondPhasePlace(const QString &secondPhasePlace);
    void setJudges(const QStringList &judges);
    void setUnionDelegate(const QString &unionDelegate);

    void setStage(Stage stage);
    void setRound(int round);
    void setRoundStage(int roundStage);


signals:
    void teamsChanged();
    void detachedTeamChanged();

    void phaseChanged();
    void nameChanged();
    void firstPhaseDateChanged();
    void secondPhaseDateChanged();
    void competitionOrganizerChanged();
    void firstPhasePlaceChanged();
    void secondPhasePlaceChanged();
    void judgesChanged();
    void unionDelegateChanged();

    void stageChanged();
    void roundChanged();
    void roundStageChanged();
    void matchesChanged();

private:

    TeamList m_teams[2];
    Team *m_detachedTeam;

    Phase m_phase;
    QString m_name;
    QString m_firstPhaseDate;
    QString m_secondPhaseDate;
    QString m_competitionOrganizer;
    QString m_firstPhasePlace;
    QString m_secondPhasePlace;
    QStringList m_judges;
    QString m_unionDelegate;

    Stage m_stage;
    int m_round;
    int m_roundStage;
    MatchList m_matches[2]; /// i would love to use here a simple QStack :/
};

#endif // EVENT_H
