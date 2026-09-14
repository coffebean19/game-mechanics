#include "raylib.h"

typedef struct Bullet {
        Vector2 bullet_position;
        Vector2 target_position;
        Color bullet_color;
        bool is_active;
        float bullet_speed;
        Vector2 bullet_speed2;
} Bullet;

extern Bullet* CreateBullet(
                Vector2 bullet_position,
                Vector2 target_position,
                Color bullet_color,
                bool is_active,
                float bullet_speed,
                Vector2 bullet_speed2
                );

void DestroyBullet(Bullet* bullet);
