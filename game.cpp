#pragma once

struct Entity{
    b32 enabled = 1;

    Vector2 pos;
    float rotation;
    
    virtual void init(){}
    virtual void born(){}
    
    virtual void update(){}
    
    virtual void enable(){}
    virtual void disable(){}
    virtual void destroy(){}
};

//scale 150 should be full screen;

struct Paper{
    f32 start_width = 100;
    f32 final_width = 1;
    f32 start_height = 5;
    f32 final_height = 60;
    
    f32 start_y_pos = 0;
    f32 final_y_pos = 10;
    
    f32 current_y_pos;
    f32 target_y_pos;
    
    f32 max_width_fold_count = 40.0f;
    f32 max_height_fold_count = 42.0f;
    
    f32 current_width;
    f32 target_width;
    
    f32 current_height;
    f32 target_height;
};

struct Cam{
    Vector2 pos;
    float rotation;
};

enum Screen{
    FULL,
    UP,  
    DOWN,
    RIGHT
};

struct Context{
    Paper up_paper = {};
    Paper down_paper = {};
    Paper right_paper = {};
    i32 fold_count;
    f32 fold_time = 2.0f;
    f32 folding_countdown;

    Cam cam = {};
    
    Screen render_screen;
    Vector2 up_screen_size;
    Vector2 down_screen_size;
    Vector2 right_screen_size;
    Vector2 unit_screen_size;
    
    RenderTexture up_render_target;
    RenderTexture down_render_target;
    RenderTexture right_render_target;
};

Context context = {};

f32 dt;

#include "game.h"

void init_game(){
    context = {};
    
    context.up_screen_size = {screen_width * 0.6f, screen_height * 0.5f};
    context.down_screen_size = {screen_width * 0.6f, screen_height * 0.5f};
    context.right_screen_size = {screen_width * 0.4f, (float)screen_height};
    context.unit_screen_size = {screen_width / UNIT_SIZE, screen_height / UNIT_SIZE};
    
    context.up_render_target = LoadRenderTexture(context.up_screen_size.x, context.up_screen_size.y);
    context.down_render_target = LoadRenderTexture(context.down_screen_size.x, context.down_screen_size.y);
    context.right_render_target = LoadRenderTexture(context.right_screen_size.x, context.right_screen_size.y);
    
    //screen_size_changed = 1;
}

void update_game(){
    if (IsKeyPressed(KEY_SPACE)){
        fold_paper();
    }
    
    //Paper *p = &context.paper;
    if (context.folding_countdown > 0){
        context.folding_countdown -= dt;
        
        if (context.folding_countdown <= 0){
            context.fold_count++;
        }
    }
    
    if (screen_size_changed){
        context.up_screen_size = {screen_width * 0.6f, screen_height * 0.5f};
        context.down_screen_size = {screen_width * 0.6f, screen_height * 0.5f};
        context.right_screen_size = {screen_width * 0.4f, (float)screen_height};
        context.unit_screen_size = {screen_width / UNIT_SIZE, screen_height / UNIT_SIZE};
        
        UnloadRenderTexture(context.up_render_target);
        UnloadRenderTexture(context.down_render_target);
        UnloadRenderTexture(context.up_render_target);
        
        context.up_render_target = LoadRenderTexture(context.up_screen_size.x, context.up_screen_size.y);
        context.down_render_target = LoadRenderTexture(context.down_screen_size.x, context.down_screen_size.y);
        context.right_render_target = LoadRenderTexture(context.right_screen_size.x, context.right_screen_size.y);
    }
    
    draw_game();
}

