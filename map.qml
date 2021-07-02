import QtQuick 2.12; 
import QtQuick.Controls 2.12;
import QtQuick.Window 2.12;
import QtQuick.Layouts 1.12;
import QtLocation 5.12;
import QtPositioning 5.12;

Item
{
  id : appWin;
  objectName : "appWin";
  width : 500;
  height : 500;
  visible : true;

  ColumnLayout
  {
    id : column;
    anchors.fill : parent;
    Row
    {
      Layout.alignment: Qt.AlignHCenter;
      Label
      {
        visible : true;
        text : "..";
        id : latLonLabel;
        color : "darkRed";
        font.pointSize : 10;
      }
    }

    Map
    {
      Layout.fillWidth : true;
      Layout.fillHeight : true;
      visible : true;
      id : osmMap;
      objectName : "osmMap";
      plugin : Plugin
      {
        name : "osm";
      }
      copyrightsVisible : false;
      zoomLevel : 3;
      center
      {
        latitude : 0;
        longitude : 0;
      }

      MouseArea
      {
        anchors.fill : parent;
        hoverEnabled : false;
        onPressed :
        {
          if (mouse.modifiers & Qt.ShiftModifier)
          {
            var coord = osmMap.toCoordinate(Qt.point(mouseX,mouseY));
            redRect.bottomRight.latitude = coord.latitude;
            redRect.bottomRight.longitude = coord.longitude;
            hoverEnabled = true;
            redRect.coords();
          }
        }
        onPositionChanged :
        {
          if (mouse.modifiers & Qt.ShiftModifier)
          {
            var coord = osmMap.toCoordinate(Qt.point(mouseX,mouseY));
            redRect.bottomRight.latitude = coord.latitude;
            redRect.bottomRight.longitude = coord.longitude;
            redRect.coords();
          }
        }
        onReleased : hoverEnabled = false;
      }

      MapRectangle
      {
        id : redRect;
        objectName : "redRect";
        border.color : "red";
        border.width : 4;
        opacity : 1;
        topLeft
        {
          latitude : 1;
          longitude : -1;
        }
        bottomRight
        {
          latitude : -1;
          longitude : 1;
        }
        MouseArea
        {
          anchors.fill : parent;
          cursorShape : drag.active ? Qt.ClosedHandCursor : Qt.OpenHandCursor;
          drag
          {
            target : parent;
          }
        }
        function coords()
        {
          var x = (redRect.topLeft.longitude + redRect.bottomRight.longitude) / 2;
          x = Number(x.toFixed(0));
          var y = (redRect.topLeft.latitude + redRect.bottomRight.latitude) / 2;
          y = Number(y.toFixed(0));
          var w = redRect.bottomRight.longitude - redRect.topLeft.longitude;
          w = Number(w.toFixed(0));
          var h = redRect.topLeft.latitude - redRect.bottomRight.latitude;
          h = Number(h.toFixed(0));
          latLonLabel.text = "latitude: " + y + "    longitude: " + x + "    width: " + w + "    height: " + h;
        }
        onXChanged : coords();
        onYChanged : coords();
      }
    }
  }
}
