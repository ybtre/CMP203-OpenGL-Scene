#include "Scene.h"
#include "Camera.h"
#include "Shadow.h"
#include <iostream>
// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.

bool torchesSwitch = true;
bool switchWireframeMode;
bool switchGrid;

double rotation_n;
double rotation_f;
double rotation_s;
double cubeX;
double cubeY;
double speed = 15;

float* shadowMatrix;


GLuint floorTile;
GLuint caveCeiling;
GLuint caveWall;
GLuint backCave;
GLuint treeTex;
GLuint crate;
GLuint flag;


GLuint skyBoxTexture;
GLuint skyFront;
GLuint skyBack;
GLuint skyLeft;
GLuint skyRight;
GLuint skyUp;
GLuint skyDown;


CCamera objCamera;

Scene::Scene(Input* in) {
	// Store pointer for input class
	input = in;

	//OpenGL settings
	glShadeModel(GL_SMOOTH);										// Enable Smooth Shading
	//glClearColor(0.39f, 0.58f, 93.0f, 1.0f);							// Cornflour Blue Background
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);													// Depth Buffer Setup
	glClearStencil(0);													// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);											// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);												// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	// Other OpenGL / render setting should be applied here.

	// Camera Starting Position || Position | View(target) | Up
	objCamera.positionCamera(0, 2.5f, 8,
		4.9f, 2.5f, 0,
		0, 1, 0);

	glutSetCursor(GLUT_CURSOR_NONE);									// hide cursor
	// Initialise scene variables

		/////// SKYBOX textures //////////
	skyFront = SOIL_load_OGL_texture(
		"gfx/front.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y
	);
	skyBack = SOIL_load_OGL_texture(
		"gfx/back.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y
	);


	skyLeft = SOIL_load_OGL_texture(
		"gfx/left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y
	);
	skyRight = SOIL_load_OGL_texture(
		"gfx/right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y
	);


	skyUp = SOIL_load_OGL_texture(
		"gfx/up.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y
	);
	skyDown = SOIL_load_OGL_texture(
		"gfx/downB.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);



	///////// textures //////////

	floorTile = SOIL_load_OGL_texture(
		"gfx/tile.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	caveWall = SOIL_load_OGL_texture(
		"gfx/stones.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	caveCeiling = SOIL_load_OGL_texture(
		"gfx/caveCeiling.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	backCave = SOIL_load_OGL_texture(
		"gfx/gem_diffuse.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	treeTex = SOIL_load_OGL_texture(
		"gfx/tree.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	crate = SOIL_load_OGL_texture(
		"gfx/crate.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	flag = SOIL_load_OGL_texture(
		"gfx/cloth_diffuse.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);


	// (skyFront || skyBack || skyLeft || skyRight || skyUp || skyDown == 0) ? std::cout << "a textures failed to load" : std::cout << "all textures loaded successfully";
}


void Scene::handleInput(float dt) {
	// Handle user input
	if (input->isKeyDown('t')) {
		input->SetKeyUp('t');
		torchesSwitch = (torchesSwitch == false) ? true : false;
	};
	if (input->isKeyDown('r')) {
		input->SetKeyUp('r');
		switchWireframeMode = (switchWireframeMode == false) ? true : false;
		switchGrid = (switchGrid == false) ? true : false;
	};

	if (input->isKeyDown('w')) {
		objCamera.moveCamera(CAMERASPEED);
	}
	if (input->isKeyDown('s')) {
		objCamera.moveCamera(-CAMERASPEED);
	}
	if (input->isKeyDown('a')) {
		objCamera.strafeCamera(-CAMERASPEED);
	}
	if (input->isKeyDown('d')) {
		objCamera.strafeCamera(CAMERASPEED);
	}

	objCamera.mouseMove(1920, 1080);

	//  rotate cube
	(input->isKeyDown('l')) ? cubeY += 1 : (input->SetKeyUp('l')); //  rotate cube right
	(input->isKeyDown('j')) ? cubeY -= 1 : (input->SetKeyUp('j')); //  rotate cube left
	(input->isKeyDown('k')) ? cubeX += 1 : (input->SetKeyUp('k')); //  rotate cube down
	(input->isKeyDown('i')) ? cubeX -= 1 : (input->SetKeyUp('i')); //  rotate cube up
	
}

void Scene::update(float dt) {
	// handle user input
	// Update object and variables (camera, rotation, etc).
	rotation_n += speed * dt;
	rotation_f += (speed * 2) * dt;
	rotation_s += (speed / 2) * dt;
	

	// Calculate FPS
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

}


void Scene::render() {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //MIN - minification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //MAG - magnification
	//other params for sampling
	// gl_nearest - point sampling
	// gl_linear - bilinear sampling
	// gl_linear_mipmap_linear - trilinear filtering
	// gl_linear/nearest_mipmap_linear/nearest - can also be any of those combinations

	// Set the camera
	// gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0); // stationary camera

	(input->isKeyDown('2')) ? birdsEye() : firstPerson();
	
	// Render geometry/scene here --------------------------------------------------------------------------
	// Skybox
	glPushMatrix();
		glTranslatef(0, 0, 6);
		glDisable(GL_DEPTH_TEST);
			drawSkybox(0, 0, 0, 100, 100, 100);	// Draw the Skybox
		glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	//switches
	// (switchGrid == true) ? drawGrid() : false;
	(switchWireframeMode == true) ? glPolygonMode(GL_FRONT, GL_LINE) : glPolygonMode(GL_FRONT, GL_FILL);


	// render world
	glPushMatrix();

		// transparent objects-----------------------------------------------------------
		// --------------------------------- forest -------------------------------------
		
		glPushMatrix();
			drawForest();
		glPopMatrix();

		////////////////////////////////////////////////////////////////////////////////////////

		glPushMatrix();
			worldAndSun();//----
		glPopMatrix();

		glPushMatrix();
			glDisable(GL_CULL_FACE);
				caveWalls();//----
			glEnable(GL_CULL_FACE);
		glPopMatrix();

		glPushMatrix();
			backAndCeiling();//----
		glPopMatrix();
		
		glPushMatrix();
			caveTorches();//----
		glPopMatrix();
	
		glPushMatrix();
			outerSpheres();//----
		glPopMatrix();

		//box ourside of cave
		// glDisable(GL_DEPTH_TEST);
		// glDisable(GL_LIGHTING);
		// glDisable(GL_TEXTURE_2D);
		//
		// glColor3f(0.1f, 0.1f, 0.1f);
		//
		// glPushMatrix();
		// 	glMultMatrixf((GLfloat	*)Shadow);
		// 	glTranslatef(-5, 2, -50);
		// 		drawBox();
		// glPopMatrix();
		//
		// glColor3f(1.0f, 1.0f, 1.0f);
		//
		// glEnable(GL_DEPTH_TEST);
		// glEnable(GL_LIGHTING);
		// glEnable(GL_TEXTURE_2D);

		glPushMatrix();
			glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, crate);

					glTranslatef(-5, 2, -50);
					glRotatef(cubeX, 1, 0, 0);
					glRotatef(cubeY, 0, 1, 0);
						drawTexturedBox();//----
				glDisable(GL_TEXTURE_2D);
	
			glPopMatrix();
			
			glPushMatrix();
					glTranslatef(-7, 2, -50);
					glRotatef(cubeX, 1, 0, 0);
					glRotatef(cubeY, 0, 1, 0);
						drawColoredBox();//----
				
			glPopMatrix();
		
			glPushMatrix();
					glTranslatef(-3,2, -50);
					glRotatef(cubeX, 1, 0, 0);
					glRotatef(cubeY, 0, 1, 0);
						drawColoredBox();//----
			
			glPopMatrix();
		glPopMatrix();

	
	glPopMatrix();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// reset colour
	glColor3f(1.0f, 1.0f, 1.0f);

	// End render geometry ---------------------------------------------------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();

}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) {
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) {
		h = 1;
	}

	float ratio = float(w) / float(h);
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 400.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}

