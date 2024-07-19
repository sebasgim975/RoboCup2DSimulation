#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPointF>
#include <QGraphicsScene>

// The Ball class inherits from QObject and QGraphicsEllipseItem to incorporate functionalities of an object and elliptical graphic item.
class Ball : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT // Macro necessary to enable slots and signals, Qt functionalities for communication between objects.

public:
    explicit Ball(QGraphicsScene* scene); // Constructor that initializes the ball within a graphic scene.
    void hitByPlayer(QPointF direction, qreal force); // Method to define how the ball is hit by a player.
    void reset(); // Method to reset the position and state of the ball.

signals:
    void goal1Reached(); // Signal emitted when the ball reaches goal 1.
    void goal2Reached(); // Signal emitted when the ball reaches goal 2.
    void goalScored(); // Signal that can be emitted when a goal is scored.

private:
    friend class Dialog;  // Allows the Dialog class to access protected and private sections of the Ball class.

    void move(); // Private method to move the ball during the game.
    void handleCollisions(); // Method to handle collisions of the ball with other scene objects.
    void checkGoal(); // Method to check if the ball has reached a goal.

    QGraphicsScene* scene_; // Reference to the scene where the ball is contained.
    qreal speedX; // Horizontal speed of the ball.
    qreal speedY; // Vertical speed of the ball.
    bool active; // State that indicates whether the ball is active in the game.
    qreal sceneWidth; // Scene width for boundary control.
    qreal sceneHeight; // Scene height for boundary control.
};

#endif // BALL_H
