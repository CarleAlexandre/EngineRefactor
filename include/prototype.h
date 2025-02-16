#ifndef PROTOTYPE_HPP
# define PROTOTYPE_HPP

#include "engine.h"

/*
	ENGINE
*/

void		close_engine(engine_t *engine);
engine_t	init_engine(void);

/*
	INPUT
*/

void	update_input(engine_t *engine);

/*
	INVENTORY
*/



/*
	RENDER
*/

void		setup_world_vao(world_t *world);
void		setup_world_ssbo(world_t *world);
void		setup_indirect_buffer(rend_pip_t *render, world_t *world);
void		reload_world_vao(world_t *world);
void		reload_world_ssbo(world_t *world);
void		reload_indirect_buffer(rend_pip_t *render, world_t *world, int chunk);
void		voxel_render(engine_t *engine, world_t *world);
gbuffer_t	loadGbuffer(int width, int height, Shader deffered_shader);

/*
	VOXEL
*/

void	set_block(chunk_t *chunk, int x, int y, int z, int id);

/*
	UI
*/

void	draw_ui(sv_player_t player);
void	draw_inventory(inventory_t inventory);
void	init_toolbar(tool_bar_t *tool_bar);
void	draw_toolbar(tool_bar_t *tool_bar);

/*
	PROCEDURAL
*/

Texture2D	gen_texture_noise(fnl_state *noise);

#endif
