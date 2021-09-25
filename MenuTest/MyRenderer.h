/*
 * An example of a custom NumericMenuItem.
 * It tries to display some ASCII graphics in edit mode.
 * This can be useful if you want to give the end user an overview of the value limits.
 * 
 * Copyright (c) 2016 arduino-menusystem
 * Licensed under the MIT license (see LICENSE)
 */

#ifndef _MY_RENDERER_H
#define _MY_RENDERER_H
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MenuSystem.h>
#include "ToggleMenuItem.h"
#include "NumericDisplayMenuItem.h"

class CustomNumericMenuItem;

class MyRenderer : public MenuComponentRenderer
{
public:
	MyRenderer(Adafruit_SSD1306* display,uint16_t lines);
    virtual void render(Menu const& menu) const;
    virtual void render_menu_item(MenuItem const& menu_item) const;
    virtual void render_back_menu_item(BackMenuItem const& menu_item) const;
    virtual void render_numeric_menu_item(NumericMenuItem const& menu_item) const;
	virtual void render_toggle_menu_item(ToggleMenuItem const& menu_item) const;
	virtual void render_numeric_display_menu_item(NumericDisplayMenuItem const& menu_item) const;
    virtual void render_menu(Menu const& menu) const;
private:
	Adafruit_SSD1306* _display;
	uint16_t _lines;
};

#endif
