#include "../platinumEyes.h"
#include <functional>
#include <imgui_stdlib.h>


void configParameter(std::string& s,int counter,const char* label) {

	std::string labelData(label);
	std::string labelText = labelData + ": ";
	ImGui::Text(labelText.c_str());
	ImGui::SameLine();

	std::string idNumber= std::to_string(counter);
	std::string id = "##label" + idNumber;
	
	ImGui::InputText(id.c_str(), &s);

	
}



struct rightPane {
	std::string description;
	std::function<void(ToolConfig&)> details;
};

void ocrServerSettings(std::string& s1, std::string& s2,std::string& s3) {

	
	configParameter(s1,1,"ocrIp");
	configParameter(s2,2,"ocrPort");
	configParameter(s3,3, "ocrType");
}


void screenshotSettings(std::string& s1, std::string& s2, std::string& s3, std::string& s4) {

	configParameter(s1, 4, "screenShotFilePath");
	configParameter(s2, 5, "coordinatesOfScreenShotCenter");
	configParameter(s3, 6, "screenShotWidth");
	configParameter(s4, 7, "screenShotHeight");



}

void windowSizesSettings(std::string& s1, std::string& s2) {

	configParameter(s1, 8, "sfmlSize");
	configParameter(s2, 9, "imguiSize");


}

void keybindingsSettings(std::string& s1, std::string& s2, std::string& s3, std::string& s4, std::string& s5, std::string& s6) {
	
	
	configParameter(s1, 10, "keyBind_ReadItemsFromScreen");
	configParameter(s2, 11, "keyBind_EscapeProgram");
	configParameter(s3, 12, "keyBind_ReadPreviousItems");
	configParameter(s4, 13, "keyBind_WindowVisibility");
	configParameter(s5, 14, "keyBind_BackupConfig");
	configParameter(s6, 15, "keyBind_ExampleItems");



}



struct settingsStructure{
	static const int length = 4;
	std::vector<std::string> leftPanes = {"Ocr server settings","Screenshot parameters","Window sizes","Keybindings"};
	std::pair < std::string, std::function<void(std::string& s1, std::string& s2,std::string& s3)>> ocrServer;
	std::pair < std::string, std::function<void(std::string& s1, std::string& s2, std::string& s3, std::string& s4)>> screenShotParameters;
	std::pair < std::string, std::function<void(std::string& s1, std::string& s2)>> windowSizes;
	std::pair < std::string, std::function<void(std::string& s1, std::string& s2, std::string& s3, std::string& s4, std::string& s5, std::string& s6)>> keyBindings;

};


void appendToSettingsStructure(int& should, settingsStructure& structure, AppState state) {

	if (should) {
		
		structure.ocrServer = 
			std::pair<std::string, std::function<void(std::string& s1, std::string& s2,std::string& s3)>>
			("Configure settings related to communication between the ocr server(main.py). "
			"For a normal user there is nothing to do here.",ocrServerSettings);
			


		structure.screenShotParameters=
			std::pair<std::string, std::function<void(std::string& s1, std::string& s2, std::string& s3, std::string& s4)>>
			( "Here u give the center of the screenshot, how wide and tall it should be."
			"U also include the path where u want to store the screenshot the app will be taking",screenshotSettings);


		structure.windowSizes=
			std::pair<std::string, std::function<void(std::string& s1, std::string& s2)>>
			( "Here u give how big the window size should be. Both the sfml(the one more to the back), and imgui (the one on top).",windowSizesSettings);


		structure.keyBindings=
			std::pair<std::string, std::function<void(std::string& s1, std::string& s2, std::string& s3, std::string& s4, std::string& s5, std::string& s6)>>
			( "Keybindings, every keybind is treated as 'Alt + <keybind>'\nIt's important to remember, that keybinds should be 1 character in length, except esc.",keybindingsSettings);

		should = 0;
		
	}
	else {
		return;
	}


}




