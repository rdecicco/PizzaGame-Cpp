import QtQuick 2.12
import QtQuick.Controls 2.5
import GameManager 1.0
import Player 1.0

Page {
    title: qsTr("Game")
    width: 640
    height: 480

    Label {
        id: numberOfPizzas
        text: "Pizzas: " + gameManager.numberOfPizzas
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.centerIn: parent
    }

    PlayerItem {
        id: playerItemA
        player: playerA

        anchors.left: parent.left
        anchors.leftMargin: 80
        anchors.verticalCenter: parent.verticalCenter
    }

    PlayerItem {
        id: playerItemB
        player: playerB

        anchors.right: parent.right
        anchors.rightMargin: 80
        anchors.verticalCenter: parent.verticalCenter
    }
}
