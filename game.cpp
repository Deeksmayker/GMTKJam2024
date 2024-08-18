#pragma once

f32 dt;

enum Screen{
    FULL,
    UP,  
    DOWN,
    RIGHT
};

struct Entity{
    b32 enabled = 1;
    
    Vector2 pos;
    Vector2 scale = {1, 1};
    Vector2 pivot = {0.5f, 1.0f};
    float rotation;
    
    virtual void init(){}
    virtual void born(){}
    
    virtual void update(){}
    virtual void draw(){}
    
    virtual void enable(){}
    virtual void disable(){}
    virtual void destroy(){}
};


struct Anim {
    Texture *frames;
    Vector2 pos;
    Vector2 scale = {1, 1};
    Vector2 pivot = {0.5f, 1.0f};
    
    Color tint = WHITE;
    int frame_count;
    const char *base_name;
    f32 change_time = 0.03f;
    
    i32 frame = 0;
    f32 anim_timer = 0;
    
    // Anim(const char *name, int count, Vector2 tex_scale, Vector2 world_pos){
    //     base_name = name;
    //     frame_count = count;
    //     scale = tex_scale;
    //     pos = world_pos;
    // }
    
    // void init() override{
    //     frames = (Texture*)malloc(frame_count * sizeof(Texture));
        
    //     if (frame_count == 1){
    //         frames[0] = LoadTexture(TextFormat("%s%s%s", "resources/", base_name, ".png"));
    //     } else{
    //         for (int i = 0; i < frame_count; i++){
    //             frames[i] = LoadTexture(TextFormat("%s%s%d%s", "resources/", base_name, i+1, ".png"));
    //         }
    //     }
        
    // }
    
    b32 backwards = 0;
    // void update() override{
    //     if (!enabled){
    //         return;
    //     }
        
    //     anim_timer += dt;
        
    //     while (anim_timer > change_time){
    //         anim_timer -= change_time;
    //         // if (backwards){
    //         //     frame--;
    //         //     if (frame <= 0){
    //         //         backwards = 0;
    //         //     }
    //         // } else{
    //         //     frame++;
    //         //     if (frame >= frame_count - 1){
    //         //         backwards = 1;
    //         //     }
    //         // }
    //         frame++;
    //         frame%=frame_count;
    //     }
    // }
    
    // void draw() override{
    //     if (frame == frame_count - 1){
    //         // BeginShaderMode(context.lerp_shader);{
    //         //     set_shader_texture(context.lerp_shader, context.tex1_loc, frames[(frame+1)%frame_count]);
    //         //     set_shader_value(context.lerp_shader, context.interp_loc, anim_timer / change_time);
    //             //draw_game_texture(frames[0], pos, scale, pivot, tint);
    //         //} EndShaderMode();
    //     } 
    //         draw_game_texture(frames[frame], pos, scale, pivot, tint);
    // }
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
    
    i32 height_grow_mode = 0;
};

struct Cam{
    Vector2 pos;
    float rotation;
};

struct Context{
    // Array<Entity*> *down_entities = new Array<Entity*>(100);
    // Array<Entity*> *right_entities = new Array<Entity*>(100);
    // Array<Entity*> *up_entities = new Array<Entity*>(100);
    
    //Array<Anim*> *grass_anims = new Array<Anim*>(20);
    
    Array<Anim*> *front_anims = new Array<Anim*>(100);
    Array<Anim*> *mid_anims   = new Array<Anim*>(100);
    Array<Anim*> *back_anims  = new Array<Anim*>(100);

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
    
    Shader lerp_shader;
    int interp_loc;
    int tex1_loc;
};

Context context = {};

#include "game.h"

Texture *grass_sprites;
Texture *earth_sprites;
Texture *tree_sprites;

