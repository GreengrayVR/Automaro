#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <memory>
#include <chrono>
#include <thread>
#include <cassert>
#include <stack>
#include <string>
#include <locale>
#include <codecvt>

#include "../CMDGraphics/CMDGraphics/CMDGraphics.hpp"

#include "Common.hpp"
#include "IComponent.hpp"
#include "Key.hpp"
#include "Vector.hpp"
#include "Transform.hpp"
#include "IKeyboardHandler.hpp"
#include "IView.hpp"
#include "ViewASCII.hpp"
#include "PopupManager.hpp"
#include "Object.hpp"
#include "ObjectIterator.hpp"
#include "Item.hpp"
#include "Inventory.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "IPlaceable.hpp"
#include "Ore.hpp"
#include "IMachine.hpp"
#include "Miner.hpp"
#include "MachineManager.hpp"
#include "IPipe.hpp"
#include "ItemPipe.hpp"