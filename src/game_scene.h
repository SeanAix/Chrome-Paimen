#pragma once

#include<vector>

#include"player.h"
#include"pig_enemy.h"

class GameScene {
public:
	enum class GameState {
		Running, GameOver
	};

public:
	GameScene();
	~GameScene();

	void on_update(int delta);
	void on_render();
	void on_input(const ExMessage& msg);
	void on_draw_score();
	void restart();
	void set_max_score(int num);
	void on_draw_game_over();
	const GameState& get_game_state()const;
	bool is_collide();
	int get_max_score()const;

private:
	Timer timer_restart;
	bool is_timer_restart_finished = false;

	GameState state = GameState::Running;

	Player* player = nullptr;
	PigEnemy* enemy = nullptr;

	Atlas atlas_player;
	Atlas atlas_enemy;

	POINT position_sky = { 0,0 };
	POINT position_grass = { 0,0 };

	IMAGE img_sky;
	IMAGE img_grass;

	TCHAR score_text[64];

	int score = 0;
	int max_score = 0;

	bool is_saved = false;

	float enemy_original_speed = -0.2f;
	float sky_original_speed = -0.06f;
	float grass_original_speed = -0.2f;

	float enemy_run_speed = -0.2f;
	float enemy_max_speed = -0.55f;
	float sky_speed = -0.06f;
	float grass_speed = -0.2f;

};