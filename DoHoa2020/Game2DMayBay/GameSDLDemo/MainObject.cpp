
#include "MainObject.h"

MainObject::MainObject()
{
  rect_.x = 0;
  rect_.y = 0;
  rect_.w = WIDTH_MAIN_OBJECT;
  rect_.h = HEIGHT_MAIN_OBJECT;
  x_val_ = 0;
  y_val_ = 0;
}

MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2])// bắt sự kiện phím bấm và chuột và âm thanh
{
  if (events.type == SDL_KEYDOWN)//những phím đc nhấn xuống
  {
    switch (events.key.keysym.sym)//kiểm tra loại phím bấm
    {
    case SDLK_UP:
      y_val_ -= SPEED_MAIN_OBJECT;// trừ đi một lượng y để đối tương di chuyển
      //Todo
      break;
    case SDLK_DOWN:
      y_val_ += SPEED_MAIN_OBJECT;
      //Todo
      break;
    case SDLK_RIGHT:
      x_val_ += SPEED_MAIN_OBJECT;
      //Todo
      break;
    case SDLK_LEFT:
      x_val_ -= SPEED_MAIN_OBJECT;
      break;;
    default:
      break;
    }
  }
  else if (events.type == SDL_KEYUP)// phím đc nhả ra, đẻ khắc phục tình trạng nhấn 1 lần đối tương đi hết màng hình
  {
    switch(events.key.keysym.sym )
    {
      case SDLK_UP: y_val_ += SPEED_MAIN_OBJECT; break; // cộng thêm 1 lượng trừ
      case SDLK_DOWN: y_val_ -= SPEED_MAIN_OBJECT; break;
      case SDLK_LEFT: x_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_RIGHT: x_val_ -= SPEED_MAIN_OBJECT; break;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONDOWN)// kiểm tra sự kiện chuột bấm
  {
    BulletObject* p_bullet = new BulletObject();// tạo ra viên đạn
    if (events.button.button == SDL_BUTTON_LEFT)
    {
      p_bullet->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);//truyền kích thước đạn laser
      p_bullet->LoadImg(g_name_bullet_main_laser);//load ảnh đạn laser
      p_bullet->set_type(BulletObject::LASER);
      Mix_PlayChannel(-1, bullet_sound[0], 0);//âm thanh
    }
    else if (events.button.button == SDL_BUTTON_RIGHT)
    {
      p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);//truyền kích thước đạn tròn
      p_bullet->LoadImg(g_name_bullet_main_fire);//load ảnh đạn tròn
      p_bullet->set_type(BulletObject::SPHERE);
      Mix_PlayChannel(-1, bullet_sound[1], 0);//âm thanh
    }

    p_bullet->SetRect(this->rect_.x + this->rect_.w - 40, this->rect_.y + this->rect_.h*0.8);//set vị trí ban đầu của viện đạn = vị trí của máy bay + thêm một lượng x, y
    p_bullet->set_is_move(true);
    p_bullet->set_x_val(SPEED_BULLET_MAIN);
    p_bullet_list_.push_back(p_bullet);
  }
  else if (events.type == SDL_MOUSEBUTTONUP)// kiểm tra sự kiện chuột nhả ra
  {

  }
  else// trường hợp còn lại
  {
    ;//
  }
}

void MainObject::MakeBullet(SDL_Surface* des)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet_ = p_bullet_list_.at(i);
    if (p_bullet_ != NULL)
    {
      if (p_bullet_->get_is_move())
      {
        p_bullet_->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        p_bullet_->Show(des);
      }
      else 
      {
        if (p_bullet_ != NULL)
        {
          p_bullet_list_.erase(p_bullet_list_.begin() + i);
          delete p_bullet_;
          p_bullet_ = NULL;
        }
      }
    }
  }
}



//************************************
// Method:    HandleMove
// FullName:  MainObject::HandleMove
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void MainObject::HandleMove() //xử lý vị trí đối tượng
{
  rect_.x += x_val_;// giá trị ban đầu + thêm 1 lượng khi nhấn phím

  if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)//giới hạn vị trí đối tượng trong màng hình,"rect_.x + WIDTH_MAIN_OBJECT" do rect là một điểm phía trên bên trái
  {
    rect_.x -= x_val_;//luôn bằng 0
  }


  rect_.y += y_val_;//tương tự trên
  if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200)//tương tự trên,"SCREEN_HEIGHT - 200" trừ thêm một lượng mật đất trên hình
  {
    rect_.y -= y_val_;
  }
}
//di chuyễn viên đạn của nhân vật chính đi chổ khác
void MainObject::RemoveBullet(const int& idx)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)// lấy đối tượng
  {
    if (idx < p_bullet_list_.size())
   {
      BulletObject* p_bullet = p_bullet_list_.at(idx);
      p_bullet_list_.erase(p_bullet_list_.begin() + idx);

      if (p_bullet != NULL)
      {
        delete p_bullet;
        p_bullet = NULL;
      }
    }
  }
}