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

void draw_rect(int x, int y, int width, int height, Color color){
    DrawRectangle(x, y, width, height, color);
}

void draw_text(char *text, Vector2 pos, float size, Color color){
    DrawText(text, pos.x, pos.y, size, color);
}

void draw_text(char *text, float x, float y, float size, Color color){
    DrawText(text, x, y, size, color);
}

void set_shader_value(Shader shader, int loc, float value){
    SetShaderValue(shader, loc, &value, SHADER_UNIFORM_FLOAT);
}

void set_shader_texture(Shader shader, int loc, Texture tex){
    SetShaderValueTexture(shader, loc, tex);
}
    
