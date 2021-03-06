#include "XinputManager.h"

XinputManager* XinputManager::instance = 0;
XinputController XinputManager::controllers[4];

bool XinputManager::create()
{
	if (!instance)
	{
		instance = new XinputManager();
		return true;
	}
	return false;
}

XinputManager::XinputManager()
{
	for (int index = 0; index < 4; index++)
		controllers[index].setControllerIndex(index);
}

bool XinputManager::controllerConnected(int index)
{
	if (index < 0 || index >= 4)
		return false;

	XINPUT_STATE connected;

	return XInputGetState(index, &connected) == ERROR_SUCCESS;
}

XinputController * XinputManager::getController(int index)
{
	if (index >= 0 && index < 4)
		return &controllers[index];

	return nullptr;
}

void XinputManager::update()
{
	for (int index = 0; index < 4; index++)
	{
		if (controllerConnected(index))
		{
			controllers[index].update();
		}
	}
}
