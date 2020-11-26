
#include "Common_Function.h"//thư viện những hàm xử lý chung
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"
#include "TestOpject.h"
#undef main

TTF_Font* g_font_text = NULL;//khai báo đối tượng text



 // định dạng màng hình và độc các file audio
bool Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == GA_FAILED) //khởi tạo các chế độ của thư viện SDL và kiểm tra việc khởi tạo.
  {
    return false; 
  }
  // nếu thành công sẽ chạy dòng dưới.
  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); // định dạng màng hình,"SDL_SWSURFACE" Create the video surface in system memory

  if (g_screen == NULL) // kiểm tra việc định dạng có thành công không
    return false;

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == GA_FAILED)
    return false;

  //Read file wav audio
  g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_bullet_main);
  g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_bullet_main2);
  g_sound_exp[0] = Mix_LoadWAV(g_name_audio_exp_threats);
  g_sound_exp[1] = Mix_LoadWAV(g_name_audio_exp_main);

  if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[1] == NULL)//kiểm tra quá trình đọc file
  {
    return false;
  }

  //khởi tạo chế độ font text
  if (TTF_Init() == GA_FAILED)
  {
      return false;
  }

  //load font text lên
  g_font_text = TTF_OpenFont("chu.ttf",40);//kích thước 20, đọc font
  if (g_font_text == NULL)
  {
      return false;
  }


  return true;// khi các quá trình điều thành công
}






