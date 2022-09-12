#include <vector>
#include "Pin.h"

#ifndef _NODE_H_
#define _NODE_H_

enum NodeType : unsigned
{
	NodeType_Flow = OW_COLORS_FLOW,
	NodeType_ValueNumber = OW_COLORS_NUMBER,
	NodeType_ValueBoolean = OW_COLORS_BOOLEAN,
	NodeType_ValueVector = OW_COLORS_VECTOR,
	NodeType_ValueEntity = OW_COLORS_ENTITY,
	NodeType_Function = OW_COLORS_FUNCTION,
};

class Node : public GraphElement<NodeType>
{
protected:
	PinList m_inputPins;
	PinList m_outputPins;

public:
	Node(NodeType type, const char* title = NULL, const char* description = NULL) : base(type, title, description)
	{

	}

	Pin* AddInputPin(PinType type, const char* title = NULL, const char* description = NULL) {
		Pin* pin = new Pin(PinKind_In, type, title, description);
		this->m_inputPins.push_back(pin);
		return pin;
	}

	Pin* AddOutputPin(PinType type, const char* title = NULL, const char* description = NULL) {
		Pin* pin = new Pin(PinKind_Out, type, title, description);
		this->m_outputPins.push_back(pin);
		return pin;
	}

	void Render() override;
};

typedef std::vector<Node*> NodeList;

#endif 