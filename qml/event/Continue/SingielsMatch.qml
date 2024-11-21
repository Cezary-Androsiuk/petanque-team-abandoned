import QtQuick 2.15
import QtQuick.Controls.Material

import "Match"

Item {
    id: singielsMatch
    anchors.fill: parent

    function setExampleData(){
        matchTemplate.setExampleData()
    }

    MatchTemplate{
        id: matchTemplate
        matchTypeIndex: 1
    }
}
