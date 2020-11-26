#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#undef main
//kích thước con khỉ
#define Width_Monkey 80 
#define Height_Mokey 95

//kích thước tấm ảnh trai banh
#define Width_Ball 60 
#define Height_Ball 60

//khai báo biến màn hình
SDL_Surface* screen = NULL;
//khai báo biến load background
SDL_Surface* background = NULL;
//khai báo biến con khỉ
SDL_Surface* conkhi = NULL;
//khai bao bien chua trai banh
SDL_Surface* banh = NULL;
SDL_Surface* gameover = NULL;
//biến chứa xử lý nhấn phím
SDL_Event sukien;

int SCREEN_WIDTH = 1000;// chiều rộng màn hình 
int SCREEN_HEIGHT = 1000; // chiều cao màn hình

int t,i = 0;// các biến vòng lặp
const int tocDoBanhRoi = 15;//biến này một giá trị cố định để banh rơi
int toaDoConKhi = 500;//tọa độ của con khỉ, ban đầu là 500(do màn hình là 1000), sẽ thay đổi khi di chuyển
int vitrirandom = 0;//biến ramdom của trái banh

const int soLuongBanh = 5; //số lượng trái banh mỗi lần rơi trên màn hình
int vitri[soLuongBanh];//mảng chứa vị trí từng trái banh random(trục x)
int roi[soLuongBanh]; //mảng chứa giá trị rơi từng trái banh random(trục y)
int left_ball[soLuongBanh];//mảng xác định giá trị bên trái của từng trái banh random để xử lý va chạm từng trái banh
int right_ball[soLuongBanh];//mảng xác định giá trị bên phải của từng trái banh random để xử lý va chạm từng trái banh
int top_ball[soLuongBanh];//mảng xác định giá trị ở trên của từng trái banh random để xử lý va chạm từng trái banh
int bot_ball[soLuongBanh];//mảng xác định giá trị ở dưới của từng trái banh random để xử lý va chạm từng trái banh
int left_monkey, right_monkey; // tọa độ vi trí trái phải của con khỉ
int top_monkey, bot_monkey;// tọa độ vi trí trên dưới của con khỉ

unsigned int frameCount = 0, timerBegin;//đếm khung hình và thời gian bắt đầu milisecond

const int FPS = 15; // biến giới hạn fps
const int DELAY_TIME = 1000 / FPS; // tính toán thời gian delay để giới hạn khung hình 
Uint32 frameStart; //
Uint32 frameTime;// thời gian sao mỗi lần hoàn thành việc draw 

//hàm Init để khởi tạo các thuộc tính ban đầu
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	//khởi tạo kích thước màn hình
	screen = SDL_SetVideoMode(1000, 650, 32, SDL_SWSURFACE);
	if (screen == NULL)
	{
		return false;
	}
	return true;

	//Initialize the truetype font API.
	if (TTF_Init() == -1)
	{
		return false;
	}
}

//load vị trí tấm ảnh lên màn hình và set vị trí của ảnh, xóa tấm ảnh củ load ảnh mới
SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);

	return offset;
}

//hàm LoadImage để thực hiện việc load các image 
SDL_Surface* LoadImage(std::string file_path)
{
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;

	load_image = IMG_Load(file_path.c_str()); //thực hiện đọc file ảnh và trả về kết quả là kiểu dữ liệu SDL_Surface.
	if (load_image != NULL) //kiểm tra việc load ảnh có thành công hay không
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 255, 255);//0,255,255 là màu xanh lam
			//ẩn tất cả nền có màu xanh lam đó
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}

//giói hạn vùng di chuyển của khỉ
void gioihanmove()
{
	//màn hình là 1000 trừ cho kích thước khỉ là 80
	if (toaDoConKhi >= 920)
	{
		toaDoConKhi = 920;
	}
	else if (toaDoConKhi <= 0)
	{
		toaDoConKhi = 0;
	}
}

void randomlanroidautien()
{
	for (t = 0; t < soLuongBanh; t++)
	{
		//rơi là trục y, vtri là trục x
		roi[t] = -100*(t+1)*2.5 ;//đặt vị trí mặc định ban đầu của từng trái banh là -100
		vitrirandom = toaDoConKhi;
		//vitrirandom = rand() % 900;
		vitri[t] = vitrirandom;
	}
	////tính toán vị trí ban đầu của từng trái banh
	//for (t = 0; t < soLuongBanh; t++)
	//{
	//	i++;
	//	roi[t] = roi[t] * i;// nhân thêm 1 lượng để set vị trí ban đầu của từng trái banh trước khi rơi		
	//}
	//i = 0;//reset biến cần nhân thêm ở trên
}

