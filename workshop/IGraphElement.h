#include <string>

#ifndef _GRAPHELEMENT_H_
#define _GRAPHELEMENT_H_

class Graph;

static volatile int32_t hardcoded_id;

template<typename T>
class GraphElement {
protected:
	T m_type;
	std::string m_title;
	std::string m_description;
	int32_t m_id;
	volatile bool m_initialized;

	using base = GraphElement;

	GraphElement(T type, const char* title = NULL, const char* description = NULL) :
		m_type(type),
		m_id(hardcoded_id++),
		m_initialized(false)
	{
		if (title)
			m_title = title;

		if (description)
			m_description = description;
	}

	~GraphElement() = default;

	virtual void PreInit(Graph* g)
	{

	}

	virtual void PostInit(Graph* g)
	{

	}

	virtual void Render() = 0;
};

#endif