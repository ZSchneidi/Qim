import Qt 4.7

Item {
    id: dialog

    anchors.centerIn: parent
    width: 400
    height: 200

    ShadowBox{
        id: dialogShadow
        color: "#E5E5E5"
        shadowIntensity: 0.5
        anchors.margins: 10
        width: parent.width
        height: parent.height
        opacity: 1

        Rectangle {
            id: body
            anchors.fill: parent
            color: "lightgray"

            Text {
                id: message
                anchors.centerIn: parent
                text: dialogInterface.message
                styleColor: "#332d2d"
            }


            Rectangle{
                id: button1
                width: 80
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
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
                    onClicked: dialogInterface.ok
                }

            }

        }
    }




}



