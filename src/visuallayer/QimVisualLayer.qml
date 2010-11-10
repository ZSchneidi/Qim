//import "QmlInterface" 1.0
import Qt 4.7
import "elements"

Item {
    id: qimVisualLayer
    width: 640
    height: 480
    property bool list_is_active: true
    property int min_scale_size: 100
    property int max_scale_size: 4000
    property double native_aspect_ratio: 0.0


    /*javascript functions*/

    /*this function scales the image in the viewport by height*/
    function fitOnHeight()
    {
        mainView.image_height = (qmlInterface.main_size.height - mainView.image_frame_margin)
        if(mainView.image_height/(listView.currentItemFileHeight/listView.currentItemFileWidth) >=
                (qmlInterface.main_size.width-mainView.image_frame_margin))
        {
                fitOnWidth()
        }
        else
            mainView.image_width = mainView.image_height/(listView.currentItemFileHeight/listView.currentItemFileWidth)
    }

    /*this function scales the image in the viewport by width*/
    function fitOnWidth()
    {
        mainView.image_width = (qmlInterface.main_size.width - mainView.image_frame_margin)
        mainView.image_height = mainView.image_width*(listView.currentItemFileHeight/listView.currentItemFileWidth)
    }

    function round_float(x,n){
      if(!parseInt(n))
            var n=0;
      if(!parseFloat(x))
            return false;
      return Math.round(x*Math.pow(10,n))/Math.pow(10,n);
    }

    /*this function is called from the ContextListView whenever the item has changed*/
    function newImageLoaded() {
        native_aspect_ratio = (listView.currentItemFileHeight/listView.currentItemFileWidth)
    }

    Connections {
        target: qmlInterface
        /*this signal will be emitted when this Layer was loaded*/
        onVisualLayerReady: {

        }
    }


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

         }

        Item {
            id: mainView
            property int image_width: 0
            property int image_height: 0
            property int image_frame_margin: 90

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

                        /*every time the main window has changed its size the mainView which
                        *contains the image is synchronizing with the main Window size.
                        */
                        /*the UpdateImageScale signal is emitted to repaint the image in the viewport so that it fits the viewport*/
                        onUpdateImageScale:
                                {
                                /*if the image hight is greater than the viewport scale it down*/
                                if(listView.currentItemFileHeight >= (qmlInterface.main_size.height-mainView.image_frame_margin))
                                {
                                    fitOnHeight()

                                }
                                /* if the image width is greater than the viewport scale it down*/
                                else if (listView.currentItemFileWidth >=  (qmlInterface.main_size.width-mainView.image_frame_margin))
                                {
                                    fitOnWidth()
                                }

                                /*if the image size is smaller than the window size paint its real size*/
                                else
                                {
                                    mainView.image_height = listView.currentItemFileHeight
                                    mainView.image_width = listView.currentItemFileWidth
                                }
                                /*make imageLabel visible when scaled to viewport*/
                                imageLabel.opacity = 1
                        }

                        onZoomIn:
                                {
                                //console.log("zoomed IN "+mainView.image_width)
                                if((mainView.image_width + (100*scalefx)) <= max_scale_size)
                                {
                                    var aspect_ratio = round_float((mainView.image_height/mainView.image_width),2);
                                    mainView.image_width += round_float((100*scalefx),2)
                                    mainView.image_height = (mainView.image_width * aspect_ratio)
                                    //console.log("seitenver. = "+(mainView.image_height/mainView.image_width)+ " : " + aspect_ratio)
                                }
                        }
                        onZoomOut:
                                {
                                //console.log("zoomed OUT by "+round_float((100*scalefx),2)+" - "+(mainView.image_width - round_float((100*scalefx),2)))
                                if((mainView.image_width - (100*scalefx)) >= min_scale_size)
                                {
                                    var aspect_ratio = round_float((mainView.image_height/mainView.image_width),2);
                                    mainView.image_width -= round_float((100*scalefx),2)
                                    mainView.image_height = (mainView.image_width * aspect_ratio)
                                    //console.log("width "+mainView.image_width+ " height "+mainView.image_height)
                                    //console.log("seitenver. = "+ aspect_ratio)
                                }
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
