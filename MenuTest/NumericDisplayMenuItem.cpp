#include "NumericDisplayMenuItem.h"

NumericDisplayMenuItem::NumericDisplayMenuItem(const char* basename, SelectFnPtr select_fn,
	float value, FormatValueFnPtr format_value_fn)
	: MenuItem(basename, select_fn),
	_value(value),
	_format_value_fn(format_value_fn) {
};

void NumericDisplayMenuItem::set_number_formatter(FormatValueFnPtr format_value_fn) {
	_format_value_fn = format_value_fn;
}

void NumericDisplayMenuItem::render(MenuComponentRenderer const& renderer) const {
	MyRenderer const& my_renderer = static_cast<MyRenderer const&>(renderer);
	my_renderer.render_numeric_display_menu_item(*this);
}

float NumericDisplayMenuItem::get_value() const {
	return _value;
}

String NumericDisplayMenuItem::get_formatted_value() const {
	String buffer;
	if (_format_value_fn != nullptr)
		buffer += _format_value_fn(_value);
	else
		buffer += _value;
	return buffer;
}

void NumericDisplayMenuItem::set_value(float value) {
	_value = value;
}
