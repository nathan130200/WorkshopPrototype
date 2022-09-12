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

	Pin* GetPinByIndex(PinKind kind, const size_t pos) {
		if (kind == PinKind_In)
			return m_inputPins.at(pos);
		else if (kind == PinKind_Out)
			return m_outputPins.at(pos);
		else
		{
			assert(!"Invalid pin kind provided");
			return NULL;
		}
	}

	void AddInputPin(Pin* pin) {
		this->m_inputPins.push_back(pin);
		pin->SetParent(this);
	}

	void AddOutputPin(Pin* pin) {
		this->m_outputPins.push_back(pin);
		pin->SetParent(this);
	}

	Pin* AddInputPin(PinType type, const char* title = NULL, const char* description = NULL) {
		Pin* pin = new Pin(PinKind_In, type, title, description);
		this->m_inputPins.push_back(pin);
		pin->SetParent(this);
		return pin;
	}

	Pin* AddOutputPin(PinType type, const char* title = NULL, const char* description = NULL) {
		Pin* pin = new Pin(PinKind_Out, type, title, description);
		this->m_outputPins.push_back(pin);
		pin->SetParent(this);
		return pin;
	}

	void Render() override;

protected:
	void BeginRender() override;
	void EndRender() override;
};

typedef std::vector<Node*> NodeList;

#endif 