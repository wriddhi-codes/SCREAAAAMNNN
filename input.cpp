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

    char imp_task[512]="";
    char task[512]="";

    bool edit = false ;
    bool edit_imp = false ;

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

        DrawText("Important Task(Red)",40,65,14,RED);
        if (GuiTextBox((Rectangle){40,90,570,140},imp_task,512,edit_imp))
        {
            edit_imp = !edit_imp;
            edit = false;
        }

        DrawText("Important Task(Red)",40,245,14,DARKGRAY);
        if (GuiTextBox((Rectangle){40,270,570,140},task,512,edit))
        {
            edit = !edit ;
            edit_imp = false;
        }

        if (GuiButton((Rectangle){480,420,130,40},"Save to File"))    
        {
            ofstream outfile("data.txt");
            if (outfile.is_open())
            {
                stringstream impstream(imp_task);
                string line;
                while (getline(impstream,line))
                {
                    if (!line.empty())
                    {
                        if (line[0] != '!')
                        {
                            outfile << "!" << line << "\n";
                        }
                        else{
                            outfile << line << "\n";
                        }
                        
                    }
                    
                }

                stringstream normstream(task);
                while (getline(normstream,line))
                {
                    if (!line.empty())
                    {
                        outfile << line << "n" ;
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