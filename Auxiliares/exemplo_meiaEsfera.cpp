/*
 * Universidade Federal da Fronteira Sul - UFFS
 * Disciplina de Computação Gráfica
 * Professor José Carlos Bins
 * Noturno 2016/02
 * Aluno Edimar Roque Martello Júnior
 * Matricula 1111100038
 * 
 * 
 * TIRAR OS DEMAIS COMENTARIOS DO CODIGO E REMOVER O CUBO2
 * 
*/
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

const double pi = 3.1415926;
int altTamanhoCubo, moveTela; 
double CuboTamanho;
GLfloat Tela, Esfera1, Cone1, Cubo1;
GLdouble p[3] = { 0,0,0 };
double matCoresEsfera[5][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}}; 
GLfloat v[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
					{1,-1,1}, {-1,-1,1}, {-1,1,1}, {1,1,1}};

void esfera(GLdouble *centro, GLdouble radius, GLfloat num) {
	GLdouble c, c2, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	GLdouble phi, theta, phi1, theta1, phi2, theta2;
	GLdouble senphi1, cosphi1, senphi2, cosphi2,
	         sentheta1, costheta1, sentheta2, costheta2,
	         passo;
	glVertex3d(centro[0], centro[1] + radius, centro[2]);
	c = pi / 180;
	passo = 180 / num * c;
	glBegin(GL_TRIANGLES);
	phi1 = 0;
	senphi1 = sin(phi1);
	cosphi1 = cos(phi1);
	int i,j,k;
	for (i=0; i < num/2; i++) {
		phi2 = phi1 + passo;
		senphi2 = sin(phi2);
		cosphi2 = cos(phi2);
		theta1 = 0;
		sentheta1 = sin(theta1);
		costheta1 = cos(theta1);
		k = 0;
		for (j = 0; j < 2 * num; j++) {
			if (j % 8 == 0) {
				glColor3f(matCoresEsfera[k][0], matCoresEsfera[k][1], matCoresEsfera[k][2]);
				k++;
			}
			theta2 = theta1 + passo;
			sentheta2 = sin(theta2);
			costheta2 = cos(theta2);
			x1 = centro[0] + radius * senphi1 * costheta1;
			y1 = centro[1] + radius * senphi1 * sentheta1;
			z1 = centro[2] + radius * cosphi1;
			glVertex3d(x1, y1, z1);
			x2 = centro[0] + radius * senphi2 * costheta1;
			y2 = centro[1] + radius * senphi2 * sentheta1;
			z2 = centro[2] + radius * cosphi2;
			glVertex3d(x2, y2, z2);
			x3 = centro[0] + radius * senphi2 * costheta2;
			y3 = centro[1] + radius * senphi2 * sentheta2;
			z3 = centro[2] + radius * cosphi2;
			glVertex3d(x3, y3, z3);
			glVertex3d(x1, y1, z1);
			glVertex3d(x3, y3, z3);
			x4 = centro[0] + radius * senphi1 * costheta2;
			y4 = centro[1] + radius * senphi1 * sentheta2;
			z4 = centro[2] + radius * cosphi1;
			glVertex3d(x4, y4, z4);
			theta1 = theta2;
			sentheta1 = sentheta2;
			costheta1 = costheta2;
		}
		phi1 = phi2;
		senphi1 = senphi2;
		cosphi1 = cosphi2;
	}
	glEnd();
}

void cubo2(double tam, double x, double y, double z) {
  // Lado branco - TRASEIRA
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f( x + tam, y - tam, z + tam );
  glVertex3f( x + tam, y + tam, z + tam );
  glVertex3f( x - tam, y + tam, z + tam );
  glVertex3f( x - tam, y - tam, z + tam );
  glEnd();

  // Lado roxo - DIREITA
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( x + tam, y - tam, z - tam );
  glVertex3f( x + tam, y + tam, z - tam );
  glVertex3f( x + tam, y + tam, z + tam );
  glVertex3f( x + tam, y - tam, z + tam );
  glEnd();

  // Lado verde - ESQUERDA
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( x - tam, y - tam, z + tam );
  glVertex3f( x - tam, y + tam, z + tam );
  glVertex3f( x - tam, y + tam, z - tam );
  glVertex3f( x - tam, y - tam, z - tam );
  glEnd();

  // Lado azul - TOPO
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f( x + tam, y + tam, z + tam );
  glVertex3f( x + tam, y + tam, z - tam );
  glVertex3f( x - tam, y + tam, z - tam );
  glVertex3f( x - tam, y + tam, z + tam );
  glEnd();

  // Lado vermelho - BASE
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f( x + tam, y - tam, z - tam );
  glVertex3f( x + tam, y - tam, z + tam );
  glVertex3f( x - tam, y - tam, z + tam );
  glVertex3f( x - tam, y - tam, z - tam );
  glEnd();

  //Lado laranja - Frente
  glBegin(GL_POLYGON);
  glColor3f( 1.0, 0.647, 0.0);
  glVertex3f( x + tam, y - tam, z - tam );
  glVertex3f( x + tam, y + tam, z - tam );
  glVertex3f( x - tam, y + tam, z - tam );
  glVertex3f( x - tam, y - tam, z - tam );
  glEnd();

}

