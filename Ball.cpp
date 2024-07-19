#include "Ball.h"
#include "Player.h"
#include <QTimer>
#include <QDebug>
#include <cmath>
#include <QRandomGenerator>

// Constructor of the Ball class.
Ball::Ball(QGraphicsScene* scene)
    : QObject(), QGraphicsEllipseItem(), scene_(scene), active(false), speedX(0), speedY(0) {
    sceneWidth = scene->width();  // Width of the scene.
    sceneHeight = scene->height();  // Height of the scene.
    qreal radius = sceneHeight / 100;  // Sets the radius of the ball as 1/100 of the scene height.
    setBrush(QBrush(Qt::red));  // Sets the ball color to red.
    setPen(QPen(Qt::NoPen));  // Sets the ball without an outline.
    setRect(0, 0, 2 * radius, 2 * radius);  // Sets the ball's rectangle.
    setPos(sceneWidth / 2 - radius, sceneHeight / 2 - radius);  // Positions the ball in the center of the scene.
}

// Method called when a player hits the ball.
void Ball::hitByPlayer(QPointF direction, qreal force) {
    qreal massOfBall = 1.0;  // Mass of the ball for game effects.
    qreal massOfPlayer = 5.0;  // Mass of the player based on attributes.
    qreal norm = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());  // Normalizes the direction.
    if (norm > 0) {
        direction /= norm;  // Normalizes the direction vector.
    }

    QPointF impulse = direction * force / (massOfBall + massOfPlayer);  // Calculates the impulse applied to the ball.
    speedX += impulse.x();  // Adjusts the X speed.
    speedY += impulse.y();  // Adjusts the Y speed.

    active = true;  // Activates the ball to start moving.
}

// Method to move the ball in the scene.
void Ball::move() {
    if (!active) {
        // Initializes a random speed for the first movement.
        qreal minSpeed = 1.0;  // Minimum speed.
        qreal maxSpeed = 3.0;  // Maximum speed.
        std::uniform_real_distribution<qreal> dist(minSpeed, maxSpeed);

        speedX = dist(*QRandomGenerator::global()) * (QRandomGenerator::global()->generate() % 2 ? 1 : -1);
        speedY = dist(*QRandomGenerator::global()) * (QRandomGenerator::global()->generate() % 2 ? 1 : -1);
        active = true;
    }

    qreal newX = x() + speedX;  // Calculates the new X position.
    qreal newY = y() + speedY;  // Calculates the new Y position.

    // Checks for collisions with the edges and adjusts speed if necessary.
    qreal margin = 10.0;  // Safety margin.
    if (newX < margin || newX > sceneWidth - rect().width() - margin) {
        speedX = -speedX;  // Reverses the horizontal speed upon collision.
        newX = qBound(margin, newX, sceneWidth - rect().width() - margin);
    }
    if (newY < margin || newY > sceneHeight - rect().height() - margin) {
        speedY = -speedY;  // Reverses the vertical speed upon collision.
        newY = qBound(margin, newY, sceneHeight - rect().height() - margin);
    }

    setPos(newX, newY);  // Sets the new position of the ball.
    checkGoal();  // Checks if the ball has reached a goal.
    handleCollisions();  // Deals with collisions with other objects.
}


// Method to handle collisions.
void Ball::handleCollisions() {
    QList<QGraphicsItem *> collisions = collidingItems();
    qreal elasticity = 0.5;  // Reduced elasticity for less energetic bounces.
    qreal collisionBuffer = 5.0;  // Increased collision buffer.

    foreach (QGraphicsItem *item, collisions) {
        Player *player = dynamic_cast<Player *>(item);
        if (player) {
            QPointF collisionVector = pos() - player->pos();
            qreal norm = std::sqrt(collisionVector.x() * collisionVector.x() + collisionVector.y() * collisionVector.y());
            if (norm == 0) continue;  // Avoids division by zero.

            QPointF collisionNormal = collisionVector / norm;
            qreal incidentVelocity = QPointF::dotProduct(QPointF(speedX, speedY), collisionNormal);
            QPointF reflectedVelocity = QPointF(speedX, speedY) - 2 * incidentVelocity * collisionNormal;
            reflectedVelocity *= elasticity;

            speedX = reflectedVelocity.x();  // Sets the new X speed after collision.
            speedY = reflectedVelocity.y();  // Sets the new Y speed after collision.

            // Adjusts the position to be out of collision reach.
            setPos(pos() + collisionNormal * collisionBuffer);
        }
    }
}

// Method to check if the ball has reached any goal.
void Ball::checkGoal() {
    QList<QGraphicsItem *> collisionList = collidingItems();
    foreach(QGraphicsItem *item, collisionList) {
        if (item->data(0).toString() == "goal1") {
            emit goal1Reached();  // Emits a goal signal for team 1.
            reset();  // Resets the ball's position.
        } else if (item->data(0).toString() == "goal2") {
            emit goal2Reached();  // Emits a goal signal for team 2.
            reset();  // Resets the ball's position.
        }
    }
}

// Method to reset the ball's position and speed.
void Ball::reset() {
    setPos(sceneWidth / 2, sceneHeight / 2);  // Sets the ball in the center of the scene.
    speedX = 0;  // Resets the X speed.
    speedY = 0;  // Resets the Y speed.
    active = false;  // Deactivates the ball.
    qDebug() << "Ball reset to center, speeds reset";  // Debug log.
}
