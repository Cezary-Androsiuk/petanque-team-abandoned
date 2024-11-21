import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: teamsMatch

    required property var event;
    required property int teamIndex;
    required property int matchTypeIndex; // 1 - SingielsMatch, 2 - DubletsMatch, 3 - TripletsMatch

    readonly property var match: event.match;
    readonly property var team1: match.getTeamByIndexes(event.teams, teamIndex, 1);
    readonly property var team2: match.getTeamByIndexes(event.teams, teamIndex, 2);
    readonly property var matchTypes1: match.getMatchTypesByIndexes(teamIndex, 1);
    readonly property var matchTypes2: match.getMatchTypesByIndexes(teamIndex, 2);

    readonly property int widthAnchorMargin: 10
    readonly property int heightAnchorMargin: 10

    readonly property double higherTeamHeight: leftTeam.height > rightTeam.height ? leftTeam.height : rightTeam.height
    height: higherTeamHeight + (heightAnchorMargin * 2)

    Component.onCompleted: {
        // is exdcuted after filling properties

        if(matchTypeIndex === 1)
        {
            matchTypes1.singiels.computePlayersUsed(team1.players);
            matchTypes2.singiels.computePlayersUsed(team2.players);
        }
        else if(matchTypeIndex === 2)
        {
            matchTypes1.dublets.computePlayersUsed(team1.players);
            matchTypes2.dublets.computePlayersUsed(team2.players);
        }
        else //if(matchTypeIndex === 3)
        {
            matchTypes1.triplets.computePlayersUsed(team1.players);
            matchTypes2.triplets.computePlayersUsed(team2.players);
        }
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
            matchTypes: teamsMatch.matchTypes1
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
            matchTypes: teamsMatch.matchTypes2
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
