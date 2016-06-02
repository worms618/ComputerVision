#define _USE_MATH_DEFINES
#include <cmath>
#include "LaboratoryScreen.h"
//#include <GL\freeglut.h>


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

void LaboratoryScreen::update(float deltaTime)
{
}


void LaboratoryScreen::drawMolecule(const MoleculeInstance * m)
{
	glPushMatrix();
	glScalef(m->scale, m->scale, m->scale);
	glRotatef(m->rotation.x, 1, 0, 0);
	glRotatef(m->rotation.y, 0, 1, 0);
	glRotatef(m->rotation.z, 0, 0, 1);
	glTranslatef(m->position.x, m->position.y, m->position.z);

	for (auto atomInstance : m->atomInstances)
		drawAtom(atomInstance);

	for (auto atomBinding : m->atomBindingInstances)
		drawAtomBinding(atomBinding);
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

	glColor4f(atom->color.red, 
		atom->color.green,
		atom->color.blue, 
		atom->color.alfa);
	
	atomModel->draw();
	glPopMatrix();
}

void LaboratoryScreen::drawAtomBinding(AtomBindingInstance * ab)
{	
	//glLineWidth(atomModel->radius*2/10);
	glLineWidth(500);
	glBegin(GL_LINES);
	glVertex3f(ab->basePosition.x + atomModel->center.x,
		ab->basePosition.y + atomModel->center.y,
		ab->basePosition.z + atomModel->center.z);

	glVertex3f(ab->bindingPosition.x + atomModel->center.x,
		ab->bindingPosition.y + +atomModel->center.y, 
		ab->bindingPosition.z + +atomModel->center.z);
	glEnd();	
}