// Calculates FPS
void Scene::calculateFPS() {

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput() {
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, " i - rotate cubes up");
	displayText(-1.f, 0.78f, 1.f, 0.f, 0.f, " k - rotate cubes down");
	displayText(-1.f, 0.72f, 1.f, 0.f, 0.f, " j - rotate cubes left");
	displayText(-1.f, 0.66f, 1.f, 0.f, 0.f, " l - rotate cubes right");
	displayText(-1.f, 0.60f, 1.f, 0.f, 0.f, " t - turns torches off/on");
	displayText(-1.f, 0.54f, 1.f, 0.f, 0.f, " r - turns wireframe off/on");
	displayText(-1.f, 0.48f, 1.f, 0.f, 0.f, " 2 - hold for birdseye camera");
	
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (float(width) / float(height)), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}



//////////////////////////////////////////////////////// draw objects functions //////////////////////////////////////////////////////// 
void drawGrid() {
	glDisable(GL_TEXTURE_2D);
	for (float i = -500; i <= 500; i += 0.8) {

		glBegin(GL_LINES);
			glTranslatef(0, 1, 0);
				// glNormal3f(0.0, -1.0, 0.0);
				glColor3f(1, 1, 1);

				glVertex3f(-500, 0, i);
				glVertex3f(500, 0, i);
				glVertex3f(i, 0, -500);
				glVertex3f(i, 0, 500);
		glEnd();
	}
	glEnable(GL_TEXTURE_2D);
};

