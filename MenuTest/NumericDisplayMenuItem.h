#ifndef NUMERIC_DISPLAY_MENU_ITEM_H
#define NUMERIC_DISPLAY_MENU_ITEM_H
#include <MenuSystem.h>
#include "MyRenderer.h"

class NumericDisplayMenuItem : public MenuItem {
public:
	//! \brief Callback for formatting the numeric value into a String.
	//!
	//! \param value The value to convert.
	//! \returns The String representation of value.
	using FormatValueFnPtr = const String(*)(const float value);

public:
	//! Constructor
	//!
	//! @param name The name of the menu item.
	//! @param select_fn The function to call when this MenuItem is selected.
	//! @param value Default value
	//! @param format_value_fn The custom formatter. If nullptr the String
	//!                        float formatter will be used.
	NumericDisplayMenuItem(const char* name, SelectFnPtr select_fn,
		float value,FormatValueFnPtr format_value_fn = nullptr);

	//!
	//! \brief Sets the custom number formatter.
	//!
	//! \param numberFormat the custom formatter. If nullptr the String float
	//!                     formatter will be used (2 decimals)
	//!
	void set_number_formatter(FormatValueFnPtr format_value_fn);

	float get_value() const;

	void set_value(float value);

	String get_formatted_value() const;

	virtual void render(MenuComponentRenderer const& renderer) const;

protected:
	float _value;
	FormatValueFnPtr _format_value_fn;
};

#endif 