#include "sprite_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <maths/math_utils.h>
#include <system/debug_log.h>
#include <input/input_manager.h>
#include "input/sony_controller_input_manager.h"
#include "graphics/colour.h"


SpriteApp::SpriteApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	font_(NULL),
	input_manager_(NULL)
{
}

void SpriteApp::Init()
{
	// create a sprite renderer to draw your sprites
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	input_manager_ = gef::InputManager::Create(platform_);

	InitFont();

	my_sprite_.set_position(platform_.width()*0.5f, platform_.height()*0.5f, 0.0f);
	my_sprite_.set_width(32.0f);
	my_sprite_.set_height(32.0f);
}

void SpriteApp::CleanUp()
{
	CleanUpFont();

	// destroy sprite renderer once you've finished using it
	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;
}

bool SpriteApp::Update(float frame_time)
{
	// frame rate = 1 second / frame_delta_time
	fps_ = 1.0f / frame_time;

	input_manager_->Update();

	// move the sprite along the x-axis

	// get a copy of the current position of the sprite
	gef::Vector4 sprite_position = my_sprite_.position();

	// update the x-axis on the COPY of the current position
	sprite_position.set_x(sprite_position.x() + 1);

	// update the sprite with the new position
	my_sprite_.set_position(sprite_position);

	int num_controllers = input_manager_->controller_input()->GetDS5ControllerCount();

	// Get additional controllers from GetController(NUM);
	auto controller = input_manager_->controller_input()->GetController(0);

	const gef::SonyController* controller_p2 = NULL;
	if (num_controllers > 1)
		controller_p2 = input_manager_->controller_input()->GetController(1);


	if(controller)
	{
		
		// Getting the button name from an Array
		float log_buttons = log2(controller->buttons_down());
		if(controller->buttons_down() != 0)
			key_name_ = button_names[(int)log_buttons];

		
		// Get angle from stick position
		gef::Vector2 up(0,1);
		gef::Vector2 stick_pos;
		stick_pos.x = controller->left_stick_x_axis();
		stick_pos.y = controller->left_stick_y_axis();

		stick_pos.Normalise();

		float angle = stick_pos.DotProduct(up);
		angle = acos(angle);
		angle = gef::RadToDeg(angle);



		// Set Controller Output data
		gef::ControllerOutputData out_data = controller->get_output_data();

		out_data.lightbar = gef::Colour(0.5, 0 ,0.5);

		out_data.left_trigger_effect.effectType = gef::ControllerOutputData::TriggerEffectType::SectionResitance;
		out_data.left_trigger_effect.Section.startPosition = 0.2;
		out_data.left_trigger_effect.Section.endPosition= 0.4;
		out_data.left_trigger_effect.Continuous.force = 0.5;

		out_data.left_rumble = controller->get_left_trigger()+ controller->get_right_trigger();

		out_data.right_rumble = controller->get_touch_position().y > 100 ? (controller->get_touch_position().y -100) / 1048.f: 0;



		controller->set_output_data(out_data);


		// Get Gyroscope and Accelerator as vector4 -- Gyro is raw data
		auto accel = controller->get_accelerometer();
		auto gyro = controller->get_gyroscope();
		

	}

	return true;
}

void SpriteApp::Render()
{
	// draw all sprites between the Begin() and End() calls
	sprite_renderer_->Begin();

	// draw my sprite here
	sprite_renderer_->DrawSprite(my_sprite_);

	DrawHUD();
	sprite_renderer_->End();
}


void SpriteApp::InitFont()
{
	// create a Font object and load in the comic_sans font data
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SpriteApp::CleanUpFont()
{
	// destroy the Font object
	delete font_;
	font_ = NULL;
}

void SpriteApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(650.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"FPS: %.1f xpos: %.1f",							// string of text to render
			fps_,									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			my_sprite_.position().x()
			);


		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(350.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			key_name_.c_str()
		);
	}


}

