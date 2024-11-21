import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: teamsMatch

    required property var event;
    required property int matchTypeIndex; // 1 - SingielsMatch, 2 - DubletsMatch, 3 - TripletsMatch

    readonly property var match: event.match;
    readonly property var team1: match.getTeamByIndexes(event.teams, index, 1);
    readonly property var team2: match.getTeamByIndexes(event.teams, index, 2);
    readonly property var matchTeam1: match.getMatchTeamByIndexes(index, 1);
    readonly property var matchTeam2: match.getMatchTeamByIndexes(index, 2);

    readonly property int widthAnchorMargin: 10
    readonly property int heightAnchorMargin: 10

    readonly property double higherTeamHeight: leftTeam.height > rightTeam.height ? leftTeam.height : rightTeam.height
    height: higherTeamHeight + (heightAnchorMargin * 2)


    Component.onCompleted: {
        // is exdcuted after filling properties

        if(matchTypeIndex === 1)
        {
            matchTeam1.singiels.computePlayersUsed(team1.players);
            matchTeam2.singiels.computePlayersUsed(team2.players);
        }
        else if(matchTypeIndex === 2)
        {
            matchTeam1.dublets.computePlayersUsed(team1.players);
            matchTeam2.dublets.computePlayersUsed(team2.players);
        }
        else //if(matchTypeIndex === 3)
        {
            matchTeam1.triplets.computePlayersUsed(team1.players);
            matchTeam2.triplets.computePlayersUsed(team2.players);
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
        height: leftTeamName.height + leftGroupsMatch.height

        Label{
            id: leftTeamName
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: 50
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: team1.teamName
        }

        GroupsMatch{
            id: leftGroupsMatch
            anchors{
                top: leftTeamName.bottom
                left: parent.left
                right: parent.right
            }

            team: teamsMatch.team1
            matchTeam: teamsMatch.matchTeam1
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
        height: rightTeamName.height + rightGroupsMatch.height

        Label{
            id: rightTeamName
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: 50
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: team2.teamName
        }

        GroupsMatch{
            id: rightGroupsMatch
            anchors{
                top: rightTeamName.bottom
                left: parent.left
                right: parent.right
            }

            team: teamsMatch.team2
            matchTeam: teamsMatch.matchTeam2
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