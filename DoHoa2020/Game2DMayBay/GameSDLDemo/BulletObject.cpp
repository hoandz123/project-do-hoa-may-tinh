
#include "BulletObject.h"

BulletObject::BulletObject()
{
  rect_.x = 0;
  rect_.y = 0;
  x_val_ = 0;
  y_val_ = 0;
  is_move_ = false; //ban đầu đạn chưa xuất hiện nên = fales
  bullet_type_ = NONE;// ban đầu đạn chưa có dạng gì cả
}

BulletObject::~BulletObject()
{

}


//hàm đạn bay từ trái sang phải
void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
  if (is_move_ == true)
  {
    rect_.x += x_val_;
    if (rect_.x > x_border)// x_border độ rộng màng hình, nếu lớn hơn thì viên đạn ko xuất hiện nữa
    {
      is_move_ = false;
    }
  }
}

//hàm đạn bay từ phải sang trái
void BulletObject::HandleMoveRightToLeft()
{
  rect_.x -= x_val_;
  if (rect_.x < 0)
  {
    is_move_ = false;
  }
}

void BulletObject::HandleInputAction(SDL_Event events)
{
  ;//Todo
}
