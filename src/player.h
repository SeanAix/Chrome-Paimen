#pragma once

#include"animation.h"

class GameScene;

class Player {
public:
	friend class GameScene;
public:

	void on_update(int delta);
	void on_render();

	void on_jump();
	bool can_jump();

	void on_floor();
	void set_atlas(Atlas* altas);
	void reset();

	const POINT& get_position()const {
		return position;
	}

private:
	bool is_on_floor = true;
	bool is_alive = true;
	bool is_jump_cd = false;
	bool is_jump_effect_visible = false;
	bool is_land_effect_visible = false;

	float gravity = 0.0012f;

	float velocity_y = 0;

	Timer timer_jump_cd;
	Animation animation_player;
	POINT position = { 0,0 };

	Atlas atlas_jump_effect;
	Atlas atlas_land_effect;

	Animation animation_jump_effect;
	Animation animation_land_effect;

private:
	Player();
	~Player();
};