int main(int arc, char*argv[])
{
  bool is_run_screen = true;// biến kiểm tra khi nào màng hình đứng lại để biến đấu với trùm trà đá
  int bkgn_x = 0;//biến offset vị trí ban đầu màng hình
  bool is_quit = false; // biến quản lý vòng lặp
  if (Init() == false)
    return 0;

  g_bkground = SDLCommonFunc::LoadImage(g_name_bk_ground); //load ảnh vào g_bkground để dùng kỹ thuật di chuyễn màng hình
  if (g_bkground == NULL) // kiểm tra việc load ảnh có thành công không
  {
    return 0;
  }


  //Make player power
  PlayerPower player_power;
  player_power.Init();

  //hiển thị FPS
  TextObject fps_game;
  fps_game.SetColor(TextObject::WHITE_TEXT);

  // hiển thị thời gian
  TextObject time_game;
  time_game.SetColor(TextObject::WHITE_TEXT);

  //thiết lặp màu sắc test và đối tượng cho test
  TextObject mark_game;
  mark_game.SetColor(TextObject::WHITE_TEXT);

  //Make MainObject
  MainObject plane_object;//tạo đối tượng
  plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);// set vị trí xuất hiện
  bool ret = plane_object.LoadImg(g_name_main_obj);//tải hình ảnh nhân vật lên
  if (!ret)//biến kiểm tra
  {
    return 0;
  }

  //Init explosion object
  ExplosionObject exp_main;
  ExplosionObject exp_threats;
  ret = exp_main.LoadImg(g_name_exp_main);//load ảnh vụ nổ nhân vật
  exp_main.set_clip();
  if (ret == false) return 0;

  ret = exp_threats.LoadImg(g_name_exp_threats );//load ảnh vụ nổ mối hiểm họa
  exp_threats.set_clip();
  if (!ret) return 0;

  //Make ThreatObject
  ThreatObject* p_threats = new ThreatObject[NUM_THREATS];

  for (int t = 0; t < NUM_THREATS; t++)
  {
    ThreatObject* p_threat = (p_threats + t);
    if (p_threat)
    {
      ret = p_threat->LoadImg(g_name_threats);
      if (ret == false)
      {
        delete [] p_threats;
        SDLCommonFunc::CleanUp();
        SDL_Quit();
        return 0;
      }

      int rand_y = SDLCommonFunc::MakeRandValue();
      p_threat->SetRect(SCREEN_WIDTH + t*VAL_OFFSET_START_POST_THREATS, rand_y);
      p_threat->set_x_val(SPEED_THREAT);

      BulletObject* p_bullet = new BulletObject();
      p_threat->InitBullet(p_bullet);
    }
  }

  //biến quản lý để nhân vật hết 3 mạng mới chết
  unsigned int die_number = 0;
  //biến quản lý điểm
  unsigned int mark_value = 0;
  //Biến hiểu thị FPS
  unsigned int frameCount =  0, timerBegin;//điếm khung hình và thời gian lấy mẩu
  unsigned int fps = 0; // giá trị frame-per-second
  timerBegin = SDL_GetTicks();// lấy thời gian bắt đầu vòng lặp


  while (!is_quit) // vòng Lặp chương trình liên tục "=true thì chương trình sẽ kết thúc) 
  {
    while (SDL_PollEvent(&g_even)) // vòng lặp kiểm tra sự kiện
    {
      if (g_even.type == SDL_QUIT) // nếu g_even.type == SDL_QUIT "sư kiện khi t nhấn vào nút close [X]"
      {
        is_quit = true; 
        break; //thoát vòng lặp while (SDL_PollEvent(&g_even))
      }
      plane_object.HandleInputAction(g_even, g_sound_bullet);//chuyền sự kiện vào đối tượng
    }

    //Implement dynamic screen, kỹ thuật di chuyễn màng hình theo cách tấm ảnh lớn gắp đôi màng hình
    if (is_run_screen == true)//màng hình được chạy
    {
      bkgn_x -= SPEED_SCREEN;//cứ một vòng lặp biến sẽ đc trừ đi 2
      if (bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))//điều kiện để màng hình dừng lại đánh boss
      {
        is_run_screen = false;// màng hình dừng lại
      }
      else
      {
        SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);//bkgn_x lúc này là giá trị vị trí mà ảnh bị trừ đi 
      }
    }
    else
    {
      SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
    }
    
    //show player power
    player_power.Render(g_screen);

    //Implement main object
    plane_object.HandleMove();//di chuyển đối tượng khi có sự kiện phím được xử lý trong hàm HandleMove()
    plane_object.Show(g_screen);// update lại vị trí đối tượng khi thay đổi
    plane_object.MakeBullet(g_screen);// update lại vị tri viên đạn

    //Implement Threats Object
    for (int tt = 0; tt < NUM_THREATS; tt++)
    {
      ThreatObject* p_threat = (p_threats + tt);
      if (p_threat)
      {
        p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);//truyền kích thước màng hình vào 
        p_threat->Show(g_screen);//hiển thị đạn trên màng hình
        p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);


        //COLLISION THREAT BULLET -> MAIN OBJECT,  kiểm tra vạ chạm của đạn của mối hiểm họa với nhân vật chính
        bool is_col1 = false;
        std::vector<BulletObject*> bullet_arr = p_threat->GetBulletList();
        for (int am = 0; am < bullet_arr.size(); am++)
        {
          BulletObject* p_bullet = bullet_arr.at(am);
          if (p_bullet)
          {
            is_col1 = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), plane_object.GetRect());
            if (is_col1 == true)
            {
              p_threat->ResetBullet(p_bullet);
              break;
            }
          }
        }

        //Check collision main and threats, Xử lý vụ nổ trong phần kiểm tra va chạm giữa main và threats
        bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
        if (is_col1 || is_col)//điều kiện vụ nổ xẩy ra
        {
          for (int ex = 0; ex < 4; ex++)
          {
            int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) -  EXP_WIDTH*0.5;//vị trí của vụ nổ ở tâm máy bay
            int y_Pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5)- EXP_HEIGHT*0.5;//vị trí của vụ nổ ở tâm máy bay

            exp_main.set_frame(ex);
            exp_main.SetRect(x_pos, y_Pos);//hàm sét vị trí
            exp_main.ShowEx(g_screen);//hàm show lên màng hình
            //lệnh delay đang nghiên cứu ****************************************************************************************************************
            //Update screen
            if ( SDL_Flip(g_screen) == -1)
            {
              delete [] p_threats;
              SDLCommonFunc::CleanUp();//giải phóng các đối tượng biến global
              SDL_Quit();//thoát chương trình khi ta nhấn vào nút close[X]
              return 0;
            }
          }

           Mix_PlayChannel(-1, g_sound_exp[1], 0); // âm thanh chết của nhân vật chính

           die_number++;//mỗi lần va chạm biến này sẽ tăng lên một
           if (die_number <= 3)
           {
               SDL_Delay(1000);
               plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
               player_power.Decrease();
               player_power.Render(g_screen);

               if (SDL_Flip(g_screen) == -1)
               {
                   delete[] p_threat;
                   SDLCommonFunc::CleanUp();
                   SDL_Quit();
                   return 0;
               }
           }
           else
           {
               if (MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)// nhấn vật đã chết.
               {
                   delete[] p_threats;
                   SDLCommonFunc::CleanUp();//giải phóng các đối tượng biến global
                   SDL_Quit();//thoát chương trình khi ta nhấn vào nút close[X]
                   return 1;
               }

           }   
        }

        //Check collision main bullet with threats, kiểm tra vạ chạm của đạn giữa máy bay và mối hiểm họa
        std::vector<BulletObject*> bullet_list = plane_object.GetBulletList();//Lấy danh sách các viên đạn được bắn ra bởi plane object
        for (int im = 0; im < bullet_list.size(); im++)
        {
          BulletObject* p_bullet = bullet_list.at(im);
          if (p_bullet != NULL)
          {
            bool ret_col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());//Kiểm tra va chạm giữa từng viên đạn và từng threats.
            if (ret_col)
            {
                mark_value++;
              for (int tx = 0; tx < 4; tx++)
              {
                int x_pos = p_bullet->GetRect().x - EXP_WIDTH*0.5;
                int y_pos = p_bullet->GetRect().y - EXP_HEIGHT*0.5;

                exp_threats.set_frame(tx);
                exp_threats.SetRect(x_pos, y_pos);
                exp_threats.ShowEx(g_screen);

                if (SDL_Flip(g_screen) == -1)
                {
                  delete [] p_threats;
                  SDLCommonFunc::CleanUp();//giải phóng các đối tượng biến global
                  SDL_Quit(); //thoát chương trình khi ta nhấn vào nút close[X]
                  return 0;
                }
              }
              //Khi va chạm có xảy ra. Thì p_threat được reset về vị trí ban đầu và đồng thời remove viên đạn hiện tại trong plane object
              p_threat->Reset(SCREEN_WIDTH + tt*VAL_OFFSET_START_POST_THREATS);
              plane_object.RemoveBullet(im);
              Mix_PlayChannel(-1, g_sound_exp[0], 0);//âm thanh nổ chết
            }
          }
        }
      }
    }
    frameCount++;//biến điếm khung hình 
    //giởi hạn số lượng khung hình
    SDL_Delay(80);

    //show FPS to screen
    std::string fps_time("FPS: ");
    UINT32 fps = frameCount / ((SDL_GetTicks() - timerBegin) / 1000.0f);// tính số FPS
    std::string fps_val = std::to_string(fps);
    fps_time += fps_val;

    fps_game.SetText(fps_time);
    fps_game.SetRect(SCREEN_WIDTH - 500, 10);//set vị trí
    fps_game.CreateGameText(g_font_text, g_screen);


    //show time for to screen
    std::string str_time("time: ");
    UINT32 time_val = SDL_GetTicks() / 1000;
    std::string str_val = std::to_string(time_val);
    str_time += str_val;

    time_game.SetText(str_time);
    time_game.SetRect(SCREEN_WIDTH - 200, 10);//set vị trí
    time_game.CreateGameText(g_font_text, g_screen);  
   

    //show mark value to screen
    std::string val_str_mark = std::to_string(mark_value);//chuyển đổi giá trị số thành chuổi
    std::string strMark("Mark: ");
    strMark += val_str_mark;

    mark_game.SetText(strMark);
    mark_game.CreateGameText(g_font_text, g_screen);

    //Update screen sẽ liên tục cập nhật windows và giữ chương trình ở trạng thái liên tục chạy.
    if ( SDL_Flip(g_screen) == -1) //nếu bị lỗi
    {
      delete [] p_threats;
      SDLCommonFunc::CleanUp();//giải phóng các đối tượng biến global
      SDL_Quit(); //thoát chương trình khi ta nhấn vào nút close[X]
      return 0; // thoát chương trình
    }
  }

  delete [] p_threats;//xóa cách đối tượng máy bay threats
  SDLCommonFunc::CleanUp();//giải phóng các đối tượng biến global
  SDL_Quit();// thoát chương trình khi ta nhấn vào nút close [X]

  return 1;
}