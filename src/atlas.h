#pragma once

#include<vector>
#include<graphics.h>

class Atlas {
public:
	Atlas() = default;
	~Atlas() = default;

	void load(LPCTSTR path_template, int num, int first_num = 0) {
		img_list.clear();
		img_list.resize(num);
		TCHAR path[256];
		for (int i = 0;i < num;i++) {
			_stprintf_s(path, path_template, i + first_num);
			loadimage(&img_list[i], path);
		}
	}

	size_t get_size()const {
		return img_list.size();
	}

	IMAGE* get_image(int idx) {
		if (idx < 0 || idx >= img_list.size())
			return nullptr;
		return &img_list[idx];
	}

	void clear() {
		img_list.clear();
	}

private:
	std::vector<IMAGE> img_list;
};