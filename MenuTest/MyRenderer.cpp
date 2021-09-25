#include "MyRenderer.h"

MyRenderer::MyRenderer(Adafruit_SSD1306* display, uint16_t lines) :
	_display(display), _lines(lines)
{
}

void MyRenderer::render(Menu const& menu) const
{
	_display->clearDisplay();
	_display->setCursor(0, 0);
	uint8_t first_displayLine = menu.get_current_component_num() - menu.get_current_component_num() % _lines;
	for (uint8_t i = first_displayLine; ((i<first_displayLine + _lines) && (i < menu.get_num_components())); ++i)
	{
		MenuComponent const* menuComponent = menu.get_menu_component(i);
		if (menuComponent->has_focus())
			_display->print("=");
		if (menuComponent->is_current())
			_display->print(">");
		else
			_display->print(" ");
		menuComponent->render(*this);
		_display->println("");
	}
	_display->display();
}

void MyRenderer::render_menu_item(MenuItem const& menu_item) const
{
    _display->print(menu_item.get_name());
}

void MyRenderer::render_back_menu_item(BackMenuItem const& menu_item) const
{
	_display->print(menu_item.get_name());
}

void MyRenderer::render_numeric_menu_item(NumericMenuItem const& menu_item) const
{
	_display->print(menu_item.get_name());
	_display->print(" ");
	_display->print(menu_item.get_value());
}

void MyRenderer::render_toggle_menu_item(ToggleMenuItem const& menu_item) const
{
	_display->print(menu_item.get_name());
	_display->print(" ");
	_display->print(menu_item.get_state_str());
}

void MyRenderer::render_numeric_display_menu_item(NumericDisplayMenuItem const& menu_item) const
{
	_display->print(menu_item.get_name());
	_display->print(" ");
	_display->print(menu_item.get_value());
}

void MyRenderer::render_menu(Menu const& menu) const
{
	_display->print(menu.get_name());
}