void init_game(){
    context = {};
    
    Context *c = &context;
    
    c->lerp_shader = LoadShader(0, "sobel.fs");
    c->interp_loc = get_shader_location(c->lerp_shader, "interp");
    c->tex1_loc = get_shader_location(c->lerp_shader, "texture1");
    
    //Anim *grass_anim = (Anim *)malloc(sizeof(Anim));
    // *grass_anim = Anim("Grass_", 60, {1, 1});
    // grass_anim->init();
    
    load_anim(grass_sprites, 401, "Grass/Grass_");
    load_anim(tree_sprites, 120, "Tree/Tree_");
    load_anim(earth_sprites, 1, "Earth");
    
    // c->down_entities->add(new Anim("Grass/Grass_", 401, {1, 1}, {0, 1}));
    // c->down_entities->add(new Anim("Grass/Grass_", 401, {1, 1}, {0, 10}));
    
    //c->right_entities->add(new Anim("Tree/Tree_", 120, {1, 1}, {-10, 10}));
    //c->down_entities->add(new Anim("Grass/Grass_", 401, {1, 1}, {10, 1}));
    
    //c->right_entities->add(new Anim("Earth", 1, {0.5f, 0.5f}, {0, 20}));
    
    c->up_screen_size = {screen_width * 0.75f, screen_height * 0.5f};
    c->down_screen_size = {screen_width * 0.75f, screen_height * 0.5f};
    c->right_screen_size = {screen_width * 0.25f, (float)screen_height};
    c->unit_screen_size = {screen_width / UNIT_SIZE, screen_height / UNIT_SIZE};
    
    Paper *up = &c->up_paper;
    up->start_width = 40;
    up->final_width = 5;
    up->start_height = 5;
    up->final_height = 10;
    up->start_y_pos = 0;
    up->final_y_pos = 0;
    up->max_width_fold_count = 30;
    up->max_height_fold_count = 30;
    
    Paper *down = &c->down_paper;
    down->start_width = 40;
    down->final_width = 5;
    down->start_height = 5;
    down->final_height = c->down_screen_size.y / UNIT_SIZE;
    down->start_y_pos = 0;
    down->final_y_pos = 10;
    down->max_width_fold_count = 30;
    down->max_height_fold_count = 13;
    
    Paper *right = &c->right_paper;
    right->start_width = 0.5f;
    right->final_width = 2;
    right->final_height = (c->right_screen_size.y / UNIT_SIZE) - 40;
    right->start_height = right->final_height / pow(2, 42);
    right->start_y_pos = 20;
    right->final_y_pos = 20;
    right->max_width_fold_count = 40;
    right->max_height_fold_count = 42;
    
    right->height_grow_mode = 1;
    
    c->up_render_target = LoadRenderTexture(c->up_screen_size.x, c->up_screen_size.y);
    c->down_render_target = LoadRenderTexture(c->down_screen_size.x, c->down_screen_size.y);
    c->right_render_target = LoadRenderTexture(c->right_screen_size.x, c->right_screen_size.y);
    
    //screen_size_changed = 1;
    
    for (int i = 0; i < c->down_entities->count; i++){
        c->down_entities->get(i)->init();
    }
    for (int i = 0; i < c->up_entities->count; i++){
        c->up_entities->get(i)->init();
    }
    for (int i = 0; i < c->right_entities->count; i++){
        c->right_entities->get(i)->init();
    }
}

