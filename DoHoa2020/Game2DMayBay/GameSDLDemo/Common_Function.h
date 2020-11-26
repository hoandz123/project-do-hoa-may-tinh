
#ifndef COMMON_FUNCTION_H_ // nếu chưa đc định nghĩa thì sẽ đc định nghĩa
#define COMMON_FUNCTION_H_ // gọi ra

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define GA_FAILED -1  // sai
#define GA_SUCCESS 0 // đúng


//Screen, tham số định dạng màng hình
const int WIDTH_BACKGROUND  = 4800; // chiều rộng ảnh, ảnh to hơn màng hình để game bớt đi tính đơn điệu
const int HEIGHT_BACKGROUND = 600;// chiều cao ảnh nền
const int SCREEN_WIDTH      = 1200;// chiều rộng màng hình 
const int SCREEN_HEIGHT     = 600; // chiều cao màng hình
const int SCREEN_BPP        = 32; //độ phân giải
const int SPEED_SCREEN      = 2;//tốc độ di chuyễn màng hình

//Main
const int POS_X_START_MAIN_OBJ  = 100;
const int POS_Y_START_MAIN_OBJ  = 200;
const int SPEED_MAIN_OBJECT     = 10;
const int SPEED_BULLET_MAIN     = 20;

//Threats

const int SPEED_THREAT = 5;
const int NUM_THREATS  = 3;
const int SPEED_BULLET_THREATS          = 10;
const int VAL_OFFSET_START_POST_THREATS = 400;
const int UNDER_LIMIT_THREAT = 200;

// biến quản lý screen và quản lý background thành các biến global.
static SDL_Surface* g_screen    = NULL;// quản lý màng hình , thêm static để biến hoạt động trong toàn bộ chương trình
static SDL_Surface* g_bkground  = NULL;//lấy dữ liệu từ g_bkground
static SDL_Event g_even; // quản lý sự kiện
//âm thanh game
static Mix_Chunk* g_sound_bullet[2];//âm thanh súng bắng
static Mix_Chunk* g_sound_exp[2];//âm thanh vụ nổ


static char g_name_bk_ground[] = {"bk2.png"};

static char g_name_main_obj[]           = {"plane_fly.png"};
static char g_name_exp_main []          = {"exp_main.png"};
static char g_name_bullet_main_laser[]  = {"laser.png"};
static char g_name_bullet_main_fire[]   = {"sphere.png"};
static char g_name_audio_bullet_main[]  = {"Laser.wav"};
static char g_name_audio_bullet_main2[] = {"Fire1.wav"};
static char g_name_audio_exp_main[]     = {"Bomb1.wav"};

static char g_name_exp_threats[]        = {"exp.png"};
static char g_name_threats[]            = {"af1.png"};
static char g_name_bullet_threats[]     = {"sphere2.png"};
static char g_name_audio_exp_threats[]  = {"Explosion+1.wav"};


//hàm load image
namespace SDLCommonFunc//hàm namespace để trách hiện tượng bị chùng khi gọi thư viện 
{
  SDL_Surface* LoadImage(std::string file_path); 
  void CleanUp();//giải phóng các đối tượng biến global
  void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);//  load Image vào màn hình screen.
  void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
  int MakeRandValue(const int& div_val = 400);
}


#endif// không đinh nghĩa nữa
