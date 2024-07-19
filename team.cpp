#include "Team.h"
#include <QDebug>

// Construtor da classe Team: inicializa uma equipe com uma cena e uma bola associadas.
Team::Team(QGraphicsScene* scene, Ball* ball) : scene(scene), ball(ball), gameStarted(false) {}

// Destrutor da classe Team.
Team::~Team() {}

// Método para inicializar os jogadores da equipe com posições e funções específicas.
void Team::initializePlayers(QGraphicsScene* scene, Ball* ball, QColor teamColor, qreal baseX, int direction) {
    qreal offsetMultiplier = 50;  // Distância entre os tipos de jogadores, mantendo consistência no layout.

    // Criação do goleiro com posição definida a depender da direção da equipe.
    qreal goalWidth = 30;  // Largura aproximada da área do gol, ajustável conforme as dimensões do campo real.
    qreal goalkeeperX = (direction != 1) ? (scene->width() - goalWidth) : goalWidth;
    qreal goalkeeperY = scene->height() / 2;  // Centralizado verticalmente.
    auto goalkeeper = std::make_unique<Goalkeeper>(scene, QPointF(goalkeeperX, goalkeeperY), teamColor, ball, direction);
    players.push_back(std::move(goalkeeper));

    // Criação dos defensores com deslocamento em relação ao goleiro.
    qreal defenderOffsetX = offsetMultiplier;  // Um passo de deslocamento do goleiro.
    qreal defenderY1 = scene->height() / 3;  // Posicionamento de um defensor mais acima.
    qreal defenderY2 = 2 * scene->height() / 3;  // Posicionamento de um defensor mais abaixo.
    auto defender1 = std::make_unique<Defender>(scene, QPointF(baseX + direction * defenderOffsetX, defenderY1), teamColor, ball, direction);
    auto defender2 = std::make_unique<Defender>(scene, QPointF(baseX + direction * defenderOffsetX, defenderY2), teamColor, ball, direction);
    players.push_back(std::move(defender1));
    players.push_back(std::move(defender2));

    // Criação do meio-campista com deslocamento duplo a partir do goleiro.
    qreal midfielderOffsetX = offsetMultiplier * 2;  // Dois passos de deslocamento do goleiro.
    qreal midfielderY = scene->height() / 2; // Centralizado verticalmente.
    auto midfielder = std::make_unique<Midfielder>(scene, QPointF(baseX + direction * midfielderOffsetX, midfielderY), teamColor, ball, direction);
    players.push_back(std::move(midfielder));

    // Criação dos atacantes com deslocamento triplo a partir do goleiro.
    qreal attackerOffsetX = offsetMultiplier * 3;  // Três passos de deslocamento do goleiro.
    qreal attackerY1 = scene->height() / 2 - 50; // Atacante superior.
    qreal attackerY2 = scene->height() / 2 + 50; // Atacante inferior.
    auto attacker1 = std::make_unique<Attacker>(scene, QPointF(baseX + direction * attackerOffsetX, attackerY1), teamColor, ball, direction);
    auto attacker2 = std::make_unique<Attacker>(scene, QPointF(baseX + direction * attackerOffsetX, attackerY2), teamColor, ball, direction);
    players.push_back(std::move(attacker1));
    players.push_back(std::move(attacker2));

    // Inicia o jogo para a equipe, ativando os jogadores.
    startGame();
}

// Método para iniciar o jogo, definindo que o jogo começou e ativando todos os jogadores.
void Team::startGame() {
    gameStarted = true;
    for (auto& player : players) {
        player->startGame();
    }
    qDebug() << "Game started for all players.";
}

// Atualiza a equipe considerando a dinâmica do jogo, ajustando posições e resolvendo sobreposições.
void Team::updateTeam(const std::vector<Player*>& allPlayers) {
    if (!gameStarted) {
        qDebug() << "Game has not started.";
        return;
    }

    // Atualiza posições com base na dinâmica do jogo.
    for (auto& player : players) {
        player->updatePosition(allPlayers);
    }

    // Verifica e resolve quaisquer sobreposições entre jogadores.
    for (auto& player : players) {
        player->checkOverlap(allPlayers);
    }

    // Opcional: Verifica se os jogadores precisam retornar às posições iniciais.
    for (auto& player : players) {
        player->checkAndMoveToStartPosition();
    }

    // Atualiza a cena.
    scene->update();
}

// Retorna uma referência constante ao vetor de jogadores únicos.
const std::vector<std::unique_ptr<Player>>& Team::getPlayers() const {
    return players;
}
