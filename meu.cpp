/* Universidade Federal da Fronteira Sul - UFFS
 * Disciplina de Computação Gráfica - 2016/02
 * Professor	José Carlos Bins
 * Alunos 	Edimar Roque Martello Júnior - 1111100038
 *			Edirlan José Censi - 1211100030
*/
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

const double pi = 3.1415927;
GLUquadricObj *obj = gluNewQuadric();
GLint dir = 0;
GLint passo = 0;
GLint okay = 0;
GLint okay2= 0;  

GLint dirx = 0;
GLint diry = 0;
GLint passox = -35;
GLint passoy = 0;
GLfloat Tela, Esfera1, Cone1, Cubo1;
GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };
GLfloat n = 20;  //esfera cabeça
GLfloat alpha = 0.0;
GLfloat alpha2 = 0.0;
GLfloat alpha3 = 0.0;
GLfloat alphaRodas = 0.0;
GLfloat alphaHead = 0.0;


GLfloat betha = 0.0;

GLfloat x=0.0;
GLfloat y=0.0;
GLfloat angle=0.0;
GLfloat angle_stepsize=0.1;
GLfloat radius=0.0;
GLfloat height=0.0;
GLfloat xcubo=3.0;
GLfloat ycubo=1.3;
GLfloat zcubo=0.2;
GLdouble p[3] = { 0,0,0 }; //esfera cabeça
GLfloat v[8][3] = { {-xcubo,-ycubo,-zcubo}, {xcubo,-ycubo,-zcubo}, //Matriz de vértices para o skate
					{xcubo,ycubo,-zcubo}, {-xcubo,ycubo,-zcubo}, 
					{xcubo,-ycubo,zcubo}, {-xcubo,-ycubo,zcubo}, 
					{-xcubo,ycubo,zcubo}, {xcubo,ycubo,zcubo}};


//Funcao chamada para desenhar meia esfera, para a cabeca do boneco
void esfera(GLdouble *centro, GLdouble radius, GLfloat num) {
	glEnable(GL_NORMALIZE); //Habilitando a nomal
	GLdouble c, c2, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	GLdouble phi, theta, phi1, theta1, phi2, theta2;
	GLdouble senphi1, cosphi1, senphi2, cosphi2,
	         sentheta1, costheta1, sentheta2, costheta2,
	         passo;
	glNormal3d(centro[0], centro[1] + radius, centro[2]); //Calculando a normal
	glVertex3d(centro[0], centro[1] + radius, centro[2]); //Desenhando os vértices normalizados
	c = pi / 180;
	passo = 180 / num * c;
	glBegin(GL_TRIANGLES);
	phi1 = 0;
	senphi1 = sin(phi1);
	cosphi1 = cos(phi1);
	int i,j,k;
	for (i=0; i < num/2; i++) { //Desenhando meia esfera
		phi2 = phi1 + passo;
		senphi2 = sin(phi2);
		cosphi2 = cos(phi2);
		theta1 = 0;
		sentheta1 = sin(theta1);
		costheta1 = cos(theta1);
		k = 0;
		for (j = 0; j < 2 * num; j++) {
			
			//glColor3f(0.0, 1.0, 0.0); //Sem cor específica, voce pode escolher a cor do objeto na main
			theta2 = theta1 + passo;
			sentheta2 = sin(theta2); 
			costheta2 = cos(theta2);
			x1 = centro[0] + radius * senphi1 * costheta1;
			y1 = centro[1] + radius * senphi1 * sentheta1;
			z1 = centro[2] + radius * cosphi1;
			glNormal3d(x1, y1, z1); //Calculando a normal
			glVertex3d(x1, y1, z1); //Desenhando os vértices normalizados
			x2 = centro[0] + radius * senphi2 * costheta1;
			y2 = centro[1] + radius * senphi2 * sentheta1;
			z2 = centro[2] + radius * cosphi2;
			glNormal3d(x2, y2, z2); //Calculando a normal
			glVertex3d(x2, y2, z2); //Desenhando os vértices normalizados
			x3 = centro[0] + radius * senphi2 * costheta2;
			y3 = centro[1] + radius * senphi2 * sentheta2;
			z3 = centro[2] + radius * cosphi2;
			glNormal3d(x3, y3, z3); //Calculando a normal
			glVertex3d(x3, y3, z3); //Desenhando os vértices normalizados
			
			glNormal3d(x1, y1, z1); //Calculando a normal
			glVertex3d(x1, y1, z1); //Desenhando os vértices normalizados
			
			glNormal3d(x3, y3, z3); //Calculando a normal
			glVertex3d(x3, y3, z3);
			x4 = centro[0] + radius * senphi1 * costheta2;
			y4 = centro[1] + radius * senphi1 * sentheta2;
			z4 = centro[2] + radius * cosphi1;
			glNormal3d(x4, y4, z4); //Calculando a normal
			glVertex3d(x4, y4, z4); //Desenhando os vértices normalizados
			theta1 = theta2;
			sentheta1 = sentheta2;
			costheta1 = costheta2;
		}
		phi1 = phi2;
		senphi1 = senphi2;
		cosphi1 = cosphi2;
	}
	glEnd();
	glDisable(GL_NORMALIZE);
}