void cubo() {
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(v[0]); //frente
	glVertex3fv(v[1]);
	glVertex3fv(v[2]);
	glVertex3fv(v[3]);

	glColor3f(0.0f, 01.0f, 0.0f);
	glVertex3fv(v[4]); // fundos
	glVertex3fv(v[5]);
	glVertex3fv(v[6]);
	glVertex3fv(v[7]);

	glColor3f(0.0f, 1.0f, 0.5f);
	glVertex3fv(v[0]); // esq
	glVertex3fv(v[3]);
	glVertex3fv(v[6]);
	glVertex3fv(v[5]);

	glColor3f(1.0f, 1.0f, 0.5f);
	glVertex3fv(v[3]); // topo
	glVertex3fv(v[2]);
	glVertex3fv(v[7]);
	glVertex3fv(v[6]);

	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3fv(v[1]); // dir
	glVertex3fv(v[4]);
	glVertex3fv(v[7]);
	glVertex3fv(v[2]);

	glColor3f(1.0f, 0.5f, 0.5f);
	glVertex3fv(v[1]); // base
	glVertex3fv(v[0]);
	glVertex3fv(v[5]);
	glVertex3fv(v[4]);

	glEnd();
}

// Função callback chamada para fazer o desenho
void desenha(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// gluLookAt(xC, yC, zC, xP, yP, zP, xU, yU, zU)
	gluLookAt(0.0, 0.0, Tela, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//void gluLookAt(GLdouble eyeX,  GLdouble eyeY,  GLdouble eyeZ,  GLdouble centerX,  GLdouble centerY,  GLdouble centerZ,  GLdouble upX,  GLdouble upY,  GLdouble upZ);

	//Esfera
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotated(Esfera1, 0, 1, 0); //Rotação sobre o eixo y da esfera
	glRotated(Esfera1 * 2, 1, 0, 0); //Rotação sobre o eixo x da esfera (dobro que em y)
	esfera(p, 2, 20);
	glPopMatrix();

	//Cone
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotated(Cone1, 0, 1, 0); //0.5 graus em y por quadro em torno da esfera
	glRotated(Cone1 * 3, 1, 0, 0); //1 grau em x por quadro em torno da esfera
	glTranslated(0, 0, 1); //Move o cone
	glutSolidCone(1.85, 5, 50, 50); //glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
	//glutWireCone(1.8, 4, 50, 50);
	glPopMatrix();

	//Cubo
	glPushMatrix();
	glRotated(Cubo1, 0, 0, 1); //Rotação sobre z no centro da esfera
	glTranslated(7, 0, 0); //7 de distância do centro da esfera
	glRotated(Cubo1, 1, 0, 0); //Rotação sobre seu eixo x
	//cubo2(CuboTamanho / 2, 0, 0, 0); //6 cores e variação de tamanho *Função cria um cubo com o dobro do tamanho, por isso /2
	cubo();
	glPopMatrix();

	// Executa os comandos OpenGL
	glutSwapBuffers();
	glFinish();
}

void repeticao() {
		
	if (altTamanhoCubo && CuboTamanho + 0.01 > 3){ 
		altTamanhoCubo = 0;
	}
	else if (altTamanhoCubo){ 
		CuboTamanho += 0.01;
	}
	if (!altTamanhoCubo && CuboTamanho - 0.01 < 1){ 
		altTamanhoCubo = 1;
	}
	else if (!altTamanhoCubo){
		CuboTamanho -= 0.01;
	}

	Cone1 += 0.5;
	Cubo1 += 0.5;
	Esfera1 += 0.5;
	
	if (moveTela && Tela + 0.2 > 50){ 
		moveTela = 0;
	}
	else if (moveTela){
		Tela += 0.2;
	}
	if (!moveTela && Tela - 0.2 < 20){
		moveTela = 1;
	}
	else if (!moveTela){
		Tela -= 0.2;
	}

	glutPostRedisplay();
}

void inicializa(void) {
	Cone1 = 0; 
	Cubo1 = 0; 
	Esfera1 = 0; 
	CuboTamanho = 1; 
	altTamanhoCubo = 0; 
	Tela = 20; 
	moveTela = 1;
	
	//Cores da esfera
	/*
	matCoresEsfera[0][0] = 1.0; 
	matCoresEsfera[0][1] = 0.0; 
	matCoresEsfera[0][2] = 0.0;
	
	matCoresEsfera[1][0] = 0.0; 
	matCoresEsfera[1][1] = 1.0; 
	matCoresEsfera[1][2] = 0.0;
	
	matCoresEsfera[2][0] = 0.0; 
	matCoresEsfera[2][1] = 0.0; 
	matCoresEsfera[2][2] = 1.0;
	
	matCoresEsfera[3][0] = 1.0; 
	matCoresEsfera[3][1] = 1.0; 
	matCoresEsfera[3][2] = 0.0;
	
	matCoresEsfera[4][0] = 0.0; 
	matCoresEsfera[4][1] = 1.0; 
	matCoresEsfera[4][2] = 1.0;
	* */

	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Habilita operação do teste do Z-buffer
	glEnable(GL_DEPTH_TEST);
	// Indica a função de teste
	glDepthFunc(GL_LESS);
}

void outraFunc(GLsizei w, GLsizei h) {
	// Evita a divisão por zero
	if (h == 0) h = 1;
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// gluPerspective(GLdouble fov, GLdouble aspect, GLdouble near, GLdouble far)
	gluPerspective(45, w/h, 1, 100);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	// GLUT_DEPTH para alocar Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Prova Edimar Junior");
	inicializa();
	glutIdleFunc(repeticao);
	glutDisplayFunc(desenha);
	glutReshapeFunc(outraFunc);
	glutMainLoop();
}