void drawSkybox(float x, float y, float z, float width, float height, float length) {
	
	// bind skybox to camera movement
	x = objCamera.mPos.x - width / 2;
	y = objCamera.mPos.y - height / 2;
	z = objCamera.mPos.z - length / 2;

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, skyFront);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, skyBack);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, skyLeft);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, skyRight);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, skyUp);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + height, z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, skyDown);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

};

void drawColoredBox() {
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

		// front
		glColor3f(0.0f, 1.0f, 0.0f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		// back
		glColor3f(0.0f, 0.5f, 0.0f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		// right
		glColor3f(0.0f, 0.0f, 1.0f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		// left
		glColor3f(0.0f, 0.0f, 0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		// top
		glColor3f(1.0f, 0.0f, 0.0f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		// bottom
		glColor3f(0.5f, 0.0f, 0.0f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

	glEnd();
	glEnable(GL_TEXTURE_2D);
};

void drawTexturedBox() {
	glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

			// front
			glTexCoord2f(0, 1);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);

			glTexCoord2f(1, 1);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);

			glTexCoord2f(1, 0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

			glTexCoord2f(0, 0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

			// back
			glTexCoord2f(0, 1);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);

			glTexCoord2f(1, 1);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(0.5f, -0.5f, -0.5f);

			glTexCoord2f(1, 0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-0.5f, -0.5f, -0.5f);

			glTexCoord2f(0, 0);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

			// right
			glTexCoord2f(0, 1);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);

			glTexCoord2f(1, 1);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);

			glTexCoord2f(1, 0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);

			glTexCoord2f(0, 0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, -0.5f);

			// left
			glTexCoord2f(0, 1);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

			glTexCoord2f(1, 1);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

			glTexCoord2f(1, 0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

			glTexCoord2f(0, 0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, -0.5f);

			// top
			glTexCoord2f(0, 1);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

			glTexCoord2f(1, 1);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);

			glTexCoord2f(1, 0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);

			glTexCoord2f(0, 0);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

			// bottom
			glTexCoord2f(0, 1);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);

			glTexCoord2f(1, 1);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

			glTexCoord2f(1, 0);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, -0.5f);

			glTexCoord2f(0, 0);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, -0.5f);

		glEnd();
		glDisable(GL_TEXTURE_2D);
};