//Funcao chamada para desenhar um cubo que sera o shape do skate
void cubo() {
	glEnable(GL_NORMALIZE); //Habilitando a normal
	glBegin(GL_QUADS);

	//frente
	glNormal3fv(v[0]); 
	glVertex3fv(v[0]); 
	
	glNormal3fv(v[1]);
	glVertex3fv(v[1]);
	
	glNormal3fv(v[2]);
	glVertex3fv(v[2]);
	
	glNormal3fv(v[3]);
	glVertex3fv(v[3]);

	//fundos
	glNormal3fv(v[4]);
	glVertex3fv(v[4]);
	
	glNormal3fv(v[5]);
	glVertex3fv(v[5]);
	
	glNormal3fv(v[6]);
	glVertex3fv(v[6]);
	
	glNormal3fv(v[7]);
	glVertex3fv(v[7]);

	//esquerda
	glNormal3fv(v[0]);
	glVertex3fv(v[0]);
	
	glNormal3fv(v[3]);
	glVertex3fv(v[3]);
	
	glNormal3fv(v[6]);
	glVertex3fv(v[6]);
	
	glNormal3fv(v[5]);
	glVertex3fv(v[5]);

	//topo
	glNormal3fv(v[3]);
	glVertex3fv(v[3]);
	
	glNormal3fv(v[2]);
	glVertex3fv(v[2]);
	
	glNormal3fv(v[7]);
	glVertex3fv(v[7]);
	
	glNormal3fv(v[6]);
	glVertex3fv(v[6]);

	//direita
	glNormal3fv(v[1]);
	glVertex3fv(v[1]);
	
	glNormal3fv(v[4]);
	glVertex3fv(v[4]);
	
	glNormal3fv(v[7]);
	glVertex3fv(v[7]);
	
	glNormal3fv(v[2]);
	glVertex3fv(v[2]);

	//base
	glNormal3fv(v[1]);
	glVertex3fv(v[1]);
	
	glNormal3fv(v[0]);
	glVertex3fv(v[0]);
	
	glNormal3fv(v[5]);
	glVertex3fv(v[5]);
	
	glNormal3fv(v[4]);
	glVertex3fv(v[4]);

	glEnd();
	glDisable(GL_NORMALIZE);
}

