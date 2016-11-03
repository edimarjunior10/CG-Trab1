#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLint dir = 0;
GLint passo = 0;

//Fun??o callback chamada para fazer o desenho
void Desenha(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualiza??o com a cor de fundo especificada
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	gluLookAt(0.0, 5.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    if (passo >= 20) {
        dir = dir == 0 ? 1 : 0;
        passo = 0;
    }
    passo++;
    if (dir == 0)
      glTranslatef(passo-10,0,0);
     else
        glTranslatef(20-passo-10,0,0);

    glutSolidCube(2);
	// Executa os comandos OpenGL
    glutSwapBuffers();
	glFinish();
}
void Redesenha(int)
{
    glutPostRedisplay();
    Desenha();
    glutTimerFunc(50,Redesenha,1);

}

// Inicializa par?metros de rendering
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualiza??o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}

// Fun??o callback chamada quando o tamanho da janela ? alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if (h == 0) h = 1;

	// Especifica as dimens?es da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, w/h, 2, 100);
}

// Programa Principal
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 350);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Cubo");
	glutTimerFunc(40,Redesenha,1);
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}
