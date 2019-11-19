#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face_mesh_list.clear();
	this->frame_mesh_list.clear();

	auto width = 15;
	for (auto x = -250; x <= 250; x += width * 2) {

		ofMesh face_mesh, frame_mesh;
		frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
		for (auto y = -200; y < 200; y += 1) {

			int index = face_mesh.getVertices().size();
			auto z_1 = ofMap(ofNoise(x * 0.015, y * 0.003 + ofGetFrameNum() * 0.005), 0, 1, -50, 50);
			auto z_2 = ofMap(ofNoise(x * 0.015, (y + 1) * 0.003 + ofGetFrameNum() * 0.005), 0, 1, -50, 50);

			face_mesh.addVertex(glm::vec3(x - width * 0.5, y, z_1));
			face_mesh.addVertex(glm::vec3(x + width * 0.5, y, z_1));
			face_mesh.addVertex(glm::vec3(x + width * 0.5, y + 1, z_2));
			face_mesh.addVertex(glm::vec3(x - width * 0.5, y + 1, z_2));

			face_mesh.addIndex(index + 0); face_mesh.addIndex(index + 1); face_mesh.addIndex(index + 2);
			face_mesh.addIndex(index + 0); face_mesh.addIndex(index + 2); face_mesh.addIndex(index + 3);

			frame_mesh.addVertex(glm::vec3(x - width * 0.5, y, z_1));
			frame_mesh.addVertex(glm::vec3(x + width * 0.5, y, z_1));
			frame_mesh.addVertex(glm::vec3(x + width * 0.5, y + 1, z_2));
			frame_mesh.addVertex(glm::vec3(x - width * 0.5, y + 1, z_2));

			frame_mesh.addIndex(index + 0); frame_mesh.addIndex(index + 3);
			frame_mesh.addIndex(index + 1); frame_mesh.addIndex(index + 2);
		}

		frame_mesh.addIndex(0); frame_mesh.addIndex(1);
		frame_mesh.addIndex(frame_mesh.getVertices().size() - 2); frame_mesh.addIndex(frame_mesh.getVertices().size() - 1);

		this->face_mesh_list.push_back(face_mesh);
		this->frame_mesh_list.push_back(frame_mesh);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	for (auto& face_mesh : this->face_mesh_list) {

		face_mesh.drawFaces();
	}

	ofSetColor(239);
	for (auto& frame_mesh : this->frame_mesh_list) {

		frame_mesh.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}