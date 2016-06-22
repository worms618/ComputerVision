#include "MoleculeInfoPanel.h"
#include <GL\freeglut.h>
#include <sstream>

MoleculeInfoPanel::MoleculeInfoPanel()
{
}

MoleculeInfoPanel::~MoleculeInfoPanel()
{
}

void MoleculeInfoPanel::draw(int width,int height)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(57 / 255.0f, 1.0f, 20 / 155.0f, 1.0f);
	drawString("Name: " + name, 0, height / 10 * 8);
	drawString("Formula: " + molecularFormula, 0, height / 10 * 8 + 18);
	drawString("Atomic mass: " + atomicMass, 0, height / 10 * 8 + 36);

	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 1.0);
	glVertex2f(0, height / 10 * 8);
	glVertex2f(0, height);
	glVertex2f(width / 10 * 1.5, height);
	glVertex2f(width / 10 * 1.5, height / 10 * 8);
	glEnd();
}

void MoleculeInfoPanel::updateInfoPanel(std::string name, std::string formula, int mass)
{
	this->name = name;
	this->molecularFormula = formula;
	std::ostringstream oss;
	oss << mass;
	atomicMass = oss.str();
}


void MoleculeInfoPanel::drawString(std::string str, int x, int y)
{
	glRasterPos2f(x, y + 18);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}
