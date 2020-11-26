
#include "BaseObject.h"

BaseObject::BaseObject()
{
  rect_.x = 0;
  rect_.y = 0;
  p_object_ = NULL; // những lỗi không mong muốn
}

BaseObject::~BaseObject()
{
  if (p_object_ != NULL)
  {
    SDL_FreeSurface(p_object_);
  }
}

bool BaseObject::LoadImg(const char* file_name)// "bool" là kiểm tra việc load có thành công hay không
{
  p_object_ = SDLCommonFunc::LoadImage(file_name);//load anh vào biến đối tượng
  if (p_object_ == NULL)
    return false;
  return true;
}

void BaseObject::Show(SDL_Surface* des) //"void" là load lên
{
  if (p_object_ != NULL)
  {
    SDLCommonFunc::ApplySurface(p_object_, des, rect_.x, rect_.y);// chuyền p_object_ vào des, rect_.x, rect_.y là vị trí của p_object_ trên nền des
  }
}
