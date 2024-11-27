import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: teamsMatch

    required property var event;
    required property int combinationIndex;
    required property int matchTypeIndex; // 1 - SingielsMatch, 2 - DubletsMatch, 3 - TripletsMatch

    readonly property var match: event.match;
    readonly property var team1: match.getTeamByIndexes(event.teams, combinationIndex, 1);
    readonly property var team2: match.getTeamByIndexes(event.teams, combinationIndex, 2);
    readonly property var matchTeam1: match.getMatchTeamByIndexes(combinationIndex, 1);
    readonly property var matchTeam2: match.getMatchTeamByIndexes(combinationIndex, 2);
    readonly property var matchType1: matchTeam1.getMatchType(matchTypeIndex);
    readonly property var matchType2: matchTeam2.getMatchType(matchTypeIndex);

    readonly property int widthAnchorMargin: 10
    readonly property int heightAnchorMargin: 10

    readonly property double higherTeamHeight: leftTeam.height > rightTeam.height ? leftTeam.height : rightTeam.height
    height: higherTeamHeight + (heightAnchorMargin * 2)

    Component.onCompleted: {
        // is exdcuted after filling properties

        matchType1.computePlayersUsed(team1.players);
        matchType2.computePlayersUsed(team2.players);
    }

    function setExampleData(){
        leftGroupsMatch.setExampleData();
        rightGroupsMatch.setExampleData();
    }

    Item{
        id: leftTeam
        anchors{
            top: parent.top
            topMargin: widthAnchorMargin
            left: parent.left
            leftMargin: heightAnchorMargin
        }
        width: parent.width /2 - (2 * anchors.leftMargin)
        height: leftGroupsMatch.height

        GroupsMatch{
            id: leftGroupsMatch
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }

            team: teamsMatch.team1
            matchTeam: teamsMatch.matchTeam1
            matchType: teamsMatch.matchType1
            matchTypeIndex: teamsMatch.matchTypeIndex
        }

        Rectangle{
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }
    }


    Item{
        id: rightTeam
        anchors{
            top: parent.top
            topMargin: widthAnchorMargin
            right: parent.right
            rightMargin: heightAnchorMargin
        }
        width: parent.width /2 - (2 * anchors.rightMargin)
        height: rightGroupsMatch.height

        GroupsMatch{
            id: rightGroupsMatch
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }

            team: teamsMatch.team2
            matchTeam: teamsMatch.matchTeam2
            matchType: teamsMatch.matchType2
            matchTypeIndex: teamsMatch.matchTypeIndex
        }

        Rectangle{
            anchors.fill: parent
            color: "transparent"
            border.color: Qt.rgba(1,1,1, 0.5)
            border.width: 1
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "transparent"
        border.color: Qt.rgba(1,1,1, 0.5)
        border.width: 1
    }
}
