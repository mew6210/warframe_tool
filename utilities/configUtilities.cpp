#include "../platinumEyes.h"




namespace screenShotParams{

    struct screenConfig {
        std::string screenShotWidth;
        std::string screenShotHeight;
        std::string centerCoordinates;
        std::string sfmlSize;
        std::string imguiSize;
    };

    screenConfig screen_1920x1080 = { "to_do","to_do","to_do","to_do","to_do" };
    screenConfig screen_3440x1440 = {"1290","90","1720,570","1200,300","1100,250"};
    screenConfig screen_NotSpecified= { "---","---","---","---","---" };





    #define SCR_Size_NotSpecified 0
    #define SCR_Size_1920x1080 1
    #define SCR_Size_3440x1440 2


    int getScreenResolution(int screenWidth, int screenHeight) {
        int screenResolution=SCR_Size_NotSpecified;

        if (screenWidth == 1920 && screenHeight == 1080) screenResolution = SCR_Size_1920x1080;
        if (screenWidth == 3440 && screenHeight == 1440) screenResolution = SCR_Size_3440x1440;


        return screenResolution;

    }

    std::string getCenterCoordinates(int screenResolution){
        switch (screenResolution) {
        case SCR_Size_1920x1080: return screen_1920x1080.centerCoordinates; break;
        case SCR_Size_3440x1440: return screen_3440x1440.centerCoordinates; break;



        case SCR_Size_NotSpecified:
        default:
            return screen_NotSpecified.centerCoordinates; break;


        }

    }

    std::string getWidth(int screenResolution){
    
        switch (screenResolution) {
        case SCR_Size_1920x1080: return screen_1920x1080.screenShotWidth; break;
        case SCR_Size_3440x1440: return screen_3440x1440.screenShotWidth; break;



        case SCR_Size_NotSpecified:
        default:
            return screen_NotSpecified.screenShotWidth; break;


        }
    
    
    }

    std::string getHeight(int screenResolution){
    
        switch (screenResolution) {
        case SCR_Size_1920x1080: return screen_1920x1080.screenShotHeight; break;
        case SCR_Size_3440x1440: return screen_3440x1440.screenShotHeight; break;



        case SCR_Size_NotSpecified:
        default:
            return screen_NotSpecified.screenShotHeight; break;


        }
    }

    std::string getSfmlSize(int screenResolution){
        switch (screenResolution) {
        case SCR_Size_1920x1080: return screen_1920x1080.sfmlSize; break;
        case SCR_Size_3440x1440: return screen_3440x1440.sfmlSize; break;



        case SCR_Size_NotSpecified:
        default:
            return screen_NotSpecified.sfmlSize; break;


        }
    
    
    
    }

    std::string getImGuiSize(int screenResolution){
    
        switch (screenResolution) {
        case SCR_Size_1920x1080: return screen_1920x1080.imguiSize; break;
        case SCR_Size_3440x1440: return screen_3440x1440.imguiSize; break;



        case SCR_Size_NotSpecified:
        default:
            return screen_NotSpecified.imguiSize; break;


        }
    
    
    
    }


}








bool checkIfConfigFileExists() {

    std::ifstream file;

    file.open(CONFIG_FILENAME);

    if (file) return true;
    else return false;



}

WindowParameters getWindowSize(std::string s,ToolConfig& toolConfig) {

    WindowParameters parameters;

    for (auto& c : s) {
        c = std::tolower(c);
    }
    if (s == "sfml") {

        std::pair<int, int> sfmlCoordinates = stringToIntPair(toolConfig["sfmlSize"]);
        parameters = WindowParameters(sfmlCoordinates.first, sfmlCoordinates.second);
    }
    else if (s == "imgui") {
        std::pair<int, int> imguiCoordinates = stringToIntPair(toolConfig["imguiSize"]);
        parameters = WindowParameters(imguiCoordinates.first, imguiCoordinates.second);

    }
    else {
        return parameters;
    }
    return parameters;


}


void createConfigFile() {

    std::ofstream configFile(CONFIG_FILENAME);

    HDC hScreen = GetDCEx(NULL, NULL, DCX_NORESETATTRS);
    int width = GetDeviceCaps(hScreen, HORZRES);
    int height = GetDeviceCaps(hScreen, VERTRES);
    int screenResolution = screenShotParams::getScreenResolution(width, height);

    for (std::string configProperty : CONFIGPROPERTIES) {

        configFile << configProperty << ": ";
        if (configProperty == "ocrIp") {
            configFile<<"127.0.0.1";
        }
        else if (configProperty == "ocrPort") {
            configFile << "5055";
        }
        else if (configProperty == "screenShotFilePath") {
            configFile << "screenshot.bmp";
        }
        else if (configProperty == "coordinatesOfScreenShotCenter") {
            configFile << screenShotParams::getCenterCoordinates(screenResolution);
        }
        else if (configProperty == "screenShotWidth") {
            configFile << screenShotParams::getWidth(screenResolution);
        }
        else if (configProperty == "screenShotHeight") {
            configFile << screenShotParams::getHeight(screenResolution);
        }
        else if (configProperty == "sfmlSize") {
            configFile << screenShotParams::getSfmlSize(screenResolution);
        }
        else if (configProperty == "imguiSize") {
            configFile << screenShotParams::getImGuiSize(screenResolution);
        }
        configFile << "\n";



    }

    configFile.close();
    DeleteDC(hScreen);

}


void resolveConfigLine(ToolConfig& toolConfig, std::string& line, int it) {

    int startingPoint = 0;


    startingPoint = CONFIGPROPERTIES[it].length() + 1;

    int whereEnds = line.find_last_of("\n");

    std::string configProperty = line.substr(startingPoint, whereEnds - 1);





    std::string key = CONFIGPROPERTIES[it];
    toolConfig.setPropertyValue(key, configProperty);




}


ToolConfig readConfigFile() {

    ToolConfig toolConfig = ToolConfig();


    std::ifstream configFile(CONFIG_FILENAME);
    std::string line;
    int it = 0;
    while (getline(configFile, line)) {
        resolveConfigLine(toolConfig, line, it);
        it += 1;
    }

    return toolConfig;


}


void copyConfigToOldFile() {

     std::ifstream fileCurrent(CONFIG_FILENAME);

     std::ofstream fileCopy(COPY_FILENAME);

     std::string line;
     while (std::getline(fileCurrent,line)) {

         fileCopy << line << "\n";

     }

}

void rewriteConfigFile(ToolConfig& config) {


    std::ofstream configFile(CONFIG_FILENAME);

    std::string line;


    for (auto& property : CONFIGPROPERTIES) {

        configFile << property <<": "<< config[property]<<"\n";


    }



}