void showSettingsMenu(bool* p_open,AppState state)
{
	static settingsStructure structure;
	static int should = 1;
	static ToolConfig newConfig = state.config;

	static const std::string  ocrTypeForRevert = newConfig["ocrType"];
	static const std::string  ocrIpForRevert = newConfig["ocrIp"];
	static const std::string  ocrPortForRevert = newConfig["ocrPort"];
	static const std::string  screenShotFilePathForRevert = newConfig["screenShotFilePath"];
	static const std::string  coordinatesOfScreenShotCenterForRevert = newConfig["coordinatesOfScreenShotCenter"];
	static const std::string  screenShotWidthForRevert = newConfig["screenShotWidth"];
	static const std::string  screenShotHeightForRevert = newConfig["screenShotHeight"];
	static const std::string  sfmlSizeForRevert = newConfig["sfmlSize"];
	static const std::string  imguiSizeForRevert = newConfig["imguiSize"];
	static const std::string  keyBind_ReadItemsFromScreenForRevert = newConfig["keyBind_ReadItemsFromScreen"];
	static const std::string  keyBind_EscapeProgramForRevert = newConfig["keyBind_EscapeProgram"];
	static const std::string  keyBind_ReadPreviousItemsForRevert = newConfig["keyBind_ReadPreviousItems"];
	static const std::string  keyBind_WindowVisibilityForRevert = newConfig["keyBind_WindowVisibility"];
	static const std::string  keyBind_BackupConfigForRevert = newConfig["keyBind_BackupConfig"];
	static const std::string  keyBind_ExampleItemsForRevert = newConfig["keyBind_ExampleItems"];





	static std::string  ocrType = newConfig["ocrType"];
	static std::string  ocrIp = newConfig["ocrIp"];
	static std::string  ocrPort=newConfig["ocrPort"];
	static std::string  screenShotFilePath=newConfig["screenShotFilePath"];
	static std::string  coordinatesOfScreenShotCenter=newConfig["coordinatesOfScreenShotCenter"];
	static std::string  screenShotWidth=newConfig["screenShotWidth"];
	static std::string  screenShotHeight=newConfig["screenShotHeight"];
	static std::string  sfmlSize=newConfig["sfmlSize"];
	static std::string  imguiSize=newConfig["imguiSize"];
	static std::string  keyBind_ReadItemsFromScreen = newConfig["keyBind_ReadItemsFromScreen"];
	static std::string  keyBind_EscapeProgram = newConfig["keyBind_EscapeProgram"];
	static std::string  keyBind_ReadPreviousItems = newConfig["keyBind_ReadPreviousItems"];
	static std::string  keyBind_WindowVisibility = newConfig["keyBind_WindowVisibility"];
	static std::string  keyBind_BackupConfig = newConfig["keyBind_BackupConfig"];
	static std::string  keyBind_ExampleItems = newConfig["keyBind_ExampleItems"];

	appendToSettingsStructure(should, structure, state);

	

	ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Settings", p_open, ImGuiWindowFlags_MenuBar))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Close", "Ctrl+W")) { *p_open = false; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		// Left
		static int selected = 0;
		{
			ImGui::BeginChild("left pane", ImVec2(150, 0), ImGuiChildFlags_Border);
			for (int i = 0; i < structure.length; i++)
			{
				char* label = structure.leftPanes[i].data();

				sprintf(label, label);
				if (ImGui::Selectable(label, selected == i))
					selected = i;
			}
			ImGui::EndChild();
		}
		ImGui::SameLine();

		// Right
		{
			ImGui::BeginGroup();
			ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
			ImGui::Text(structure.leftPanes[selected].data());
			ImGui::Separator();
			if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("Description"))
				{

					switch (selected) {
					case 0: ImGui::TextWrapped(structure.ocrServer.first.c_str()); break;
					case 1: ImGui::TextWrapped(structure.screenShotParameters.first.c_str()); break;
					case 2: ImGui::TextWrapped(structure.windowSizes.first.c_str()); break;
					case 3: ImGui::TextWrapped(structure.keyBindings.first.c_str()); break;
						
						
						//ImGui::TextWrapped(structure.rightPanes[selected].description.data());
					}

					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Details"))
				{
					switch (selected) {

					case 0: structure.ocrServer.second(ocrIp,ocrPort,ocrType); break;
					case 1: structure.screenShotParameters.second(screenShotFilePath, coordinatesOfScreenShotCenter, screenShotWidth, screenShotHeight); break;
					case 2: structure.windowSizes.second(sfmlSize, imguiSize); break;
					case 3: structure.keyBindings.second(keyBind_ReadItemsFromScreen, keyBind_EscapeProgram, keyBind_ReadPreviousItems, keyBind_WindowVisibility, keyBind_BackupConfig, keyBind_ExampleItems); break;


						//structure.rightPanes[selected].details(newConfig);

					}
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::EndChild();
			
			if (ImGui::Button("Revert")) {

				ocrType = ocrTypeForRevert;
				ocrIp = ocrIpForRevert;
				ocrPort = ocrPortForRevert;
				screenShotFilePath = screenShotFilePathForRevert;
				coordinatesOfScreenShotCenter = coordinatesOfScreenShotCenterForRevert;
				screenShotWidth = screenShotWidthForRevert;
				screenShotHeight = screenShotHeightForRevert;
				sfmlSize = sfmlSizeForRevert;
				imguiSize = imguiSizeForRevert;
				keyBind_ReadItemsFromScreen = keyBind_ReadItemsFromScreenForRevert;
				keyBind_EscapeProgram = keyBind_EscapeProgramForRevert;
				keyBind_ReadPreviousItems = keyBind_ReadPreviousItemsForRevert;
				keyBind_WindowVisibility = keyBind_WindowVisibilityForRevert;
				keyBind_BackupConfig = keyBind_BackupConfigForRevert;
				keyBind_ExampleItems = keyBind_ExampleItemsForRevert;

			}
			ImGui::SameLine();
			if (ImGui::Button("Save")) {
			
				newConfig.setPropertyValue("ocrType", ocrType);
				newConfig.setPropertyValue("ocrIp", ocrIp);
				newConfig.setPropertyValue("ocrPort", ocrPort);
				newConfig.setPropertyValue("screenShotFilePath", screenShotFilePath);
				newConfig.setPropertyValue("coordinatesOfScreenShotCenter", coordinatesOfScreenShotCenter);
				newConfig.setPropertyValue("screenShotWidth", screenShotWidth);
				newConfig.setPropertyValue("screenShotHeight", screenShotHeight);
				newConfig.setPropertyValue("sfmlSize", sfmlSize);
				newConfig.setPropertyValue("imguiSize", imguiSize);
				
				newConfig.setPropertyValue("keyBind_ReadItemsFromScreen", keyBind_ReadItemsFromScreen);
				newConfig.setPropertyValue("keyBind_EscapeProgram", keyBind_EscapeProgram);
				newConfig.setPropertyValue("keyBind_ReadPreviousItems", keyBind_ReadPreviousItems);
				newConfig.setPropertyValue("keyBind_WindowVisibility", keyBind_WindowVisibility);
				newConfig.setPropertyValue("keyBind_BackupConfig", keyBind_BackupConfig);
				newConfig.setPropertyValue("keyBind_ExampleItems", keyBind_ExampleItems);




				

				if (newConfig == state.config) {
					std::cout << "You haven't changed anything";
				}
				else {
					std::cout << "New configuration detected";

					state.config = newConfig;

					rewriteConfigFile(state.config);
					reRegisterHotkeys(state.config);

				}






			}
			ImGui::EndGroup();
		}
	}
	ImGui::End();
}