void draw_paper(Paper *p){
    b32 folding = context.folding_countdown > 0;
    
    update_paper(p);
    
    if (folding){
        p->target_width *= 0.5f;
    }
    
    p->current_y_pos = lerp(p->current_y_pos, p->target_y_pos, dt * 10.0f);
    p->current_width = lerp(p->current_width, p->target_width, dt * 10.0f);
    p->current_height = lerp(p->current_height, p->target_height, dt * 10.0f);
    Vector2 p_pos = {0, p->current_y_pos};
    Vector2 p_scale = {p->current_width, p->current_height};
    
    draw_game_rect(p_pos, p_scale, {folding ? 1 : 0.5f, 1.0f}, WHITE);
    
    //int fold_lines_count = pow(2, context.fold_count);
    i32 fold_lines_count = context.fold_count;
    for (int i = 0; i < fold_lines_count; i++){
        f32 line_y_pos = p->target_y_pos + p->current_height * (float)(i + 1) / (float)(fold_lines_count + 1);
        draw_game_line({-p->current_width * 0.5f, line_y_pos}, {p->current_width * 0.5f, line_y_pos}, 0.2f, BLACK);
    }
    
    if (context.folding_countdown > 0){
        f32 rotation_t = context.folding_countdown / context.fold_time;
        f32 rotation = lerp(-180, 0, rotation_t * rotation_t);
        draw_game_rect(p_pos, p_scale, {0, 1.0f}, rotation, WHITE);
    }
}

void update_paper(Paper *p){
    f32 width_t = clamp01((f32)context.fold_count / p->max_width_fold_count);
    p->target_width = lerp(p->start_width, p->final_width, sqrtf(width_t));
    
    f32 height_t = clamp01((f32)context.fold_count / p->max_height_fold_count);
    p->target_height = lerp(p->start_height, p->final_height, sqrtf(height_t));
    
    p->target_y_pos = lerp(p->start_y_pos, p->final_y_pos, width_t);
    // Vector2 p_pos = {0, y_pos};
    // Vector2 p_scale = {paper_width, paper_height};
}

void draw_up_screen(){
    context.render_screen = UP;
    //Paper *p = &context.paper;
    
    draw_paper(&context.up_paper);
}

void draw_down_screen(){
    context.render_screen = DOWN;
    //Paper *p = &context.paper;
    
    draw_game_rect({0, 10}, {50, 30}, {0.5f, 0}, BROWN);
    draw_paper(&context.down_paper);
}

void draw_right_screen(){
    context.render_screen = RIGHT;
    //Paper *p = &context.paper;
    
    
    draw_paper(&context.right_paper);
}

void draw_borders(){
    context.render_screen = FULL;
    f32 width = 3.0f;
    
    draw_game_rect({-context.unit_screen_size.x * 0.5f, 0}, {width, 100}, {0, 1}, PINK);
    draw_game_rect({-context.unit_screen_size.x * 0.5f, 0}, {200, width}, {0, 1}, PINK);
    draw_game_rect({-context.unit_screen_size.x * 0.5f, context.unit_screen_size.y}, {200, width}, {0, 0}, PINK);
    draw_game_rect({context.unit_screen_size.x * 0.5f, 0}, {width, 100}, {1, 1}, PINK);
    draw_game_rect({-context.unit_screen_size.x * 0.5f, (context.down_screen_size.y / UNIT_SIZE)}, {context.down_screen_size.x / UNIT_SIZE, width}, {0, 0.5f}, PINK);
    draw_game_rect({(context.down_screen_size.x / UNIT_SIZE) - context.unit_screen_size.x * 0.5f, 0}, {width, 100}, {0, 1}, PINK);
}

