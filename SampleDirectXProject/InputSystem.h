#pragma once

#include "InputListener.h"
#include <unordered_set>
#include "Point.h"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void setCursorPosition(const Point& point);
	void showCursor(bool show);

	Point GetMousePositionInWindow() const;

public:
	static InputSystem* get();

public:
	void ConsumeLeftMouseButton();

private:
	std::unordered_set<InputListener*> m_set_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point m_old_mouse_pos;
	bool m_first_time = true;

	bool lmbConsumed = false;
};

