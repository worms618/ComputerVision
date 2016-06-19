#define _USE_MATH_DEFINES
#include <cmath>
#include "LaboratoryScreen.h"
//#include <GL\freeglut.h>
#include <iostream>

float lineWidth[2];

LaboratoryScreen::LaboratoryScreen()
{
}


LaboratoryScreen::~LaboratoryScreen()
{
	if (lab)
		delete lab;
	if (currentMolecule)
		delete currentMolecule;
}

void LaboratoryScreen::init()
{
	index = 0;
	Screen::init();
	
	lab = new laboratory();
	camera.posZ = -10.0f;
	atomModel = Model::load("models/sphere/sphere.obj");

	for (auto molecule : lab->molecules)
	{
		MoleculeInstance* m = new MoleculeInstance(molecule);
		molecule_instances.push_back(m);
	}
	currentMolecule = molecule_instances[0];
}

void LaboratoryScreen::draw(int width, int height)
{
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	
	drawMolecule(currentMolecule);
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height,0, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 1.0);
	glVertex2f(0, height / 10 * 8);
	glVertex2f(0, height);
	glVertex2f(width / 10, height);
	glVertex2f(width / 10, height / 10 * 8);
	glEnd();
}

bool rotX = false, rotY = false, rotZ = false;
void LaboratoryScreen::update(float deltaTime, bool keys[])
{
	glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidth);
	//currentMolecule->rotation.x += 0.1f;
	//currentMolecule->rotation.y += 0.1f;
	//currentMolecule->rotation.z += 0.1f;
	//std::cout << lineWidth[0] << ", " << lineWidth[1] << std::endl;
	if (keys['p'])
	{
		index++;
		index %= molecule_instances.size();
		currentMolecule = molecule_instances[index];
	}
	if (keys['x'])
	{
		rotX = true;
		rotY = false;
		rotZ = false;
	}		
	if (keys['y'])
	{ 
		rotX = false;
		rotY = true;
		rotZ = false;
	}		
	if (keys['z'])
	{
		rotX = false;
		rotY = false;
		rotZ = true;
	}
		

	if (rotX)	
		currentMolecule->rotation.x += 0.1f;

	if (rotY)
		currentMolecule->rotation.y += 0.1f;

	if (rotZ)
		currentMolecule->rotation.z += 0.1f;
	
}



void LaboratoryScreen::drawMolecule(MoleculeInstance * m)
{
	glPushMatrix();
	glScalef(m->scale, m->scale, m->scale);
	glRotatef(m->rotation.x, 1, 0, 0);
	glRotatef(m->rotation.y, 0, 1, 0);
	glRotatef(m->rotation.z, 0, 0, 1);
	glTranslatef(m->position.x, m->position.y, m->position.z);

	for (auto atomInstance : m->atomInstances)
		drawAtom(atomInstance);

	glLineWidth(lineWidth[1]);

	for (auto ab : m->atomBindingInstances)
	{	
		drawAtomBinding(ab);
	}	

	glPopMatrix();
}

void LaboratoryScreen::drawAtom(AtomInstance * a)
{
	glPushMatrix();
	glScalef(a->scale, a->scale, a->scale);
	glRotatef(a->rotation.x, 1, 0, 0);
	glRotatef(a->rotation.y, 0, 1, 0);
	glRotatef(a->rotation.z, 0, 0, 1);
	glTranslatef(a->position.x, a->position.y, a->position.z);
	
	Atom* atom = lab->periodicTable->getAtom(a->atomicNumber);
	atom->bindColor();

	atomModel->draw();
	glPopMatrix();
}

void LaboratoryScreen::drawAtomBinding(AtomBindingInstance* ab)
{
	Vec3f base = ab->basePosition + atomModel->center;
	Vec3f binding = ab->bindingPosition + atomModel->center;
	Vec3f diff = binding - base;

	lab->periodicTable->getAtom(currentMolecule->molecule->atoms[ab->atomBinding->baseAtomIndex])->bindColor();
	glBegin(GL_LINES);
	glVertex3f(base.x, base.y, base.z);
	glVertex3f(base.x + diff.x / 2, base.y + diff.y / 2, base.z + diff.z / 2);
	glEnd();

	lab->periodicTable->getAtom(currentMolecule->molecule->atoms[ab->atomBinding->bindingAtomIndex])->bindColor();
	glBegin(GL_LINES);
	glVertex3f(binding.x, binding.y, binding.z);
	glVertex3f(binding.x - diff.x / 2, binding.y - diff.y / 2, binding.z - diff.z / 2);
	glEnd();
}