void draw_game(){
    BeginDrawing();
    
    Context *c = &context;
    
    if (c->fold_count <= 1){
        c->render_screen = FULL;
        ClearBackground(GRAY);
        draw_game_rect({0, 10}, {300, 30}, {0.5f, 0}, BROWN);
        draw_paper(&c->right_paper);
    } else{
        BeginTextureMode(c->up_render_target);{
            ClearBackground(BLUE);
            draw_up_screen();
            draw_text("up", 60, 60, 40, RED);
        } EndTextureMode();
        BeginTextureMode(c->down_render_target);{
            ClearBackground(YELLOW);
            draw_down_screen();
            draw_text("down", 60, 60, 40, RED);
        } EndTextureMode();
        BeginTextureMode(c->right_render_target);{
            ClearBackground(PURPLE);
            draw_right_screen();
            draw_text("right", 60, 60, 40, RED);
        } EndTextureMode();
        
        Texture *up_tex = &c->up_render_target.texture;
        DrawTextureRec(*up_tex, {0, 0, (float)(up_tex->width), (float)-(up_tex->height)}, {0, 0}, WHITE);
        Texture *down_tex = &c->down_render_target.texture;
        DrawTextureRec(*down_tex, {0, 0, (float)(down_tex->width), (float)-(down_tex->height)}, {0, c->up_screen_size.y}, WHITE);
        Texture *right_tex = &c->right_render_target.texture;
        DrawTextureRec(*right_tex, {0, 0, (float)(right_tex->width), (float)-(right_tex->height)}, {c->up_screen_size.x, 0}, WHITE);
        
        draw_borders();
    }
    
    draw_text(c->fold_count, 50, 50, 40, RED);
    
    f64 paper_thick = 0.0001 * pow(2, c->fold_count);
    
    draw_text(paper_thick, 50, 100, 40, BLUE);
    EndDrawing();
}

Vector2 world_to_screen(Vector2 pos){
    Vector2 cam_pos = context.render_screen == DOWN ? context.cam.pos : Vector2Zero();

    Vector2 with_cam = add(pos, cam_pos);
    Vector2 pixels = multiply(pos, UNIT_SIZE);
    
    //Horizontal center and vertical bottom
    
    f32 width_add, height_add;
    
    switch (context.render_screen){
        case UP:{
            width_add = context.up_screen_size.x * 0.5f;    
            height_add = context.up_screen_size.y;    
        } break;
        case DOWN:{
            width_add = context.down_screen_size.x * 0.5f;    
            height_add = context.down_screen_size.y;    
        } break;
        case RIGHT:{
            width_add = context.right_screen_size.x * 0.5f;    
            height_add = context.right_screen_size.y;    
        } break;
        default:{
            width_add = screen_width * 0.5f;    
            height_add = screen_height;    
        } break;
    }
    Vector2 to_center = {pixels.x + width_add, height_add - pixels.y};

    return to_center;
}

Vector2 rect_screen_pos(Vector2 pos, Vector2 scale, Vector2 pivot){
    Vector2 pivot_add = multiply(pivot, scale);
    Vector2 with_pivot_pos = {pos.x - pivot_add.x, pos.y + pivot_add.y};
    Vector2 screen_pos = world_to_screen(with_pivot_pos);
    
    return screen_pos;
}

void draw_game_rect(Vector2 pos, Vector2 scale, Vector2 pivot, Color color){
    Vector2 screen_pos = rect_screen_pos(pos, scale, pivot);
    draw_rect(screen_pos, multiply(scale, UNIT_SIZE), color);
}

void draw_game_rect(Vector2 pos, Vector2 scale, Vector2 pivot, f32 rotation, Color color){
    Vector2 screen_pos = rect_screen_pos(pos, scale, pivot);
    draw_rect(screen_pos, multiply(scale, UNIT_SIZE), rotation, color);
}

void draw_game_line(Vector2 start, Vector2 end, float thick, Color color){
    draw_line(world_to_screen(start), world_to_screen(end), thick * UNIT_SIZE, color);
}

void fold_paper(){
    //Paper *p = &context.paper;
    
    if (context.folding_countdown > 0){
        context.fold_count++;
        
        if (context.fold_count >= 3){
            context.folding_countdown = 0;   
        }
    }
    
    if (context.fold_count >= 3){
        context.fold_count++;  
    } else{
        context.folding_countdown = context.fold_time;
    }
}
