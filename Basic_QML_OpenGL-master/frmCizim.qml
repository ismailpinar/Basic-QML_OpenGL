/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0


import SceneGraphRendering 1.0
import QtQuick 2.14


Item {
    width: 1000
    height: 766




    signal tiklananNokta(msg: int,msg: int);
    signal onOynatBasildi(msg: int);
    signal onMercekDegisti(msg: double);
    signal onBasildi(msg: int,msg: int);
    signal onBirakildi(msg: int,msg: int);
    signal onSurukleniyor(msg: int,msg: int);



    property bool oynat: true




    CizimPenceresi
    {

        id:cizimPenceresi
        width: 700
        height: 700
    }



    Rectangle {
        id: rectangle4
        x: 787
        y: 450
        width: 200
        height: 40
        color: "#cceee989"
        border.width: 5

        TextEdit {
            id: textMercek
            x: 0
            y: 0

            width: parent.width
            height: parent.height
            color: "#0a0a0a"
            text:"1"
            mouseSelectionMode: TextInput.SelectWords
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12

            onTextChanged:
            {
                onMercekDegisti(textMercek.text)

            }

        }

    }

    Text {
        id: txtMercek
        x: 787
        y: 426
        text: qsTr("Mercek")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 13
    }


    Rectangle {
        id: rectangle1
        x: 787
        y: 161
        width: 200
        height: 40
        color: "#cceee989"
        border.width: 5


        TextEdit {
            id: textPiksel
            x: 0
            y: 0

            width: parent.width
            height: parent.height
            color: "#0a0a0a"
            text:""
            mouseSelectionMode: TextInput.SelectWords
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12

            onTextChanged:
            {

            }
        }
      }




    Rectangle {
        id: rectangle2
        x: 787
        y: 250
        width: 200
        height: 40
        color: "#cceee989"
        border.width: 5

        TextEdit {
            id: textGL
            x: 0
            y: 0

            width: parent.width
            height: parent.height
            color: "#0a0a0a"
            text:""
            mouseSelectionMode: TextInput.SelectWords
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12

            onTextChanged:
            {

            }

        }

    }

    Text {
        id: element
        x: 787
        y: 140
        text: qsTr("GL Noktası")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 13
    }

Text {
    id: element1
    x: 787
    y: 227
    text: qsTr("Piksel Noktası")
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: 13
    horizontalAlignment: Text.AlignHCenter
}

Rectangle {
    id: rectangle3
    x: 893
    y: 343
    width: 80
    height: 80
    color: "#c34d4d"

    Text {
        id: txtOynat
        x: 0
        y: 0
        color: "#eee2e2"
        text: qsTr("Oynat")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 18

    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            oynat = !oynat;

            if(oynat)
            {
                txtOynat.text = "OYNAT";
                onOynatBasildi(1);
            }
            else
            {
                txtOynat.text = "YÜRÜT";
                onOynatBasildi(0);
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