//ramdom vị trí xuất hiện trái banh
void randombanh()
{
	//nếu là trái banh cuối cùng thì random lại mảng vị trí
	//if (roi[soLuongBanh-1] >= 650)
	//{	
	//	//tính toán vị trí xuất hiện random của từng trái banh
	//	for (t = 0; t < soLuongBanh; t++)
	//	{
	//		roi[t] = -100;//đặt vị trí mặc định ban đầu của từng trái banh là -100
	//		vitrirandom = toaDoConKhi;
	//		//vitrirandom = rand() % 900;
	//		vitri[t] = vitrirandom;	
	//	}
	//	//tính toán vị trí ban đầu của từng trái banh
	//	for (t = 0; t < soLuongBanh; t++)
	//	{
	//		i++;
	//		roi[t] = roi[t] * i;// nhân thêm 1 lượng để set vị trí ban đầu của từng trái banh trước khi rơi		
	//	}
	//	i=0;//reset biến cần nhân thêm ở trên
	//}

	for (int i = 0; i < soLuongBanh; i++)
	{
		if (roi[i] >= 650)
		{
			roi[i] = -100;
			vitri[i] = toaDoConKhi;
		}
	}

	//biến dành cho con khỉ để xử lý va chạm
	left_monkey = toaDoConKhi;
	right_monkey = toaDoConKhi + Width_Monkey;
	top_monkey = 550;//giá trị đúng là 530 giá trị 550 là giá trị canh chỉnh cho trái banh chạm vào con khỉ
	bot_monkey = 530 + Height_Mokey;

	//vòng lặp xuất từng trái banh ra màng hình
	for (t = 0; t < soLuongBanh; t++)
	{
		roi[t] = roi[t]+ tocDoBanhRoi; // từng trái banh đc công thêm 1 lượng cố định để rơi xuống
		left_ball[t] = vitri[t]; //gán giá trị bên trái của trái banh bằng giá trị vị trí random từng trái banh để xử lý va chạm từng trái banh
		right_ball[t] = vitri[t] + Width_Ball; //gán giá trị bên phải của trái banh bằng giá trị vị trí random từng trái banh để xử lý va chạm từng trái banh
		top_ball[t] = roi[t]; //gán giá trị ở trên của trái banh bằng giá trị vị trí rơi từng trái banh để xử lý va chạm từng trái banh
		bot_ball[t] = roi[t] + Height_Ball; //gán giá trị ở dưới của trái banh bằng giá trị vị trí rơi từng trái banh để xử lý va chạm từng trái banh
		ApplySurface(banh, screen, vitri[t], roi[t]);// xuất trái banh lên màn hình 
	}	
}

//xữ lý va chạm
bool checkvacham()
{
	//chia ra 4 trường hợp khi chạm
	for (t = 0; t < soLuongBanh; t++)
	{
		//bên trái trái banh chạm bên phải con khỉ
		if (left_ball[t] > left_monkey && left_ball[t] < right_monkey)
		{
			//đỉnh top trái banh chạm cạnh phải con khỉ
			if (top_ball[t] > top_monkey && top_ball[t] < bot_monkey)
			{
				return true;
			}
		}
		//bên trái trái banh chạm bên phải con khỉ
		if (left_ball[t] > left_monkey && left_ball[t] < right_monkey)
		{
			//bot trái banh chạm cạnh phải con khỉ
			if (bot_ball[t] > top_monkey && bot_ball[t] < bot_monkey)
			{
				return true;
			}
		}
		//bên phải trái banh chạm bên trái con khỉ
		if (right_ball[t] > left_monkey && right_ball[t] < right_monkey)
		{
			//đỉnh top trái banh chạm cạnh trái con khỉ
			if (top_ball[t] > top_monkey && top_ball[t] < bot_monkey)
			{
				return true;
			}
		}
		//bên phải trái banh chạm bên trái con khỉ
		if (right_ball[t] > left_monkey && right_ball[t] < right_monkey)
		{
			//bot trái banh chạm cạnh trái con khỉ
			if (bot_ball[t] > top_monkey && bot_ball[t] < bot_monkey)
			{
				return true;
			}
		}
	}
	return false;
}

//hàm giải phóng các đối tượng biến global
void CleanUp()
{
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
}

