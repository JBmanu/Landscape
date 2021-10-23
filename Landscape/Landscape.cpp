#include <iostream>
#include "ObjectGL.h"
#include "Fisic.h"
#include "ShaderMaker.h"

static unsigned int programId;

mat4 Projection;
GLuint MatProj, MatModel;

ObjectGL Ground = {};
ObjectGL Sky = {};
ObjectGL Mountains = {};
ObjectGL Palo = {};
ObjectGL PalaEolica = {};
ObjectGL Sun = {};
ObjectGL SunAlone = {};
ObjectGL Ball = {};
ObjectGL Ombra = {};
ObjectGL OmbraAlone = {};
EqFisic Jump = {};


float heighPiano = 100.0f;
float widthPiano = WIDTH / 2.0f;

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();

	char* vertexShader = (char*)"vertexShader_M.glsl";
	char* fragmentShader = (char*)"fragmentShader_M.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	build_square(&Ground,vec_RGBA(28, 84, 45), vec_RGBA(28, 84, 45), vec_RGBA(28, 84, 45), vec_RGBA(0, 255, 0));
	create_VAO_VBO_vertex(&Ground);

	build_square(&Sky, vec_RGBA(0, 128, 255), vec_RGBA(0, 128, 255), vec_RGBA(138, 43, 226), vec_RGBA(138, 43, 226));
	create_VAO_VBO_vertex(&Sky);

	build_square(&Palo, vec_RGBA(105, 105, 105), vec_RGBA(105, 105, 105), vec_RGBA(105, 105, 105), vec_RGBA(105, 105, 105));
	create_VAO_VBO_vertex(&Palo);

	build_circle(&Sun, 100, 10.0f, vec_RGBA(255, 140, 0, 255), vec_RGBA(255, 255, 255, 255));
	create_VAO_VBO_vertex(&Sun);
	
	build_circle(&SunAlone, 100, 12.0f, vec_RGBA(237, 255, 33, 255), vec_RGBA(237, 255, 33, 0));
	create_VAO_VBO_vertex(&SunAlone);


	build_palaEolica(&PalaEolica, 5, 10.0f, vec_RGBA(216, 191, 216, 255), vec_RGBA(105, 105, 105, 355));
	create_VAO_VBO_vertex(&PalaEolica);

	build_mountain(&Mountains, 20, vec_RGBA(205, 133, 63, 255), vec_RGBA(139, 69, 19, 255));
	create_VAO_VBO_vertex(&Mountains);

	build_circle(&Ball, 100, 10.0f, vec_RGBA(255, 0, 0, 255), vec_RGBA(139, 0, 0, 255));
	set_value_transfom_2D(&Ball, widthPiano, heighPiano, 3.0f, 3.0f, 0.0f);
	create_VAO_VBO_vertex(&Ball);

	build_circle(&Ombra, 100, 10.0f, vec_RGBA(0, 0, 0, 255), vec_RGBA(0, 0, 0, 255));
	set_value_transfom_2D(&Ombra, widthPiano, heighPiano, 3.0f, 3.0f, 0.0f);
	create_VAO_VBO_vertex(&Ombra);

	build_circle(&OmbraAlone, 100, 10.0f, vec_RGBA(59, 50, 50, 255), vec_RGBA(0, 0, 0, 0));
	set_value_transfom_2D(&OmbraAlone, widthPiano, heighPiano, Ombra.scalex, 3.0f, 0.0f);
	create_VAO_VBO_vertex(&OmbraAlone);

	Jump.a = -9.81f;
	Jump.e = 80.0f;
	set_eq_init(&Jump, widthPiano, heighPiano, 80.0f, 0.0f);
	
	Projection = ortho(0.0f, WIDTH, 0.0f, HEIGHT);
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");
}

