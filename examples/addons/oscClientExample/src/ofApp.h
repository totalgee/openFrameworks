#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define SERVER_HOST "localhost"
#define SERVER_PORT 12255

//--------------------------------------------------------
struct MessageInfo {
	void setText(string const& str, float duration = 1000.f){
		text = str;
		expiration = duration + ofGetElapsedTimef();
	}
	bool hasExpired() const{
		return ofGetElapsedTimef() > expiration;
	}

	string text;
	float expiration = 0;
};

//--------------------------------------------------------
class MessageLog {
	public:
		MessageLog()
		: currentString(0){}

		void update(){
			// hide old messages
			for(auto& message: messages){
				if(message.hasExpired()){
					message.setText("");
				}
			}
		}
		void draw(int x, int y){
			for(int i = 0; i < messages.size(); ++i){
				ofDrawBitmapString(messages[i].text, x, y + 15 * i);
			}
		}
		void append(string const& str, float inExpiration){
			messages.resize(std::max(currentString, kMaxSize));

			// add to the list of strings to display
			messages[currentString].setText(str, 5.0f);
			currentString = (currentString + 1) % kMaxSize;
			// clear the next line
			messages[currentString].setText("");
		}

	protected:
		int currentString;
		const int kMaxSize = 20;
		vector<MessageInfo> messages;
};

//--------------------------------------------------------
class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxOscSender sender;
		ofxOscReceiver receiver;
		int localPort;

		MessageLog log;
};