void outerSpheres() {
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();

		// Material variables ----------------------------------------------------------------
		GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };

		GLfloat mat_diff_red[] = { 1.0, 0.0, 0.0, 1.0 };
		GLfloat mat_diff_blue[] = { 0.1, 0.5, 0.8, 1.0 };
		GLfloat diffGreen[] = {0, 1, 0, 1};
		GLfloat diffBlack[] = { 0, 0, 0, 1 };
		GLfloat diffWhite[] = { 1, 1, 1, 1 };
		
		GLfloat lowSpecular[] = { 0.2, 0.2, 0.2, 1};
		GLfloat medSpecular[] = { 0.4, 0.4, 0.4, 1 };
		GLfloat highSpecular[] = {0.8, 0.8, 0.8, 1};
		
		GLfloat low_shininess[] = { 5.0 };
		GLfloat medShininess[] = { 50 };
		GLfloat high_shininess[] = { 100.0 };
		
		
			glTranslatef(5, 3, -50); // x = -left/+right ; y = z-depth/forward - back  ; z = height
			glScalef(4, 4, 4);
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffGreen);
				glMaterialfv(GL_FRONT, GL_SPECULAR, medSpecular);
				glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
					glColor3f(0.6, 0.5, 0);
						gluSphere(gluNewQuadric(), 0.20, 200, 200); // Center ball

			glPushMatrix();
				glRotatef(rotation_s, 1, 0, 1);
				glTranslatef(0, 0.4, 0); // small bue ball, orbiting center ball
				glScalef(0.8, 0.8, 0.8);
				glColor3f(0, 0, 1);
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
					glMaterialfv(GL_FRONT, GL_SPECULAR, highSpecular);
					glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
						gluSphere(gluNewQuadric(), 0.10, 50, 50);
			
				glPushMatrix();
					glRotatef(rotation_n, 1, 1, 0);
					glTranslatef(0, 0.2, 0); // small red ball, orbiting center ball
					glScalef(0.5, 0.5, 0.5);
					glColor3f(1, 0, 0);
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_red);
						glMaterialfv(GL_FRONT, GL_SPECULAR, lowSpecular);
						glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
						glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
							gluSphere(gluNewQuadric(), 0.10, 50, 50);
				
				glPopMatrix();
			glPopMatrix();

			//side balls
			glPushMatrix(); 
			glRotatef(rotation_n, 0, 1, 0);
				glTranslatef(1, 0,0); // big red ball
				glColor3f(1, 0, 0);
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffWhite);
					glMaterialfv(GL_FRONT, GL_SPECULAR, highSpecular);
					glMaterialfv(GL_FRONT, GL_SHININESS, medShininess);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
						gluSphere(gluNewQuadric(), 0.20, 50, 50);
			
				glTranslatef(-2, 0, 0); // big blue ball
				glColor3f(0, 0, 1); 
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffBlack);
					glMaterialfv(GL_FRONT, GL_SPECULAR, lowSpecular);
					glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
						gluSphere(gluNewQuadric(), 0.20, 50, 50);
			glPopMatrix();

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
};

void worldAndSun() {
	
		//Attenuation for the Sun-----------------------------------------------------------
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
	
		// Floor tiles and Sun	
		glBindTexture(GL_TEXTURE_2D, floorTile); // Tell openGl what texture to use
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //MIN - minification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR); //MAG - magnification

		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		// 	glTranslatef(0, 0, 0.5);
		// 	glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glEnable(GL_TEXTURE_2D);
			// should point the normals in the right direction, currently towards the inside of the cave, on Z axis after the object has been rotated
				glNormal3f(0.0, 0.0, 1.0);
				const GLfloat sqSizeMulti = 1.5;
				for (int i = -150; i < 150; ++i) {
					for (int j = -150; j < 150; ++j) {
						glTexCoord2f(0, 1);
						glVertex3f(j * sqSizeMulti, i * sqSizeMulti, 0);

						glTexCoord2f(1, 1);
						glVertex3f((j + 1) * sqSizeMulti, i * sqSizeMulti, 0);

						glTexCoord2f(1, 0);
						glVertex3f((j + 1) * sqSizeMulti, (i + 1) * sqSizeMulti, 0);

						glTexCoord2f(0, 0);
						glVertex3f(j * sqSizeMulti, (i + 1) * sqSizeMulti, 0);
					}
				}
			glDisable(GL_TEXTURE_2D);
		glEnd();

		// The Sun
		glPushMatrix();
			glDisable(GL_TEXTURE_2D);
				glRotatef(rotation_s / 4, 1, 0, 0);
				glTranslatef(0, 150, -10); // x = left/right ; y = z-depth/forward - back  ; z = height
				glScalef(4, 4, 4);
				glColor3f(0.6, 0.5, 0);
					gluSphere(gluNewQuadric(), 0.60, 10, 10); // no need for the sun sphere to be too detailed, it is far away

				GLfloat ambientSun[] = { 0.3f, 0.3f, 0.3f, 1.0f };
				GLfloat diffuseSun[] = { 0.9f, 0.55f, 0.32f, 1.0f };
				GLfloat lightPositionSun[] = { 0.0f, 0.0f, 0.0f, 1.0f };

				glLightfv(GL_LIGHT0, GL_AMBIENT, ambientSun);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseSun);
				glLightfv(GL_LIGHT0, GL_POSITION, lightPositionSun);

				glEnable(GL_LIGHT0);

			glEnable(GL_TEXTURE_2D);
		glPopMatrix();
};

