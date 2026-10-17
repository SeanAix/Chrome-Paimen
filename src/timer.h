#pragma once

#include<functional>

class Timer {
public:
	Timer() = default;
	~Timer() = default;

	void set_wait_time(int val) {
		this->wait_time = val;
	}

	void set_one_shot(bool flag) {
		this->one_shot = flag;
	}

	void paused() {
		this->pause = true;
	}

	void resume() {
		this->pause = false;
	}

	void set_time_out(std::function<void()> time_out) {
		this->time_out = time_out;
	}

	void reset() {
		pass_time = 0;
		shotted = false;
	}

	void on_update(int delta) {
		if (pause)
			return;
		pass_time += delta;
		if (pass_time >= wait_time) {
			pass_time -= wait_time;
			if (((!one_shot) || (one_shot && !shotted)) && time_out) {
				time_out();
			}
			shotted = true;
		}
	}

private:
	int pass_time = 0;
	int wait_time = 0;
	bool shotted = false;
	bool one_shot = true;
	bool pause = false;
	std::function<void()> time_out;
};