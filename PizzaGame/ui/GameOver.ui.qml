import QtQuick 2.12
import QtQuick.Controls 2.5
import GameManager 1.0
import Player 1.0

Page {
    title: qsTr("Game Over")
    width: 640
    height: 480

    Label {
        text: playerA.state == 1 && playerB.state == 1 ? qsTr("Game Over") :
              playerA.state == 1 && playerB.state == 0 ? qsTr("Winner is " + playerA.name) :
              playerA.state == 0 && playerB.state == 1 ? qsTr("Winner is " + playerB.name) : qsTr("Players are both dead")

        font.pointSize: 24
        anchors.centerIn: parent
    }
}
