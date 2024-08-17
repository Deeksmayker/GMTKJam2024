#pragma once

void draw_texture(Texture tex, Vector2 pos, Color tint){
    DrawTextureV(tex, pos, tint);
}

void draw_texture(Texture tex, int x, int y, Color tint){
    DrawTexture(tex, x, y, tint);
}

void draw_texture(Texture tex, Vector2 pos, float rotation, Color tint){
    DrawTextureEx(tex, pos, rotation, 1, tint);
}

void draw_rect(Vector2 pos, Vector2 size, Color color){
    DrawRectangleV(pos, size, color);
}

void draw_rect(Vector2 pos, Vector2 size, f32 rotation, Color color){
    DrawRectanglePro({pos.x, pos.y, size.x, size.y}, {0, 0}, rotation, color);
}

void draw_rect(int x, int y, int width, int height, Color color){
    DrawRectangle(x, y, width, height, color);
}

void draw_line(Vector2 start, Vector2 end, f32 thick, Color color){
    DrawLineEx(start, end, thick, color);
}

void draw_text(char *text, Vector2 pos, float size, Color color){
    DrawText(text, pos.x, pos.y, size, color);
}

void draw_text(char *text, float x, float y, float size, Color color){
    DrawText(text, x, y, size, color);
}

void draw_text(int num, float x, float y, float size, Color color){
    char *str = to_string(num);
    DrawText(str, x, y, size, color);
    free(str);
}

void draw_text(f32 num, float x, float y, float size, Color color){
    char *str = to_string(num);
    DrawText(str, x, y, size, color);
    free(str);
}

void draw_text(f64 num, float x, float y, float size, Color color){
    char *str = to_string(num);
    DrawText(str, x, y, size, color);
    free(str);
}

void draw_text(int num, Vector2 pos, float size, Color color){
    char *str = to_string(num);
    DrawText(str, pos.x, pos.y, size, color);
    free(str);
}
void draw_text(f32 num, Vector2 pos, float size, Color color){
    char *str = to_string(num);
    DrawText(str, pos.x, pos.y, size, color);
    free(str);
}
void draw_text(f64 num, Vector2 pos, float size, Color color){
    char *str = to_string(num);
    DrawText(str, pos.x, pos.y, size, color);
    free(str);
}

int get_shader_location(Shader shader, const char *name){
    return GetShaderLocation(shader, name);
}

void set_shader_value(Shader shader, int loc, float value){
    SetShaderValue(shader, loc, &value, SHADER_UNIFORM_FLOAT);
}

void set_shader_texture(Shader shader, int loc, Texture tex){
    SetShaderValueTexture(shader, loc, tex);
}
    
