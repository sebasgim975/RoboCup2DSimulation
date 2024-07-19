#ifndef DEFENDER_H
#define DEFENDER_H

#include "Player.h"
#include <QGraphicsScene>
#include <QPointF>
#include <QColor>

// The Defender class inherits from Player, specializing it for the role of defender in the game.
class Defender : public Player {
public:
    // Constructor that initializes a defender with a scene, initial position, color, associated ball, and game direction.
    Defender(QGraphicsScene* scene, const QPointF& startPosition, const QColor& color, Ball* ball, int direction);

    // Function to check and move the defender back to the starting position based on the game conditions.
    void checkAndMoveToStartPosition() override;

private:
    qreal triggerDistance; // Distance from the goal that triggers the return to the starting position.
};

#endif // DEFENDER_H
