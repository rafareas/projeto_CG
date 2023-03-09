

#define _USE_MATH_DEFINES
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <regex>
#include <GL/glut.h>
#include "generator/Include/Shape.hpp"
#include "engine/include/tinyxml2.hpp"

using namespace tinyxml2;

using namespace std;


#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { cout << "Error: " << a_eResult << endl;  }
#endif



int windowsizex = 800;
int windowsizey = 800;

vector<Triangle> allTriangles;
float UPx  = 0.0, UPy = 1.0, UPz = 0.0;
float camX = 5.0;
float camY = 10.0;
float camZ = 5.0;
float camYaw = -0.8;
float camPitch = -1.7;
float camLookX = 0.0;
float camLookY = 0.0;
float camLookZ = 0.0;
char* filemodel;



void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set camera
	glLoadIdentity();
	float radius = 5.0 ;
	glLoadIdentity();
	
	gluLookAt(camX, camY, camZ,         // Camera position
		camLookX+ sin(camYaw), camLookY + sin(camPitch), camLookZ - cos(camYaw), // Look at point
		UPx, UPy, UPz);           // Up vector
	/*
	gluLookAt(camX, camY, camZ,         // Camera position
		camLookX,camLookY,camLookZ, // Look at point
		UPx, UPy, UPz);           // Up vector
*/

	// put axis drawing in here
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	// put drawing instructions here
	Triangle t;
	Point p1, p2, p3;

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < allTriangles.size(); i++){
		t = allTriangles[i];
		p1 = t.getp1();
		p2 = t.getp2();
		p3 = t.getp3();

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(p1.getx(), p1.gety(), p1.getz());
		glVertex3f(p2.getx(), p2.gety(), p2.getz());

		//glColor3f(1.0f, 1.0f, 1.0f);
		//glVertex3f(p2.getx(), p2.gety(), p2.getz());
		//glVertex3f(p3.getx(), p3.gety(), p3.getz());

		//glColor3f(1.0f, 2.0f, 3.0f);
		glVertex3f(p3.getx(), p3.gety(), p3.getz());
		//glVertex3f(p1.getx(), p1.gety(), p1.getz());
		
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// End of frame
	glutSwapBuffers();
}

void ReadFile(string shape)
{
	string line{};			  // line with 1 triangle
	string value;			  // the thing we wanna store
	string delimiter = ",";	  // delimiter between x , y , z
	string delimiter2 = "|";  // delimiter between points
	string delimiter3 = "\n"; // delimiter between triangles
	int pos;				  // position before the delimiter
	float xx, yy, zz;		  // Coordenates
	Triangle t;				  // Triangles to be saved
	Point p1, p2, p3;		  // Points of the readen triangles

	ifstream MyFile(shape);

	if (!MyFile)
		cout << "File not created!";
	else
	{
		while (getline(MyFile, line))
		{	
			// Point 1 of the triangle
			pos = line.find(delimiter);
			value = line.substr(0, pos);
			xx = atof(value.c_str());
			line.erase(0, pos + delimiter.length()); // erases x + ","  of the file

			pos = line.find(delimiter);
			value = line.substr(0, pos);
			yy = atof(value.c_str());
			line.erase(0, pos + delimiter.length()); // erases y + ","  of the file

			pos = line.find(delimiter2);
			value = line.substr(0, pos);
			zz = atof(value.c_str());
			line.erase(0, pos + delimiter2.length()); // erases z + "|"  of the file

			p1 = Point(xx, yy, zz);

			// Point 2 of the triangle
			pos = line.find(delimiter);
			value = line.substr(0, pos);
			xx = atof(value.c_str());
			line.erase(0, pos + delimiter.length()); // erases x + ","  of the file
			

			pos = line.find(delimiter);
			value = line.substr(0, pos);
			yy = atof(value.c_str());
			line.erase(0, pos + delimiter.length()); // erases y + ","  of the file
			

			pos = line.find(delimiter2);
			value = line.substr(0, pos);
			zz = atof(value.c_str());
			line.erase(0, pos + delimiter2.length()); // erases z + "|"  of the file
			
			p2 = Point(xx, yy, zz);

			// Point 3 of the triangle
			pos = line.find(delimiter);
			value = line.substr(0, pos);
			xx = atof(value.c_str());
			line.erase(0, pos + delimiter.length()); // erases x + ","  of the file
			

			pos = line.find(delimiter);
			value = line.substr(0, pos);
			yy = atof(value.c_str());
			line.erase(0, pos + delimiter.length()); // erases y + ","  of the file
			

			pos = line.find(delimiter3);
			value = line.substr(0, pos);
			zz = atof(value.c_str());
			line.erase(0, pos + delimiter3.length()); // erases z + "\n"  of the file
			
			p3 = Point(xx, yy, zz);

			// creating the triangle and saving it on the globale vector allTriangles
			t = Triangle(p1, p2, p3);
			allTriangles.push_back(t);
		}

		MyFile.close();
	}
}


