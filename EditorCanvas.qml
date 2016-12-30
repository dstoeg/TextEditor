import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

Canvas {

    focus: true
    objectName: "canvas"
    anchors.fill: parent

    MouseArea {
        anchors.fill: parent
        onClicked: {
            viewer.OnMouseClicked(mouseX, mouseY);
            mouse.accepted = true;
        }
        onPositionChanged: {
            if (pressedButtons & Qt.LeftButton)
                viewer.OnMouseDragged(mouseX, mouseY);
        }
        onReleased: {
            viewer.OnMouseReleased();
            mouse.accepted = true;
        }
    }

    Keys.onPressed:
    {
        if (event.key === Qt.Key_Left || event.key === Qt.Key_Right ||
                event.key === Qt.Key_Up || event.key === Qt.Key_Down)
            viewer.OnKeyPressed(event.key);
        else
            viewer.OnKeyTyped(event.key);
        event.accepted = true;
    }

    function drawString(text, x, y, font, style)
    {
        var ctx = getContext("2d");
        //ctx.reset();
        ctx.font = font;

        ctx.fillText(qsTr(text), x, y);
    }

    onPaint: {
        viewer.paint();
    }
}
