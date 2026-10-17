#pragma once

#include"atlas.h"
#include"util.h"
#include"timer.h"

class Animation {
public:
	Animation() {
		timer.set_one_shot(false);
		timer.set_time_out([&]() {
			idx_frame++;
			if (idx_frame >= atlas->get_size()) {
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				if (!is_loop && finished)
					finished();
			}
			});
	}
	~Animation() = default;

	void set_finished(std::function<void()> on_finished) {
		this->finished = on_finished;
	}

	void set_atlas(Atlas* atlas) {
		this->atlas = atlas;
	}

	void set_interval(int val) {
		timer.set_wait_time(val);
	}

	void set_loop(bool flag) {
		is_loop = flag;
	}

	void set_position(POINT position) {
		this->position = position;
	}

	void reset() {
		idx_frame = 0;
		timer.reset();
	}

	void on_update(int delta) {
		timer.on_update(delta);
	}

	void on_render() {
		putimage_alpha(position.x, position.y, atlas->get_image(idx_frame));
	}

private:
	int idx_frame = 0;
	bool is_loop = true;
	POINT position = { 0,0 };
	Timer timer;
	Atlas* atlas = nullptr;
	std::function<void()> finished;
};
