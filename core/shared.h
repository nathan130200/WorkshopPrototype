#include <imgui.h>
#include "../imnodes/imnodes.h"

#ifndef _SHARED_H_
#define _SHARED_H_

template<typename T>
class GraphElement;
class Graph;
class Node;
class Pin;

#define OW_COLORS_FLOW IM_COL32(240, 240, 240, 255)
#define OW_COLORS_ANY IM_COL32(189, 189, 189, 255)
#define OW_COLORS_NUMBER IM_COL32(169, 247, 126, 255)
#define OW_COLORS_BOOLEAN IM_COL32(255, 48, 48, 255)
#define OW_COLORS_VECTOR IM_COL32(255, 89, 0, 255)
#define OW_COLORS_ENTITY IM_COL32(136, 0, 255, 255)
#define OW_COLORS_FUNCTION IM_COL32(72, 105, 240, 255)
#define OW_COLORS_ENUM IM_COL32(230, 39, 230, 255)

#include "IGraphElement.h"
#include "Node.h"
#include "Pin.h"
#include "impl.h"

#endif