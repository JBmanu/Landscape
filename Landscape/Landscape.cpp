#include <iostream>
#include "ObjectGL.h"
#include "ShaderMaker.h"

static unsigned int programId;

float width = 1280.0f;
float height = 720.0f;
mat4 Projection;
GLuint MatProj, MatModel;
float angolo = 0.0;
float dx = 0.0, dy = 0.0;


ObjectGL Ground = {};
ObjectGL Sky = {};
ObjectGL Mountains = {};
ObjectGL Palo = {};
ObjectGL PalaEolica = {};
ObjectGL Sun = {};
ObjectGL Ball = {};

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
	build_square(&Ground,
		vec4(28 / 255.0f, 84 / 255.0f, 045 /255.0f, 1.0),
		vec4(28 / 255.0f, 84 / 255.0f, 045 /255.0f, 1.0),
		vec4(28 / 255.0f, 84 / 255.0f, 045 /255.0f, 1.0),
		vec4(0, 1, 0, 1.0));
	crea_VAO_Vector(&Ground);

	build_square(&Sky,
		vec4(0 / 255.0f, 128 / 255.0f, 255 / 255.0f, 1.0),
		vec4(0 / 255.0f, 128 / 255.0f, 255 / 255.0f, 1.0),
		vec4(0 / 255.0f, 128 / 255.0f, 255 / 255.0f, 1.0),
		vec4(0 / 255.0f, 128 / 255.0f, 255 / 255.0f, 1.0));
	crea_VAO_Vector(&Sky);

	build_square(&Palo,
		vec4(0, 1.0, 0, 1.0),
		vec4(0, 1.0, 0, 1.0),
		vec4(0, 1.0, 0, 1.0),
		vec4(0, 1.1, 0, 1.0));
	crea_VAO_Vector(&Palo);

	Sun.nTriangles = 100;
	build_circle(&Sun, 0.0f, 0.0f, 10.0f, vec4(237 / 255.0f, 1.0, 033 / 255.0f, 1.0));
	crea_VAO_Vector(&Sun);

	Ball.nTriangles = 100;
	build_circle(&Ball, 0.0f, 0.0f, 10.0f, vec4(139 / 255.0, 0 / 255.0, 0 / 255.0, 1.0));
	crea_VAO_Vector(&Ball);

	build_palaEolica(&PalaEolica, 0.0f, 0.0f, 10.0f, vec4(139 / 255.0, 0 / 255.0, 0 / 255.0, 1.0));
	crea_VAO_Vector(&PalaEolica);

	//build_mountains(&Mountains, 10, 0.0f, 0.0f);
	//crea_VAO_Vector(&Mountains);

	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");

	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));

	glBindVertexArray(Ground.VAO);
	Ground.Model = mat4(1.0);
	Ground.Model = scale(Ground.Model, vec3(width, height / 2, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Ground.Model));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, Ground.nv);

	glBindVertexArray(Sky.VAO);
	Sky.Model = mat4(1.0);
	Sky.Model = translate(Sky.Model, vec3(width*0.0, height*0.5, 0.0));
	Sky.Model = scale(Sky.Model, vec3(width, height / 2, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Sky.Model));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, Sky.nv);




	for (int i = 0; i < 5; i++)
	{
		glBindVertexArray(Palo.VAO);
		Palo.Model = mat4(1.0);
		Palo.Model = translate(Palo.Model, vec3(50.0f * 2.0 * (i+1), height * 0.5, 0.0));
		Palo.Model = scale(Palo.Model, vec3(width / 100, height / 5, 1.0));
		glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Palo.Model));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, Palo.nv);
	}

	glBindVertexArray(PalaEolica.VAO);
	PalaEolica.Model = mat4(1.0);
	PalaEolica.Model = translate(PalaEolica.Model, vec3(width * 0.5, height * 0.5, 0.0));
	PalaEolica.Model = scale(PalaEolica.Model, vec3(10.0, 10.0, 1.0));
	PalaEolica.Model = rotate(PalaEolica.Model, radians(angolo), vec3(1.0, 1.0, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(PalaEolica.Model));
	glDrawArrays(GL_TRIANGLE_FAN, 0, PalaEolica.nv);

	//glBindVertexArray(Mountains.VAO);
	//Mountains.Model = mat4(1.0);
	//Mountains.Model = scale(Mountains.Model, vec3(width, height / 2, 0.0));
	//glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Mountains.Model));
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, Mountains.nv);

	glBindVertexArray(Sun.VAO);
	Sun.Model = mat4(1.0);
	Sun.Model = translate(Sun.Model, vec3(width / 2, height / 1.15, 0.0));
	Sun.Model = scale(Sun.Model, vec3(3.0, 3.0, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Sun.Model));
	glDrawArrays(GL_TRIANGLE_FAN, 0, Sun.nv);


	glBindVertexArray(Ball.VAO);
	Ball.Model = mat4(1.0);
	Ball.Model = translate(Ball.Model, vec3((width / 2) + dx, (height / 2.5f) + dy, 0.0));
	Ball.Model = scale(Ball.Model, vec3(3.0, 3.0, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Ball.Model));
	glDrawArrays(GL_TRIANGLE_FAN, 0, Ball.nv);

	glutSwapBuffers();
}

void keyboardPressedEvent(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'a': dx -= 2.0f; break;
	case 'd': dx += 2.0f; break;
	case 'w': dy += 2.0f; break;
	case 's': dy -= 2.0f; break;
	default:
		break;
	}
	glutPostRedisplay();
}

void update_Pale(int a) {
	angolo += 1.0f;
	glutPostRedisplay();
	glutTimerFunc(24, update_Pale, 0);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Paesaggio");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyboardPressedEvent);
	glutTimerFunc(66, update_Pale, 0);

	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}
