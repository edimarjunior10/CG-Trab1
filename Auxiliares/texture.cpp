// Texturas
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "BCommandLine.h"

#define MAXTEXTURES 1
#define MAP_DEFAULT 2
#define MAP_AUTO 1
#define MAP_MANUAL 2
#define OBJ_DEFAULT 2
#define OBJ_ESFERA 1
#define OBJ_CUBO 2

const double pi = 3.1415926;

GLdouble p[3] = { 0,0,0 };

char * infile;
float angtex, angobjx, angobjy, angobjz;
float ctex_ix, ctex_iy, ctex_fx, ctex_fy;
int objeto, map;
GLuint id;
GLfloat especular[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat vert[8][3] = { { -2.0,-2.0,2.0 },{ -2.0, 2.0, 2.0 } ,{ 2.0,2.0,2.0 },{ 2.0,-2.0,2.0 },{ -2.0,-2.0,-2.0 },{ -2.0,2.0,-2.0 },{ 2.0,2.0,-2.0 },{ 2.0,-2.0,-2.0 } };


unsigned char *  loadBMP_custom(const char *, unsigned int&, unsigned int&);

// Fun??o Esfera: aproxima??o usando quadrilateros
// E as formulas:
// x(theta,phi) = r seno(phi) coseno(theta)
// y(theta,phi) = r seno(phi) seno(theta)
// z(theta,phi) = r coseno(phi)
void esfera(GLdouble *centro, GLdouble radius, GLfloat num) {
	GLdouble c, c2, x, y, z, s1, s2, t1, t2;
	GLdouble phi, theta, phi1, theta1, phi2, theta2;
	GLdouble senphi1, cosphi1, senphi2, cosphi2,
	         sentheta1, costheta1, sentheta2, costheta2,
					 passo;

	GLfloat dx = ctex_fx - ctex_ix;
	GLfloat dy = ctex_fy - ctex_iy;
	c = pi / 180;
	passo = 180 / num * c;

	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUADS);
	phi1 = 0;
	senphi1 = sin(phi1);
	cosphi1 = cos(phi1);
	int i,j;
	for (i=0; i < num; i++) {
		phi2 = phi1 + passo;
		senphi2 = sin(phi2);
		cosphi2 = cos(phi2);
		theta1 = 0;
		sentheta1 = sin(theta1);
		costheta1 = cos(theta1);
		for (j=0; j < 2 * num; j++) {
			theta2 = theta1 + passo;
			sentheta2 = sin(theta2);
			costheta2 = cos(theta2);
			s1 = ctex_fx - theta1 / (2 * pi) * dx;
			s2 = ctex_fx - theta2 / (2 * pi) * dx;
			t1 = ctex_iy + phi1 / pi * dy;
			t2 = ctex_iy + phi2 / pi * dy;
			x = centro[0] + radius * senphi1 * costheta1;
			y = centro[1] + radius * senphi1 * sentheta1;
			z = centro[2] + radius * cosphi1;
			glTexCoord2f(s1, t1);
			glVertex3d(y, x, -z);
			x = centro[0] + radius * senphi2 * costheta1;
			y = centro[1] + radius * senphi2 * sentheta1;
			z = centro[2] + radius * cosphi2;
			glTexCoord2f(s1, t2);
			glVertex3d(y, x, -z);
			x = centro[0] + radius * senphi2 * costheta2;
			y = centro[1] + radius * senphi2 * sentheta2;
			z = centro[2] + radius * cosphi2;
			glTexCoord2f(s2, t2);
			glVertex3d(y, x, -z);
			x = centro[0] + radius * senphi1 * costheta2;
			y = centro[1] + radius * senphi1 * sentheta2;
			z = centro[2] + radius * cosphi1;
			glTexCoord2f(s2, t1);
			glVertex3d(y, x, -z);
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

void quadrado(int a, int b, int c, int d) {
	glTexCoord2f(ctex_ix, ctex_iy);
	glVertex3fv(vert[a]);
	glTexCoord2f(ctex_ix, ctex_fy);
	glVertex3fv(vert[b]);
	glTexCoord2f(ctex_fx, ctex_fy);
	glVertex3fv(vert[c]);
	glTexCoord2f(ctex_fx, ctex_iy);
	glVertex3fv(vert[d]);

}

void colorcube() {
	glBegin(GL_QUADS);
	quadrado(0, 1, 2,3);
	quadrado(4, 5, 6, 7);
	quadrado(1, 5, 6, 2);
	quadrado(4, 0, 3, 7);
	quadrado(3, 2, 6, 7);
	quadrado(0, 1, 5, 4);
	glEnd();
	glFlush();

}

/*void GerenciaMouse(int button, int state, int x, int y)
{
	if (button ==  GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) { angobjx +=15;
		}
	if (button ==  GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) { angobjy +=15;
			}
	glutPostRedisplay();
}*/

// Fun��o callback chamada para fazer o desenho
void Desenha(void)
{
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	glColor3f(0.0f, 0.0f, 1.0f);

	if (angtex != 0 ) {
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glRotated(angtex, 0, 0, 1);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (angobjx != 0 || (objeto == OBJ_ESFERA && map == MAP_MANUAL)) {
		glRotated(angobjx, 1, 0, 0);
	}
	if (angobjy != 0) {
		glRotated(angobjy, 0, 1, 0);
	}
	if (angobjz != 0 || (objeto == OBJ_ESFERA && map == MAP_MANUAL)) {
		glRotated(angobjz, 0, 0, 1);
	}
	/*switch (objeto) {
	case OBJ_CUBO:
		switch (map) {
		case MAP_AUTO:
			break;
		case MAP_MANUAL:
			colorcube();
			break;
		}
	case OBJ_ESFERA:
		switch (map) {
		case MAP_AUTO:
			glCallList(id);
			break;
		case MAP_MANUAL:
			esfera(p, 1, 20);
			break;
		}
	};*/
	
	//esfera(p, 1, 20);
	//colorcube();
	
	/*glColor3f(0.2f, 0.2f, 0.2f);

	glTranslated(1,1,1); //Move o cone
	glutSolidCone(1.8, 4, 50, 50);*/

	
	//QUADRADO PRA PAREDE
	glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(-3,3);
		glVertex2i(-3,3);
		glTexCoord2f(-3,-3);
		glVertex2i(-3,-3);
		glTexCoord2f(3,-3);
		glVertex2i(3,-3);
		glTexCoord2f(3,3);
		glVertex2i(3,3);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	
	//CILINDRO
	glutSolidCube(2);
	
	
	
	//ESFERA
	
	
		
		
	glutSwapBuffers();
	
}

// Inicializa par�metros de rendering
void Inicializa(void)
{

	// carrega a uma imagem
	unsigned int ih=0, iw=0;
	unsigned char * texture = NULL;
	unsigned char * texture2 = NULL;
	texture = loadBMP_custom("parede.bmp", iw, ih);
	texture2 = loadBMP_custom(infile, iw, ih);
	glShadeModel(GL_SMOOTH);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

	glEnable(GL_DEPTH_TEST); // habilita ZBuffer

	if (map == MAP_AUTO) {
		switch (objeto) {
		case OBJ_CUBO:
			break;
		case OBJ_ESFERA:
			GLUquadricObj * esfera = NULL;
			esfera = gluNewQuadric();
			gluQuadricDrawStyle(esfera, GLU_FILL);
			gluQuadricTexture(esfera, true);
			gluQuadricNormals(esfera, GL_SMOOTH);
			id = glGenLists(1);
			glNewList(id, GL_COMPILE);
			gluSphere(esfera, 1, 20, 20);
			glEndList();
			gluDeleteQuadric(esfera);
		}
	};


	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	gluPerspective(45.0, 1.0, 2.0, 10.0);
	gluLookAt(0,0, 5, 0, 0, 0, 0, 1, 0);

}


// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if (h == 0) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	gluPerspective(45.0, 1.0, 2.0, 10.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

}


// Programa Principal
void getParameters(int argc, char **argv) {
	float param;
	bool paramok;
	char *paramchar;
	// le argumentos e devolve o nome do arquivo
	// para funcionar deve ser usado : -input = nome_arq
	paramok = getCommandLineParameter<bool>(
		argc,
		argv,
		NAME_CLPARAM,
		"-help"
		);
	/*if (paramok) {
		printf("Sintaxe:\n ");
		printf("\t -help \t\t\t\t Imprime este help\t\t\t\t\tOpcional\n ");
		printf("\t -arq=nome_do_arquivo \t\t Define o arquivo de entrada\t\t\t\tObrigatorio\n ");
		printf("\t -obj=tipo_do_objeto \t\t Define o tipo do objeto (cubo ou esfera)\t\tOpcional (default: cubo)\n ");
		printf("\t -map=tipo_de_mapeamento \t Define o tipo de mapeamento (manual ou auto (opengl)) \tOpcional (default: manual)\n ");
		printf("\t -rottex=angulo_de_rotacao \t Define o angulo de rotacao da textura sobre o eixo z \tOpcional (intervalo:[-360.0,360.0];default: 0)\n ");
		printf("\t -rotobjx=angulo_de_rotacao \t Define o angulo de rotacao do objeto sobre o eixo x \tOpcional (intervalo:[-360.0,360.0];default: 0)\n ");
		printf("\t -rotobjy=angulo_de_rotacao \t Define o angulo de rotacao do objeto sobre o eixo y \tOpcional (intervalo:[-360.0,360.0];default: 0)\n ");
		printf("\t -rotobjz=angulo_de_rotacao \t Define o angulo de rotacao do objeto sobre o eixo z \tOpcional (intervalo:[-360.0,360.0];default: 0)\n ");
		printf("\t -sinic=coordenada \t\t Define a coordenada inicial da textura no eixo s \tOpcional (intervalo:[0.0,1.0];default: 0)\n ");
		printf("\t -sfim=coordenada \t\t Define a coordenada final da textura no eixo s \tOpcional (intervalo:[0.0,1.0];default: 0)\n ");
		printf("\t -tinic=coordenada \t\t Define a coordenada inicial da textura no eixo t \tOpcional (intervalo:[0.0,1.0];default: 0)\n ");
		printf("\t -tfim=coordenada \t\t Define a coordenada final da textura no eixo t \tOpcional (intervalo:[0.0,1.0];default: 0)\n");
	};*/
	infile = getCommandLineParameter<char *>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-arq"
		);
	/*if (infile == NULL) {
		printf("ERRO: >> Opcao -arq = nome_do_arquivo\" nao encontrada !\n");
		exit(EXIT_FAILURE);
	} else
		printf("INFO: >> Arquivo = %s\n", infile);
	objeto = OBJ_DEFAULT;
	paramchar = getCommandLineParameter<char *>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-obj"
		);
		if (paramchar != NULL)
			if (strcmp(paramchar, "cubo") == 0 )
			objeto = OBJ_CUBO;
		else if (strcmp(paramchar, "esfera") == 0)
			objeto = OBJ_ESFERA;
	printf("INFO: >> Objeto = %s\n", (objeto == OBJ_CUBO ? "cubo" : "esfera"));
	map = MAP_DEFAULT;
	paramchar = getCommandLineParameter<char *>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-map"
		);
	*/if (paramchar != NULL)
		if (strcmp(paramchar, "auto") == 0)
			map = MAP_AUTO;
			else if (strcmp(paramchar, "manual") == 0)
			map = MAP_MANUAL;
	//printf("INFO: >> Mapeamento = %s\n", (map == MAP_AUTO ? "auto" : "manual"));
	param = getCommandLineParameter<float>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-rottex"
		);
	if (!isInvalidValue(param))
		angtex = max<float>(min<float>(param, 360.0), -360.0);
	//printf("INFO: >> Rotacao Textura eixo z = %5.1f\n", angtex);
	param = getCommandLineParameter<float>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-rotobjx"
		);
	if (!isInvalidValue(param))
		angobjx = max<float>(min<float>(param, 360.0), -360.0);
	//printf("INFO: >> Rotacao Objeto eixo x = %5.1f\n", angobjx);
	param = getCommandLineParameter<float>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-rotobjy"
		);
	if (!isInvalidValue(param))
		angobjy = max<float>(min<float>(param, 360.0), -360.0);
	//printf("INFO: >> Rotacao Objeto eixo y = %5.1f\n", angobjy);
	param = getCommandLineParameter<float>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-rotobjz"
		);
	if (!isInvalidValue(param))
		angobjz = max<float>(min<float>(param, 360.0), -360.0);
	//printf("INFO: >> Rotacao Objeto eixo z = %5.1f\n", angobjz);
	ctex_ix = ctex_iy = 0.0;
	ctex_fx = ctex_fy = 1.0;
	param = getCommandLineParameter<float>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-xinic"
		);
	if (!isInvalidValue(param))
		ctex_ix = max<float>(min<float>(param, 1.0), 0.0);
	//printf("INFO: >> Inicio Coordenada s da Textura = %5.1f\n", ctex_ix);
	param = getCommandLineParameter<float>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-xfim"
		);
	if (!isInvalidValue(param))
		ctex_fx = max<float>(min<float>(param, 1.0), 0.0);
	//printf("INFO: >> Final Coordenada s da Textura = %5.1f\n", ctex_fx);
	param = getCommandLineParameter<float>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-yinic"
		);
	if (!isInvalidValue(param))
		ctex_iy = max<float>(min<float>(param, 1.0), 0.0);
	//printf("INFO: >> Inicio Coordenada t da Textura = %5.1f\n", ctex_iy);
	param = getCommandLineParameter<float>(
		argc,
		argv,
		NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
		"-yfim"
		);
	if (!isInvalidValue(param))
		ctex_fy = max<float>(min<float>(param, 1.0), 0.0);
	//printf("INFO: >> Final Coordenada t da Textura = %5.1f\n", ctex_fy);
	if (objeto == OBJ_CUBO && map == MAP_AUTO) {
		printf("AVISO: >> Mapeamento automatico do cubo nao implementado !\n          Revertendo para mapeamento manual !");
		map = MAP_MANUAL;
	}
}

int main(int argc, char ** argv) {
	getParameters(argc, argv);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Exercício Textura");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	//glutMouseFunc(GerenciaMouse);
  Inicializa();
	glutMainLoop();
}
