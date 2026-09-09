#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


int main(){
    InitWindow(650,480,"TASK WRITE");
    SetTargetFPS(60);
    // ToggleFullscreen();
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    char imp_task[3][512]={"","",""};
    char task[3][512]={"","",""};

    int edit = -1 ;
    int edit_imp = -1 ;

    float timer = 0.0f;

    while (!WindowShouldClose())
    {

        if (timer > 0.0f)
        {
            timer -= GetFrameTime();
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("TASK EDITOR DASHBOARD",width/2 - MeasureText("TASK EDITOR DASHBOARD",20)/2,30,20,BLACK);

        DrawText("Important Task(Red)",40,90,14,RED);
        for (int i = 0; i < 3; i++)
        {
            if (GuiTextBox((Rectangle){40,float(110 + i*35 ),570,30},imp_task[i],128,edit_imp == i))
            {
                if (edit_imp == i)
                {
                    edit_imp = -1;
                }
                else
                {
                    edit_imp = i;
                }

                edit = -1;
            }
        }
        

        DrawText("Normal Task",40,235,14,DARKGRAY);
        for (int i = 0; i < 3; i++)
        {
            if (GuiTextBox((Rectangle){40,float(250+ i*35),570,30},task[i],512,edit == i))
            {
                if (edit == i)
                {
                    edit = -1;
                }
                else
                {
                    edit = i ;
                }

                edit_imp = -1;
            }
        }
        

        if (GuiButton((Rectangle){480,420,130,40},"Save to File"))    
        {
            ofstream outfile("data.txt");
            if (outfile.is_open())
            {
                for (int i = 0; i < 3; i++)
                {
                    string line(imp_task[i]);

                    if (!line.empty())
                    {
                        outfile << "!" << line << "\n";
                    }

                }

                for (int i = 0; i < 3; i++)
                {
                    string line(task[i]);

                    if (!line.empty())
                    {
                        outfile << line << "\n" ;
                    }
                }   
                outfile.close();  
                timer = 2.0f;

            }
            
        }
        
        if (timer > 0.0f)
        {   
                DrawText("Data Saved",325 - MeasureText("Data Saved",14),420,14,DARKGREEN);
        }
        
        
        EndDrawing();
    }
    CloseWindow();
    return 0 ;

}

// cmd : g++ .\input.cpp -o input.exe -I"C:\raylib\raylib\src" -L"C:\raylib\raylib\src" -lraylib -lopengl32 -lgdi32 -lwinmm