void backAndCeiling() {
	glEnable(GL_TEXTURE_2D);
		// cave ceiling
		glPushMatrix();
		glDisable(GL_CULL_FACE);
			glBindTexture(GL_TEXTURE_2D, caveCeiling); // Tell openGl what texture to use
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //MIN - minification
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR); //MAG - magnification
		
			glTranslatef(0, 4.55, -10);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			glRotatef(90, 1.0f, 0.0f, 0.0f);

			glBegin(GL_QUADS);
			// should point the normals in the right direction, currently up on Y
			glNormal3f(0.0, 1.0, 0.0);
			const GLfloat ceiling = 0.5;
			for (int height = -4; height < 4; ++height) {
				for (int width = -40; width < 40; ++width) {
					glTexCoord2f(0, 1);
					glVertex3f(width * ceiling, height * ceiling, 0);

					glTexCoord2f(1, 1);
					glVertex3f((width + 1) * ceiling, height * ceiling, 0);

					glTexCoord2f(1, 0);
					glVertex3f((width + 1) * ceiling, (height + 1) * ceiling, 0);

					glTexCoord2f(0, 0);
					glVertex3f(width * ceiling, (height + 1) * ceiling, 0);
				}
			}
			glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();

		//cave back 
		glPushMatrix();
			glDisable(GL_CULL_FACE);
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, backCave); // Tell openGl what texture to use
				glTranslatef(0, 2, 10);
				glRotatef(180, 0, 1, 0);

				glBegin(GL_QUADS);
				// should point the normals in the right direction, currently up on Y
				glNormal3f(0.0, 0.0, 1.0);
				const GLfloat backC = 0.5;
				for (int height = -5.5; height < 5.5; ++height) {
					for (int width = -6.5; width < 6.5; ++width) {
						glTexCoord2f(0, 1);
						glVertex3f(width * backC, height * backC, 0);

						glTexCoord2f(1, 1);
						glVertex3f((width + 1) * backC, height * backC, 0);

						glTexCoord2f(1, 0);
						glVertex3f((width + 1) * backC, (height + 1) * backC, 0);

						glTexCoord2f(0, 0);
						glVertex3f(width * backC, (height + 1) * backC, 0);
					}
				}
				glEnd();
			glEnable(GL_CULL_FACE);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		
	glDisable(GL_TEXTURE_2D);
};

