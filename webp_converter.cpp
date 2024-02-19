//#pragma execution_character_set("utf-8")

#include "webp_converter.h"
#include "imgui.h"
#include "tinyfiledialogs.h"
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <string>
#include <iostream>

namespace webp_converter {
    static char path_final[1024] = u8"";
    char *path_temp = new char[1024];
    static int format = 0;
    static bool nesting = false;
    static bool webp_delete = false;
    static ImGuiWindowFlags window_flags = 0;

    /*
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_MenuBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    window_flags |= WindowFlags_NoBackground;
    window_flags |= WindowFlags_NoBringToFrontOnFocus;
    window_flags |= WindowFlags_NoDocking;
    window_flags |= WindowFlags_UnsavedDocument;
    */

    void RenderUI() {
        // could probably move these outside the loop and pass through RenderUI function, if more efficiency is needed
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoMove;

        // Command needs to be within the loop to work properly
        std::string sys_command = u8"";

        ImGui::Begin("My Window", NULL, window_flags);

        //ImGui::SetWindowSize(io.DisplaySize());
        ImGui::SetWindowFontScale(1.4);

        //std::cout<<"Window size : "<<ImGui::GetWindowSize().x<<" "<<ImGui::GetWindowSize().y;

        ImGui::Text("Select a folder to convert all the .webp files stored inside it -");
        // Text Box
        ImGui::InputText("",path_final, 1024);
        ImGui::SameLine();
        // Select Folder for conversion
        if(ImGui::Button("Browse")){
            path_temp = tinyfd_selectFolderDialog("Select","");
            if(path_temp != NULL) std::strcpy(path_final,path_temp);
        }
        ImGui::Checkbox("Convert files in subfolders", &nesting);
        ImGui::SameLine(0,50);
        ImGui::RadioButton("png", &format, 0);
        ImGui::SameLine();
        ImGui::RadioButton("jpg", &format, 1);
        ImGui::Checkbox("Delete .webp files afterwards?", &webp_delete);
        //ImGui::SameLine(200);
        ImGui::Indent(ImGui::GetWindowWidth()*2/3); // janky alignment, but only 1 button so eh

        // Convert using bash script
        /*if(ImGui::Button("Convert")){
            sys_command += "./convert.sh -f \"";
            sys_command += path_final;
            sys_command += "\"";
            sys_command += (format == 1) ? " -t jpg":" -t png";
            sys_command += nesting? " -n":"";
            sys_command += webp_delete? " -d":"";
            std::cout<<sys_command<<"\n";
            std::system(sys_command.c_str());
        }*/
        // Convert using python
        if(ImGui::Button("Convert")){
            sys_command += "python3 convert.py -f \"";
            sys_command += path_final;
            sys_command += "\"";
            sys_command += (format == 1) ? " -t jpg":" -t png";
            sys_command += nesting? " -n":"";
            sys_command += webp_delete? " -d":"";
            std::cout<<sys_command<<"\n";
            std::system(sys_command.c_str());
        }
        ImGui::End();

        // ImGui::ShowDemoWindow(); // in case you need to reference anything
    }
}
// TODO : Single Window