void update_game(){
    if (IsKeyPressed(KEY_SPACE)){
        fold_paper();
    }
    Context *c = &context;
    
    //Paper *p = &context.paper;
    if (c->folding_countdown > 0){
        c->folding_countdown -= dt;
        
        if (c->folding_countdown <= 0){
            c->fold_count++;
        }
    }
    
    if (screen_size_changed){
        c->up_screen_size = {screen_width * 0.6f, screen_height * 0.5f};
        c->down_screen_size = {screen_width * 0.6f, screen_height * 0.5f};
        c->right_screen_size = {screen_width * 0.4f, (float)screen_height};
        c->unit_screen_size = {screen_width / UNIT_SIZE, screen_height / UNIT_SIZE};
        
        UnloadRenderTexture(c->up_render_target);
        UnloadRenderTexture(c->down_render_target);
        UnloadRenderTexture(c->up_render_target);
        
        c->up_render_target = LoadRenderTexture(c->up_screen_size.x, c->up_screen_size.y);
        c->down_render_target = LoadRenderTexture(c->down_screen_size.x, c->down_screen_size.y);
        c->right_render_target = LoadRenderTexture(c->right_screen_size.x, c->right_screen_size.y);
    }
    
    for (int i = 0; i < c->down_entities->count; i++){
        c->down_entities->get(i)->update();
    }
    for (int i = 0; i < c->up_entities->count; i++){
        c->up_entities->get(i)->update();
    }
    for (int i = 0; i < c->right_entities->count; i++){
        c->right_entities->get(i)->update();
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
    
    if (p->height_grow_mode == 1){
        p->target_height = p->start_height * pow(2, context.fold_count);
    } else{
        f32 height_t = clamp01((f32)context.fold_count / p->max_height_fold_count);
        p->target_height = lerp(p->start_height, p->final_height, sqrtf(height_t));
    }
    p->target_y_pos = lerp(p->start_y_pos, p->final_y_pos, width_t);
    // Vector2 p_pos = {0, y_pos};
    // Vector2 p_scale = {paper_width, paper_height};
}

void update_anim(Anim *anim){
    anim->anim_timer += dt;
    
    while (anim->anim_timer > anim->change_time){
        anim->anim_timer -= anim->change_time;
        // if (backwards){
        //     frame--;
        //     if (frame <= 0){
        //         backwards = 0;
        //     }
        // } else{
        //     frame++;
        //     if (frame >= frame_count - 1){
        //         backwards = 1;
        //     }
        // }
        anim->frame++;
        anim->frame%=anim->frame_count;
    }
}

void draw_anim(Anim *anim, Texture *textures){
    draw_game_texture(textures[anim->frame], anim->pos, anim->scale, anim->pivot, anim->tint);
}

void load_anim(Texture *frames, int count, const char *name){
    frames = (Texture*)malloc(count * sizeof(Texture))
    if (count == 1){
        frames[0] = LoadTexture(TextFormat("%s%s%s", "resources/", name, ".png"));
    } else{
        for (int i = 0; i < count; i++){
            frames[i] = LoadTexture(TextFormat("%s%s%d%s", "resources/", name, i+1, ".png"));
        }
    }

}

void draw_up_screen(){
    context.render_screen = UP;
    //Paper *p = &context.paper;
    
    for (int i = 0; i < context.up_entities->count; i++){
        context.up_entities->get(i)->draw();
    }

    
    draw_paper(&context.up_paper);
}

void draw_down_screen(){
    context.render_screen = DOWN;
    //Paper *p = &context.paper;
    context.down_entities->get(1)->draw();
    
    //draw_game_rect({0, 10}, {50, 30}, {0.5f, 0}, BROWN);
    draw_paper(&context.down_paper);
    
    context.down_entities->get(0)->draw();
}

void draw_right_screen(){
    context.render_screen = RIGHT;
    //Paper *p = &context.paper;
    
    for (int i = 0; i < context.right_entities->count; i++){
        context.right_entities->get(i)->draw();
    }

    
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
    
    if (c->fold_count <= 13){
        c->render_screen = FULL;
        ClearBackground(GRAY);
        draw_game_rect({0, 10}, {300, 30}, {0.5f, 0}, BROWN);
        draw_paper(&c->down_paper);
    } else{
        BeginTextureMode(c->up_render_target);{
            ClearBackground(BLUE);
            draw_up_screen();
            draw_text("up", 60, 60, 40, RED);
        } EndTextureMode();
        BeginTextureMode(c->down_render_target);{
            ClearBackground(SKYBLUE);
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

void draw_game_texture(Texture tex, Vector2 pos, Vector2 scale, Vector2 pivot, Color color){
    tex.width *= scale.x;
    tex.height *= scale.y;
    // scale.x *= tex.width  / UNIT_SIZE;
    // scale.y *= tex.height / UNIT_SIZE;
    Vector2 screen_pos = rect_screen_pos(pos, {(float)tex.width / UNIT_SIZE, (f32)tex.height / UNIT_SIZE}, pivot);
    draw_texture(tex, screen_pos, color);
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
