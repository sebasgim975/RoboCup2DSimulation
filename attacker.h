#ifndef ATTACKER_H
#define ATTACKER_H

#include "Player.h"
#include <QGraphicsScene>
#include <QPointF>
#include <QColor>

// The Attacker class inherits from Player, specializing it for the role of attacker in the game.
class Attacker : public Player {
public:
    // Constructor that initializes an attacker with a scene, initial position, color, associated ball, and game direction.
    Attacker(QGraphicsScene* scene, const QPointF& startPosition, const QColor& color, Ball* ball, int direction);

    // Function to check and return to the starting position based on the game conditions
    void checkAndMoveToStartPosition() override;

private:
    qreal triggerDistance; // Distance from the goal to trigger the return to the starting position
};

#endif // ATTACKER_H
