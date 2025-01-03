#ifndef PROTOTYPE_HPP
# define PROTOTYPE_HPP

#include <engine.hpp>

engine_t init_engine(void);
void close_engine(engine_t &engine);

void UpdateLightValues(Shader shader, light_t light);
light_t CreateLight(int type, Vector3 position, Vector3 target, Color color, Shader shader);
void render(level_t level, engine_t &engine, void (*render_ui)(void));

void update_input(engine_t &engine);

void draw_inventory(inventory_t inventory);

void draw_ui(std::vector<Texture2D> texture, int TEXTURE_CROSSAIR, sv_player_t player);

#endif