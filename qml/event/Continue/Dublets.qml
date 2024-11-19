import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selection
    anchors.fill: parent

    readonly property var event: Backend.event
    readonly property var match: event.match

    Item{
        anchors{
            fill: parent
            margins: 30
        }
        clip: true

        ListView {
            id: listView
            anchors.fill: parent

            model: match.matchCombinations.length
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

            ScrollBar.vertical: ScrollBar{
                policy: ScrollBar.AsNeeded
            }

            footer: Item{
                width: listView.width
                height: 50
            }

            delegate: Item{
                width: listView.width
                height: leftTeam.height + 30

                // readonly property var delegateTeam1: {
                //     console.log("readonly property", index)
                //     match.getTeamByIndexes(event.teams, index, 1)
                // }

                // readonly property var delegateTeam2:
                //     match.getTeamByIndexes(event.teams, index, 2)

                function intFromPair(pair, index)
                {
                    return match.intFromPair(pair, index); // static method
                }

                readonly property int teamIndex1: intFromPair(match.matchCombinations[index], 1) -1;
                readonly property int teamIndex2: intFromPair(match.matchCombinations[index], 2) -1;
                readonly property var team1: event.teams[teamIndex1];
                readonly property var team2: event.teams[teamIndex2];
                readonly property var matchTeam1: match.matchTeams[teamIndex1].dublets;
                readonly property var matchTeam2: match.matchTeams[teamIndex2].dublets;

                Component.onCompleted: {
                    // is exdcuted after filling properties
                    match.matchTeams[teamIndex1].dublets.computePlayersUsed(team1.players);
                    match.matchTeams[teamIndex2].dublets.computePlayersUsed(team2.players);
                }

                Item{
                    id: leftTeam
                    anchors{
                        top: parent.top
                        left: parent.left
                    }
                    width: parent.width/2
                    height: 200

                    Column{
                        id: column1

                        Label{
                            text: team1.teamName
                        }

                        Label{
                            text: {
                                var group = matchTeam1.usedPlayersInGroups[0];
                                if(group)
                                {
                                    var player = group[0];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam1.usedPlayersInGroups[0];
                                if(group)
                                {
                                    var player = group[1];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam1.usedPlayersInGroups[1];
                                if(group)
                                {
                                    var player = group[0];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam1.usedPlayersInGroups[1];
                                if(group)
                                {
                                    var player = group[1];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam1.usedPlayersInGroups[2];
                                if(group)
                                {
                                    var player = group[0];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam1.usedPlayersInGroups[2];
                                if(group)
                                {
                                    var player = group[1];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                    }
                }

                Item{
                    id: rightTeam
                    anchors{
                        top: parent.top
                        right: parent.right
                    }
                    width: parent.width/2
                    height: 200

                    Column{
                        id: column2

                        Label{
                            text: team2.teamName
                        }

                        Label{
                            text: {
                                var group = matchTeam2.usedPlayersInGroups[0];
                                if(group)
                                {
                                    var player = group[0];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam2.usedPlayersInGroups[0];
                                if(group)
                                {
                                    var player = group[1];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam2.usedPlayersInGroups[1];
                                if(group)
                                {
                                    var player = group[0];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam2.usedPlayersInGroups[1];
                                if(group)
                                {
                                    var player = group[1];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam2.usedPlayersInGroups[2];
                                if(group)
                                {
                                    var player = group[0];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }

                        Label{
                            text: {

                                var group = matchTeam2.usedPlayersInGroups[2];
                                if(group)
                                {
                                    var player = group[1];
                                    player.fname + player.lname;
                                }
                                else ""
                            }
                        }
                    }
                }


            }

        }
    }
}