void caveWalls() {

	// right cave wall
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, caveWall); // Tell openGl what texture to use
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //MIN - minification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR); //MAG - magnification
		
		glTranslatef(3, 1, -10);
		glRotatef(-90, 0.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
		// should point the normals in the right direction, currently towards the inside of the cave, on Z axis after the object has been rotated
			glNormal3f(0.0, 0.0, 1.0);
			const GLfloat rightWS = 0.5;
			for (int height = -5; height < 5; ++height) {
				for (int width = -40; width < 40; ++width) {
					glTexCoord2f(0, 1);
					glVertex3f(width * rightWS, height * rightWS, 0);

					glTexCoord2f(1, 1);
					glVertex3f((width + 1) * rightWS, height * rightWS, 0);

					glTexCoord2f(1, 0);
					glVertex3f((width + 1) * rightWS, (height + 1) * rightWS, 0);

					glTexCoord2f(0, 0);
					glVertex3f(width * rightWS, (height + 1) * rightWS, 0);
				}
			}
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// right cave wall, sloped upper part
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, caveWall); // Tell openGl what texture to use
		glTranslatef(2.65, 3.85, -10);
		glRotatef(-90, 0.0f, 1.0f, 0.0f);
		glRotatef(45, 1.0f, 0.0f, 0.0f);

		glBegin(GL_QUADS);
		// should point the normals in the right direction, currently towards the inside of the cave, on Z axis after the object has been rotated
		glNormal3f(0.0, 0.0, 1.0);
		const GLfloat rightCUP = 0.5;
		for (int height = -1.2; height < 1.2; ++height) {
			for (int width = -40; width < 40; ++width) {
				glTexCoord2f(0, 1);
				glVertex3f(width * rightCUP, height * rightCUP, 0);

				glTexCoord2f(1, 1);
				glVertex3f((width + 1) * rightCUP, height * rightCUP, 0);

				glTexCoord2f(1, 0);
				glVertex3f((width + 1) * rightCUP, (height + 1) * rightCUP, 0);

				glTexCoord2f(0, 0);
				glVertex3f(width * rightCUP, (height + 1) * rightCUP, 0);
			}
		}
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// left cave wall
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, caveWall); // Tell openGl what texture to use
		glTranslatef(-3, 1, -10);
		glRotatef(90, 0.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
		// should point the normals in the right direction, currently towards the inside of the cave, on Z axis after the object has been rotated
		glNormal3f(0.0, 0.0, 1.0);
		const GLfloat leftCW = 0.5;
		for (int height = -5; height < 5; ++height) {
			for (int width = -40; width < 40; ++width) {
				glTexCoord2f(0, 1);
				glVertex3f(width * leftCW, height * leftCW, 0);

				glTexCoord2f(1, 1);
				glVertex3f((width + 1) * leftCW, height * leftCW, 0);

				glTexCoord2f(1, 0);
				glVertex3f((width + 1) * leftCW, (height + 1) * leftCW, 0);

				glTexCoord2f(0, 0);
				glVertex3f(width * leftCW, (height + 1) * leftCW, 0);
			}
		}
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// left cave wall, sloped upper part
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, caveWall); // Tell openGl what texture to use
		glTranslatef(-2.65, 3.85, -10);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glRotatef(45, 1.0f, 0.0f, 0.0f);

		glBegin(GL_QUADS);
		// should point the normals in the right direction, currently towards the inside of the cave, on Z axis after the object has been rotated
		glNormal3f(0.0, 0.0, 1.0);
		const GLfloat leftCUP = 0.5;
		for (int height = -1.2; height < 1.2; ++height) {
			for (int width = -40; width < 40; ++width) {
				glTexCoord2f(0, 1);
				glVertex3f(width * leftCUP, height * leftCUP, 0);

				glTexCoord2f(1, 1);
				glVertex3f((width + 1) * leftCUP, height * leftCUP, 0);

				glTexCoord2f(1, 0);
				glVertex3f((width + 1) * leftCUP, (height + 1) * leftCUP, 0);

				glTexCoord2f(0, 0);
				glVertex3f(width * leftCUP, (height + 1) * leftCUP, 0);
			}
		}
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
};

void caveTorches() {
	glDisable(GL_TEXTURE_2D);
	
	//
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, no_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	
	// Lighting variables ----------------------------------------------------------------
	GLfloat ambientTorch[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuseTorch[] = { 0.3f, 0.9f, 0.2f, 1.0f };
	GLfloat lightPositionTorch[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	GLfloat ambientTorch2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuseTorch2[] = { 0.3f, 0.9f, 0.2f, 1.0f };
	GLfloat lightPositionTorch2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	// attenuation for cave torches----------------------------------------------------
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01f);

	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.01f);
	
	// left cave torch
		glTranslatef(-2.5, 3, 5.5);
		glScalef(0.5, 0.5, 0.5);
		glColor3f(0.8f, 0.5f, 0.0f);
			gluSphere(gluNewQuadric(), 0.20, 400, 400);

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientTorch);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseTorch);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionTorch);

		(torchesSwitch == true) ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);
		glPopMatrix();

		// right cave torch
		glPushMatrix();
		// glBindTexture(GL_TEXTURE_2D, torchStick); // Tell openGl what texture to use
		glTranslatef(2.5, 3, 5.5);
		// glRotatef(180, 1, 0, 0);
		glScalef(0.5, 0.5, 0.5);
		glColor3f(0.8f, 0.5f, 0.0f);
		gluSphere(gluNewQuadric(), 0.20, 400, 400);

		glLightfv(GL_LIGHT2, GL_AMBIENT, ambientTorch2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseTorch2);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPositionTorch2);

		(torchesSwitch == true) ? glEnable(GL_LIGHT2) : glDisable(GL_LIGHT2);

		//torch handle
		// glPushMatrix();
		// 	glTranslatef(0, -0.5, 0);
		// 	glScalef(0.1, 1.1, 0.05);
		// 	glRotatef(25, 0, 0, 1);
		// 		drawBox();
		// glPopMatrix();
		// 
	glEnable(GL_TEXTURE_2D);
};