//Funcao chamada para desenhar um boneco Android
void draw_Android(){
	
	//PuchMatrix do Boneco
	glPushMatrix();

		//Desenhando o tronco principal
		glColor3f(0.0f, 1.0f, 0.0f);
		glTranslatef(0.0, -3.0, 0.0);
		glRotated(-90, 1, 0, 0); //Rotação sobre o eixo x do boneco deixando ele de pé
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
			glTranslatef(0.0, 0.0, 0.3);
			glutSolidSphere(2.0, 50.0, 50.0);
		glPopMatrix();
	
		//Desenhando o pescoço branco
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(0.0, 0.0, 3.5);
			//glTranslatef(0.0, 0.0, 4.5);
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
				glTranslatef(2.5, 0.0, 4.0); 
				glRotatef(alpha3-=1.0, -1.0, 0.0, 0.0);		//Faz o movimento do braço
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
			glPopMatrix();//termina o Cilindro do braço
		glPopMatrix(); //Termina o braço direito
	
		//Desenhando o braço esquerdo
		glPushMatrix();
			//Desenhando a ligação do braço esquerdo
			glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(-2.5, 0.0, 4.0); 
				glRotatef(90.0, 0.0, 1.0, 0.0);
				gluCylinder(obj, 0.3, 0.3, 1, 50, 50);
			glPopMatrix();
		
			//Cilindro do braço
			glPushMatrix();
				glColor3f(0.0f, 1.0f, 0.0f);
				glTranslatef(-2.5, 0.0, 4.0); 
				
				glRotatef(-180, -1.0, 0.0, 0.0);		//Faz o movimento do braço
				glRotatef(alpha2+=1.0, -1.0, 0.0, 0.0);		//Faz o movimento do braço
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
					glutSolidSphere(0.4, 50.0, 50.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix(); //Termina o braço esquerdo

		//Desenhando a perna esquerda
		glPushMatrix();
			//Cilindro da perna
			glPushMatrix();
				glColor3f(0.0f, 1.0f, 0.0f);
				glTranslatef(-0.7, -0.5, -0.5); 
				glRotatef(-180.0, 1.0, 0.0, 0.0);
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
		glPopMatrix(); //Termina a perna esquerda

		//Desenhando a perna direita
		glPushMatrix();
			//Cilindro da perna
			glPushMatrix();
				glColor3f(0.0f, 1.0f, 0.0f);
				glTranslatef(0.7, -0.5, -0.5); 
				glRotatef(-180.0, 1.0, 0.0, 0.0);
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
		glPopMatrix(); //Termina a perna direita
	
		//Desenhar cabeça
		glPushMatrix();
			glTranslatef(0.0, 0.0, 5.5);
			//glRotatef(alphaHead+=1.5, 0.0, 0.0, 1.0);
		
		esfera(p, 2.0, 20);	
		if( alphaHead <= 10.0 && okay2 == 0){
			glRotatef(alphaHead+=0.5, 0.0, 0.0, 1.0);
		}else{
		  okay2=1;
		  glRotatef(alphaHead-=0.5, 0.0, 0.0, 1.0);
		  if(alphaHead <= -10.0 ) okay2=0;
		}
			//Desenhando o olho esquerdo
			glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(0.6, -1.3, 1.2);
				glutSolidSphere(0.25, 50.0, 50.0);
			glPopMatrix();
			
			//Desenhando o olho direito
			glPushMatrix();	
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(-0.6, -1.3 , 1.2);
				glutSolidSphere(0.25, 50.0, 50.0);
			glPopMatrix();
		
		//Desenhando as antenas
		glPushMatrix(); 
			//Desenhando a antena esquerda
			glPushMatrix(); 
				glColor3f(0.0f, 1.0f, 0.0f);
				glTranslatef(-1.0, 0.0, 1.5); 
				glRotatef(-25.0, 0.0, 1.0, 0.0);
				gluCylinder(obj, 0.1, 0.1, 1, 50, 50);

				//Esfera de baixo
				glPushMatrix();
					glColor3f(0.0f, 1.0f, 0.0f);
					glTranslatef(0.0, 0.0, 1.0);
					glutSolidSphere(0.1, 50.0, 50.0);
				glPopMatrix();
			glPopMatrix();
			
			//Desenhando a antena direita
			glPushMatrix(); 
				glColor3f(0.0f, 1.0f, 0.0f);
				glTranslatef(1.0, 0.0, 1.5); 
				glRotatef(25.0, 0.0, 1.0, 0.0);
				gluCylinder(obj, 0.1, 0.1, 1, 50, 50);

				//Esfera de baixo
				glPushMatrix();
					glColor3f(0.0f, 1.0f, 0.0f);
					glTranslatef(0.0, 0.0, 1.0);
					glutSolidSphere(0.1, 50.0, 50.0);
				glPopMatrix();
			glPopMatrix();
		 glPopMatrix();
		glPopMatrix();
		//Desenhando o Skate
		glPushMatrix();
			//Shape
			glPushMatrix();
				glColor3f(0.1f, 0.1f, 0.1f);
				glTranslatef(0.0, 0.0, -3.4);
				cubo();
			
				//Rodinha 1
				glPushMatrix();
					//glColor3f(0.1f, 0.1f, 0.1f);
					glColor3f(1.0f, 0.1f, 0.1f);
					glTranslatef(-2.5, 0.7, -0.5);
					glRotatef(alphaRodas+=10.0, 1.0, 0.0, 0.0);
					glutSolidSphere(0.25, 50.0, 50.0);
				glPopMatrix();
				
				//Rodinha 2
				glPushMatrix();
					//glColor3f(0.1f, 0.1f, 0.1f);
					glColor3f(1.0f, 0.1f, 0.1f);
					glTranslatef(-2.5, -0.7, -0.5);
					glRotatef(alphaRodas+=10.0, 1.0, 0.0, 0.0);
					glutSolidSphere(0.25, 50.0, 50.0);
				glPopMatrix();
				
				//Rodinha 3
				glPushMatrix();
					//glColor3f(0.1f, 0.1f, 0.1f);
					glColor3f(1.0f, 0.1f, 0.1f);
					glTranslatef(2.5, 0.7, -0.5);
					glRotatef(alphaRodas+=10.0, 1.0, 0.0, 0.0);
					glutSolidSphere(0.25, 50.0, 50.0);				
				glPopMatrix();
				
				//Rodinha 4
				glPushMatrix();
					glColor3f(1.0f, 0.1f, 0.1f);
					glTranslatef(2.5, -0.7, -0.5);
					glRotatef(alphaRodas+=10.0, 1.0, 0.0, 0.0);
					glutSolidSphere(0.25, 50.0, 50.0);			
				glPopMatrix();
			glPopMatrix();
			
			
		glPopMatrix();//Termina o Skate

		
		
	glColor3f(0.0f, 1.0f, 0.0f);
	glPopMatrix(); //Termina o Boneco	
	
	
}

// Funcao callback chamada para fazer o desenho
void draw(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	gluLookAt(0.0, 0.0, Tela, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//posicaoLuz[2]=Tela;
	
	
	//Desenhando o boneco Android
	glPushMatrix();		
		
		if( alpha <= 10.0 && okay == 0){
			glTranslatef(alpha+=0.15, 0.0,0.0);
			glRotatef(betha+=0.2, 0.0,1.0,0.0);
		}else{
		  okay=1;
		  glTranslatef(alpha-=0.15, 0.0,0.0);
		  glRotatef(betha-=0.2, 0.0,1.0,0.0);
		  if(alpha <= -10.0 ) okay=0;
		}
		draw_Android();
		
	glPopMatrix();
	
	

	// Executa os comandos OpenGL
	glutSwapBuffers();
	glFinish();
}

void redraw(int)
{
    glutPostRedisplay();
    draw();
    glutTimerFunc(40,redraw,1);

}

void init(void) {
	Esfera1 = 0;  
	Tela = 30; //distancia da camera 
	
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
	glutInitWindowSize(1000, 600);
	//glutInitWindowPosition(50, 50);
	glutCreateWindow("Trabalho 1 - Boneco Android");
	init();
	glutTimerFunc(40,redraw,1);
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);

	glutMainLoop();
}
