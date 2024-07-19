#include "defender.h"
#include <QBrush>

// Defender constructor, initializes with the scene, start position, color, ball, and game direction.
Defender::Defender(QGraphicsScene* scene, const QPointF& startPosition, const QColor& color, Ball* ball, int direction)
    : Player(scene, startPosition, color, ball, direction) {
    QPen pen(Qt::blue);  // Sets the border color of the player's drawing to blue.
    pen.setWidth(2);  // Sets the width of the border of the player's drawing.
    setPen(pen);      // Applies the configured pen to set the border color.
}


// Checks the position of the ball and determines if the defender should return to the start position.
void Defender::checkAndMoveToStartPosition() {
    QPointF ballPosition = ball->pos();  // Gets the current position of the ball.
    qreal sceneWidth = scene->width();  // Width of the game scene.
    // Sets the return trigger based on the direction of the defender.
    qreal returnTriggerX = sceneWidth * 0.5;  // Return point set as the middle of the field

    // Determines if the defender should return based on the position of the ball and direction.
    bool shouldReturn = (direction == 1) ? (ballPosition.x() < returnTriggerX) : (ballPosition.x() > returnTriggerX);
    if (shouldReturn) {
        moveToStartPosition();  // Returns to the start position if necessary.
    }
}
