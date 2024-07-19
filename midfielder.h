#ifndef MIDFIELDER_H
#define MIDFIELDER_H

#include "Player.h"
#include <QGraphicsScene>
#include <QPointF>
#include <QColor>
#include <QTimer>

// Midfielder class, derived from the Player class, representing a midfield player in the game.
class Midfielder : public Player {
public:
    // Constructor that initializes a midfield player with a scene, initial position, color, associated ball, and game direction.
    Midfielder(QGraphicsScene* scene, const QPointF& startPosition, const QColor& color, Ball* ball, int direction);

    // Function to check and move the midfield player back to the starting position based on game conditions.
    void checkAndMoveToStartPosition() override;
};

#endif // MIDFIELDER_H
