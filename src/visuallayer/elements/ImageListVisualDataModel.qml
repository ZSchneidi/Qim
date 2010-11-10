import Qt 4.7

VisualDataModel {
    id: visualDataModel

    /*data Model definition
    model: ListModel {
        id:contactdata
        ListElement {
            name: "Sweety"
            number: "555 3264"
            age: "22"
            picture: "../img/desktop_catrinel01_by_dB_9.jpg"
        }
        ListElement {
            name: "Honey"
            number: "555 8426"
            age: "24"
            picture: "../img/itb_wallpaper_sam1280x1024_a.jpg"
        }
        ListElement {
            name: "Bunny"
            number: "555 0473"
            age: "25"
            picture: "../img/Painting___Sailing_Away_by_Italiener.jpg"
        }
    }*/

    delegate:
            /*data Delegate definition*/
            Component {
                 id: imageDelegate

                 /*the listItem contains the an item of the list*/
                 Item {
                     property float labelRadius: itemRadius
                     property int labelHeight: 55
                     property int selectedLabelHeight: 100

                     property string fileName
                     property string filePath

                     id:listItem
                     width: contextShowWidth-5; height: labelHeight

                        /*The listItemLabel is the visual representation of each list Entry*/
                        Rectangle{
                            id: listItemLabel
                            anchors.fill: parent
                            clip: true
                            border.color: "transparent"
                            color: "transparent"
                            Rectangle{
                                id:itemBackground
                                anchors.fill:parent
                                border.color: "transparent"
                                radius: labelRadius
                                anchors.margins: 2
                                opacity: itembackgroundOpacity
                                gradient: Gradient {
                                        GradientStop { position: 0.0; color:  itemColor1}
                                        GradientStop { position: 1.0; color:  itemColor2 }
                                    }
                            }
                            /*short information include a picture thumbnail and some text*/
                            Item {
                                id: shortInfo
                                height: labelHeight
                                anchors {
                                    top: parent.top; topMargin: 7
                                    left: parent.left; leftMargin: 6
                                }

                                Row{

                                    Image {
                                        id: picCol
                                        height: labelHeight-12; fillMode: Image.PreserveAspectFit
                                        source: picture
                                        sourceSize.height: labelHeight-10
                                        onSourceChanged: {
                                            //console.log("image is " + picture)
                                            filePath = picture
                                            fileName = name
                                        }
                                    }
                                    Column {
                                        Text { x: 10; font.pixelSize: 14; text: '<b>Name:</b> ' + name; }
                                        Text { x: 10; font.pixelSize: 14; text: '<b>Number:</b> ' + number }
                                    }
                                }
                            }

                            Item {
                                id: details
                                anchors.top: shortInfo.bottom
                                y:-10
                                Loader{
                                    id:detailLoader
                                    anchors.fill:parent
                                    //onLoaded: console.log("status " + detailLoader.status)
                                }
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
                                        {
                                            detailLoader.source = "ImageListDelegateDetails.qml"
                                            listItem.state = "selected"
                                        }
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
                                     //PropertyChanges { target: listItemLabel; border.color: "red" }
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
}
