import QtQuick 2.12
import QtQuick.Controls 2.5
import GameManager 1.0
import "qrc:/ui" as UI

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("PizzaGame")

    Connections {
        id: gameManagerItem
        target: gameManager
        onStateChanged: {
            if (gameManager.state === GameManager.GameOver)
                stackView.pop()
        }
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("New Game")
                width: parent.width
                onClicked: {
                    gameManager.newGame();
                    stackView.push("Game.ui.qml");
                    drawer.close();
                }
            }
            ItemDelegate {
                text: qsTr("Exit")
                width: parent.width
                onClicked: {
                    Qt.quit();
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "GameOver.ui.qml"
        anchors.fill: parent
    }
}
