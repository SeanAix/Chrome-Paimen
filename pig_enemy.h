#pragma once

#include"animation.h"

class GameScene;

class PigEnemy {
	friend class GameScene;
public:
	void on_render();
	void on_update(int delta);

	void set_atlas(Atlas* atlas);
	void set_enemy_speed(float speed);
	void reset();
	bool is_run_out();

	const POINT& get_position()const;
private:
	float velocity = -0.2f;
	Animation animation;
	POINT position;

private:
	PigEnemy();
	~PigEnemy();
};