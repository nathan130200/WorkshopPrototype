#include "impl.h"

void EnumPin_Impl::SetOptions(const char* values) {
	m_values = values;
}

void EnumPin_Impl::SetWidth(const float width) {
	m_width = width;
}

void EnumPin_Impl::Render()
{
	this->BeginRender();

	if (m_title.size() > 0) {
		ImGui::TextUnformatted(m_title.c_str());
	}

	if (!m_connected) {
		ImGui::SameLine();

		float width = m_width;

		if (width < 0.1f) {
			width = std::min(abs(ImNodes::GetNodeDimensions(m_parent->GetId()).x - 2.f), 256.f);
		}

		ImGui::SetNextItemWidth(width);
		ImGui::Combo("##", &m_index, m_values, -1);
	}

	this->EndRender();
}

void NumberPin_Impl::Render()
{
	this->BeginRender();

	if (m_title.size() > 0) {
		ImGui::TextUnformatted(m_title.c_str());
	}

	if (!m_connected) {
		ImGui::SameLine();
		ImGui::SetNextItemWidth(84.f);
		ImGui::DragFloat("##", m_value);
	}

	this->EndRender();
}

void VectorNode_Impl::Render()
{
	Node::Render();
}