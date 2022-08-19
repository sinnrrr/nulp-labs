#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimerEvent>

#include <TileType.h>
#include <direction.h>
#include <tiles.h>

#define BASE_TICK_TIME_MS 1000

enum GameState { READY_FOR_START, RUNNING, STOPPED };

class GameController : public QObject {
  Q_OBJECT

public:
  GameController(int fieldSize);
  ~GameController();

  GameState gameState() { return state; }

  void forceFieldRedraw();

  void snakeLeft() { tryChangeDirection(DIRECTION_LEFT); }
  void snakeRight() { tryChangeDirection(DIRECTION_RIGHT); }
  void snakeUp() { tryChangeDirection(DIRECTION_UP); }
  void snakeDown() { tryChangeDirection(DIRECTION_DOWN); }

  void resetGame();
  void startGame();

  void setGameSpeed(int speed);

signals:
  void gameStartEvent();

  void tileUpdateEvent(int x, int y, TileType newType);

  void gameStopEvent(int score);

private slots:
  void timerEvent(QTimerEvent *event);

private:
  const int INITIAL_SNAKE_LENGTH = 3;
  const int INITIAL_SNAKE_POSITION_X = 5;
  const int INITIAL_SNAKE_POSITION_Y = 3;

  GameState state;
  int timerId;

  int fieldSize;
  tile **field;

  int snakeHeadX;
  int snakeHeadY;
  direction snakeHeadDirection;
  direction newSnakeHeadDirection;

  int snakeLength;

  int gameSpeed = 5;

  tiletype getTileTypeInFront();

  void moveHead(direction headDirection);
  void moveTail();

  void updateGameState(GameState newState);

  void allocateField();
  void prepareFieldForStart();
  void prepareSnake();
  void deleteField();

  void placeFruit();

  void tick();
  void getRandomCoordinates(int *x, int *y);

  void tryChangeDirection(direction newDirection);

  void updateTileAt(int x, int y, tile newTile);
  TileType tileToEnum(tile t);
};

#endif // GAMECONTROLLER_H
