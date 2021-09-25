#include "ToggleMenuItem.h"


ToggleMenuItem::ToggleMenuItem(const char* name, SelectFnPtr select_fn, const char* onString, const char* offString, bool state = false) :
	MenuItem(name, select_fn), _onString(onString), _offString(offString), _state(state)
{

}
void ToggleMenuItem::set_state(bool state)
{
	_state = state;
}
bool ToggleMenuItem::get_state()
{
	return _state;
}

const char* ToggleMenuItem::get_state_str()
{
	if (get_state())
		return _onString;
	else 
		return _offString;
}

void ToggleMenuItem::set_state_on()
{
	_state = true;
}

void ToggleMenuItem::set_state_off()
{
	_state = false;
}

void ToggleMenuItem::toggle_state()
{
	_state = !_state;
}

Menu* ToggleMenuItem::select()
{
	toggle_state();
	if (_select_fn != nullptr)
		_select_fn(this);
	return nullptr;
}

void ToggleMenuItem::render(MenuComponentRenderer const& renderer) const {
	MyRenderer const& my_renderer = static_cast<MyRenderer const&>(renderer);
	my_renderer.render_toggle_menu_item(*this);
}


