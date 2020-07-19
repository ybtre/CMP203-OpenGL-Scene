// #include "Scene.h"
//
//
// void worldAndSun() {
//
// 	//Attenuation for the Sun-----------------------------------------------------------
// 	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
// 	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
// 	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
//
// 	// Floor tiles and Sun
// 	glBindTexture(GL_TEXTURE_2D, floorTile); // Tell openGl what texture to use
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //MIN - minification
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR); //MAG - magnification
//
// 	glRotatef(-90, 1.0f, 0.0f, 0.0f);
// 	// 	glTranslatef(0, 0, 0.5);
// 	// 	glColor3f(1.0f, 1.0f, 1.0f);
//
// 	glBegin(GL_QUADS);
// 	// should point the normals in the right direction, currently towards the inside of the cave, on Z axis after the object has been rotated
// 	glNormal3f(0.0, 0.0, 1.0);
// 	const GLfloat sqSizeMulti = 1.5;
// 	for (int i = -150; i < 150; ++i) {
// 		for (int j = -150; j < 150; ++j) {
// 			glTexCoord2f(0, 1);
// 			glVertex3f(j * sqSizeMulti, i * sqSizeMulti, 0);
//
// 			glTexCoord2f(1, 1);
// 			glVertex3f((j + 1) * sqSizeMulti, i * sqSizeMulti, 0);
//
// 			glTexCoord2f(1, 0);
// 			glVertex3f((j + 1) * sqSizeMulti, (i + 1) * sqSizeMulti, 0);
//
// 			glTexCoord2f(0, 0);
// 			glVertex3f(j * sqSizeMulti, (i + 1) * sqSizeMulti, 0);
// 		}
// 	}
// 	glEnd();
//
// 	// The Sun
// 	glPushMatrix();
// 		glDisable(GL_TEXTURE_2D);
// 		glRotatef(rotation_s / 4, 1, 0, 0);
// 		glTranslatef(0, 150, -10); // x = left/right ; y = z-depth/forward - back  ; z = height
// 		glScalef(4, 4, 4);
// 		glColor3f(0.6, 0.5, 0);
// 		gluSphere(gluNewQuadric(), 0.60, 10, 10); // no need for the sun sphere to be too detailed, it is far away
//
// 		GLfloat ambientSun[] = { 0.3f, 0.3f, 0.3f, 1.0f };
// 		GLfloat diffuseSun[] = { 0.9f, 0.55f, 0.32f, 1.0f };
// 		GLfloat lightPositionSun[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//
// 		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientSun);
// 		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseSun);
// 		glLightfv(GL_LIGHT0, GL_POSITION, lightPositionSun);
//
// 		glEnable(GL_LIGHT0);
// 		glEnable(GL_TEXTURE_2D);
// 	glPopMatrix();
// };