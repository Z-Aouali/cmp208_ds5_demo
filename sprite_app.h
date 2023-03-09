#ifndef _sprite_app_H
#define _sprite_app_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector4.h>
#include <vector>
#include <string>

#include <cmath>


const std::string button_names[] = {
"gef_SONY_CTRL_START	",
"gef_SONY_CTRL_L3		",
"gef_SONY_CTRL_R3		",
"gef_SONY_CTRL_SELECT	",
"gef_SONY_CTRL_UP		",
"gef_SONY_CTRL_RIGHT	",
"gef_SONY_CTRL_DOWN		",
"gef_SONY_CTRL_LEFT		",
"gef_SONY_CTRL_L2		",
"gef_SONY_CTRL_R2		",
"gef_SONY_CTRL_L1		",
"gef_SONY_CTRL_R1		",
"gef_SONY_CTRL_TRIANGLE	",
"gef_SONY_CTRL_CIRCLE	",
"gef_SONY_CTRL_CROSS	",
"gef_SONY_CTRL_SQUARE	",
"gef_SONY_CTRL_PLAYSTATION_LOGO",
"gef_SONY_CTRL_MIC_BUTTON",
"gef_SONY_CTRL_TOUCH_PAD"
};




// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
}

class SpriteApp : public gef::Application
{
public:
	SpriteApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();

	gef::SpriteRenderer* sprite_renderer_;
	gef::InputManager* input_manager_;
	gef::Font* font_;

	float fps_;
	gef::Sprite my_sprite_;

	std::string key_name_;

	float yaxisval;
	float xaxisval;
};

#endif // _sprite_app_H
