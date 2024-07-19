#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPointF>
#include <QColor>
#include "Ball.h"
#include <vector>

// Player class is a base class for all types of players in the game.
class Player : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    // Player constructor that sets up the scene, initial position, color, ball, direction, and player type.
    Player(QGraphicsScene* scene, const QPointF& position, const QColor& color, Ball* ball, int direction);
    virtual ~Player();

    // Game control methods
    void startGame();  // Starts the game settings for the player.
    void moveToStartPosition();  // Moves the player to the starting position.
    virtual void checkAndMoveToStartPosition() = 0; // Ensures this function is purely virtual.
    virtual void interactWithBall(); // Method to interact with the ball, customizable by child classes.

    // Position and interaction methods
    void updatePosition(std::vector<Player*> players);  // Updates position based on other players.
    bool checkOverlap(std::vector<Player*> players);  // Checks for overlap with other players.
    void resetPosition();  // Resets the position to the initial.

protected:
    QGraphicsScene* scene;
    QPointF currentPosition;  // Current position in the game.
    QPointF startPosition;  // Initial position.
    QColor teamColor;  // Team color.
    Ball* ball;  // Game ball.
    int direction;  // Movement direction.
    qreal playerSize;  // Player size.
    bool gameStarted = false;  // Indicates whether the game has started.

    // Parameters for interaction, to be defined in derived classes
    virtual qreal interactionDistance() const;  // Interaction distance with the ball.
    virtual qreal interactionForce() const;  // Interaction force with the ball.
};

#endif // PLAYER_H
