#include "shared.h"

#ifndef _IMPL_H_
#define _IMPL_H_

class NumberPin_Impl : public Pin {
protected:
	float* m_value;

public:
	NumberPin_Impl(PinKind kind, const char* title, const char* desc, float* dest = NULL) :
		Pin(kind, PinType_Number, title, desc)
	{
		if (dest)
			m_value = dest;
		else
			m_value = new float(0.f);
	}

	void Render();
};

class VectorNode_Impl : public Node {
protected:
	float m_x, m_y, m_z;

public:
	VectorNode_Impl() :
		Node(NodeType_ValueVector, "Vector"),
		m_x(0),
		m_y(0),
		m_z(0)
	{
		AddInputPin(new NumberPin_Impl(PinKind_In, "X", "X Component of vector", &m_x));
		AddInputPin(new NumberPin_Impl(PinKind_In, "Y", "Y Component of vector", &m_y));
		AddInputPin(new NumberPin_Impl(PinKind_In, "Z", "Z Component of vector", &m_z));
		AddOutputPin(PinType_Vector, "Result");
	}

	void Render() override;
};

enum FunctionCallNodeFlags {
	eFCNF_None = 0,
	eFCNF_FlowStart = 1 << 1,
	eFCNF_FlowEnd = 1 << 2,
	eFCNF_FlowBoth = eFCNF_FlowStart | eFCNF_FlowEnd
};

class FunctionCallNode_Impl : public Node {
protected:
	FunctionCallNodeFlags m_flags;

public:
	FunctionCallNode_Impl(FunctionCallNodeFlags flags, const char* name, const char* desc = NULL) :
		Node(NodeType_Function, name, desc),
		m_flags(flags)
	{
		if (m_flags & eFCNF_FlowStart)
			this->AddInputPin(PinType_Flow);

		if (m_flags & eFCNF_FlowEnd)
			this->AddOutputPin(PinType_Flow);
	}
};

class EnumPin_Impl : public Pin {
protected:
	int32_t m_index;
	const char* m_values;
	float m_width;

public:
	EnumPin_Impl(PinKind kind, const char* title, const char* desc) :
		Pin(kind, PinType_Enum, title, desc),
		m_index(0),
		m_width(-1.f)
	{
		m_values = "Item 1\0Item 2";
	}

	void SetOptions(const char* options);
	void SetWidth(const float width);

	void Render();
};

#endif 