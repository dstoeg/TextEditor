import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

Canvas {

    focus: true
    objectName: "canvas"
    anchors.fill: parent
    antialiasing: false

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

    function drawString(text, x, y, font)
    {
        var ctx = getContext("2d");
        ctx.font = font;
        ctx.fillStyle = "black";
        ctx.fillText(qsTr(text), x, y);
        ctx.stroke();
    }

    property bool caret: false;

    function invertCaret(caretX, caretY)
    {
        caret = !caret;
        var ctx = getContext("2d");
        ctx.strokeStyle = caret ? "black" : "white";

        var x = caretX;
        var y = caretY;
        ctx.beginPath();
        for (var i = 8; i>0; i--)
        {
            ctx.moveTo(x, y)
            ctx.lineTo(x, y+i);
            x++;
            y++;
            ctx.stroke();
        }
    }

    function invertSelection(x, y, width, height)
    {
        var ctx = getContext("2d");
        ctx.save();
        ctx.globalCompositeOperation = "xor";
        ctx.fillRect(x, y, width, height);
        ctx.restore();
    }

    function repaint(x, y, width, height)
    {
        var ctx = getContext("2d");
        ctx.clearRect(x,y,width, height);
        requestPaint();
    }

    onPaint: {
        viewer.paint();
    }
}
