import QtQuick 2.12
import QtQuick.Controls 2.5
import GameManager 1.0
import Player 1.0

Page {
    title: qsTr("Game Over")
    width: 640
    height: 480

    Label {
        text: playerA.state === Player.Alive && playerB.state === Player.Alive ? qsTr("Game Over") :
              playerA.state === Player.Alive && playerB.state === Player.Dead ? qsTr("Winner is " + playerA.name) :
              playerA.state === Player.Dead && playerB.state === Player.Alive ? qsTr("Winner is " + playerB.name) :
              playerA.state === Player.Dead && playerB.state === Player.Dead ? qsTr("Players are both dead") :
                                                                             qsTr("Players states are undefined")

        font.pointSize: 24
        anchors.centerIn: parent
    }
}
