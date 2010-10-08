import Qt 4.7

Item {
    id: customTitleBar

    property int titlebarheight: 30
    property string title: "Qim"


    anchors.right: parent.right
    anchors.left: parent.left
    anchors.top: parent.top
    height: titlebarheight

    /*title background area*/
    Rectangle {
        id: background
        anchors.fill: parent
        Image {
            anchors.fill: parent
            source: "qrc:/img_source/titlebar_background.png"
        }

    }
    /*this is the textarea which defines the title of the application*/
    Text {
        id: mainTitle
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        text: title
        font.pointSize: 8
        color: "white"
    }

    /*this is the mouse handler which is designed to move the MainWindow of the application via qmlInterface*/
    MouseArea{
        id:moveArea
        anchors.fill: parent
        onPositionChanged: {

            qmlInterface.setMainPos()
        }
        onReleased:
            qmlInterface.resetPositionCursor()
    }

    /*this is the close button of the titlebar*/
    Rectangle {
        id: closebutton
        color: "transparent"
        anchors.right: parent.right
        anchors.rightMargin: 2
        //anchors.top: parent.top
        //anchors.bottom: parent.bottom
        /*by defining static sizes the icons wont dynamically resizing with the titlebar*/
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        Image {
            id: closeIcon
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
            source: "../img/close_inactive.png"
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: closeIcon.source = "../img/close_active.png"
            onExited: closeIcon.source = "../img/close_inactive.png"
            /*the button control parameter should be changed to enum type*/
            onClicked: qmlInterface.sendCoreAction(3)
        }
    }

    /*this is the maximizing button of the titlebar*/
    Rectangle {
        id: maxbutton
        color: "transparent"
        anchors.right: closebutton.left
        anchors.rightMargin: 2
        //anchors.top: parent.top
        //anchors.bottom: parent.bottom
        /*by defining static sizes the icons wont dynamically resizing with the titlebar*/
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        Image {
            id: maxIcon
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
            source: "../img/max_inactive.png"
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: maxIcon.source = "../img/max_active.png"
            onExited: maxIcon.source = "../img/max_inactive.png"
            onClicked: qmlInterface.sendCoreAction(0)
        }
    }

    /*this is the minimizing button of the titlebar*/
    Rectangle {
        id: minbutton
        color: "transparent"
        anchors.right: maxbutton.left
        anchors.rightMargin: 2
        //anchors.top: parent.top
        //anchors.bottom: parent.bottom
        /*by defining static sizes the icons wont dynamically resizing with the titlebar*/
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        Image {
            id: miniIcon
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
            source: "../img/mini_inactive.png"
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: miniIcon.source = "../img/mini_active.png"
            onExited: miniIcon.source = "../img/mini_inactive.png"
            onClicked: qmlInterface.sendCoreAction(1)
        }
    }

}
