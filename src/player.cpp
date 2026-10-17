#include"player.h"

Player::Player() {
	atlas_jump_effect.load(_T("resources/jump_effect_%d.png"), 5, 1);
	atlas_land_effect.load(_T("resources/land_effect_%d.png"), 2, 1);

	animation_jump_effect.set_atlas(&atlas_jump_effect);
	animation_jump_effect.set_interval(75);
	animation_jump_effect.set_loop(false);
	animation_jump_effect.set_finished([&]() {is_jump_effect_visible = false;});

	animation_land_effect.set_atlas(&atlas_land_effect);
	animation_land_effect.set_interval(75);
	animation_land_effect.set_loop(false);
	animation_land_effect.set_finished([&]() {is_land_effect_visible = false;});

	position = { 50,120 };

	animation_player.set_position(position);
	animation_player.set_interval(100);
	animation_player.set_loop(true);
	animation_player.set_finished([]() {});

	timer_jump_cd.set_one_shot(true);
	timer_jump_cd.set_wait_time(150);
	timer_jump_cd.set_time_out([&]() {is_jump_cd = false;});
}
Player::~Player() = default;

void Player::on_render() {
	animation_player.on_render();
	if (is_jump_effect_visible)
		animation_jump_effect.on_render();
	if (is_land_effect_visible)
		animation_land_effect.on_render();
}

void Player::on_update(int delta) {
	velocity_y += gravity * delta;
	position.y += velocity_y * delta;
	if (position.y > 120)
	{
		position.y = 120;
		velocity_y = 0;
		on_floor();
	}

	if(is_jump_cd){
		timer_jump_cd.on_update(delta);
	}

	if (is_jump_effect_visible)
		animation_jump_effect.on_update(delta);
	if (is_land_effect_visible)
		animation_land_effect.on_update(delta);

	animation_player.set_position(position);
	animation_player.on_update(delta);
}

bool Player::can_jump() {
	return is_alive && is_on_floor && !is_jump_cd;
}

void Player::on_jump() {
	animation_jump_effect.reset();
	animation_jump_effect.set_position(position);
	is_jump_effect_visible = true;
	velocity_y = -0.50f;
	is_on_floor = false;
}

void Player::on_floor() {
	if (!is_on_floor) {
		is_jump_cd = true;
		timer_jump_cd.reset();
		animation_land_effect.reset();
		animation_land_effect.set_position(position);
		is_land_effect_visible = true;
	}
	is_on_floor = true;
}

void Player::set_atlas(Atlas* atlas) {
	animation_player.set_atlas(atlas);
}

void Player::reset() {
	position = { 50,120 };
	velocity_y = 0;
	is_on_floor = true;
	is_jump_cd = false;
	is_jump_effect_visible = false;
	is_land_effect_visible = false;
	animation_player.set_position(position);
	animation_player.reset();
}