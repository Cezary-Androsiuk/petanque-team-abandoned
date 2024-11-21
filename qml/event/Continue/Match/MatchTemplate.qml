import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: matchTemplate
    anchors.fill: parent

    required property int matchTypeIndex; // 1 - SingielsMatch, 2 - DubletsMatch, 3 - TripletsMatch
    readonly property var event: Backend.event
    readonly property var match: event.match

    function setExampleData(){
        log.w("set example data not finished")
    }

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

            delegate: Item{
                width: listView.width - 40
                anchors.horizontalCenter: parent.horizontalCenter
                height: teamsMatch.height

                TeamsMatch{
                    id: teamsMatch
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }

                    event: matchTemplate.event
                    teamIndex: index
                    matchTypeIndex: matchTemplate.matchTypeIndex
                }



/*

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
                                var group = matchTeam1.dublets.usedPlayersInGroups[0];
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

                                var group = matchTeam1.dublets.usedPlayersInGroups[0];
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

                                var group = matchTeam1.dublets.usedPlayersInGroups[1];
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

                                var group = matchTeam1.dublets.usedPlayersInGroups[1];
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

                                var group = matchTeam1.dublets.usedPlayersInGroups[2];
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

                                var group = matchTeam1.dublets.usedPlayersInGroups[2];
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
                                var group = matchTeam2.dublets.usedPlayersInGroups[0];
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

                                var group = matchTeam2.dublets.usedPlayersInGroups[0];
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

                                var group = matchTeam2.dublets.usedPlayersInGroups[1];
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

                                var group = matchTeam2.dublets.usedPlayersInGroups[1];
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

                                var group = matchTeam2.dublets.usedPlayersInGroups[2];
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

                                var group = matchTeam2.dublets.usedPlayersInGroups[2];
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

*/
            }

        }
    }
}
