#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "misc/cpp/imgui_stdlib.h"
#include <stdio.h>
#include <SDL.h>

#include "Game.hpp"
#include "Schedule.hpp"
#include "Leauge.hpp"

#include <vector>
#include <string>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

using namespace daniel;
int main(int, char**)
{
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

    // Setup SDL_Renderer instance
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return false;
    }
    //SDL_RendererInfo info;
    //SDL_GetRendererInfo(renderer, &info);
    //SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);


    // Our state
    bool show_first_window = true;
    bool show_second_window = false;

    bool showWinsByWL = true;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //My data
    std::vector<std::string> team_names;
    std::vector<float> team_skills;
    TeamRefGroup teams;
    Leauge* l;

    team_names.emplace_back("Golden State Warrior");
    team_names.emplace_back("Boston Celtics");
    team_names.emplace_back("Brooklyn Nets");
    team_names.emplace_back("Denver Nuggets");
    team_names.emplace_back("Philadelphia 76ers");
    team_names.emplace_back("Minnesota Timberwolves");
    team_names.emplace_back("Chicago Bulls");
    team_names.emplace_back("Portland Trail Blazers");
    team_names.emplace_back("LA Clippers");
    team_names.emplace_back("Los Angeles Laker");
    team_names.emplace_back("Milwaukee Bucks");
    team_names.emplace_back("Atlanta Hawks");
    team_names.emplace_back("Charlotte Hornets");
    team_names.emplace_back("Miami Heat");
    team_names.emplace_back("Phoenix Suns");
    team_names.emplace_back("Dallas Mavericks");
    team_names.emplace_back("Memphis Grizzlies");
    team_names.emplace_back("Utah Jazz");
    team_names.emplace_back("Washington Wizard");
    team_names.emplace_back("Oklahoma City Thunder");

    team_skills.emplace_back( 1);
    team_skills.emplace_back( 0.4);
    team_skills.emplace_back( 0.5);
    team_skills.emplace_back( 0.3);
    team_skills.emplace_back( 0.4);
    team_skills.emplace_back( 0.5);
    team_skills.emplace_back( 0.3);
    team_skills.emplace_back( 0.2);
    team_skills.emplace_back( 0.5);
    team_skills.emplace_back( 1);
    team_skills.emplace_back( 0.7);
    team_skills.emplace_back( 0.3);
    team_skills.emplace_back( 0.2);
    team_skills.emplace_back( 0.6);
    team_skills.emplace_back( 0.8);
    team_skills.emplace_back( 0.6);
    team_skills.emplace_back( 0.5);
    team_skills.emplace_back( 0.3);
    team_skills.emplace_back( 0);
    team_skills.emplace_back( 0.1);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_first_window)
        {
            for(int i = 0; i < 20 ; i++){
                ImGui::PushItemWidth(200);
                std::string title = "##name" + std::to_string(i);
                ImGui::InputText(title.c_str(),&team_names.at(i));
                ImGui::SameLine();
                title = "##hidden skill" + std::to_string(i);
                ImGui::SliderFloat(title.c_str(),(float *)&team_skills.at(i), 0.0f, 1.0f);
                ImGui::PopItemWidth();
            }
            if(ImGui::Button("Next"))
            {
                show_first_window = false;
                for (size_t i = 0; i < 20; i++)
                {
                    teams.push_back(std::make_shared<Team>(team_names.at(i),team_skills.at(i)));
                }
                
                l = new Leauge(teams);
                l->simulateSeason();
                show_second_window = true;
                l->printTopTeamsByWLR();
            }
        }
        

        if(show_second_window){
            if(showWinsByWL)
            {
                if(ImGui::Button("show by score diff"))
                {
                    showWinsByWL = false;
                }
                auto teamsOrder = l->getTopTeamsByWLR();
                for(auto& team : teamsOrder){
                    ImGui::Text(team->getName().c_str());
                    ImGui::SameLine();
                    std::string wl = std::to_string(team->getStats().wins) + " - " + std::to_string(team->getStats().losses);
                    ImGui::Text(wl.c_str());
                }
            }
            else
            {
                if(ImGui::Button("show by W/L ratio"))
                {
                    showWinsByWL = true;
                }
                auto teamsOrder = l->getTopTeamsByPR();
                for(auto& team : teamsOrder){
                    ImGui::Text(team->getName().c_str());
                    ImGui::SameLine();
                    std::string wl = std::to_string(team->getStats().pointsDiff);
                    ImGui::Text(wl.c_str());
                }
            }
            
            ImGui::Begin("stats");
            ImGui::Text("Longest win streak is:%d",l->getTeamWithLongestWinStreak());
            ImGui::Text("Longest loss streak is:%d",l->getTeamWithLongestLossStreak());
            ImGui::Text("More teams score more the been scorred:%d",l->getNumOfTeamWithPositiveScoreRatio());
            ImGui::Text("Highest score in a game:%d",l->getHighestMaxPts());
            ImGui::Text("Highest avg point score:%f",l->getHighestAvgPts());

            ImGui::End();
        }


        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}