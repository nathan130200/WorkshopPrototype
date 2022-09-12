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


	auto node = new Node(NodeType_ValueEntity, "Last Created Entity");
	node->AddOutputPin(PinType_Entity, "Self", "A reference to the last effect or icon entity created by the event player (or created at the global level).");

	NodeList nodes;
	nodes.push_back(node);

	auto node1 = new Node(NodeType_ValueVector, "Make Vector");
	node1->AddInputPin(PinType_Number, "X", "X component of vector.");
	node1->AddInputPin(PinType_Number, "Y", "Y component of vector.");
	node1->AddInputPin(PinType_Number, "Z", "Z component of vector.");
	node1->AddOutputPin(PinType_Vector, "Result");
	nodes.push_back(node1);

	auto node2 = new Node(NodeType_Function, "Teleport");
	node2->AddInputPin(PinType_Flow);
	node2->AddOutputPin(PinType_Flow);
	node2->AddInputPin(PinType_Any, "Player");
	node2->AddInputPin(PinType_Vector, "Position");
	nodes.push_back(node2);

	auto node3 = new Node(NodeType_Function, "Preload Hero");
	node3->AddInputPin(PinType_Flow);
	node3->AddOutputPin(PinType_Flow);

	node3->AddInputPin(PinType_Entity, "Player");
	auto* hero = node3->AddInputPin(PinType_Enum, "Hero");

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
		"LÚCIO\0"
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

	hero->SetEnumValues(s_heroes);

	nodes.push_back(node3);

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

			ImNodes::MiniMap();
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