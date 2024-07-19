#ifndef GOALKEEPER_H
#define GOALKEEPER_H

#include "Player.h"
#include <QGraphicsScene>
#include <QPointF>
#include <QColor>

// Goalkeeper class, a specialization of Player, representing the goalkeeper in the game.
class Goalkeeper : public Player {
public:
    // Constructor that initializes a goalkeeper with a scene, initial position, color, associated ball, and game direction.
    Goalkeeper(QGraphicsScene* scene, const QPointF& startPosition, const QColor& color, Ball* ball, int direction);

    // Function to check and move the goalkeeper back to the starting position based on the game conditions.
    void checkAndMoveToStartPosition() override;

private:
    qreal triggerDistance; // Distance from the goal that triggers the return to the starting position.
};

#endif // GOALKEEPER_H
