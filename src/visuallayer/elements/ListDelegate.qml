import Qt 4.7

/*Delegate definition*/
Component {
     id: contactDelegate
     /*the listItem contains the an item of the list*/
     Item {
         id:listItem
         width: view.width; height: labelHeight

            /*The listItemLabel is the visual representation of each list Entry*/
            Rectangle{
                id: listItemLabel
                anchors.fill: parent


                gradient: Gradient {

                         GradientStop { position: 0.0; color:  itemColor1}
                        GradientStop { position: 1.0; color:  itemColor2 }
                     }

                border.color: "transparent"
                radius: labelRadius
                anchors.margins: 4
                clip: true

                Row{
                    id: shortInfo
                        Image {
                            id: picCol
                            height: 45; fillMode: Image.PreserveAspectFit
                            x: 5
                            source: picture
                        }
                    Column {
                        Text { x: 10; font.pixelSize: 18; text: '<b>Name:</b> ' + name }
                        Text { x: 10; font.pixelSize: 17; text: '<b>Number:</b> ' + number }
                    }
                }

                Item {
                    id: details
                    anchors.top: shortInfo.bottom

                    Text {id: detailsTitle; x: 10; font.pixelSize: 18; text: 'Details'}
                    Text { x: 10; anchors.top: detailsTitle.bottom; font.pixelSize: 18; text: '<b>Age:</b> ' + age }
                    opacity: 0
                }
                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
                        if(mouse.button == Qt.LeftButton)
                            {
                            ListView.view.currentIndex = index
                            //ListView.view.positionViewAtIndex ( index, ListView.Center )

                        }
                        else if(mouse.button == Qt.RightButton)
                            {
                            if (listItem.state == "")
                                listItem.state = "selected"
                            else
                                listItem.state = ""
                            }
                    }
                }
            }
            states: [
                     State {
                         name: "selected"
                         PropertyChanges { target: listItem; height: selectedLabelHeight }
                         PropertyChanges { target: listItemLabel; border.color: "red" }
                         PropertyChanges { target: details; opacity: 1 }
                     }
                 ]
            transitions: [
                     Transition {
                         from: ""
                         to: "selected"
                         reversible: true
                         ParallelAnimation{
                             NumberAnimation { properties: "height"; duration: 400; easing.type: "OutBack" }
                             NumberAnimation { properties: "opacity"; duration: 200 }
                             ColorAnimation { properties: "color"; duration: 200 }
                         }
                     }
                ]
     }
}
