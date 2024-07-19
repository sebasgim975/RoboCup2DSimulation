#include "goalkeeper.h"
#include <QBrush>

// Constructor of the Goalkeeper, initializes with the scene, start position, color, ball, and game direction.
Goalkeeper::Goalkeeper(QGraphicsScene* scene, const QPointF& startPosition, const QColor& color, Ball* ball, int direction)
    : Player(scene, startPosition, color, ball, direction) {
    QPen pen(Qt::green);  // Sets the border color of the player's drawing to green.
    pen.setWidth(2);  // Sets the width of the border of the player's drawing.
    setPen(pen);      // Applies the configured pen to set the border color.
}

// Checks the position of the ball and determines if the goalkeeper should return to the start position.
void Goalkeeper::checkAndMoveToStartPosition() {
    QPointF ballPosition = ball->pos();  // Gets the current position of the ball.
    qreal sceneWidth = scene->width();   // Width of the game scene.
    // Sets the return trigger based on the direction of the goalkeeper.
    qreal returnTriggerX = sceneWidth * 0.25;  // Return point set as a quarter of the scene width.

    // Determines if the goalkeeper should return based on the ball's position and direction.
    bool shouldReturn = (direction == 1) ? (ballPosition.x() > returnTriggerX) : (ballPosition.x() < sceneWidth - returnTriggerX);
    if (shouldReturn) {
        moveToStartPosition();  // Returns to the start position if necessary.
    }
}
