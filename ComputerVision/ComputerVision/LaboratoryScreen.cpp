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
	
}

void LaboratoryScreen::init()
{
	Screen::init();
	index = 0;
	lab = new laboratory();
	camera.posZ = -10.0f;
	atomModel = Model::load("models/sphere/sphere.obj");

	for (auto molecule : lab->molecules)
	{
		MoleculeInstance* m = new MoleculeInstance(molecule);
		molecule_instances.push_back(m);
	}

}

void LaboratoryScreen::draw(int, int)
{
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	if(molecule_instances.size() > 0);
		drawMolecule(molecule_instances[1]);
	
	/*glColor3f(0.1f, 1.0f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-15, -1, -15);
	glVertex3f(15, -1, -15);
	glVertex3f(15, -1, 15);
	glVertex3f(-15, -1, 15);
	glEnd();*/

	/*AtomInstance *ai = new AtomInstance(8);
	drawAtom(ai);
	delete ai;*/
}

void LaboratoryScreen::update(float deltaTime, bool keys[])
{
	glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidth);
	//std::cout << lineWidth[0] << ", " << lineWidth[1] << std::endl;
	if (keys['p']) index %= 2; index++;
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

		Vec3f base = ab->basePosition + atomModel->center;
		Vec3f binding = ab->bindingPosition + atomModel->center;

		m->drawAtomBindingLines(
			lab->periodicTable->getAtom(m->molecule->atoms[ab->atomBinding->baseAtomIndex]),
			lab->periodicTable->getAtom(m->molecule->atoms[ab->atomBinding->bindingAtomIndex]), 
			base, binding);
		//drawAtomBinding(ab);
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

//void LaboratoryScreen::drawAtomBinding(AtomBindingInstance* ab)
//{
//	Vec3f base = ab->basePosition + atomModel->center;
//	Vec3f binding = ab->bindingPosition + atomModel->center;
//	Vec3f diff = binding - base;
//
//	//base->bindColor();
//
//	//lab->periodicTable->getAtom(ab->atomBinding->atomicNumber)->bindColor();
//	
//	glBegin(GL_LINES);
//	glVertex3f(base.x, base.y, base.z);
//	glVertex3f(base.x + diff.x / 2, base.y + diff.y / 2, base.z + diff.z / 2);
//	glEnd();
//
//	//binding->bindColor();
//
//	glBegin(GL_LINES);
//	glVertex3f(binding.x, binding.y, binding.z);
//	glVertex3f(binding.x - diff.x / 2, binding.y - diff.y / 2, binding.z - diff.z / 2);
//	glEnd();
//}
