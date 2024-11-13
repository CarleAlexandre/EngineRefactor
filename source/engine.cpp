#include <engine.hpp>

engine_t init_engine(void) {
	int screenwidth, screenheight;

	screenwidth = GetScreenWidth();
	screenheight = GetScreenHeight();
	engine_t engine;
	Camera3D camera;
	camera.fovy = 90;
	camera.position = {0, 10, 0};
	camera.projection = CAMERA_PERSPECTIVE;
	camera.target = {0, 0, 0};
	camera.up = {0, 1, 0};
	engine.camera = camera;

	engine.posprocess = LoadShader(0, "shader/postprocess.fs");
	engine.deffered_shader = LoadShader("shader/defered.vs", "shader/defered.fs");
	engine.light = LoadShader("shader/light.vs", "shader/light.fs");
	engine.gbuffer_shader = LoadShader("shader/gbuffer.vs", "shader/gbuffer.fs");

	engine.fbo = LoadRenderTexture(screenwidth, screenheight);
	engine.gbuffer = {0};
	engine.gbuffer.framebuffer = rlLoadFramebuffer(screenwidth, screenheight);
	if (!engine.gbuffer.framebuffer) {
		TraceLog(LOG_WARNING, "failed to create framebuffer");
		exit(1);
	}
	rlEnableFramebuffer(engine.gbuffer.framebuffer);

	engine.gbuffer.positionTexture = rlLoadTexture(NULL, screenwidth,screenheight, RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32, 1);
	engine.gbuffer.normalTexture = rlLoadTexture(NULL, screenwidth,screenheight, RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32, 1);
	engine.gbuffer.albedoSpecTexture = rlLoadTexture(NULL, screenwidth,screenheight, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
	rlActiveDrawBuffers(3);

	rlFramebufferAttach(engine.gbuffer.framebuffer, engine.gbuffer.positionTexture, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
	rlFramebufferAttach(engine.gbuffer.framebuffer, engine.gbuffer.normalTexture, RL_ATTACHMENT_COLOR_CHANNEL1, RL_ATTACHMENT_TEXTURE2D, 0);
	rlFramebufferAttach(engine.gbuffer.framebuffer, engine.gbuffer.albedoSpecTexture, RL_ATTACHMENT_COLOR_CHANNEL2, RL_ATTACHMENT_TEXTURE2D, 0);

	engine.gbuffer.depthRenderbuffer = rlLoadTextureDepth(screenwidth, screenheight, true);
	rlFramebufferAttach(engine.gbuffer.framebuffer, engine.gbuffer.depthRenderbuffer, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);

	if (!rlFramebufferComplete(engine.gbuffer.framebuffer)) {
		TraceLog(LOG_WARNING, "Framebuffer is not complete");
		exit(1);
	}

	rlEnableShader(engine.deffered_shader.id);
		rlSetUniformSampler(rlGetLocationUniform(engine.deffered_shader.id, "gPosition"), 0);
    	rlSetUniformSampler(rlGetLocationUniform(engine.deffered_shader.id, "gNormal"), 1);
        rlSetUniformSampler(rlGetLocationUniform(engine.deffered_shader.id, "gAlbedoSpec"), 2);
	rlDisableShader();

	rlEnableDepthTest();

	SetTargetFPS(60);

	engine.mode = DEFERRED_SHADING;
	return (engine);
}

void close_engine(engine_t &engine) {
	UnloadShader(engine.deffered_shader);
    UnloadShader(engine.gbuffer_shader);
	UnloadShader(engine.light);
	UnloadShader(engine.posprocess);

    // Unload geometry buffer and all attached textures
    rlUnloadFramebuffer(engine.gbuffer.framebuffer);
    rlUnloadTexture(engine.gbuffer.positionTexture);
    rlUnloadTexture(engine.gbuffer.normalTexture);
    rlUnloadTexture(engine.gbuffer.albedoSpecTexture);
    rlUnloadTexture(engine.gbuffer.depthRenderbuffer);
	CloseWindow();
}