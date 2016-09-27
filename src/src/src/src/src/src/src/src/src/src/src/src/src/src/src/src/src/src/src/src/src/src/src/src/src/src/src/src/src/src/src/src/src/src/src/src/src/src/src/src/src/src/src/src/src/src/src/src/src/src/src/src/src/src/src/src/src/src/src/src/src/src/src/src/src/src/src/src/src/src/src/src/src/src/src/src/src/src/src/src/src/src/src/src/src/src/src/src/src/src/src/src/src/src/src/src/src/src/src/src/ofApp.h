#pragma once


#include "ofMain.h"
#include "LFO/LFO.hpp"
#include "Mixer.hpp"
#include "Oscillator.hpp"
#include "outputWindow.hpp"
#include "ofxGuiExtended.h"
#include "TempoSensor.hpp"
#include "ofxMasterSlaveControl.h"

#define BASE_OSC 5

class ofApp : public ofBaseApp{
    ofxGui gui;
    ofxGuiGroup * all;
    ofxGuiGroup * oscillatorGroup;
    ofxGuiGroup * lfosGroup;
    ofxGuiGroup *  mixerGroup;
    ofxMasterSlaveControl msc;
    ofParameter<int> res_width, res_height;
    ofParameter<int> BPM;
    ofParameter<int> tapBPM;
        ofParameter<float> trail;
    ofFbo fbo;
    TempoSensor * tempoSensor;
    
    ofxGuiButton * playPause;
    bool playPauseFlag = false;
    shared_ptr<ofApp> mainApp;
    shared_ptr<ofAppBaseWindow> mainWindow;
    
    vector <Oscillator *> oscillators;
    vector <LFO *> lfos;
    
    
    Mixer * preMixer;
    Mixer * postPixer;
    void tapBPMToBPM(){
        BPM = tapBPM;
    }
    void playPauseLFOS(){
        playPauseFlag = !playPauseFlag;
        if(playPauseFlag){
            playPause->setName("PLay");
        }
        else{
            playPause->setName("Pause");
        }
    }
    void resolutionWidthChanged(int &value)
    {
        fbo.allocate(value, fbo.getHeight());
        for(Oscillator * osc : oscillators){
            osc->setWidth(value);
        }
    }
    void resolutionHeightChanged(int &value)
    {
        fbo.allocate(fbo.getWidth(), value);
        for(Oscillator * osc : oscillators){
            osc->setHeight(value);
        }
    }
    
    void createOutputWindow()
    {
        shared_ptr<OutputWindow> outputWindowApp_ptr(new OutputWindow);
        outputWindowApp_ptr->init(mainWindow, &preMixer->mainOut);
        ofRunApp(outputWindowApp_ptr->window_ptr, outputWindowApp_ptr);
        outputWindowApp_ptr = NULL;
    }
    void createOscillatorMixer(){
        createOscillator();
        preMixer->addChannel();
    }
    void createOscillator(){
        oscillators.push_back(new Oscillator(oscillatorGroup, ofPoint(fbo.getWidth(),fbo.getHeight()), &msc));
    }
    void createLfo(){
        lfos.push_back(new LFO(lfosGroup, &msc, &BPM));
    }
	public:
        void setMainAppWindows(shared_ptr<ofApp> app, shared_ptr<ofAppBaseWindow> window){
            mainApp = app;
            mainWindow = window;
        };

		void setup();
		void update();
		void draw();
		void keyReleased(int key);
		void exit();
};
