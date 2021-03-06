#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,2);
    settings.setPosition(ofVec2f(0,0));
    settings.width = 1920;
    settings.height = 1200;
    settings.title = "mainWindow";
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setMainAppWindows(mainApp, mainWindow);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
