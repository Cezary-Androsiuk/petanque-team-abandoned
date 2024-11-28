import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: matchSummary
    anchors.fill: parent

    function setExampleData(){
        // method only for unification files and validation purposes
        log.i("no example data to set", "matchSummary - setExampleData()");
    }

    Label{
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: 30
        text: "Summary"
    }
}
