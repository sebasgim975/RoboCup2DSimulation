#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Defender.h"
#include "Midfielder.h"
#include "Attacker.h"
#include "Goalkeeper.h"
#include "Ball.h"
#include <QGraphicsScene>

class Team
{
public:
    // Team constructor: sets up the scene and the ball associated with the team.
    Team(QGraphicsScene* scene, Ball* ball);
    // Team destructor.
    ~Team();

    // Initializes team players with color, base X position, and direction.
    void initializePlayers(QGraphicsScene* scene, Ball* ball, QColor teamColor, qreal baseX, int direction);
    // Updates the team's state based on the list of all players.
    void updateTeam(const std::vector<Player*>& allPlayers);
    // Starts the game, marking the game state as started.
    void startGame();
    // Returns the list of players in the team.
    const std::vector<std::unique_ptr<Player>>& getPlayers() const;

private:
    std::vector<std::unique_ptr<Player>> players; // Vector containing the team's players.
    QGraphicsScene* scene; // Game scene where the team is operating.
    Ball* ball; // Ball used in the game.
    bool gameStarted; // Indicates whether the game has been started.
};

#endif // TEAM_H
