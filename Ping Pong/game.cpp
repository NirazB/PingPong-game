#include "raylib.h"
#include<iostream>

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};


int player_score=0;
int computer_score=0;

const int screen_width=1100;
const int screen_height=600;

class BAll
{
    public: 
    float x=600,y=360;
    int speed_x=5,speed_y=5;
    int radius=15;

    void draw()
    {
        DrawCircle(x,y,radius,Yellow);
    }
    void move()
    {
        x+=speed_x;
        y+=speed_y;

        if((y+radius)>=screen_height) speed_y*=-1;
        
        if((y-radius)<=0) speed_y*=-1;
    }
}b;
class CONTROL
{
    public:
    float player_x=20;
    float player_y=screen_height/2;
    int speed=5;

    float paddle_Width=20;
    float paddle_height=150;
    
    float comp_x=screen_width-40;
    float comp_y=screen_height/2;

    void draw_player_rect()
    {
        Rectangle rec={player_x,player_y,paddle_Width,paddle_height};
        DrawRectangleRounded(rec,0.3,0,WHITE);
    }

    void comp_draw()
    {
        Rectangle rec={comp_x,comp_y,paddle_Width,paddle_height};
        DrawRectangleRounded(rec,0.3,0,WHITE);
    }

    void player_move()
    {
        if(player_y>=0)
            if(IsKeyDown(KEY_UP)) player_y-=speed;
        if(player_y<screen_height-paddle_height)
            if(IsKeyDown(KEY_DOWN)) player_y+=speed;
    }

    void comp_move()
    {
        if(comp_y>=0)
        {
            if(b.y<comp_y){comp_y-=speed;}
        }
        if(comp_y<screen_height-paddle_height)
        {
            if(b.y>comp_y){comp_y+=speed;}
        }
    }
    
    void win()
    {
        if((b.x-b.radius)<=0)
        {
            computer_score+=1;
            b.x=600;
            b.y=360;
            player_x=20;
            player_y=screen_height/2;

            comp_x=screen_width-40;
            comp_y=screen_height/2;
        };
        if((b.x+b.radius)>=screen_width)
        {
            player_score+=1;
            b.x=600;
            b.y=360;
            player_x=20;
            player_y=screen_height/2;

            comp_x=screen_width-40;
            comp_y=screen_height/2;
        }
    }
};

int main(void)
{
    int check=0;
    InitWindow(screen_width,screen_height,"Ping POng");
    SetTargetFPS(60);

    InitAudioDevice();

    Music theme= LoadMusicStream("music/theme.mp3");
    Sound hit = LoadSound("music/hit.wav");
    PlayMusicStream(theme);

    CONTROL p;
    
    while(!WindowShouldClose())
    {
        UpdateMusicStream(theme);

        BeginDrawing();

            ClearBackground(Dark_Green);
            DrawLine(screen_width/2, 0, screen_width/2, screen_height,Light_Green);
            
            DrawText(TextFormat("%i",player_score),screen_width/2 -50, 30,40,WHITE);
            DrawText(TextFormat("%i",computer_score),screen_width/2 +30, 30,40,WHITE);

            b.draw();
            p.draw_player_rect();
            p.comp_draw();

            b.move();
            p.player_move();
            p.comp_move();

            if(CheckCollisionCircleRec({b.x,b.y},b.radius,{p.player_x,p.player_y,p.paddle_Width,p.paddle_height})) 
            {

                PlaySound(hit);
                b.speed_x*=-1;
            }
            if(CheckCollisionCircleRec({b.x,b.y},b.radius,{p.comp_x,p.comp_y,p.paddle_Width,p.paddle_height})) 
            {
                PlaySound(hit);
                b.speed_x*=-1;
            }
    
            p.win();
            

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}