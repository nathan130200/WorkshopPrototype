#include "shared.h"

using namespace ImNodes;

void Pin::Render()
{
	PushColorStyle(ImNodesCol_Pin, m_type);
	PushColorStyle(ImNodesCol_PinHovered, m_type);
	PushColorStyle(ImNodesCol_Link, m_type);
	PushColorStyle(ImNodesCol_LinkHovered, m_type);
	PushColorStyle(ImNodesCol_LinkSelected, m_type);

	if (m_kind == PinKind_In)
		BeginInputAttribute(m_id, m_shape);
	else if (m_kind == PinKind_Out)
		BeginOutputAttribute(m_id, m_shape);

	ImGui::BeginGroup();

	ImGui::Text(m_title.c_str());

	if (!m_connected) {
		ImGui::PushItemWidth(120.f);

		if (m_type == PinType_Number)
			//ImGui::InputFloat("", &state.f, 0.1, 0.5);
		{
			ImGui::SameLine();
			ImGui::DragFloat("##", &state.f, 0.5, -9999.f, 9999.f, "%.3f", 1.f);
		}
		else if (m_type == PinType_Boolean)
			ImGui::Checkbox("##", &state.b);
		else if (m_type == PinType_Enum)
			ImGui::Combo("##", &state.enum_index, enumValues, -1);

		ImGui::PopItemWidth();
	}

	ImGui::EndGroup();

	if (ImGui::IsItemHovered() && m_description.size() > 0) {
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(m_description.c_str());
		ImGui::EndTooltip();
	}

	if (m_kind == PinKind_In)
		EndInputAttribute();
	else if (m_kind == PinKind_Out)
		EndOutputAttribute();

	PopColorStyle();
	PopColorStyle();
	PopColorStyle();
	PopColorStyle();
	PopColorStyle();
}

void Node::Render()
{
	PushColorStyle(ImNodesCol_TitleBar, m_type);
	PushColorStyle(ImNodesCol_TitleBarHovered, m_type);
	PushColorStyle(ImNodesCol_TitleBarSelected, m_type);
	PushStyleVar(ImNodesStyleVar_NodeCornerRounding, 4.f);

	BeginNode(m_id);
	{
		if (ImGui::IsItemHovered() && m_description.size() > 0) {
			ImGui::BeginTooltip();
			ImGui::TextWrapped("%s", m_description.c_str());
			ImGui::EndTooltip();
		}

		BeginNodeTitleBar();

		if (m_title.size() > 0)
			ImGui::TextUnformatted(m_title.c_str());

		EndNodeTitleBar();

		ImGui::BeginGroup();
		{
			for (auto pin : this->m_inputPins) {
				pin->Render();
			}
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		{
			for (auto pin : this->m_outputPins) {
				pin->Render();
			}
		}
		ImGui::EndGroup();
	}
	EndNode();

	PopStyleVar();
	PopColorStyle();
	PopColorStyle();
	PopColorStyle();
}