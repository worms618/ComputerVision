#define _USE_MATH_DEFINES
#include <cmath>
#include "LaboratoryScreen.h"
//#include <GL\freeglut.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "ScreenHandler.h"

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
	if (skybox)
		delete skybox;
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
	currentMolecule = molecule_instances[index];
	updateMoleculeData();
	
	skybox = new Skybox(ScreenHandler::perpective, "skyboxes/labo/");
	skybox->init();
}

void LaboratoryScreen::draw(int width, int height)
{	
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	skybox->draw();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_COLOR_MATERIAL);
	drawMolecule(currentMolecule);
	
	mip.draw(width,height);	
}

bool rotX = false, rotY = false, rotZ = false;
void LaboratoryScreen::update(float deltaTime, bool keys[]){
	glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidth);
	
	if (keys['p'])
	{
		index++;
		index %= molecule_instances.size();
		currentMolecule = molecule_instances[index];
		updateMoleculeData();
	}
	if (keys['x'])
	{
		rotX = !rotX;
		rotY = false;
		rotZ = false;
	}		
	if (keys['y'])
	{ 
		rotX = false;
		rotY = !rotY;
		rotZ = false;
	}		
	if (keys['z'])
	{
		rotX = false;
		rotY = false;
		rotZ = !rotZ;
	}
	if (keys['r'])
	{
		currentMolecule->rotation = Vec3f(0, 0, 0);
		rotX = false;
		rotY = false;
		rotZ = false;
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
	for (auto abi : ab->positions)
	{
		Vec3f base = abi.first+ atomModel->center;
		Vec3f binding = abi.second+ atomModel->center;
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
	
}


void LaboratoryScreen::updateMoleculeData()
{
	std::ostringstream oss;
	for (auto &atom_pair : currentMolecule->molecule->atom_pairs)
	{
		oss << std::showbase << std::uppercase;
		oss << lab->periodicTable->getAtom(atom_pair.first)->chemicalSymbol;
		if (atom_pair.second > 1)
			oss << atom_pair.second;

	}
	std::string atoms = oss.str();
	std::transform(atoms.begin(), atoms.end(), atoms.begin(), toupper);
	//moleculeFormula = atoms;

	float tam = 0;
	for (auto &atom : currentMolecule->molecule->atoms)
		tam+=lab->periodicTable->getAtom(atom)->atomicMass;

	/*oss.str("");
	oss.clear();
	oss.flush();

	oss.precision(4);
	oss << tam;
	totalAtomicMass = oss.str();*/

	mip.updateInfoPanel(currentMolecule->molecule->name, atoms, tam);
}
