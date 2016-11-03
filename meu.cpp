/* Universidade Federal da Fronteira Sul - UFFS
 * Disciplina de Computação Gráfica - 2016/02
 * Professor	José Carlos Bins
 * Alunos 	Edimar Roque Martello Júnior - 1111100038 - Noturno
 *			Edirlan José Censi - 1211100030 - Matutino
*/
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "BCommandLine.h"

#define MAXTEXTURES 1

const double pi = 3.1415927;
GLUquadricObj *obj = gluNewQuadric();
GLint Pause = 0;
GLint dir = 0;
GLint passo = 0;
GLint okay = 0;
GLint okay2= 0;  
GLint okayShape= 0;  
GLint okayBracoDir= 0;  
GLint okayBracoEsq= 0;  
GLint okayPernaDir= 0;  
GLint okayPernaEsq= 0;  
GLint dirx = 0;
GLint diry = 0;
GLint passox = -35;
GLint passoy = 0;
GLfloat Esfera1, Cone1, Cubo1;
GLfloat n = 20;  //esfera cabeça
GLfloat alpha = 0.0;
GLfloat alpha2 = 0.0;
GLfloat alpha3 = 0.0;
GLfloat alphaRodas = 0.0;
GLfloat alphaHead = 0.0;
GLfloat alphaShape = 0.0;
GLfloat alpha4 = 0.0;
GLfloat alphaBracoDir = 0.0;
GLfloat alphaBracoEsq = 0.0;
GLfloat alphaPernaDir = 0.0;
GLfloat alphaPernaEsq = 0.0;
GLfloat TelaX, TelaY, TelaZ, TelaInit;
GLfloat betha = 0.0;
GLfloat x=0.0;
GLfloat y=0.0;
GLfloat angle=0.0;
GLfloat angle_stepsize=0.1;
GLfloat radius=0.0;
GLfloat height=0.0;
GLfloat xcubo=3.0;
GLfloat ycubo=1.3;
GLfloat zcubo=0.1;
GLdouble p[3] = { 0,0,0 }; //esfera cabeça
double matCoresEsfera[5][3] = {{0.1, 0.1, 0.1}, {0.3, 0.3, 0.3}, {0.1, 0.1, 0.1}, {0.3, 0.3, 0.3}, {0.1, 0.1, 0.1}};
GLfloat v[8][3] = { {-xcubo,-ycubo,-zcubo}, {xcubo,-ycubo,-zcubo}, //Matriz de vértices para o skate
					{xcubo,ycubo,-zcubo}, {-xcubo,ycubo,-zcubo}, 
					{xcubo,-ycubo,zcubo}, {-xcubo,-ycubo,zcubo}, 
					{-xcubo,ycubo,zcubo}, {xcubo,ycubo,zcubo}};

//Funcao chamada para carregar imagem para textura
unsigned char *  loadBMP_custom(const char *, unsigned int&, unsigned int&);

//Funcao chamada para desenhar esfera colorida para as rodas, para exibir a roda rotacionando
void rodas(GLdouble *centro, GLdouble radius, GLfloat num) {
	glEnable(GL_NORMALIZE); //Habilitando a nomal
	GLdouble c, c2, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	GLdouble phi, theta, phi1, theta1, phi2, theta2;
	GLdouble senphi1, cosphi1, senphi2, cosphi2,
	         sentheta1, costheta1, sentheta2, costheta2,
	         passo;
	glNormal3d(centro[0], centro[1] + radius, centro[2]);
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
			glNormal3d(x1, y1, z1);
			glVertex3d(x1, y1, z1);
			x2 = centro[0] + radius * senphi2 * costheta1;
			y2 = centro[1] + radius * senphi2 * sentheta1;
			z2 = centro[2] + radius * cosphi2;
			glNormal3d(x2, y2, z2);
			glVertex3d(x2, y2, z2);
			x3 = centro[0] + radius * senphi2 * costheta2;
			y3 = centro[1] + radius * senphi2 * sentheta2;
			z3 = centro[2] + radius * cosphi2;
			glNormal3d(x3, y3, z3);
			glVertex3d(x3, y3, z3);
			
			glNormal3d(x1, y1, z1);
			glVertex3d(x1, y1, z1);
			
			glNormal3d(x3, y3, z3);
			glVertex3d(x3, y3, z3);
			x4 = centro[0] + radius * senphi1 * costheta2;
			y4 = centro[1] + radius * senphi1 * sentheta2;
			z4 = centro[2] + radius * cosphi1;
			glNormal3d(x4, y4, z4);
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
	glDisable(GL_NORMALIZE);
}

