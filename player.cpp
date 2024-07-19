#include "Player.h"
#include <QGraphicsScene>
#include <cmath>
#include <QDebug>

// Constructor of the Player class. Initializes a player with specific parameters.
Player::Player(QGraphicsScene* scene, const QPointF& position, const QColor& color, Ball* ball, int direction)
    : QObject(nullptr), QGraphicsEllipseItem(), scene(scene), currentPosition(position), startPosition(position), teamColor(color), ball(ball), direction(direction), playerSize(scene->height() / 25) {
    // Sets up the player's visual rectangle in the scene.
    setRect(-playerSize / 2, -playerSize / 2, playerSize, playerSize);
    // Sets the player's fill color.
    setBrush(QBrush(color));
    // Sets the border color and thickness.
    setPen(QPen(color, 2));
    // Sets the player's initial position in the scene.
    setPos(position);
    // Adds the player object to the graphic scene.
    scene->addItem(this);
}

// Destructor: performs necessary cleanup when a Player object is destroyed.
Player::~Player() {
}

// Starts the game, allowing the player to begin interacting in the game.
void Player::startGame() {
    gameStarted = true;
}

// Method that defines how the player interacts with the ball if close enough.
void Player::interactWithBall() {
    // If there is no ball or the game hasn't started, does nothing.
    if (!ball || !gameStarted) return;

    // Calculates the direction and distance to the ball.
    QPointF ballPosition = ball->pos();
    QPointF directionToBall = ballPosition - pos();
    qreal distance = std::sqrt(directionToBall.x() * directionToBall.x() + directionToBall.y() * directionToBall.y());

    // If within the interaction distance, interacts with the ball.
    if (distance < interactionDistance()) {
        directionToBall /= distance;  // Normalizes the direction.
        qreal force = interactionForce();  // Determines the player's force.
        ball->hitByPlayer(directionToBall, force);  // Impacts the ball with the calculated direction and force.
    }
}

// Returns the standard distance at which the player can interact with the ball.
qreal Player::interactionDistance() const {
    return 30;  // Standard interaction distance.
}

// Returns the standard interaction force of the player with the ball.
qreal Player::interactionForce() const {
    return 2.0;  // Standard interaction force.
}

// Moves the player back to their starting position.
void Player::moveToStartPosition() {
    // Calculates the direction and distance to the starting position.
    QPointF directionToStart = startPosition - pos();
    qreal distanceToStart = std::sqrt(directionToStart.x() * directionToStart.x() + directionToStart.y() * directionToStart.y());
    if (distanceToStart > 0) {
        // Normalizes the direction and moves the player back with a base speed.
        QPointF normalizedDirection = directionToStart / distanceToStart;
        qreal moveSpeed = 2.0;  // Movement speed to the starting position.
        setPos(pos() + normalizedDirection * moveSpeed);
    }
}
// Checks for collisions with other players and adjusts the position to avoid overlap.
bool Player::checkOverlap(std::vector<Player*> players) {
    bool collisionDetected = false;
    qreal radius = playerSize / 2;
    const qreal separationFactor = 2.5;  // Factor that adjusts the separation during collision correction.

    for (Player* other : players) {
        if (other != this) {
            // Calculates the distance and checks for overlap.
            qreal distance = QLineF(pos(), other->pos()).length();
            qreal requiredDistance = (radius + other->playerSize / 2) + 5;

            if (distance < requiredDistance) {
                collisionDetected = true;
                // Calculates the correction vector to resolve the overlap.
                qreal overlap = (requiredDistance - distance) / 2 * separationFactor;
                QPointF direction = pos() - other->pos();
                qreal norm = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

                if (norm != 0) {
                    direction /= norm;  // Normalizes the direction.
                    QPointF correctionVector = direction * overlap;
                    // Adjusts the positions of the players to resolve the overlap.
                    setPos(pos() + correctionVector);
                    other->setPos(other->pos() - correctionVector);
                }
            }
        }
    }
    return collisionDetected;
}

// Updates the player's position based on the ball's position and the proximity of other players.
void Player::updatePosition(std::vector<Player*> players) {
    if (!ball || !gameStarted) return;

    // Calculates the distance to the ball.
    QPointF ballPosition = ball->pos();
    qreal distance = QLineF(pos(), ballPosition).length();
    qreal decelerationFactor = 1.0;
    qreal minDistanceToPlayer = std::numeric_limits<qreal>::max();

    for (auto& player : players) {
        if (player != this) {
            // Calculates the shortest distance to another player.
            qreal distToPlayer = QLineF(pos(), player->pos()).length();
            if (distToPlayer < minDistanceToPlayer) {
                minDistanceToPlayer = distToPlayer;
            }
        }
    }

    // Adjusts the speed if there are nearby players.
    if (minDistanceToPlayer < 100) {
        decelerationFactor = minDistanceToPlayer / 100;
    }

    // Interacts with the ball if within a specified distance.
    if (distance < 150) {
        interactWithBall();
        QPointF direction = (ballPosition - pos()).toPoint();
        qreal norm = std::hypot(direction.x(), direction.y());
        if (norm != 0) {
            // Normalizes the direction and adjusts the movement speed based on calculated factors.
            QPointF normalizedDirection = direction / norm;
            qreal adjustedSpeed = 3.0 * decelerationFactor;
            setPos(pos() + normalizedDirection * adjustedSpeed);
        }
    }
}

// Resets the player's position to the starting position after a goal or similar.
void Player::resetPosition() {
    setPos(startPosition);
}
