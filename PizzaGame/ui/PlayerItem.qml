import QtQuick 2.0
import Player 1.0
import GameManager 1.0
import Player 1.0
import QtQuick.Controls 2.5

Rectangle {
    property Player player
    property ListModel comboPizzasModel

    width: 150
    height: 230
    radius: 10

    enabled: player.currentPlayer

    color: "Black"
    border.color: "Black"
    border.width: 1

    Label {
        id: name
        text: player.name
        color: "White"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        height: 35
    }

    ComboBox {
        id: comboPizzas
        enabled: parent.enabled
        textRole: "value"
        model: player.comboPizzasModel

        anchors.top: name.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    Button {
        id: confirm
        text: qsTr("Confirm");

        enabled: parent.enabled

        onClicked: {
            gameManager.eatPizzas(comboPizzas.model[comboPizzas.currentIndex].value);
        }

        anchors.top: comboPizzas.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    Button {
        id: pass
        text: qsTr("Pass");

        enabled: parent.enabled && gameManager.canPass()

        onClicked: {
            gameManager.eatPizzas(0, player);
        }

        anchors.top: confirm.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }
}
