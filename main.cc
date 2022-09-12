#include "stdafx.h"

#include <Windows.h>
#include <iostream>

BOOL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
		std::cerr << "Cannot initialize SDL framework!" << std::endl;
		return 1;
	}

	atexit(SDL_Quit);

	ImVec2 defaultWindowSize = { 840, 580 };

	SDL_Window* window = SDL_CreateWindow("Workshop.App",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		static_cast<int>(defaultWindowSize.x),
		static_cast<int>(defaultWindowSize.y),
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_Renderer* render = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_ShowWindow(window);

	ImGui::CreateContext();
	ImNodes::CreateContext();

	auto& io = ImGui::GetIO();
	io.DisplaySize = defaultWindowSize;

	ImGui::StyleColorsDark();
	ImNodes::StyleColorsDark();
	// ----------------------------------------------------------------


	NodeList nodes;

	auto* entry = new FunctionCallNode_Impl(eFCNF_FlowEnd, "Rule Start");
	nodes.push_back(entry);


	auto* conditions = new Node(NodeType_Function, "Rule Conditions");
	conditions->AddInputPin(PinType_Flow);
	conditions->AddInputPin(PinType_Boolean, "Result");
	nodes.push_back(conditions);

	auto* node = new FunctionCallNode_Impl(eFCNF_FlowBoth, "Start Forcing Player To Be Hero");
	node->AddInputPin(PinType_Entity, "Player");

	auto p1 = entry->GetPinByIndex(PinKind_Out, 0);
	auto p2 = node->GetPinByIndex(PinKind_In, 0);
	static bool doLink = true;

	auto* hero = new EnumPin_Impl(PinKind_In, "Hero", NULL);
	{
		const char* s_heroes =
		{
			"ANA\0"
			"ASHE\0"
			"BAPTISTE\0"
			"BASTION\0"
			"BRIGITTE\0"
			"DOOMFIST\0"
			"DVA\0"
			"ECHO\0"
			"GENJI\0"
			"WRECKING BALL\0"
			"HANZO\0"
			"JUNKRAT\0"
			"LUCIO\0"
			"MCCREE\0"
			"MEI\0"
			"MERCY\0"
			"MOIRA\0"
			"ORISA\0"
			"PHARAH\0"
			"REAPER\0"
			"REINHARDT\0"
			"ROADHOG\0"
			"SIGMA\0"
			"SOLDIER: 76\0"
			"SOMBRA\0"
			"SYMMETRA\0"
			"TORBJORN\0"
			"TRACER\0"
			"WIDOWMAKER\0"
			"WINSTON\0"
			"ZARYA\0"
			"ZENYATTA\0"
		};

		hero->SetOptions(s_heroes);
	}

	node->AddInputPin(hero);
	nodes.push_back(node);

	nodes.push_back(new VectorNode_Impl());
	nodes.push_back(new VectorNode_Impl());

	// ----------------------------------------------------------------
	ImGui_ImplSDL2_InitForSDLRenderer(window, render);
	ImGui_ImplSDLRenderer_Init(render);

	static bool update = true;

	while (update) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				update = false;

			else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					io.DisplaySize.x = static_cast<float>(event.window.data1);
					io.DisplaySize.y = static_cast<float>(event.window.data2);
				}
			}

			ImGui_ImplSDL2_ProcessEvent(&event);
		}

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		// ----------------------------------------------------------------

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(io.DisplaySize);
		ImGui::Begin("#", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		{
			ImNodes::BeginNodeEditor();

			for (auto node : nodes) {
				node->Render();
			}

			static bool linked = true;

			if (linked) {
				ImNodes::Link(1234, p1->GetId(), p2->GetId());
			}

			if (ImGui::IsKeyPressed(ImGuiKey_ModCtrl)) {
				linked = !linked;
			}

			ImNodes::MiniMap(0.15f, ImNodesMiniMapLocation_TopRight);
			ImNodes::EndNodeEditor();
		}
		ImGui::End();

		// ----------------------------------------------------------------
		ImGui::Render();
		SDL_SetRenderDrawColor(render, 25, 25, 25, 255);
		SDL_RenderClear(render);
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(render);
	}

	return 0;
}