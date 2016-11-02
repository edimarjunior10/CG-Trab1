/* Universidade Federal da Fronteira Sul - UFFS
 * Disciplina de Computação Gráfica - 2016/02
 * Professor José Carlos Bins
 * Alunos 	Edimar Roque Martello Júnior - 1111100038
 *			Edirlan Cenci - matriculaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
 *
 * 
 * 
 * TIRAR OS DEMAIS COMENTARIOS DO CODIGO E REMOVER O CUBO2
 * 
*/
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

const double pi = 3.1415927;
int altTamanhoCubo, moveTela; 
double CuboTamanho;
GLfloat Tela, Esfera1, Cone1, Cubo1;
GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };
GLdouble p[3] = { 0,0,0 };
GLfloat alpha = 0.0;
GLUquadricObj *obj = gluNewQuadric();
GLfloat x=0.0;
GLfloat y=0.0;
GLfloat angle=0.0;
GLfloat angle_stepsize=0.1;
GLfloat radius=0.0;
GLfloat height=0.0;




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
	for (i=0; i < num; i++) {
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
void draw(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	gluLookAt(0.0, 0.0, Tela, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//posicaoLuz[2]=Tela;

	//PuchMatrix do Boneco
	glPushMatrix();
	
		//Desenhando o tronco principal
		glColor3f(0.0f, 1.0f, 0.0f);
		glTranslatef(0.0, -5.0, 0.0);
		glRotated(Esfera1, 0, 1, 0); //Rotação sobre o eixo y da esfera
		glRotated(Esfera1 * 2, 1, 0, 0); //Rotação sobre o eixo x da esfera (dobro que em y)
		//glRotatef(-80.0, 1.0, 0.0, 0.0);
		gluCylinder(obj, 2.0, 2, 5, 50, 50);
			
		//Fechar o topo do cilindro
		glPushMatrix();
			glBegin(GL_POLYGON);
				glColor3f(0.0f, 1.0f, 0.0f);
				radius=2.0;
				height=5.0;//tem que ser o mesmo do cilindo desenhado anteriormente
				angle = 0.0;
				while( angle < 2*pi ) {
					x = radius * cos(angle);
					y = radius * sin(angle);
					glVertex3f(x, y , height);//A posição da tampa
					angle = angle + angle_stepsize;
				}
				glVertex3f(radius, 0.0, height);
			glEnd();
		glPopMatrix();
			
		//Fechar a base do cilindro
		glPushMatrix();
			glColor3f(0.0f, 1.0f, 0.0f);
			//glTranslatef(0.0, 0.0, 0.3);
			glutSolidSphere(2.0, 50.0, 50.0);
		glPopMatrix();
	
		//Desenhando o pescoço branco
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(0.0, 0.0, 3.5);
			gluCylinder(obj, 1.8, 1.8, 2, 50, 50);
		glPopMatrix();
		
		//Desenhando o braço direito
		glPushMatrix();
		
			//Desenhando a ligação do braço direito
			glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(1.5, 0.0, 4.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				gluCylinder(obj, 0.3, 0.3, 1, 50, 50);
			glPopMatrix();
		
			//Cilindro do braço
			glPushMatrix();
				glColor3f(0.0f, 1.0f, 0.0f);
				glTranslatef(2.5, 0.0, 2.0);
				gluCylinder(obj, 0.4, 0.4, 2.5, 50, 50);
			
				//Esfera de cima
				glPushMatrix();
					glColor3f(0.0f, 1.0f, 0.0f);
					glTranslatef(0.0, 0.0, 2.5);
					glutSolidSphere(0.4, 50.0, 50.0);
				glPopMatrix();
				
				//Esfera de baixo
				glPushMatrix();
					glColor3f(0.0f, 1.0f, 0.0f);
					glTranslatef(0.0, 0.0, 0.0);
					glutSolidSphere(0.4, 50.0, 50.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix(); //Termina o braço direito
	
	
	
	
	glPopMatrix(); //Termina o Boneco


	// Executa os comandos OpenGL
	glutSwapBuffers();
	glFinish();
}

void idle() {
		
	/*if (altTamanhoCubo && CuboTamanho + 0.01 > 3){ 
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
	}*/

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

void init(void) {
	Cone1 = 0; 
	Cubo1 = 0; 
	Esfera1 = 0; 
	CuboTamanho = 1; 
	altTamanhoCubo = 0; 
	Tela = 20; 
	moveTela = 1;
	
	GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4] = { 0.5,0.5,0.5,1.0 };	   // "cor"
	GLfloat luzEspecular[4] = { 0.7,0.7,0.7, 1.0 };// "brilho"
	//GLfloat posicaoLuz[4] = { 50.0, Tela, 50.0, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 10;
	
	//tem a cor de fundo
	
	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);
	
	// Define a reflet�ncia do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz);

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT1);
	

	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	// Habilita operação do teste do Z-buffer
	glEnable(GL_DEPTH_TEST);
	// Indica a função de teste
	glDepthFunc(GL_LESS);
}

void reshape(GLsizei w, GLsizei h) {
	// Evita a divisão por zero
	if (h == 0) h = 1;
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	// Inicializa o sistema de coordenadas da projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas da projeção
	glLoadIdentity();
	
	// gluPerspective(GLdouble fov, GLdouble aspect, GLdouble near, GLdouble far)
	gluPerspective(45, w/h, 1, 100);
	
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();	
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	// GLUT_DEPTH para alocar Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	//glutInitWindowPosition(50, 50);
	glutCreateWindow("Trabalho 1 - Boneco Android");
	init();
	glutIdleFunc(idle);
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
