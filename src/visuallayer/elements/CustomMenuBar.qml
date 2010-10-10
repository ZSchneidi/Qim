import Qt 4.7

Item {
    id: menuBar

    Rectangle{
        id:background
        color: "white"
        anchors.fill: parent

        /*openAction begin*/
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
                    qmlInterface.sendCoreAction(2)
                }
            }
        }
        /*openAction end*/
        /*configAction begin*/
        Item {
            id: configAction
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: 70
            Rectangle{
                anchors.fill: parent
                color: "green"
            }
            Text {
                anchors.centerIn: parent
                text: "Config"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    qmlInterface.sendCoreAction(6)
                }
            }
        }
        /*configAction end*/
        /*fullscreen begin*/
        Item {
            id: fullscreen
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: configAction.left
            width: 70
            Rectangle{
                anchors.fill: parent
                color: "green"
            }
            Text {
                anchors.centerIn: parent
                text: "Fullscreen"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    qmlInterface.sendCoreAction(5)
                }
            }
        }
        /*fullscreen end*/
    }

}

