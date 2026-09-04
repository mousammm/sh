#ifndef GFX_DRAW_HEADER
#define GFX_DRAW_HEADER

#include <math.h>
#include <stdint.h>
#include "./sdl_gfx.h"

typedef struct {
  float x, y;
} vec2_t;

static void gfx_draw_line(sdl_gfx* gfx, const vec2_t a, const vec2_t b, const uint32_t color) {
    const float d_x = b.x - a.x;
    const float d_y = b.y - a.y;

    const float longer_delta = fabsf(d_x) >= fabsf(d_y) ? fabsf(d_x) : fabsf(d_y);

    const float inc_x = d_x / longer_delta;
    const float inc_y = d_y / longer_delta;

    float x = a.x;
    float y = a.y;

    for (int i = 0; i <= (int)longer_delta; ++i) {
        sdl_gfx_put_pixel(gfx, (int)x, (int)y, color);
        x += inc_x;
        y += inc_y;
    }
}

#endif // ifndef GFX_DRAW_HEADER
