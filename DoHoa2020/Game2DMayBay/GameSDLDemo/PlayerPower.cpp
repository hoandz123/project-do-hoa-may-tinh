#include "PlayerPower.h"

PlayerPower::PlayerPower()
{

}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int& xpos)
{
	pos_list_.push_back(xpos);//lưu số mạng vào danh sách
}

void PlayerPower::Render(SDL_Surface* des)
{
	if (number_ == pos_list_.size())
	{
		for (int i = 0; i < pos_list_.size(); i++)
		{
			rect_.x = pos_list_.at(i);
			Show(des);
		}
	}
}

void PlayerPower::Init()
{
	LoadImg("mang_sung.png");//load ảnh 
	number_ = 3; //số mạng của nhân vật
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	//vị trí của qua hình ảnh thể hiện mạng nhân vật
	AddPos(20);
	AddPos(70);
	AddPos(120);
}

void PlayerPower::Decrease()
{
	number_--;
	pos_list_.pop_back();
}