#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(255);
	ofFill();
	
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 160, true, true, true);

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofClear(0);
	ofSetColor(0);

	auto word = "Noise";
	this->font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) - 250);

	fbo.end();
	auto span = 10;
	ofPixels pixels;
	fbo.readToPixels(pixels);
	for (int x = 0; x < 700; x += span) {

		for (int y = 0; y < 720; y += span) {

			ofColor color = pixels.getColor(x, y);
			if (color != ofColor(0, 0)) {

				this->font_location_list.push_back(glm::vec3(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.25, 0));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->font_location_list.size(); i++) {

		auto size = ofMap(ofNoise(this->font_location_list[i].x * 0.01, this->font_location_list[i].y * 0.01 + ofGetFrameNum() * 0.025), 0, 1, 1, 5);
		ofDrawCircle(this->font_location_list[i], size);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}