#include <raylib.h>

typedef struct Animation {
    int first;
    int last;
    int current;

    float speed;
    float duration_left;
} Animation;

void AnimationUpdate(Animation* self);

Rectangle AnimationFrame(Animation* self,int num_frames_per_row);

int main() {

  InitWindow(600, 400, "Sprite test");

  Texture2D player_texture = LoadTexture("assets/sprite.png");

  Animation anim = (Animation) {
    .first = 0,
    .last = 3,
    .current = 0,
    .speed = 0.1f,
    .duration_left = 0.1f
  };

  while (!WindowShouldClose()) {

    AnimationUpdate(&anim);

    BeginDrawing();

    ClearBackground(SKYBLUE);

    DrawTexturePro(
        player_texture,
        AnimationFrame(&anim, 4),
        (Rectangle){10, 10, 100, 100}, 
        (Vector2){0, 0},
        0,
        WHITE);

    EndDrawing();
  }

  UnloadTexture(player_texture);

  CloseWindow();

  return 0;
}

void AnimationUpdate(Animation* self) {
    float dt = GetFrameTime();
    self->duration_left -= dt;
    if (self->duration_left <=0) {
        self->duration_left = self->speed;
        self->current++;

        if (self->current > self->last) {
            // repeat
            self->current = self->first;
        }
    }
}

Rectangle AnimationFrame(Animation* self, int num_frames_per_row) {
    int x = (self->current % num_frames_per_row) * 16;
    int y = (self->current / num_frames_per_row) * 16;

    return (Rectangle) {
        x=x,
        y=y,
        16.0f,
        16.0f
    };
}