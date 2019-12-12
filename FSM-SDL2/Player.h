#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
	Player();
	~Player();

	void handleInput();
	void update();
};

#endif // !PLAYER_H