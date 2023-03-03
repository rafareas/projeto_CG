#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glut.h>
#include "generator/Include/Shape.hpp"

using namespace std;

vector<Triangle> allTriangles;
float myX = 0.0;
float myZ = 0.0;
float myRadius = 0.0;
float myAlpha = 0.0;
float myBeta = 0.0;



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
	gluLookAt(10 + radius + myRadius, 10 + radius + myX + myRadius, 10 + radius + myZ + myRadius,
		0.0 + (sin(myAlpha) * cos(myBeta) * radius), 0.0 + (sin(myAlpha) * cos(myBeta) * radius), 0.0 + (cos(myAlpha) * cos(myBeta) * radius),
		0.0f, 1.0f, 0.0f);

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

	ifstream MyFile("../generator/shape.txt");

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


void processKeys(unsigned char key, int xx, int yy) {


	if (key == 'w') {
		myX += 0.5;
	}
	if (key == 's') {
		myX -= 0.5;
	}
	if (key == 'd') {
		myZ -= 0.5;
	}
	if (key == 'a') {
		myZ += 0.5;
	}
	if (key == '+') {
		myRadius -= 0.5;
	}
	if (key == '-') {
		myRadius += 0.5;
	}
	if (key == 'u') {
		myBeta += 0.5;
	}
	if (key == 'j') {
		myBeta -= 0.5;
	}
	if (key == 'h') {
		myAlpha += 0.5;
	}
	if (key == 'k') {
		myAlpha -= 0.5;
	}

	glutPostRedisplay();

}


void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here

}


int main(int argc, char **argv)
{
	ReadFile("shape.txt");
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

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