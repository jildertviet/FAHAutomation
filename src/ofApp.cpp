#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(1);
    ofSetWindowShape(100, 100);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(smartMeter.isConnected()){
        string msg = smartMeter.receive();
        if( msg.length() > 0 ){
            vector<string> lines = ofSplitString(msg, "\n");
            for(int i=0; i<lines.size(); i++){
                if(ofStringTimesInString(lines[i], "Leveren:")){
                    overProduction = ofToInt(ofSplitString(lines[i], ":")[1]);
                    cout << overProduction << endl;
                }
            }
            if(overProduction > 500 && bRunning == false){
                turnFAHOn();
            }
            if(overProduction < 200 && bRunning == true){
                turnFAHOff();
            }
            ofSleepMillis(2000);
            smartMeter.close();
        }
    } else{
        ofSleepMillis(2000);
        ofxTCPSettings settings("192.168.178.35", 8888);
        smartMeter.setup(settings);
        smartMeter.setMessageDelimiter("m3\n\n"); // Changed the msg-style from ESP32 to a human readable version, these are the last char's
    }
}

void ofApp::turnFAHOn(){
    bRunning = true;
    cout << "Turn FAH on" << endl;
//    ofSystem("FAHClient --send-unpause 0");
    ofSystem("echo 'unpause 0' | telnet localhost 36330");
}

void ofApp::turnFAHOff(){
    bRunning = false; 
    cout << "Turn FAH off" << endl;
//    ofSystem("FAHClient --send-pause 0");
    ofSystem("echo 'pause 0' | telnet localhost 36330");
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
