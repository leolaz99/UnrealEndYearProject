#include "LLPlayerController.h"

void ALLPlayerController::CheckGamepad(struct FKey pressedKey)
{
	bool isGamepadKey = pressedKey.IsGamepadKey();

	if (isGamepadKey)
		isUsingGamepad = true;
	else
		isUsingGamepad = false;
}
