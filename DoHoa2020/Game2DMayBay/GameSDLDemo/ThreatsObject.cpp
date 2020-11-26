
#include "ThreatsObject.h"

ThreatObject::ThreatObject()
{
  rect_.x = SCREEN_WIDTH;//bình thường là bằng 0 nhưng do nó xuất hiện bên phải màng hình nên bằng kích thước màng hình
  rect_.y = SCREEN_HEIGHT*0.5;// xuất hiện ở giữa màng hình
  rect_.w = WIDTH_THREAT; //động rộng ảnh quái vật máy bay
  rect_.h = HEIGHT_THREAT;//chiều cao ảnh quái vật máy bay

  x_val_ = 0;
  y_val_ = 0;
}

ThreatObject::~ThreatObject()
{
  if (p_bullet_list_.size() > 0)
  {
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
      BulletObject* p_bullet = p_bullet_list_.at(i);
      if (p_bullet != NULL)
      {
        delete p_bullet;
        p_bullet = NULL;
      }
    }
    p_bullet_list_.clear();// giải phóng bộ nhớ
  }
}


void ThreatObject::InitBullet(BulletObject* p_bullet)//tạo đạn cho các đối tượng threat
{
  if (p_bullet)
  {
    bool ret = p_bullet->LoadImg(g_name_bullet_threats);//load tấm ảnh đạn máy bay quái vật
    if (ret)
    {
      p_bullet->set_is_move(true);
      p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
      p_bullet->set_type(BulletObject::SPHERE);
      p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);//sét vị trí đạn xuất hiện
      p_bullet->set_x_val(SPEED_BULLET_THREATS);
      p_bullet_list_.push_back(p_bullet);
    }
  }
}


void ThreatObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit)// hàm bắn đạn ra
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet = p_bullet_list_.at(i);
    if (p_bullet)
    {
      if (p_bullet->get_is_move())
      {
        p_bullet->Show(des);
        p_bullet->HandleMoveRightToLeft();//đạn bay từ phải sang trái
      }
      else
      {
        p_bullet->set_is_move(true);
        p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);// khi đạn đến màng hình trái thì đang sẽ về vị trí ban đầu
      }
    }
  }
}

void ThreatObject::HandleMove(const int& x_bordr, const int& y_border)
{
  rect_.x -= x_val_;
  if (rect_.x < 0)// nếu máy bay quái vật đi hết màng hình thì
  {
    rect_.x  = SCREEN_WIDTH;// quay lại đi tiếp chứ ko bị xóa như viên đạn
    rect_.y= SDLCommonFunc::MakeRandValue();//hàm xử lý để máy bay quái vật xuất hiện ngẩu nhiên
  }
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
  //Todo
}

//reset vị trí của mối hiểm họa khi bị va chạm
void ThreatObject::Reset(const int& xboder)
{
  rect_.x = xboder; 
  rect_.y = SDLCommonFunc::MakeRandValue();//lấy lại vị trí ramdom của mối hiểm họa
  ///reset viên đạn
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet = p_bullet_list_.at(i);
    if (p_bullet)
    {
      ResetBullet(p_bullet);
    }
  }
}
//định nghĩa hàm ResetBullet(p_bullet)
void ThreatObject::ResetBullet(BulletObject* p_bullet)
{
   p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}