import Qt 4.7
import "../models"

Item {
    id: listItem
    property alias menuTitle: title.text
    property alias menuColor: background.color
    property alias menuListModel: menuList.model



    Rectangle {
        id: background
        anchors.fill: parent
    }
    Text {
        id: title
        anchors.centerIn: parent

    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            console.log("entered")

        }
        onExited: {
            console.log("exited")

        }
    }

    ListView {
        id: menuList
        model: fileMenuModel

    }

}

