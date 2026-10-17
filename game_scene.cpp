#include"game_scene.h"

GameScene::GameScene() {
	loadimage(&img_grass, _T("resources/grass.png"));
	loadimage(&img_sky, _T("resources/sky.png"));
	atlas_player.load(_T("resources/player_right_%d.png"), 6);
	atlas_enemy.load(_T("resources/enemy_left_%d.png"), 5);

	player = new Player();
	player->set_atlas(&atlas_player);

	enemy = new PigEnemy();
	enemy->set_atlas(&atlas_enemy);

	timer_restart.set_one_shot(true);
	timer_restart.set_wait_time(800);
	timer_restart.set_time_out([&]() {is_timer_restart_finished = true;});

}
GameScene::~GameScene() {
	mciSendString(_T("stop bgm"), NULL, 0, NULL);
	delete player;
	delete enemy;
}

void GameScene::on_input(const ExMessage& msg) {
	if(state==GameState::Running){
		if (msg.message == WM_KEYDOWN) {
			if (player->can_jump())
				player->on_jump();
		}
	}
	else if (state == GameState::GameOver) {
		if (msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE && is_timer_restart_finished) {
			restart();
		}
	}
}

void GameScene::on_render() {
	putimage_alpha(position_sky.x, position_sky.y, &img_sky);
	putimage_alpha(position_sky.x + img_sky.getwidth(), position_sky.y, &img_sky);
	putimage_alpha(position_grass.x, position_grass.y, &img_grass);
	putimage_alpha(position_grass.x + img_grass.getwidth(), position_grass.y, &img_grass);

	player->on_render();
	enemy->on_render();

	if(state==GameState::Running){
		on_draw_score();
	}
	else {
		on_draw_game_over();
	}
}

void GameScene::on_update(int delta) {
	if (state == GameState::Running) {
		if (position_sky.x <= -img_sky.getwidth())
			position_sky.x += img_sky.getwidth();

		if (position_grass.x <= -img_grass.getwidth())
			position_grass.x += img_grass.getwidth();

		position_sky.x += static_cast<int>(sky_speed * delta);
		position_grass.x += static_cast<int>(grass_speed * delta);

		if (enemy->is_run_out()) {
			enemy_run_speed -= 0.015f;
			if (enemy_run_speed < enemy_max_speed)
				enemy_run_speed = enemy_max_speed;
			sky_speed = enemy_run_speed * 0.3f;
			grass_speed = enemy_run_speed;

			enemy->set_enemy_speed(enemy_run_speed);
			enemy->reset();
			score++;
		}

		player->on_update(delta);
		enemy->on_update(delta);

		if (is_collide()) {
			if (score > max_score) {
				max_score = score;
			}
			state = GameState::GameOver;
			is_timer_restart_finished = false;
			timer_restart.reset();
		}
	}
	else {
		if (!is_saved) {
			write_max_score(max_score);
			is_saved = true;
		}
		timer_restart.on_update(delta);
	}
}

void GameScene::on_draw_score() {
	settextstyle(16, 0, _T("宋体"), 0, 0, FW_BOLD, false, false, false);

	_stprintf_s(score_text, _T("当前玩家得分:%d  最高得分:%d"), score,max_score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 100, 185));
	outtextxy(10, 10, score_text);
}

bool GameScene::is_collide() {
	POINT player_center;
	player_center.x = player->get_position().x + (atlas_player.get_image(0)->getwidth() / 2);
	player_center.y = player->get_position().y + (atlas_player.get_image(0)->getheight() / 2);
	bool is_collide_x = (player_center.x >= enemy->get_position().x) &&
		(player_center.x <= (enemy->get_position().x + atlas_enemy.get_image(0)->getwidth()));
	bool is_collide_y = (player_center.y >= enemy->get_position().y) &&
		(player_center.y <= (enemy->get_position().y + atlas_enemy.get_image(0)->getheight()));
	return is_collide_x && is_collide_y;
}

void GameScene::restart() {
	enemy->reset();
	enemy->set_enemy_speed(enemy_original_speed);
	player->reset();

	enemy_run_speed = enemy_original_speed;
	sky_speed = sky_original_speed;
	grass_speed = grass_original_speed;
	score = 0;
	state = GameState::Running;

	is_saved = false;
}

void GameScene::set_max_score(int num) {
	this->max_score = num;
}

const GameScene::GameState& GameScene::get_game_state()const {
	return state;
}

int GameScene::get_max_score()const {
	return max_score;
}

void GameScene::on_draw_game_over() {
	settextstyle(40, 0, _T("微软雅黑"), 0, 0, FW_BOLD, false, false, false);
	settextcolor(RGB(255, 0, 0));
	int title_x = (600 - textwidth(_T("GAME OVER"))) / 2;
	outtextxy(title_x, 80, _T("GAME OVER"));

	settextstyle(20, 0, _T("微软雅黑"));
	settextcolor(WHITE);
	int hint_x = (600 - textwidth(_T("按空格重新开始"))) / 2;
	outtextxy(hint_x, 140, _T("按空格重新开始"));

	settextstyle(25, 0, _T("微软雅黑"));
	TCHAR final_score[64];
	_stprintf_s(final_score, _T("得分: %d"), score);
	int score_x = (600 - textwidth(final_score)) / 2;
	outtextxy(score_x, 180, final_score);


}