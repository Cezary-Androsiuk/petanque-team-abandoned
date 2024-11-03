import QtQuick 2.15
import QtQuick.Controls.Material

Item {
    id: selection
    anchors.fill: parent

    function verifyData(){

        verifiedData();
    }

    signal verifiedData();
}