void drawScene(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));

	glBindVertexArray(Ground.VAO);
	set_value_transfom_2D(&Ground, 0.0f, 0.0f, WIDTH, HEIGHT * 0.5f, 0.0f);
	transform(&Ground, MatModel);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, Ground.nv);

	glBindVertexArray(Sky.VAO);
	set_value_transfom_2D(&Sky, 0.0f, HEIGHT * 0.5f, WIDTH, HEIGHT * 0.5f, 0.0f);
	transform(&Sky, MatModel);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, Sky.nv);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(3.0);
	for (int i = 0; i < 6; i++)
	{
		glBindVertexArray(Mountains.VAO);
		set_value_transfom_2D(&Mountains, (213.0f * i), (HEIGHT / 2.0f), 428.0f, 120.0f, 0.0f);
		transform(&Mountains, MatModel);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, Mountains.nv);
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	for (int i = 0; i < 7; i++)
	{
		glBindVertexArray(Palo.VAO);
		set_value_transfom_2D(&Palo, (160.0f * (i + 1)), (HEIGHT / 2.0f), WIDTH / 100.0f, HEIGHT / 6.0f, 0.0f);
		transform(&Palo, MatModel);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, Palo.nv);

		glBindVertexArray(PalaEolica.VAO);
		set_value_transfom_2D(&PalaEolica, (160.0f * (i + 1)) + (WIDTH / 250.0), (HEIGHT * 0.66), 5.0f, 5.0f, PalaEolica.angle);
		transform(&PalaEolica, MatModel);
		glDrawArrays(GL_TRIANGLE_FAN, 0, PalaEolica.nv);
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(Sun.VAO);
	set_value_transfom_2D(&Sun, WIDTH * 0.5f, HEIGHT / 1.10, 3.0f, 3.0f, 0.0f);
	transform(&Sun, MatModel);
	glDrawArrays(GL_TRIANGLE_FAN, 0, Sun.nv);


	glBindVertexArray(SunAlone.VAO);
	set_value_transfom_2D(&SunAlone, WIDTH * 0.5f, HEIGHT / 1.10, 6.0f, 6.0f, 0.0f);
	transform(&SunAlone, MatModel);
	glDrawArrays(GL_TRIANGLE_FAN, 0, SunAlone.nv);


	glBindVertexArray(OmbraAlone.VAO);
	set_value_transfom_2D(&OmbraAlone, OmbraAlone.dx, OmbraAlone.dy, (Ball.dy / 50.0f), (Ball.dy / 150), 0.0f);
	transform(&OmbraAlone, MatModel);
	glDrawArrays(GL_TRIANGLE_FAN, 0, OmbraAlone.nv);

	glBindVertexArray(Ombra.VAO);
	set_value_transfom_2D(&Ombra, Ombra.dx, Ombra.dy, (Ball.dy / 150.0f), (Ball.dy / 350), 0.0f);
	transform(&Ombra, MatModel);
	glDrawArrays(GL_TRIANGLE_FAN, 0, Ombra.nv);

	glBindVertexArray(Ball.VAO);
	set_value_transfom_2D(&Ball, Ball.dx, Ball.dy, Ball.scalex, Ball.scaley, 0.0f);
	transform(&Ball, MatModel);
	glDrawArrays(GL_TRIANGLE_FAN, 0, Ball.nv);


	glutSwapBuffers();
}

void keyboardPressedEvent(unsigned char key, int x, int y) {
	switch (key) {
		case 'a': Jump.e += 10.0f; break;
		case 'd': Jump.e -= 10.0f; break;
	}
	glutPostRedisplay();
}

void jump_ball(int a) {
	compute_eq_y(&Jump);
	compute_eq_x(&Jump);
	Jump.t += 0.07;

	//Ball.dy = Ball.dy < heighPiano ? heighPiano : heighPiano + Jump.y;
	Ball.dy = Jump.y;
	Ombra.dx = OmbraAlone.dx = Ball.dx = Jump.x;

	if (Ball.dy < heighPiano)
	{
		set_eq_init(&Jump, Ball.dx, Ball.dy, 80.0f, 0);
		printf("%f  --  %f", Ball.dy, heighPiano);
		heighPiano = Ball.dy;
	}
	
	glutPostRedisplay();
	glutTimerFunc(1, jump_ball, 0);
}

void update_Pale(int a) {
	PalaEolica.angle += 5.0f;
	glutPostRedisplay();
	glutTimerFunc(60, update_Pale, 0);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Paesaggio");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyboardPressedEvent);

	glutTimerFunc(60, update_Pale, 0);
	glutTimerFunc(60, jump_ball, 0);


	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}
