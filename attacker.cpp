#include "attacker.h"
#include <QBrush>

// Attacker constructor, initializes with scene, start position, color, ball, and game direction.
Attacker::Attacker(QGraphicsScene* scene, const QPointF& startPosition, const QColor& color, Ball* ball, int direction)
    : Player(scene, startPosition, color, ball, direction) {
    QPen pen(Qt::red);  // Sets the border color of the player's drawing to red.
    pen.setWidth(2);  // Sets the width of the border of the player's drawing.
    setPen(pen);      // Applies the configured pen to set the border color.
}

// Checks the position of the ball and determines if the attacker should return to the start position.
void Attacker::checkAndMoveToStartPosition() {
    QPointF ballPosition = ball->pos();  // Gets the current position of the ball.
    qreal sceneWidth = scene->width();  // Width of the game scene.
    // Sets the return trigger based on the attacker's direction.
    qreal returnTriggerX = (direction == 1) ? sceneWidth * 0.25 : sceneWidth * 0.75;  // Return point set as one quarter of the field width for direction 1, and three quarters for the opposite direction

    // Determines if the attacker should return based on the ball's position and direction.
    bool shouldReturn = (direction == 1) ? (ballPosition.x() < returnTriggerX) : (ballPosition.x() > returnTriggerX);
    if (shouldReturn) {
        moveToStartPosition();  // Returns to the start position if necessary.
    }
}
