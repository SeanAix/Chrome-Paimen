#include"animation.h"
#include"game_scene.h"

#include<ctime>
#include <mmsystem.h>
#include<fstream>
#pragma comment(lib, "winmm.lib")



int main() {

	mciSendString(_T("open resources/bgm.mp3 alias bgm"), NULL, 0, NULL);

	srand(static_cast<unsigned int>(time(NULL)));

	initgraph(600, 288);
	
	ExMessage msg;
	GameScene game_scene;

	bool running = true;

	const int FPS = 30;

	POINT position_enemy = { getwidth(),140};

	int max_score;
	std::ifstream in_file("MaxScore.txt");
	if (!in_file.is_open()) {
		max_score = 0;
		write_max_score(max_score);
	}
	else {
		if (!(in_file >> max_score)) {
			max_score = 0;
		}
	}
	game_scene.set_max_score(max_score);

	DWORD last_time = GetTickCount();

	BeginBatchDraw();

	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	while (running) {
		while (peekmessage(&msg)) {
			game_scene.on_input(msg);
		}

		DWORD start_time = GetTickCount();
		DWORD delta_time = start_time - last_time;
		last_time = start_time;

		cleardevice();

		game_scene.on_update(delta_time);
		game_scene.on_render();

		FlushBatchDraw();

		DWORD frame_time = GetTickCount() - start_time;
		if (frame_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_time);
	}
	EndBatchDraw();

	return 0;
}