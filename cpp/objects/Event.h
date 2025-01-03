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
    Q_PROPERTY(TeamList teams       READ getTeams                           NOTIFY teamsChanged             FINAL)
    Q_PROPERTY(Team* detachedTeam   READ getDetachedTeam                    NOTIFY detachedTeamChanged      FINAL)

    Q_PROPERTY(Phase phase                  READ getPhase                   WRITE setPhase                  NOTIFY phaseChanged                 FINAL)
    Q_PROPERTY(QString name                 READ getName                    WRITE setName                   NOTIFY nameChanged                  FINAL)
    Q_PROPERTY(QString date                 READ getDate                    WRITE setDate                   NOTIFY dateChanged                  FINAL)
    Q_PROPERTY(QString competitionOrganizer READ getCompetitionOrganizer    WRITE setCompetitionOrganizer   NOTIFY competitionOrganizerChanged  FINAL)
    Q_PROPERTY(QString place                READ getPlace                   WRITE setPlace                  NOTIFY placeChanged                 FINAL)
    Q_PROPERTY(QStringList judges           READ getJudges                  WRITE setJudges                 NOTIFY judgesChanged                FINAL)
    Q_PROPERTY(QString unionDelegate        READ getUnionDelegate           WRITE setUnionDelegate          NOTIFY unionDelegateChanged         FINAL)

    Q_PROPERTY(Stage stage              READ getStage                               NOTIFY stageChanged             FINAL)
    Q_PROPERTY(int round                READ getRound           WRITE setRound      NOTIFY roundChanged             FINAL)
    Q_PROPERTY(RoundStage roundStage    READ getRoundStage      WRITE setRoundStage NOTIFY roundStageChanged        FINAL)
    Q_PROPERTY(Match *match             READ getMatch                               NOTIFY matchesChanged           FINAL)

    Q_PROPERTY(bool hasNextRoundStage READ hasNextRoundStage NOTIFY roundStageChanged FINAL)
    Q_PROPERTY(bool hasPrevRoundStage READ hasPrevRoundStage NOTIFY roundStageChanged FINAL)

public:
    explicit Event(QObject *parent = nullptr);
    ~Event();
    void clearTeams();
    void clearMatches();
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
        SingielsSelection = 0,
        SingielsMatch,
        DubletsSelection,
        DubletsMatch,
        TripletsSelection,
        TripletsMatch,
        MatchSummary,
    };
    static constexpr RoundStage firstRoundStage = RoundStage::SingielsSelection;
    static constexpr RoundStage lastRoundStage = RoundStage::MatchSummary;

public slots:
    void validateConfigureData();
    void createExampleConfigureData();

    void createDetachedTeam();
    void deleteDetachedTeam();

    void addTeamUsingDetachedTeam();
    void deleteTeam(const Team *const team);

    void addJudge();
    void deleteJudge(int index);
    void setJudge(int index, QString judge);

    void goToNextStage();
    void goToPrevStage();
    void goToConfigureStage(); /// used after changing to second phase

    void goToNextRoundStage();
    void goToPrevRoundStage();
    void goToFirstRoundStage();

    void createMatchIfNotExist(); /// mostly used by qml
    Match *createNewMatch(bool assignMatchCombinations = true); /// mostly used by Memory
    void verifyCurrentRoundStage();

    void startSecondPhase();

public:
    bool hasNextRoundStage() const;
    bool hasPrevRoundStage() const;

signals:
    void configureDataValidatedCorrectly();
    void configureDataValidationFailed(QString description);

    void matchWasCreated();
    void matchAlreadyExist();
    void currentRoundStageVerified();
    void currentRoundStageVerificationFailed(QString message);

    void secondPhaseStarted();
    void newEventStarted();

private:
    void validateConfigureFirstPhaseData();
    void validateConfigureSecondPhaseData();

    uint generateUniqueTeamID() const;
    bool isTeamIDUniqueInTeamssList(uint id) const;

    void copyPlayersFromFirstToSecondPhase();

public:
    const TeamList &getTeams() const;
    Team *getDetachedTeam() const;

    Phase getPhase() const;
    const QString &getName() const;
    const QString &getDate(int phase = -1) const;
    const QString &getCompetitionOrganizer() const;
    const QString &getPlace(int phase = -1) const;
    const QStringList &getJudges() const;
    const QString &getUnionDelegate() const;

    Stage getStage() const;
    int getRound() const;
    RoundStage getRoundStage() const;
    Match* getMatch() const;
    const MatchList &getMatches() const;


    void setPhase(Phase phase);
    void setName(const QString &name);
    void setDate(const QString &date, int phase = -1);
    void setCompetitionOrganizer(const QString &competitionOrganizer);
    void setPlace(const QString &place, int phase = -1);
    void setJudges(const QStringList &judges);
    void setUnionDelegate(const QString &unionDelegate);

    void setStage(Stage stage);
    void setRound(int round);
    void setRoundStage(RoundStage roundStage);

    TeamList &getTeamsP1();
    TeamList &getTeamsP2();
    MatchList &getMatchesP1();
    MatchList &getMatchesP2();

signals:
    void teamsChanged();
    void detachedTeamChanged();

    void phaseChanged();
    void nameChanged();
    void dateChanged();
    void competitionOrganizerChanged();
    void placeChanged();
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
    QString m_date[2];
    QString m_competitionOrganizer;
    QString m_place[2];
    QStringList m_judges;
    QString m_unionDelegate;

    Stage m_stage;
    int m_round;
    RoundStage m_roundStage;
    MatchList m_matches[2]; /// i would love to use here a simple QStack :/
};

#endif // EVENT_H
