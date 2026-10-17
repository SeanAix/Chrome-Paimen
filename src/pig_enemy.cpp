#include"pig_enemy.h"

PigEnemy::PigEnemy() {
	position = { getwidth(),135 };

	animation.set_interval(100);
	animation.set_loop(true);
	animation.set_position(position);
	animation.set_finished([]() {});

}
PigEnemy::~PigEnemy() = default;

void PigEnemy::on_update(int delta) {
	position.x += velocity * delta;
	animation.set_position(position);
	animation.on_update(delta);
}

void PigEnemy::on_render() {
	animation.on_render();
}

void PigEnemy::set_atlas(Atlas* atlas) {
	animation.set_atlas(atlas);
}

const POINT& PigEnemy::get_position()const {
	return position;
}

bool PigEnemy::is_run_out() {
	return (position.x + 80) < 0;
}

void PigEnemy::set_enemy_speed(float speed) {
	this->velocity = speed;
}

void PigEnemy::reset() {
	position.x = getwidth() + rand_range(0, 80);
	animation.reset();
}