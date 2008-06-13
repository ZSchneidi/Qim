import Qt 4.7

Item {
    id: dialog

    anchors.centerIn: parent
    width: 250
    height: 150

    ShadowBox{
        id: dialogShadow
        width: 230
        height: 114
        color: "#E5E5E5"
        anchors.bottomMargin: 26
        anchors.fill: parent
        shadowIntensity: 0.5
        anchors.margins: 10
        opacity: 1

        Rectangle {
            id: head
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 25
            border.color: "#adadad"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#c8c8c8"
                }

                GradientStop {
                    position: 1
                    color: "#919191"
                }
            }
            z: 1

            Text {
                id: title
                width: 80
                color: "#e5e6ea"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: dialogInterface.title
                style: Text.Normal
                smooth: false
                font.pointSize: 10
                styleColor: "#332d2d"
            }
            MouseArea{
                id:moveArea
                anchors.fill: parent
                onPositionChanged: {
                    dialogInterface.setDialogPos()
                }
            }
        }

        Rectangle {
            id: body
            x: 0
            y: 0
            border.color: "#626262"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#e6e6e6"
                }

                GradientStop {
                    position: 1
                    color: "#cfcfcf"
                }
            }
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0

            Text {
                id: message
                x: 11
                y: 43
                text: dialogInterface.message
                anchors.verticalCenterOffset: 0
                anchors.horizontalCenterOffset: 1
                verticalAlignment: Text.AlignTop
                transformOrigin: Item.Center
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
                clip: true
                font.bold: true
                font.pointSize: 9
                styleColor: "#332d2d"
            }


            Rectangle{
                id: button1
                x: 75
                y: 78
                width: 80
                height: 25
                anchors.horizontalCenterOffset: 0
                opacity: 0.99
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 11
                gradient: Gradient {
                    GradientStop {
                        position: 0.00;
                        color: "#bebebe";
                    }
                    GradientStop {
                        position: 1.00;
                        color: "#6b6868";
                    }
                }
                Text {
                    id: ok
                    anchors.centerIn: parent
                    text: "Ok"
                    font.bold: true
                    font.pointSize: 10
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: dialogInterface.ok()
                }

            }

        }
    }




}



