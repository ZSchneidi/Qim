//import "QmlInterface" 1.0
import Qt 4.7
import "elements"

Item {
    id: qimVisualLayer
    width: 640
    height: 480
    property bool list_is_active: true


        ContextListView {
             id: listView
             listmodel: imageDataModel
             currentIndex: qmlInterface.index
             z: 1
             backgroundColor1: "#a2a2a2"
             backgroundColor2: "#cacacf"
             itemColor1: "grey"
             itemColor2: "lightgray"
             backgroundOpacity: 0.2
             highlightColor1: "#a2a2a2"
             highlightColor2: "#cacacf"
             itembackgroundOpacity: 0.9
             Connections {
                 target: qmlInterface
             }
         }

        Item {
            id: mainView
            property int image_width: 0
            property int image_height: 0
            property int image_frame_margin: 50

            anchors.centerIn: parent

            ShadowBox{
                id: imageLabel
                color: "#E5E5E5"
                shadowIntensity: 0.5
                anchors.centerIn: parent
                anchors.margins: 10
                width: mainView.image_width
                height: mainView.image_height
                opacity: 0.0

                Image {
                    id: mainpicture
                    anchors.fill: parent
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                    source: listView.currentItemFilePath
                    width: mainView.image_width
                    height: mainView.image_height

                    Connections {
                        target: qmlInterface

                        onUpdateImageScale:
                                {
                                /*if the image size is bigger than the window size scale the image down*/
                                if(listView.currentItemFileHeight >= (qmlInterface.main_size.height-mainView.image_frame_margin)
                                        || listView.currentItemFileWidth >=  (qmlInterface.main_size.width-mainView.image_frame_margin))
                                {
                                    mainView.image_height = qmlInterface.main_size.height-mainView.image_frame_margin
                                    mainView.image_width = qmlInterface.main_size.width-mainView.image_frame_margin
                                }
                                /*if the image size is smaller than the window size paint its real size*/
                                else
                                {
                                    mainView.image_height = listView.currentItemFileHeight
                                    mainView.image_width = listView.currentItemFileWidth
                                }

                                imageLabel.opacity = 1
                        }

                        onZoomIn:
                                {
                               console.log("zoomed IN "+mainpicture.width/2)
                               mainpicture.width = (mainpicture.width/2)
                               mainpicture.height = (mainpicture.height/2)
                        }
                        /*every time the main window has changed its size the mainView which
                        *contains the image is synchronizing with the main Window size.
                        */
                        onSizeChanged:
                        {
                                console.log("new size is "+size.width+":"+size.height)
                                mainView.image_width = size.width-mainView.image_frame_margin
                                mainView.image_height = size.height-mainView.image_frame_margin
                        }
                    }
                }
            }
        }



        /*just a kind of temporary debug output*/
         Text {
             id: info
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.bottom: parent.bottom
             text: ""
                     //"index is : " + qmlInterface.index
         }


}
