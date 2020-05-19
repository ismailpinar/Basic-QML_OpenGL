

import QtQuick 2.0


import SceneGraphRendering 1.0

Item {


    x:30
    y:30


    property bool oynat: true



    Component {
              id: comp1
              Rectangle { color: internalSettings.color; width: 400; height: 50 }
          }



    Rectangle {
        id: rectangle
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent



        Renderer {
            id: renderer
            anchors.fill: parent


            Text {
                id: tH
                x: 395
                y: 161
                color: "#0cccc2"
                text:  ""
                font.pointSize: 15
                font.family: "Verdana"


            }

            Text {
                id: tH1
                x: 200
                y: 161
                color: "#0cccc2"
                text: ""
                font.pointSize: 15
                font.family: "Verdana"

            }
            MouseArea{
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                hoverEnabled: true
                anchors.fill: parent
                onClicked:
                {


                    tiklananNokta(mouse.x,mouse.y);

                    var x = msg.tiklananGLNoktasi();

                    textPiksel.text ="X = " + x[0] +"  Y = " + x[1];

                    textGL.text ="X = " + mouse.x +"  Y = " + mouse.y;

                }

                onPressed:
                {
                    onBasildi(mouse.x, mouse.y);
                }

                onPositionChanged:
                {
                   onSurukleniyor(mouse.x, mouse.y);

                }
                onReleased:
                {
                    onBirakildi(mouse.x, mouse.y);
                }

            }

        }




    }



}

/*##^##
Designer {
    D{i:2;anchors_height:700;anchors_width:700}D{i:1;anchors_height:200;anchors_width:200}
}
##^##*/
