#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup()
{
    tempoSensor = new TempoSensor ();
    
    //ofSetLogLevel(OF_LOG_ERROR/*OF_LOG_VERBOSE*/);
    
    gui.setupFlexBoxLayout();
    all = gui.addGroup("all", ofJson({
        {"position", "static"},
        {"show-header", false},
        {"background-color" , "transparent"}
    }));
    ofxGuiTabs* tabbed_pages = all->addTabs("tabbedpages", ofJson({{"flex", 1}}));

    ofxGuiGroup* configTab = tabbed_pages->addGroup("Base", ofJson({
        {"flex-direction", "row"},
        {"flex-wrap", "nowrap"},
        {"background-color" , "transparent"}
    }));
    
    ofxGuiGroup * resolutionGroup = configTab->addGroup("Resolution : ", ofJson({
        {"show-header", false},
        {"background-color" , "transparent"}
    }));
    resolutionGroup->addLabel("Resolution : ");
    resolutionGroup->add<ofxGuiIntInputField>(res_width.set("Width",800,10,1920));
    res_width.addListener(this, &ofApp::resolutionWidthChanged);
    resolutionGroup->add<ofxGuiIntInputField>(res_height.set("Height",600,10,1200));
    res_height.addListener(this, &ofApp::resolutionHeightChanged);

    ofxGuiGroup * createGroup = configTab->addGroup("New : ", ofJson({
        {"show-header", false},
        {"background-color" , "transparent"}
    }));
    createGroup->addLabel(" New : ");
    createGroup->add<ofxGuiButton>("Output", ofJson({
        {"type", "fullsize"},
        {"text-align", "center"}
    }))
    ->addListener(this, &ofApp::createOutputWindow);
    
    
    ofxGuiGroup* controlsWrapper = tabbed_pages->addGroup("Oscillators", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));

    ofxGuiGroup* oscillatorsTab = controlsWrapper->addGroup("Oscillators", ofJson({
        {"flex-direction", "row"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    
    ofxGuiGroup* oscillatorsLFO = oscillatorsTab->addGroup("LFOs", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    oscillatorsLFO->add<ofxGuiButton>("New Oscillator", ofJson({
        {"type", "fullsize"},
        {"text-align", "center"}
    }))->addListener(this, &ofApp::createOscillatorMixer);
    
    oscillatorGroup = oscillatorsTab->addGroup("Oscillators : ", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    fbo.allocate(res_width, res_height);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();
    

    for(unsigned i = 0 ; i < BASE_OSC ; i ++){
        createOscillator();
    }
    
    ofxGuiGroup* lfosTab = controlsWrapper->addGroup("LFOs", ofJson({
        {"flex-direction", "row"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    
    
    
    ofxGuiGroup* wrapper = lfosTab->addGroup("LFOs : ", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    
    ofxGuiGroup*  lfoscontrolerGroup = wrapper->addGroup("LFOs : ", ofJson({
        {"show-header", false},
        {"flex-direction", "row"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    
    lfosGroup = wrapper->addGroup("LFOs : ", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    ofxGuiGroup*  bpmGroup  = lfoscontrolerGroup->addGroup("BPM : ", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    
    bpmGroup->add<ofxGuiIntInputField>(BPM.set("BPM",60,0,1000))->setWidth(100);
    bpmGroup->add<ofxGuiIntInputField>(tapBPM.set("tapBPM", 0,0,1000))->setWidth(100);
    bpmGroup->add<ofxGuiButton>("Sync", ofJson({
        {"type", "fullsize"},
        {"text-align", "center"}
    }))
    ->addListener(this, &ofApp::tapBPMToBPM);
    
    
    ofxGuiGroup*  playStopGroup  = lfoscontrolerGroup->addGroup("play/stop : ", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    playPause = playStopGroup->add<ofxGuiButton>("Pause", ofJson({
        {"type", "fullsize"},
        {"text-align", "center"}
    }));
    playPause->addListener(this, &ofApp::playPauseLFOS);
    
    
    for(unsigned i = 0 ; i < 6 ; i ++){
        createLfo();
    }
    
    
    
    mixerGroup = lfosTab->addGroup("Mixer : ", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    
    preMixer = new Mixer(mixerGroup, BASE_OSC, &msc, ofPoint(fbo.getWidth(),fbo.getHeight()));
}

//--------------------------------------------------------------
void ofApp::update()
{
    tapBPM = round(tempoSensor->tempo);
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    for(int i = 0 ; i < lfos.size() && !playPauseFlag; i ++)
    {
        lfos.at(i)->update();
    }
    
    if(oscillators.size()>0)
    {
        vector <ofTexture *> oscOut;
        int latActive;
        for(int i = 0 ; i < oscillators.size() ; i ++)
        {
            ofFbo * modifier = &preMixer->fbo;
            if(i >= 1){
                modifier = oscillators.at(i-1)->getModifier();
            }
            ofTexture * tmp = oscillators.at(i)->draw(modifier);
            oscOut.push_back(tmp) ;
        }
        preMixer->setPreview(oscOut);
        preMixer->update();
    }
    ;
    fbo.begin();
    preMixer->mainOut.draw(0, 0, fbo.getWidth(), fbo.getHeight());
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0, 0, mainWindow->getWidth(), mainWindow->getHeight());
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if(key == 'h')
    {
        all->setHidden(!all->isHidden());
    }
}

//--------------------------------------------------------------
void ofApp::exit()
{
    delete tempoSensor;
    tempoSensor = NULL;
}