int main(int arc, char*argv[])
{
	//khai báo thư viện font để vẽ chữ
	TTF_Init();
	SDL_Surface* messagefps = NULL; //quản lý text fps
	SDL_Surface* messagetime = NULL;//quản lý text time
	TTF_Font* font = NULL;
	SDL_Color textcolor = { 255,255,255 }; // màu cho text trắng
	font = TTF_OpenFont("chu.ttf", 40); // gọi font dùng cho text và kích thước
	// vị trí xuất hiện 2 text
	SDL_Rect posTexttime;
	posTexttime.x = 600;
	posTexttime.y = 10;
	SDL_Rect posTextfps;
	posTextfps.x = 800;
	posTextfps.y = 10;

	bool is_quit = false;
	if (Init() == false)
		return 0;
	//load ảnh nền 
	background = LoadImage("rung.png");
	if (background == NULL)
	{
		return 0;
	}
	//cửa sổ khi vừa chạy game lên
	ApplySurface(background, screen, 100, -100);

	//load ảnh con khi
	conkhi = LoadImage("conkhi.png");
	if (conkhi == NULL)
		return 0;
	ApplySurface(conkhi, screen, 500, 530);// 2 số cuối là vị trí nhân vật xuất hiện

	//load ảnh trái banh
	banh = LoadImage("banh.png");
	if (banh == NULL)
		return 0;
	ApplySurface(banh, screen, 500, -100);// xuất hình ảnh trái banh lên màn hình
	// ảnh game over
	gameover = LoadImage("thua.png");
	if (gameover == NULL)
		return 0;
	
	timerBegin = SDL_GetTicks();// lấy thời gian bắt đầu vòng lặp
	randomlanroidautien();
	//is_quit thư viện hổ trợ bạn có bấm nút x thoát hay esc hay k?
	while (!is_quit)
	{
		//lấy thời gian hiện tại của hệ thống, get milisecond
			frameStart = SDL_GetTicks();
			//khai báo sự kiện nhấn nút gì
			SDL_PollEvent(&sukien);
			//kiểm tra xem có click nút thoát k?
			if (sukien.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			if (sukien.type == SDL_KEYDOWN)//những phím đc nhấn xuống
			{
				switch (sukien.key.keysym.sym)//kiểm tra loại phím bấm
				{
					case SDLK_RIGHT:
						toaDoConKhi += 10;
						break;
					case SDLK_LEFT:
						toaDoConKhi -= 10;
						break;
					default:
						break;
				}
			}
			gioihanmove();
			ApplySurface(background, screen, 0, 0);
			randombanh();	
			bool check = checkvacham();
			if (check)
			{
				//dừng 1s trước khi qua màn hình gameover
				Sleep(3000);
				//SDL_Delay(1000);
				while (!is_quit)
				{
					SDL_PollEvent(&sukien);
					if (sukien.type == SDL_QUIT)
					{
						is_quit = true;
						break;
					}
					ApplySurface(gameover, screen, 0, 0);
					if (SDL_Flip(screen) == -1)
						return 0;
				}
					CleanUp();
					SDL_Quit();
					return 0;
				//printf_s("bla bla");
			}

			// 2 số cuối là vị trí x,y nhân vật xuất hiện			
			ApplySurface(conkhi, screen, toaDoConKhi, 530);
	
			frameCount++;//biến đếm khung hình 			
			
			//giới hạn số lượng khung hình
			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME)
			{
				Sleep(DELAY_TIME - frameTime);
				//SDL_Delay(DELAY_TIME - frameTime);			
			}

			//show FPS to screen
			std::string fps_time("FPS: ");
			UINT32 fps_v = frameCount / ((SDL_GetTicks() - timerBegin) / 1000.0f);// tính số FPS
			std::string fps_val = std::to_string(fps_v);
			fps_time += fps_val;
			const char* cfps_time = fps_time.c_str();
			messagefps = TTF_RenderText_Solid(font, cfps_time, textcolor);

			//show time for to screen
			std::string str_time("time: ");
			UINT32 time_val = SDL_GetTicks() / 1000;
			std::string str_val = std::to_string(time_val);
			str_time += str_val;
			const char* cstr_time = str_time.c_str();
			messagetime = TTF_RenderText_Solid(font, cstr_time, textcolor);

			SDL_BlitSurface(messagefps, NULL, screen, &posTextfps);
			SDL_BlitSurface(messagetime, NULL, screen, &posTexttime);

			//để xuất hiện lên màn hình
		if (SDL_Flip(screen) == -1)
			return 0;
	}

	CleanUp();
	SDL_Quit();
	return 0;
}