void treesForForest_transparent() {

		glBindTexture(GL_TEXTURE_2D, treeTex); // Tell openGl what texture to 
		glScalef(3, 5, 0);
	
		// glRotatef(-objCamera.mPos.z, 0, 1, 0); //closest i've gotten to billboarding so far

		glBegin(GL_QUADS); // begin drawing state
			//everything is of type float
			for (int width = -75; width < 75; ++width) {
					glNormal3f(0, 0, 1);
					glTexCoord2f(0, 1);
					glVertex3f(-width, -0.5, 1);

					glNormal3f(0, 0, 1);
					glTexCoord2f(1, 1);
					glVertex3f((-width + 1), -0.5, 1);
																
					glNormal3f(0, 0, 1);
					glTexCoord2f(1, 0);
					glVertex3f((-width + 1), 0.5, 1);

					glNormal3f(0, 0, 1);
					glTexCoord2f(0, 0);
					glVertex3f(-width, 0.5, 1);
			};
		glEnd();
};

void drawForest() {
	glEnable(GL_BLEND);
		// front rows
		glPushMatrix();
			glColor4f(1, 1, 1, 1);

			glTranslatef(0, 2.4, -250);
			glScalef(0.8, 1, 0);
				treesForForest_transparent();//-------

		glPopMatrix();

		glPushMatrix();
			glColor4f(1, 1, 1, 1);

			glTranslatef(1.5, 2.4, -225);
				treesForForest_transparent();//-------

		glPopMatrix();

		//back rows
		glPushMatrix();
			glColor4f(1, 1, 1, 1);

			glTranslatef(0, 2.4, 250);
			glScalef(0.8, 1, 0);
			glRotatef(180, 0, 1, 0);
				treesForForest_transparent();//-------

		glPopMatrix();

		glPushMatrix();
			glColor4f(1, 1, 1, 1);

			glTranslatef(0, 2.4, 225);
			glRotatef(180, 0, 1, 0);
				treesForForest_transparent();//--------

		glPopMatrix();

		// left rows
		glPushMatrix();
			glColor4f(1, 1, 1, 1);

			glTranslatef(-250, 2.4, 0);
			glScalef(0.8, 1, 0);
			glRotatef(90, 0, 1, 0);
				treesForForest_transparent();//-------

		glPopMatrix();

		glPushMatrix();
			glColor4f(1, 1, 1, 1);

			glTranslatef(-225, 2.4, 0);
			glRotatef(90, 0, 1, 0);
				treesForForest_transparent();//--------

		glPopMatrix();

		// right rows
		glPushMatrix();
			glColor4f(1, 1, 1, 1);

			glTranslatef(250, 2.4, 0);
			glScalef(0.8, 1, 0);
			glRotatef(-90, 0, 1, 0);
				treesForForest_transparent();//-------

		glPopMatrix();

		glPushMatrix();
			glColor4f(1, 1, 1, 1);

			glTranslatef(225, 2.4, 0);
			glRotatef(-90, 0, 1, 0);
				treesForForest_transparent();//------

		glPopMatrix();
	glDisable(GL_BLEND);
};

// cameras
void firstPerson() {
	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mLookAt.x, objCamera.mLookAt.y, objCamera.mLookAt.z,	//1st person camera
			   objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
};

void birdsEye() {
	gluLookAt(25, 30, -5,
			0, -5, -50,	
			   0, 1, 0);
};