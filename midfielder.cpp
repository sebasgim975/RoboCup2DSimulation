#include "midfielder.h"
#include <QBrush>

// Constructor of the Midfielder, initializes with the scene, start position, color, ball, and game direction.
Midfielder::Midfielder(QGraphicsScene* scene, const QPointF& startPosition, const QColor& color, Ball* ball, int direction)
    : Player(scene, startPosition, color, ball, direction) {
    QPen pen(QColorConstants::Svg::purple);  // Sets the border color of the player's drawing to purple.
    pen.setWidth(2);  // Sets the width of the border of the player's drawing.
    setPen(pen);      // Applies the configured pen to set the border color.
}

// Function to check and move the midfielder back to the starting position.
void Midfielder::checkAndMoveToStartPosition() {
    // Simply does nothing or logs that this method was called, if necessary for debugging.
}