void processKeys(unsigned char key, int xx , int yy) {

	float moveSpeed = 0.1;
	float rotateSpeed = 0.05;

	switch (key){
	case 'w': // Move camera forward
		camX += moveSpeed * sin(camYaw);
		camZ -= moveSpeed * cos(camYaw);
		break;
	case 's': // Move camera backward
		camX -= moveSpeed * sin(camYaw);
		camZ += moveSpeed * cos(camYaw);
		break;
	case 'd': // Move camera left
		camX += moveSpeed * sin(camYaw + 90 * (M_PI / 180.0));
		camZ -= moveSpeed * cos(camYaw + 90 * (M_PI / 180.0));
		break;
	case 'a': // Move camera right
		camX += moveSpeed * sin(camYaw - 90 * (M_PI / 180.0));
		camZ -= moveSpeed * cos(camYaw - 90 * (M_PI / 180.0));
		break;
	case 'e': // Rotate camera right
		camYaw += rotateSpeed;
		break;
	case 'q': // Rotate camera left
		camYaw -= rotateSpeed;
		break;
	case 'i': // Move camera up
		camY += moveSpeed;
		break;
	case 'k': // Move camera down
		camY -= moveSpeed;
		break;
	case 'u': // Look up
		camPitch += moveSpeed;
		break;
	case 'h': // look down
		camPitch -= moveSpeed;
		break;
	}
	glutPostRedisplay();

}


void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here
	float moveSpeed = 0.1;
	float rotateSpeed = 0.05;

	switch (key)
	{
	case GLUT_KEY_UP: // Move camera forward
		camX += moveSpeed * sin(camYaw);
		camZ -= moveSpeed * cos(camYaw);
		break;
	case GLUT_KEY_DOWN: // Move camera backward
		camX -= moveSpeed * sin(camYaw);
		camZ += moveSpeed * cos(camYaw);
		break;
	case GLUT_KEY_RIGHT: // Rotate camera right 
		camYaw += rotateSpeed;
		break;
	case GLUT_KEY_LEFT: // Rotate camera left
		camYaw -= rotateSpeed;
		break;
	}
}

void readxml(string path) {

	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile(path.c_str());
	XMLCheckResult(eResult);
	XMLNode* pRoot = xmlDoc.FirstChild();
	if (pRoot != nullptr) {

		XMLElement* window = pRoot->FirstChildElement("window");
		if (NULL != window) {
			window->QueryIntAttribute("width", &windowsizex);
			window->QueryIntAttribute("height", &windowsizey);
		}

		XMLElement* pCam = pRoot->FirstChildElement("camera");
		if (NULL != pCam) {

			XMLElement* pPos = pCam->FirstChildElement("position");
			if (NULL != pPos) {
				pPos->QueryFloatAttribute("x", &camX);
				pPos->QueryFloatAttribute("y", &camY);
				pPos->QueryFloatAttribute("z", &camZ);
			}

			XMLElement* pLookAt = pCam->FirstChildElement("lookAt");
			float xx = 0, yy = 0, zz = 0;
			if (NULL != pLookAt) {
				pLookAt->QueryFloatAttribute("x", &camLookX);
				pLookAt->QueryFloatAttribute("y", &camLookY);
				pLookAt->QueryFloatAttribute("z", &camLookZ);
			}

			XMLElement* pUp = pCam->FirstChildElement("up");
			if (NULL != pUp) {
				pUp->QueryFloatAttribute("x", &UPx);
				pUp->QueryFloatAttribute("y", &UPy);
				pUp->QueryFloatAttribute("z", &UPz);
			}
		}
		string path = "../generator/";
		string filename;
		XMLElement* pGroup = pRoot->FirstChildElement("group");
		if (NULL != pGroup) {
			XMLElement* pmodels= pGroup->FirstChildElement("models");
			if (NULL != pmodels) {
				XMLElement* pmodel = pmodels->FirstChildElement("model");
				if (NULL != pmodel) {
					while (pmodel)
					{
						filename = pmodel->Attribute("file");
						filename = path + filename;
						ReadFile(filename);
						pmodel = pmodel->NextSiblingElement("model");
					}
				}
			}
		}	
	}
}

int main(int argc, char **argv){

	readxml("../test/x_test_files_phase_1/test_1_2.xml");
	
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowsizex, windowsizey);
	glutCreateWindow("Sistema Solar");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}