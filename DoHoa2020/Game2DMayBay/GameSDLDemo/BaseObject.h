
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"//thư viện những hàm xử lý chung
// lớp cơ sở đại diện cho những đối tượng cơ bản
class BaseObject
{
public:
  BaseObject();
  ~BaseObject();
  void Show(SDL_Surface* des);
  bool LoadImg(const char* file_name);

  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
  SDL_Rect GetRect() const {return rect_;}
  SDL_Surface* GetObject() {return p_object_;}
protected:// để protected thì class MainObject : public BaseObject mới chọn đc vào "chú ý"
  SDL_Rect rect_;// biến thành viên của các lớp
  SDL_Surface* p_object_;// biến đối tượng
};

#endif 