//Funcao chamada para desenhar meia esfera, para a cabeca do boneco
void head(GLdouble *centro, GLdouble radius, GLfloat num) {
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
void shape(){
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

/* Funcao chamada para desenhar um boneco Android
 * Desenha os tronco, bracos, pernas, cabeca, olhos e antenas
 * Tambem faz os movimentos dos membros*/
void draw_Android(){
	
	glEnable(GL_NORMALIZE); //Habilitando a nomal
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
					glNormal3f(x, y , height);
					glVertex3f(x, y , height);//A posição da tampa
					angle = angle + angle_stepsize;
				}
				glNormal3f(radius, 0.0, height);
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
				//glRotatef(alpha3-=1.0, -1.0, 0.0, 0.0);		//Faz o movimento do braço
				
				// if e else para mecher o braço para cima e para baixo
				if(Pause==1){
					glRotatef(alphaBracoDir, 1.0, 0.0, 0.0);
				}
				if( alphaBracoDir <= 180.0 && okayBracoDir == 0 && Pause==0){
					glRotatef(alphaBracoDir+=1.0, 1.0, 0.0, 0.0);
				}else{
				  if(Pause==0){
					  okayBracoDir=1;
					  glRotatef(alphaBracoDir-=1.0, 1.0, 0.0, 0.0);
					  if(alphaBracoDir <= 0.0 ) okayBracoDir=0;
				  }
				}
				
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
				
				glRotatef(-180, -1.0, 0.0, 0.0);		//Rotaciona primeiro para movimentar ao contrário
				//glRotatef(alpha2+=1.0, -1.0, 0.0, 0.0);		//Faz o movimento do braço
				
				// if e else para mecher o braço para baixo e para cima (ao contrario da outra)
				if(Pause==1){
					glRotatef(alphaBracoEsq, 1.0, 0.0, 0.0);
				}
				if( alphaBracoEsq <= 0.0 && okayBracoEsq == 0 && Pause ==0){
					glRotatef(alphaBracoEsq+=1.0, 1.0, 0.0, 0.0);
				}else{
					if(Pause==0){
						okayBracoEsq=1;
						glRotatef(alphaBracoEsq-=1.0, 1.0, 0.0, 0.0);
						if(alphaBracoEsq <= -180.0 ) okayBracoEsq=0;
					}
				}
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
				glTranslatef(-0.7, 0.0, -0.5); 
				glRotatef(-180.0, 1.0, 0.0, 0.0);
				
				// if e else para mecher a perna
				if(Pause==1){
					glRotatef(alphaPernaEsq, 0.0, 1.0, 0.0);
				}
				if( alphaPernaEsq <= 10.0 && okayPernaEsq == 0 && Pause==0){
					glRotatef(alphaPernaEsq+=0.5, 0.0, 1.0, 0.0);
				}else{
					if(Pause==0){
					  okayPernaEsq=1;
					  glRotatef(alphaPernaEsq-=0.5, 0.0, 1.0, 0.0);
					  if(alphaPernaEsq <= -10.0 ) okayPernaEsq=0;
					 }
				}
				
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
				glTranslatef(0.7, 0.0, -0.5); 
				glRotatef(-180.0, 1.0, 0.0, 0.0);
				
				// if e else para mecher a perna direita
				if(Pause==1){
					glRotatef(alphaPernaDir, 0.0, 1.0, 0.0);
				}
				if( alphaPernaDir <= 10.0 && okayPernaDir == 0 && Pause==0){
					glRotatef(alphaPernaDir+=0.5, 0.0, 1.0, 0.0);
				}else{
					if(Pause==0){
					  okayPernaDir=1;
					  glRotatef(alphaPernaDir-=0.5, 0.0, 1.0, 0.0);
					  if(alphaPernaDir <= -10.0 ) okayPernaDir=0;
					 }
				}
				
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
			// if e else para mecher a cabeça para os lados
			if(Pause==1){
					glRotatef(alphaHead, 0.0, 0.0, 1.0);
			}
			if( alphaHead <= 25.0 && okay2 == 0 && Pause==0){
				glRotatef(alphaHead+=1.0, 0.0, 0.0, 1.0);
			}else{
			   if(Pause==0){
				  okay2=1;
				  glRotatef(alphaHead-=1.0, 0.0, 0.0, 1.0);
				  if(alphaHead <= -25.0 ) okay2=0;
				}
			}
			head(p, 2.0, 20);
			
			//Fechar a base da esfera da cabeça
			glPushMatrix();
				glBegin(GL_POLYGON);
					glColor3f(0.0f, 1.0f, 0.0f);
					radius=2.0;
					height=5.0;
					angle = 0.0;
					while( angle < 2*pi ) {
						x = radius * cos(angle);
						y = radius * sin(angle);
						glVertex3f(x, y , 0.0);//A posição da tampa
						angle = angle + angle_stepsize;
					}
				glEnd();
			glPopMatrix();
			
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
				glColor3f(0.2f, 0.2f, 0.2f);
				//glTranslatef(0.0, 0.0, -3.4);
				
				// if e else para mecher o skate junto com a perna
				if(Pause==1){
						glTranslatef(alpha4, 0.0, -3.4);
						glRotatef(alphaShape, 0.0, 1.0, 0.0);
				}
				if( alphaShape <= 10.0 && okayShape == 0 && Pause==0){
					glRotatef(alphaShape+=0.5, 0.0, 1.0, 0.0);
					glTranslatef(alpha4+=0.05, 0.0, -3.4);
				}else{
					if(Pause==0){
					  okayShape=1;
					  glRotatef(alphaShape-=0.5, 0.0, 1.0, 0.0);
					  glTranslatef(alpha4-=0.05, 0.0, -3.4);
					  if(alphaShape <= -10.0 ) okayShape=0;
					}
				}
				shape();
			
				//Rodinha 1
				glPushMatrix();
					//glColor3f(0.1f, 0.1f, 0.1f);
					glColor3f(1.0f, 0.1f, 0.1f);
					glTranslatef(-2.5, 0.7, -0.5);
					if (Pause==0) glRotatef(alphaRodas+=0.5, 1.0, 1.0, 0.0);
					if (Pause==1) glRotatef(alphaRodas, 1.0, 1.0, 0.0);
					//glutSolidSphere(0.25, 50.0, 50.0);
					rodas(p, 0.4, 20);
				glPopMatrix();
				
				//Rodinha 2
				glPushMatrix();
					//glColor3f(0.1f, 0.1f, 0.1f);
					glColor3f(1.0f, 0.1f, 0.1f);
					glTranslatef(-2.5, -0.7, -0.5);
					if (Pause==0) glRotatef(alphaRodas+=0.5, 1.0, 1.0, 0.0);
					if (Pause==1) glRotatef(alphaRodas, 1.0, 1.0, 0.0);
					//glutSolidSphere(0.25, 50.0, 50.0);
					rodas(p, 0.4, 20);
				glPopMatrix();
				
				//Rodinha 3
				glPushMatrix();
					//glColor3f(0.1f, 0.1f, 0.1f);
					glColor3f(1.0f, 0.1f, 0.1f);
					glTranslatef(2.5, 0.7, -0.5);
					if (Pause==0) glRotatef(alphaRodas+=0.5, 1.0, 1.0, 0.0);
					if (Pause==1) glRotatef(alphaRodas, 1.0, 1.0, 0.0);
					//glutSolidSphere(0.25, 50.0, 50.0);
					rodas(p, 0.4, 20);				
				glPopMatrix();
				//Rodinha 4
				glPushMatrix();
					glColor3f(1.0f, 0.1f, 0.1f);
					glTranslatef(2.5, -0.7, -0.5);
					if (Pause==0) glRotatef(alphaRodas+=0.5, 1.0, 1.0, 0.0);
					if (Pause==1) glRotatef(alphaRodas, 1.0, 1.0, 0.0);
					//glutSolidSphere(0.25, 50.0, 50.0);
					rodas(p, 0.4, 20);			
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();//Termina o Skate
		
	glColor3f(0.0f, 1.0f, 0.0f);
	glPopMatrix(); //Termina o Boneco	

	glDisable(GL_NORMALIZE);	
}

//Funcao que desenha um sol ao fundo com a segunda iluminacao
void sol(void){
	glPushMatrix();
		glColor3f(255.0f, 255.0f, 0.0f);
		glTranslatef(-20.0, 20.0, -20.0);
		glutSolidSphere(2.0, 50.0, 50.0);
	glPopMatrix();
}
	
/*Funcao callback chamada para desenhar o quadro
 * Faz a chamada das demais funcoes para unir e formar o desenho
 * Faz movimentos para os lados
 * Cria uma textura para o chão*/
void draw(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//void gluLookAt(GLdouble eyeX,  GLdouble eyeY,  GLdouble eyeZ,  GLdouble centerX,  GLdouble centerY,  GLdouble centerZ,  GLdouble upX,  GLdouble upY,  GLdouble upZ);
	gluLookAt(TelaX, TelaY, TelaInit, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//Aplicando textura em um quadrado para o chão para o boneco
	glPushMatrix();
		glTranslatef(0.0, -7.7, 0.0);
		glRotatef(-80, 1.0,0.0,0.0);
		glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			glTexCoord2f(-50,50);
			glVertex2i(-50,50);
			glTexCoord2f(-50,-50);
			glVertex2i(-50,-50);
			glTexCoord2f(50,-50);
			glVertex2i(50,-50);
			glTexCoord2f(50,50);
			glVertex2i(50,50);
			glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Desenhando o boneco Android
	glPushMatrix();		
		if(Pause==1){
			glTranslatef(alpha,0.0,0.0);
			glRotatef(betha, 0.0,1.0,0.0);
		}
		if( alpha <= 20.0 && okay == 0 && Pause==0){
			glTranslatef(alpha+=0.15, 0.0,0.0);
			glRotatef(betha+=0.2, 0.0,1.0,0.0);
		}else{
			if(Pause==0){
			  okay=1;	
			  glTranslatef(alpha-=0.15, 0.0,0.0);
			  glRotatef(betha-=0.2, 0.0,1.0,0.0);
			  if(alpha <= -20.0 ) okay=0;
			}
		}
		draw_Android();
	glPopMatrix();
	
	sol();
	// Executa os comandos OpenGL
	glutSwapBuffers();
	glFinish();
}

//Funcao chamada para iterações com o teclado
void keys(unsigned char key, int x, int y){
	switch (key){
	case 'w': //para cima
		TelaY+=1;   
		break;
	case 's': //para baixo
		TelaY-=1;  
		break;
	case 'a': //para esquerda
		TelaX-=1;
		break;
	case 'd': //para direita
		TelaX+=1;
		break;
	case 'q': // menos profundidade
		TelaZ-=1;
		break;
	case 'e': // menos profundidade
		TelaZ+=1;
		break;
	case 'o': //mais zoom
		TelaInit-=1;
		break;
	case 'p': //menos zoom
		TelaInit+=1;
		break;
	case 'i': //volta ao inicio
		TelaInit = 60.0; //distancia da camera 
		TelaX = 0.0;
		TelaY = 0.0;  
		TelaZ = 0.0; 
		break;
	case 'm':
		Pause = 1;
	break;
	
	case 'n':
		Pause = 0;
	break;
	
	}
}

//Funcao chamada para redesenhar e tambem para delay
void redraw(int){
    glutPostRedisplay();
    draw();
    glutTimerFunc(40,redraw,1);

}

/*Funcao dos valores inicial
 * Seta a posição da camera
 * Cria as duas fontes de iluminacao
 * Seta as variaveis para usar textura, carrega imagem
 * Habilita o z-buffer */
void init(void){
	TelaInit = 60.0; //distancia da camera 
	TelaX = 0.0;
	TelaY = 0.0;  
	TelaZ = 0.0; 
	
	//Iluminacao 1 - padrao
	GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4] = { 0.5,0.5,0.5,1.0 };	   // "Cor Branca do vizualizador
	GLfloat luzEspecular[4] = { 0.5,0.5,0.5, 1.0 };// "brilho"
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };
	
	//Iluminacao 2 - Sol
	GLfloat luzAmbiente2[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa2[4] = { 1.0,1.0,0.0,1.0 }; // "Cor Amarelo do Sol
	GLfloat luzEspecular2[4] = { 0.7,0.7,0.7, 1.0 };// "brilho"
	GLfloat posicaoLuz2[4] = { -20.0, 20.0, -20.0, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLfloat especularidade2[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 5;
	GLint especMaterial2 = 10;
	
	//tem a cor de fundo
	
	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);
	
	// Define a reflet�ncia do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade2);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial2);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente2);

	// Define os par�metros da luz de n�mero 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz);

	// Define os par�metros da luz de n�mero 2
	glLightfv(GL_LIGHT2, GL_AMBIENT, luzAmbiente2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, luzDifusa2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luzEspecular2);
	glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuz2);

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 1
	glEnable(GL_LIGHT1);
	// Habilita a luz de n�mero 2
	glEnable(GL_LIGHT2);
	
	//TEXTURA
	// carrega a uma imagem
	unsigned int ih=0, iw=0;
	unsigned char * texture = NULL;
	texture = loadBMP_custom("asfalto1.bmp", iw, ih);
	glShadeModel(GL_SMOOTH);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLuint texnum[MAXTEXTURES];
	// Define a textura corrente
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, texnum);
	glBindTexture(GL_TEXTURE_2D, texnum[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iw, ih, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture);
	gluBuild2DMipmaps(texnum[0], GL_RGB, iw, ih, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	delete texture;
	glEnable(GL_TEXTURE_2D);

	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	// Habilita operação do teste do Z-buffer
	glEnable(GL_DEPTH_TEST);
	// Indica a função de teste
	glDepthFunc(GL_LESS);
}

/*Especifica o tamanho da janela
 *Inicializa o sistema de coordenadas da projecao
 *Especifica e inicializa o sistema de coordenadas do modelo*/
void reshape(GLsizei w, GLsizei h){
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

// Funcao main(principal)
int main(int argc, char **argv){
	glutInit(&argc, argv);
	// GLUT_DEPTH para alocar Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Trabalho 1 - Boneco Android");
	init();
	glutKeyboardFunc(keys);
	glutTimerFunc(40,redraw,1);
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);

	glutMainLoop();
}
