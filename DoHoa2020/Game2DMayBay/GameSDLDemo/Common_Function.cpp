
#include "Common_Function.h"//thư viện những hàm xử lý chung

//hàm LoadImage,trả về là kiểu SDL Surface, đầu vào là tên của ảnh background.
//kết quả trả về được đưa vào hàm định dạng hiển thị SDL_DisplayFormat để tối ưu hóa surface cho phù hợp.
SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
  SDL_Surface * load_image = NULL; // lấy kết quả đặt tấm ảnh.
  SDL_Surface* optimize_image = NULL;// tối ưu hóa định dạng tấm ảnh
  load_image = IMG_Load(file_path.c_str());
  if (load_image != NULL)// kiểm tra quá trình Load_image có thành công hay không 
  {
    optimize_image= SDL_DisplayFormat(load_image);
    SDL_FreeSurface(load_image);// lúc này Load_inmage không cần thiết nữa nên giải phóng nó đi.

    // thực hiện transparent background của nhân vật.
    if (optimize_image != NULL) // nếu background của nhân vật khác thì...
    {
      UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);//mã màu truyền vào phải trùng với mã màu của background.
      SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
    }
  }
  return optimize_image;
}

//-----------------------------------------------------------------------

// thực hiện load Image vào màn hình screen.
void SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)// thêm SDLCommonFunc:: phía trước đi tránh hiện tượng bị trùng thư viện
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);
}
//thực hiện load nhân vật vào màn hình screen.
void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)//des, clip là 2 ảnh chèn vào src. x,y là tọa độ xuất hiện của 2 ảnh
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, clip, des, &offset);
}


// hàm xử lý va chạm dành cho hai đối tượng
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
  int left_a = object1.x;//vị trí ở góc trên bên trái hình 1(ảnh của đối tượng 1)
  int right_a = object1.x + object1.w;//vị trí ở góc trên bên phải hình 1(ảnh của đối tượng 1)
  int top_a = object1.y; // vị trí ở trên đầu của hình 1(ảnh của đối tượng 1)
  int bottom_a = object1.y + object1.h;// vị trí ở dưới đích của hình 1(ảnh của đối tượng 1)
  //tương tự nhưng là của đối tượng 2
  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 > size object 2, các điều kiện có sự va chạm của 2 đối tượng
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}

//hàm xử lý xuất hiện khẩu nhiên
int SDLCommonFunc::MakeRandValue(const int& div_val /*400*/)
{
  int rand_y = rand()%div_val;
  if (rand_y > SCREEN_HEIGHT - 200)//200 đẻ máy bay quái vậy ko bay gần mặt đất
  {
    rand_y = SCREEN_HEIGHT*0.3;
  }
  return rand_y;
}

//hàm giải phóng các đối tượng biến global.
void SDLCommonFunc::CleanUp()
{
  SDL_FreeSurface(g_screen);
  SDL_FreeSurface(g_bkground);
}