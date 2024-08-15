#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdint.h>
#include "include\raylib.h"
#include "include\raymath.h"
#include "include\rlgl.h"

//#define _CRT_SECURE_NO_WARNINGS

#define global_variable static
#define local_persist   static
#define internal        static

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef u32 b32;

typedef float  f32;
typedef double f64;

#include "render.cpp"
#include "my_math.cpp"
#include "utils.cpp"

#include "game.cpp"

int main(){
    InitWindow(800, 600, "aboba");

    Shader shader = LoadShader(0, "lerp_shader.fs");
    
    Shader color_shader = LoadShader(0, "color_shader.fs");

    Texture bear = LoadTexture("resources/cat.png");
    Texture2D *swordAnim = (Texture2D*)malloc(10 * sizeof(Texture2D));
    
    char swordName[30];
    strcpy_s(swordName, "resources/3D animations00");
    
    for (int i = 1; i <= 10; i++){
        char coolName[50];
        strcpy_s(coolName, swordName);
        if (i < 10){
            strcat_s(coolName, "0");
        }
        strcat_s(coolName, to_string(i));
        strcat_s(coolName, ".png");
        swordAnim[i-1] = LoadTexture(coolName);
    }
    float timer = 0.0f;
    
    int texture1Loc = GetShaderLocation(shader, "texture1");
    int interpLoc = GetShaderLocation(shader, "interp");
    
    int alpha_loc = GetShaderLocation(color_shader, "alpha");
    
    Array<Vector2> line_points = Array<Vector2>(3);
    
    // for (int i = 0; i < line_points.count; i++){
    //     Vector2 new_point = {(float)i * 10, 200 * sqrtf((float)i)};
    //     array_add(&line_points, &new_point);
    // }
    
    Vector2 first_point = {50, 50};
    Vector2 second_point = {250, 150};
    Vector2 third_point = {550, 150};
    line_points.add({50, 50});
    line_points.add({250, 150});
    line_points.add({550, 150});
    
    Image imBlue = GenImageColor(800, 450, (Color){ 0, 0, 255, 255 });
    Texture texBlue = LoadTextureFromImage(imBlue);
    UnloadImage(imBlue);
    bear.width *= 0.5f;
    
    while(!WindowShouldClose()){
        float dt = GetFrameTime();
        float changeTime = 0.5;
        float animTime = changeTime * 10;
        timer += dt;
        while (timer > animTime){
            timer -= animTime;
            
            Image screenshot = LoadImageFromScreen();
            FILE* image_file;
            image_file = fopen("abobaaauaua.txt", "w");
            fclose(image_file);
        }
        BeginDrawing();
        ClearBackground(GRAY);
        
        int frame = (int)(timer / changeTime) % 10;
        
        float animT = (timer - frame * changeTime) / changeTime;
        
        // SetShaderValue(shader, texture0Loc, &swordAnim[frame], SHADER_UNIFORM_SAMPLER2D);
        
        BeginShaderMode(shader);
        {
            BeginShaderMode(color_shader);{
                float new_alpha = timer / 5;
                set_shader_value(color_shader, alpha_loc, new_alpha);
                draw_rect(150, 100, 100, 75, BLUE);
                
                new_alpha *= 0.2f;
                set_shader_value(color_shader, alpha_loc, new_alpha);
                
                set_shader_texture(shader, texture1Loc, swordAnim[(frame + 1)%10]);
                set_shader_value(shader, interpLoc, animT);
                
                draw_texture(swordAnim[frame], 100, 100, GREEN);
                DrawSplineLinear(line_points.data, line_points.count, 10, GREEN);
            } EndShaderMode();
        } EndShaderMode();
        
        draw_text(to_string(frame), 500, 50, 40, RED);
        
        //DrawTexturePro(bear, {50, 50, (float)bear.width, (float)bear.height},  {50, 50, 100, 100}, {50, 50}, 0, WHITE);
        //DrawTextureEx(bear, {25, 25}, 20, 1, WHITE);
        
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
