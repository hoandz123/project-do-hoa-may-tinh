
#ifndef PLAYER_POWER_H	
#define PLAYER_POWER_H	
#include "BaseObject.h"
#include <vector>

//lớp quản lý mạng nhân vật của game
class PlayerPower : public BaseObject
{
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& num) {number_ = num; }
	void AddPos(const int& xpos);
	void Render(SDL_Surface * des);//show các mạng sống lên vựa vào pos_list
	void Init();//khởi tạo thông số ban đầu
	void Decrease();//hàm giảm đi một mạng khi va chạm
private:
	int number_;//đại viện số mạng nhân vật
	std::vector <int> pos_list_;//danh sách vị trí từng hình hiển thị mạng nhân vật

};

#endif // !PlAYER_POWER
