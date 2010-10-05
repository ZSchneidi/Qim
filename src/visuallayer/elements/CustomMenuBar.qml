import Qt 4.7

Item {
    id: menuBar

    Rectangle{
        id:background
        color: "white"
        anchors.fill: parent


        Item {
            id: openAction
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: 70

            Rectangle{
                anchors.fill: parent
                color: "green"
            }
            Text {
                anchors.centerIn: parent
                text: "Open"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    qmlInterface.sendCoreAction(3)
                }
            }


        }

    }

}

