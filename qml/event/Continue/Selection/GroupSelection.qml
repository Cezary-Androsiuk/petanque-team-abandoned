import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: groupSelection
    required property int teamIndex;
    readonly property var team: event.teams[teamIndex];
    required property int groupSize; // 1, 2 or 3
    onGroupSizeChanged: {
        if(groupSize !== 1 && groupSize !== 2 && groupSize !== 3){ // easy to read
           console.log("groupSize is not an required value! received: " + groupSize +
                       ", changing to 1")
            groupSize = 1
        }
    }
    readonly property int groupsCount: {
        if(groupSize === 3)         2;
        else if(groupSize === 2)    3;
        else /* groupSize === 1 */  6;
    }
    readonly property string groupsSelectionName: {
        if(groupSize === 3)         "Triplets";
        else if(groupSize === 2)    "Dublets";
        else /* groupSize === 1 */  "Singiels";
    }

    readonly property int delegateHeight: 30;
    readonly property int headerHeight: 60;
    readonly property int footerHeight: 30;
    readonly property int playersCount: (!team)?0: team.players.length
    readonly property int groupSelectionHeight: playersCount * delegateHeight + headerHeight + footerHeight
    readonly property var listOfSelected: []

    height: groupSelectionHeight

    function inputDataAreValid(){ // called by Selection.qml
        // console.log("verifyData - groupSelection")
        let messageError = Backend.isSelectionDataValid(listOfSelected, groupSize, groupsCount);

        if(messageError !== "")
        {
            console.log("error occur in team "+team.teamName+" in " + groupsSelectionName)
            console.log("message: " + messageError) // popup
            return false;
        }
        else
            return true;
    }

    function setExampleData(){
        var i,j,h;

        for(i=0; i<groupSize; i++)
        {
            for(j=0; j<groupsCount; j++)
            {
                h = i + j*groupSize;
                // set Group j
                listOfSelected[h][j+1] = true;
                listView.itemAtIndex(h).radioButtonsAlias.itemAt(j).checked = true

            }
        }
    }

    function returnListOfSelected(){
        return listOfSelected;
    }


    function setAlreadyExistingTriplets(matchTriplets)
    {
        var i, j, h;
        // vertically align values depending on whether they fit into a triplet group
        for(i=0; i<matchTriplets.length; i++) // for each group (contains 3 or 4 players) in triplets
        {
            for(h=0; h<matchTriplets[i].playersID.length; h++) // for each selected player in group
            {
                for(j=0; j<team.players.length; j++) // for each players
                {
                    if(team.players[j].playerID === matchTriplets[i].playersID[h])
                    {
                        // set group i+1 and player j
                        listOfSelected[j][i+1] = true;
                        listView.itemAtIndex(j).radioButtonsAlias.itemAt(i).checked = true
                    }
                }
            }
        }

    }
    function setAlreadyExistingDublets(matchDublets)
    {
        var i, j, h;
        // vertically align values depending on whether they fit into a dublet group
        for(i=0; i<matchDublets.length; i++) // for each group (contains 2 or 3 players) in dublets
        {
            for(h=0; h<matchDublets[i].playersID.length; h++) // for each selected player in group
            {
                for(j=0; j<team.players.length; j++) // for each players
                {
                    if(team.players[j].playerID === matchDublets[i].playersID[h])
                    {
                        // set group i+1 and player j
                        listOfSelected[j][i+1] = true;
                        listView.itemAtIndex(j).radioButtonsAlias.itemAt(i).checked = true
                    }
                }
            }
        }
    }
    function setAlreadyExistingSingiels(matchSingiels)
    {
        var i, j;
        // vertically align values depending on whether they fit into a dublet group
        for(i=0; i<matchSingiels.length; i++) // for each group (contains 1 player) in dublets
        {
            for(j=0; j<team.players.length; j++) // for each players
            {
                if(team.players[j].playerID === matchSingiels[i].playerID)
                {
                    // set group i+1 and player j
                    listOfSelected[j][i+1] = true;
                    listView.itemAtIndex(j).radioButtonsAlias.itemAt(i).checked = true
                }
            }
        }
    }

    Component.onCompleted: {
        // create list for checked
        if(groupSize === 3)
        {
            for(let i=0; i<playersCount; i++)
                listOfSelected.push({1: false, 2: false});
        }
        else
        if(groupSize === 2)
        {
            for(let i=0; i<playersCount; i++)
                listOfSelected.push({1: false, 2: false, 3: false});
        }
        else
        // groupSize === 1
        {
            for(let i=0; i<playersCount; i++)
                listOfSelected.push({1: false, 2: false, 3: false, 4: false, 5: false, 6: false});
        }


        // Check if match was already created, if it was load data
        if(Backend.event.matchCreated)
        {
            var matchTeam = Backend.event.match.matchTeams[teamIndex];
            var i;

            if(groupSize === 3)
            {
                setAlreadyExistingTriplets(matchTeam.triplets);
            }
            else
            if(groupSize === 2)
            {
                setAlreadyExistingDublets(matchTeam.dublets);
            }
            else
            // groupSize === 1
            {
                setAlreadyExistingSingiels(matchTeam.singiels);
            }
        }
    }

    Component.onDestruction: {
        // console.log("")

        // if(groupSize === 3)
        // {
        //     for(let selected of listOfSelected)
        //         console.log("1: " + selected[1] + ", 2: " + selected[2])
        // }
        // else
        // if(groupSize === 2)
        // {
        //     for(let selected of listOfSelected)
        //         console.log("1: " + selected[1] + ", 2: " + selected[2] + ", 3: " + selected[3])
        // }
        // else
        // // groupSize === 1
        // {
        //     for(let selected of listOfSelected)
        //         console.log("1: " + selected[1] + ", 2: " + selected[2] + ", 3: " + selected[3] +
        //                     "4: " + selected[4] + ", 5: " + selected[5] + ", 6: " + selected[6])
        // }
    }

    ListView{
        id: listView
        anchors.fill: parent

        model: (!team)?null:team.players
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        interactive: false
        cacheBuffer: 10000 // for god sake, keep delegates alive while scrolling

        footer: Item{
            width: listView.width
            height: footerHeight
        }

        header: Item{
            width: listView.width
            height: headerHeight

            Item{
                id: groupsSelectionNameTitle
                anchors{
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                height: parent.height/2

                Label{
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 18 // default is 14
                    text: groupsSelectionName
                }
                Item{
                    id: exampleSelectionButtonField
                    anchors{
                        top: parent.top
                        left: parent.left
                        bottom: parent.bottom
                    }
                    width: 3* height

                    Button{
                        id: exampleSelectionButton
                        anchors.fill: parent
                        onClicked: {
                            setExampleData();
                        }
                    }

                    Label{
                        id: exampleSelectionButtonText
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 14
                        text: "Set Example"
                    }

                }

                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Qt.rgba(1,1,1, 0.4)
                    border.width: 1
                }
            }

            Row{
                anchors{
                    top: groupsSelectionNameTitle.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }

                spacing: 0

                Label{
                    width: 140
                    height: parent.height
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 16 // default is 14
                    text: "Player Info"
                }

                Repeater{
                    model: groupSelection.groupsCount
                    Item{
                        height: parent.height
                        width: 140
                        Rectangle{
                            anchors.fill: parent
                            color: Qt.rgba(1,1,1, (8-(index+1))/14)
                        }

                        Label{
                            anchors.fill: parent
                            width: 140
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 16 // default is 14
                            text: "Group " + (index+1)
                        }
                    }
                }
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.2)
                border.width: 1
            }
        }

        delegate: Item{
            width: listView.width
            height: delegateHeight

            property alias radioButtonsAlias: radioButtons;

            Row{
                id: row
                anchors.fill: parent
                spacing: 0

                readonly property int parentIndex: index

                Label{
                    id: playerInfo
                    width: 140
                    height: parent.height
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    // pixelSize is 14
                    text: modelData.fname + " " + modelData.lname
                }
                Repeater{
                    id: radioButtons
                    model: groupSelection.groupsCount
                    RadioButton{
                        id: radioButton
                        width: 140
                        height: parent.height
                        // text: "group " + (row.parentIndex+1) +  "" + (index+1)

                        // uncheck mechanic
                        property bool wasCheckedWhilePressing: false
                        onPressed: {
                            wasCheckedWhilePressing = checked
                        }
                        onClicked: {
                            if(wasCheckedWhilePressing)
                                checked = false
                        }

                        onCheckedChanged: {
                            listOfSelected[row.parentIndex][index+1] = checked
                        }
                    }
                }
            }

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                border.color: Qt.rgba(1,1,1, 0.2)
                border.width: 1
            }


        }

    }



    Rectangle{
        anchors.fill: parent
        color: "transparent"
        border.color: Qt.rgba(1,1,1, 0.5)
        border.width: 1
    }

}
