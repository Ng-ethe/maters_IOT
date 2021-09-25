#ifndef _TOGGLEMENUITEM_H
#define _TOGGLEMENUITEM_H
#include <MenuSystem.h>
#include "MyRenderer.h"

class ToggleMenuItem : public MenuItem
{
public:
	/**
	 * @param width the width of the edit mode 'ASCII graphics', must be > 1
	 * @param name The name of the menu item.
	 * @param value Default value.
	 * @param valueFormatter The custom formatter. If nullptr the String float
	 *                       formatter will be used.
	 */
	ToggleMenuItem(const char* name, SelectFnPtr select_fn,const char* onString, const char* offString, bool state);
	void set_state(bool state);
	void set_state_on();
	void set_state_off();
	void toggle_state();
	bool get_state();
	const char* get_state_str();
	virtual void render(MenuComponentRenderer const& renderer) const;

protected:
	virtual Menu* select();

private:
	bool _state;
	const char* _onString;
	const char* _offString;
};

#endif // _TOGGLEMENUITEM_H
