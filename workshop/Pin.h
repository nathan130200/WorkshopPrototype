#include "shared.h"

#ifndef _PIN_H_
#define _PIN_H_

enum PinType : unsigned {
	PinType_Flow = OW_COLORS_FLOW,
	PinType_Any = OW_COLORS_ANY,
	PinType_Boolean = OW_COLORS_BOOLEAN,
	PinType_Vector = OW_COLORS_VECTOR,
	PinType_Number = OW_COLORS_NUMBER,
	PinType_Entity = OW_COLORS_ENTITY,
	PinType_Enum = OW_COLORS_ENUM
};

enum PinKind {
	PinKind_In,
	PinKind_Out
};

class Pin : public GraphElement<PinType>
{
protected:
	PinKind m_kind;
	ImNodesPinShape m_shape;
	bool m_connected;

	struct {
		float f = 0;
		int32_t i = 0;
		bool b = false;
		float v[3] = { 0,0,0 };
		int enum_index = 0;
	} state;

	const char* enumValues;

public:
	Pin(PinKind kind, PinType type, const char* title, const char* description = NULL) : base(type, title, description)
	{
		m_kind = kind;

		if (type == PinType_Flow)
			m_shape = ImNodesPinShape_TriangleFilled;
		else
			m_shape = ImNodesPinShape_QuadFilled;

		m_connected = false;
	}

	void SetEnumValues(const char* values) {
		enumValues = values;
	}

	void Render() override;
};

typedef std::vector<Pin*> PinList;

#endif