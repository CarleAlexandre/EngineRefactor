#include <engine.hpp>

void update_input(engine_t &engine) {
	Vector2 delta = GetMouseDelta();
	SetMousePosition(GetScreenWidth()* 0.5, GetScreenHeight() * 0.5); 
	Vector3 step = {0};

	if (IsKeyDown(KEY_W)) {
		step.x++;
	}
	if (IsKeyDown(KEY_S)) {
		step.x--;
	}
	if (IsKeyDown(KEY_A)) {
		step.y--;
	}
	if (IsKeyDown(KEY_D)) {
		step.y++;
	}
	if (IsKeyDown(KEY_SPACE)) {
		step.z++;
	}
	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		step.z--;
	}

	// CameraYaw(&engine.camera, delta.x * DEG2RAD * 0.2, false);
	// CameraPitch(&engine.camera, -delta.y * DEG2RAD * 0.2, true, false, false);
	UpdateCameraPro(&engine.camera, step, {(float)(delta.x * 0.2), (float)(delta.y * 0.2), 0}, 0);
}
