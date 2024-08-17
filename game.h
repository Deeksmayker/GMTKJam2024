#pragma once

void fold_paper();
void draw_game();
void update_paper(Paper *p);
Vector2 world_to_screen(Vector2 pos);
void draw_game_rect(Vector2 pos, Vector2 scale, Vector2 pivot, Color color);
void draw_game_rect(Vector2 pos, Vector2 scale, Vector2 pivot, f32 rotation, Color color);
void draw_game_line(Vector2 start, Vector2 end, float thick, Color color);

