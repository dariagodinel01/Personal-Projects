// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include<math.h>

// Include GLEW
#include "dependente\glew\glew.h"

// Include GLFW
#include "dependente\glfw\glfw3.h"

// Include GLM
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"
#include "Camera\camera.h"

//variables
GLFWwindow* window;
const int width = 1024, height = 768;

//Time
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
int ok[6] = { 0,0,0,0,0,0 };//0 at start, 1 when P is pressed
int ok2[6] = { 1,1,1,1,1,1 };//is zero if the ball is not in the frame, and is one of the ball has been translated at the wanted position
int k = 0;//index of the balls that appear on the screen
glm::mat4 trans2[6];//array of translations for each ball

//Add the camera parameters here and create a camera object
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 200.0f);
glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDir));
int bilalaunched[6] = { 0,0,0,0,0,0 };//0 at start, 1 if the ball at that index has been launched
int j = 0;//counts how many times the user has pressed P
float launches[10] = { 250.0f, 90.0f, 200.0f,197.0f, 120.0f,210.0f,113.0f,20.0f,238.0f,210.0f };//random distances for the balls
int r[6] = { 0,0,0,0,0,0 };//1 after we randomly choose a value for the distance the ball has to travel
int x;//index of the distance in launches that we have chosen
float scoreRed = 0, scoreBlue = 0, won = 0;//score for each team, won is 1 if the game is done and 0 if we are still palying

//PLANE
float verticesplane[] = {

	
	-300.5f,-0.1f,1.5f,  // top right
	300.5f, -0.1f, 1.5f,  // bottom right
	-300.5f, 0.0f, 1.5f,  // bottom left
	300.5f,  0.0f, 1.5f,   // top left 

	-300.5f, -0.1f, -1.5f,
	300.5f, -0.1f, -1.5f,
	-300.5f, 0.0f, -1.5f,
	300.5f, 0.0f, -1.5f
};


unsigned int indicesplane[] = {

		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4


};


//sphere
float verticesSphere[] = {


		 0.0f,0.0f,0.0f,//0
		0.0f,0.18f,0.0f,//1
		0.13f, 0.13f, 0.0f,//2
		0.18f, 0.0f, 0.0f,//3//// dreapta mult
		0.13f, -0.13f, 0.0f,//4
		0.0f, -0.18f, 0.0f,//5
		-0.13f, -0.13f, 0.0f,//6
		-0.18f, 0.0f, 0.0f,//7
		-0.13f, 0.13f, 0.0f,//8

		0.0f,0.15f,0.1f,//9
		0.1f, 0.1f, 0.1f,//10
		0.15f, 0.0f, 0.1f,//11
		0.1f, -0.1f, 0.1f,//12
		0.0f, -0.15f, 0.1f,//13
		-0.1f, -0.1f, 0.1f,//14
		-0.15f, 0.0f, 0.1f,//15
		-0.1f, 0.1f, 0.1f,//16

		0.0f,0.15f,-0.1f,//17
		0.1f, 0.1f, -0.1f,//18
		0.15f, 0.0f, -0.1f,//19
		0.1f, -0.1f, -0.1f,//20
		0.0f, -0.15f, -0.1f,//21
		-0.1f, -0.1f, -0.1f,//22
		-0.15f, 0.0f, -0.1f,//23
		-0.1f, 0.1f, -0.1f,//24


		0.0f,0.1f,-0.15f,//25
		0.05f, 0.05f, -0.15f,//26
		0.1f, 0.0f, -0.15f,//27
		0.05f, -0.05f, -0.15f,//28
		0.0f, -0.1f, -0.15f,//29
		-0.05f, -0.05f,-0.15f,//30
		-0.1f, 0.0f, -0.15f,//31
		-0.05f, 0.05f, -0.15f,//32

		0.0f,0.1f,0.15f,//33
		0.05f, 0.05f, 0.15f,//34
		0.1f, 0.0f, 0.15f,//35
		0.05f, -0.05f, 0.15f,//36
		0.0f, -0.1f, 0.15f,//37
		-0.05f, -0.05f,0.15f,//38
		-0.1f, 0.0f, 0.15f,//39
		-0.05f, 0.05f, 0.15f,//40
		//
		0.0f,0.05f,0.18f,//41
		0.02f, 0.02f, 0.18f,//42
		0.05f, 0.0f, 0.18f,//43
		0.02f, -0.02f, 0.18f,//44
		0.0f, -0.05f, 0.18f,//45
		-0.02f, -0.02f,0.18f,//46
		-0.05f, 0.0f, 0.18f,//47
		-0.02f, 0.02f, 0.18f,//48

		0.0f,0.05f,-0.18f,//49
		0.02f, 0.02f, -0.18f,//50
		0.05f, 0.0f, -0.18f,//51
		0.02f, -0.02f, -0.18f,//52
		0.0f, -0.05f, -0.18f,//53
		-0.02f, -0.02f,-0.18f,//54
		-0.05f, 0.0f, -0.18f,//55
		-0.02f, 0.02f, -0.18f,//56

};

unsigned int indicesSphere[] = {
		0,2,1,
		0,3,2,
		0,4,3,
		0,5,4,
		0,6,5,
		0,7,6,
		0,8,7,
		0,1,8,
		0,8,1,

		0,10,9,
		0,11,10,
		0,12,11,
		0,13,12,
		0,14,13,
		0,15,14,
		0,16,15,
		0,9,16,

		0,18,17,
		0,19,18,
		0,20,19,
		0,21,20,
		0,22,21,
		0,23,22,
		0,24,23,
		0,17,24,

		0,26,25,
		0,27,26,
		0,28,27,
		0,29,28,
		0,30,29,
		0,31,30,
		0,32,31,
		0,25,32,

		0,34,33,
		0,35,34,
		0,36,35,
		0,37,36,
		0,38,37,
		0,39,38,
		0,40,39,
		0,33,40,

		// varfuri
		0,42,41,
		0,43,42,
		0,44,43,
		0,45,44,
		0,46,45,
		0,47,46,
		0,48,47,
		0,41,48,

		0,50,49,
		0,51,50,
		0,52,51,
		0,53,52,
		0,54,53,
		0,55,54,
		0,56,55,
		0,49,56,

		//
		33,9,10,
		34,10,11,
		35,11,12,
		36,12,13,
		37,13,14,
		38,14,15,
		39,15,16,
		40,16,9,

		25,17,18,
		26,18,19,
		27,19,20,
		28,20,21,
		29,21,22,
		30,22,23,
		31,23,24,
		32,24,17,

		9,1,2,
		10,2,3,
		11,3,4,
		12,4,5,
		13,5,6,
		14,6,7,
		15,7,8,
		16,8,1,

		17,1,2,
		18,2,3,
		19,3,4,
		20,4,5,
		21,5,6,
		22,6,7,
		23,7,8,
		24,8,1,
		//fill ins
	9, 1, 16,
	10, 2, 9,
	11, 3, 10,
	12, 4, 11,
	13, 5, 12,
	14, 6, 13,
	15, 7, 14,
	16, 8, 15,

	17, 1, 24,
	18, 2, 17,
	19, 3, 18,
	20, 4, 19,
	21, 5, 20,
	22, 6, 21,
	23, 7, 22,
	24, 8, 23,
	//
33, 9, 40,
34, 10, 33,
35, 11, 34,
36, 12, 35,
37, 13, 36,
38, 14, 37,
39, 15, 38,
40, 16, 39,

25, 17, 32,
26, 18, 25,
27, 19, 26,
28, 20, 27,
29, 21, 28,
30, 22, 29,
31, 23, 30,
32, 24, 31,
//varfuri fill ins
41, 33, 40,
42,33,34,
43,34,35,
44,35,36,
45,36,37,
46,37,38,
47,38,39,
48,39,40,

41, 33, 42,
42, 34, 43,
43, 35, 44,
44, 36, 45,
45, 37, 46,
46, 38, 47,
47, 39, 48,
48, 40, 41,

49, 25,32,
50,26,25,
51,27,26,
52,28,27,
53,29,28,
54,30,29,
55,31,30,
56,32,31,

49, 25, 50,
50, 26, 51,
51, 27, 52,
52, 28, 53,
53, 29, 54,
54, 30, 55,
55, 31, 56,
56, 32, 49,


};




Camera camera = Camera(cameraPos, cameraDir, cameraUp);

void window_callback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	//when P is pressed we launch a ball
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {

		if (j < 6) {
			ok[j] = 1;
			j++;
		}
	}
	//when V is pressed a ball appears at the start position
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		k++;
	}
	//when O is pressed we reset the game
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		for (int q = 0; q < 6; q++) {
			trans2[q] = glm::translate(trans2[q], glm::vec3(1000.0f, 1000.0f, 1000.0f));
			bilalaunched[q] = 0;
			ok[q] = 0;
			j = 0;
			ok2[q] = 1;
			won = 0;
			r[q] = 0;
			scoreRed = scoreBlue = 0;
			k = 0;
		}
	}


}
void processInput(GLFWwindow* window)
{
	float cameraSpeed = 50.0f * deltaTime;

	//w translate front
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

		camera.translateFront(cameraSpeed);
	}

	//s tr back
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

		camera.translateBack(cameraSpeed);
	}

	//r tr up
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		camera.translateUp(cameraSpeed);
	}
	//f tr down
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		camera.translateDown(cameraSpeed);
	}

	//rotations 
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		camera.rotateOy(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		camera.rotateOy(-cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		camera.rotateOx(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		camera.rotateOx(-cameraSpeed);
	}
	//we translate the ball to left and right with the arrows
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		trans2[k] = glm::translate(trans2[k], glm::vec3(-0.0003f, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		trans2[k] = glm::translate(trans2[k], glm::vec3(0.0003f, 0, 0));
	}

}


int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "3D demo", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}



	glfwMakeContextCurrent(window);


	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}

	//specify the size of the rendering window
	glViewport(0, 0, width, height);

	// Dark blue background
	glClearColor(0.706f, 0.424f, 0.984f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	//sphere
	GLuint programID2 = LoadShaders("LightVertexShader.vertexshader", "LightFragmentShader.fragmentshader");
	//ground plane
	GLuint programID3 = LoadShaders("PlaneVertexShader.vertexshader", "PlaneFragmentShader.fragmentshader");
	// the jack
	GLuint programID4 = LoadShaders("JackVertexShader.vertexshader", "JackFragmentShader.fragmentshader");


	//we translate the balls out of frame at start and each of them will be translated at the start position at their turn
	for (int q = 0; q < 6; q++) {
		trans2[q] = glm::translate(trans2[q], glm::vec3(1000.0f, 1000.0f, 1000.0f));
	}
	camera.setCameraPosition(cameraPos + 1.3f * cameraUp);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	GLuint vbo2, vao2, ibo2,
		vbo3, vao3, ibo3,
		vbo4, vao4, ibo4;


	//Bindings for jack 
	glGenVertexArrays(1, &vao4);
	glGenBuffers(1, &vbo4);
	glGenBuffers(1, &ibo4);

	glBindVertexArray(vao4);

	glBindBuffer(GL_ARRAY_BUFFER, vbo4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSphere), verticesSphere, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSphere), indicesSphere, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);




	//Bindings for plane
	glGenVertexArrays(1, &vao3);
	glGenBuffers(1, &vbo3);
	glGenBuffers(1, &ibo3);

	glBindVertexArray(vao3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesplane), verticesplane, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesplane), indicesplane, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);





	//Bindings for SPHERE
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo2);
	glGenBuffers(1, &ibo2);

	glBindVertexArray(vao2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSphere), verticesSphere, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSphere), indicesSphere, GL_STATIC_DRAW);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);




	glfwSetFramebufferSizeCallback(window, window_callback);

	//Change accordingly for camera
	//glm::mat4 view;
	//view = glm::lookAt(glm::vec3(0.0f, 30.0f, 100.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::lookAt(cameraPos, cameraDir, cameraUp);


	//ground plane
	//glm::mat4 transpl(1.0f);
	//transpl = glm::translate(transpl, glm::vec3(0.0, 0.0, 1.0));



	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100000.0f);

	// Check if the window was closed
	while (!glfwWindowShouldClose(window))
	{
		//calculate delta time 
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glm::mat4  view = glm::lookAt(camera.getCameraPosition(), camera.getCameraViewDirection(), camera.getCameraUp());

		// Swap buffers
		glfwSwapBuffers(window);

		// Check for events
		glfwPollEvents();
		processInput(window);
		glfwSetKeyCallback(window, key_callback);



		//ground plane
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programID3);
		glm::mat4 rotatepl(1.0f);
		rotatepl = glm::rotate(rotatepl, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 mpvplane(1.0f);

		mpvplane = projection * view * rotatepl;

		unsigned int transformLoc1 = glGetUniformLocation(programID3, "transform");
		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(mpvplane));
		unsigned int coloTransf = glGetUniformLocation(programID3, "color");
		glm::vec4 color = glm::vec4(0.5f, 0.25f, 0.0f, 1.0);

		glUniform4fv(coloTransf, 1, glm::value_ptr(color));


		glBindVertexArray(vao3);

		glDrawElements(GL_TRIANGLES, 90, GL_UNSIGNED_INT, 0);


		//sphere
		glUseProgram(programID2);

		//we have to draw 6 balls
		for (int i = 0; i < 6; i++)
		{
			//checks if the ball has been launched, if it has been translated to the start position and if it is its turn
			if (!bilalaunched[i] && ok2[i] && k == i) {
				//translates the ball at the start position
				trans2[i] = glm::translate(trans2[i], glm::vec3(-trans2[i][3][0], -trans2[i][3][1] + 0.15f, -trans2[i][3][2] + 100.0f));
				//tells us the ball has been translated to the start position
				ok2[i] = 0;

			}
			srand((unsigned)time(NULL));
			//checks if the key P has been pressed and if the ball has already been launched
			if (ok[i] && !bilalaunched[i]) {
				//checks if a random distance has been assinged to the ball
				if (!r[i]) {
					//chooses a random distance from the launched array
					x = rand() % 10;
					r[i] = 1;
				}
				//translates the ball to the random distance
				if (trans2[i][3][2] > -launches[x]) {
					trans2[i] = glm::translate(trans2[i], glm::vec3(0.0f, 0, -launches[x] / 1000));

				}
				else {
					//tells us the ball has been launched
					if (i == 5) {
						k++;
					}
					bilalaunched[i] = 1;
					ok[i] = 0;
				}


			}

			glm::mat4 matrix2(1.0f);



			//rotates the ball
			matrix2 = glm::rotate(matrix2, (float)glfwGetTime() * 900, glm::vec3(1.0f, 0.0f, 0.0f));



			glm::mat4 mpv = projection * view * trans2[i] * matrix2;

			unsigned int transformLoc1000 = glGetUniformLocation(programID2, "transform");
			glUniformMatrix4fv(transformLoc1000, 1, GL_FALSE, glm::value_ptr(mpv));
			glm::vec4 color1;
			//if the ball is odd then it is from the blue team and if it is even is from the red team
			if (i % 2 == 0) {
				color1 = glm::vec4(1.0f, 0, 0, 1.0f);
			}
			else {
				color1 = glm::vec4(0, 0, 1.0f, 1.0f);
			}



			unsigned int transformLoc2 = glGetUniformLocation(programID2, "color");
			glUniform4fv(transformLoc2, 1, glm::value_ptr(color1));

			glBindVertexArray(0);
			glBindVertexArray(vao2);
			glDrawElements(GL_TRIANGLES, 2000, GL_UNSIGNED_INT, 0);



		}


		//the jack

		glUseProgram(programID4);
		glm::mat4 transjk;
		transjk = glm::translate(transjk, glm::vec3(0.0f, -0.35f, -200.0f));//translates the jack to the right position
		glm::mat4 mvpjk = projection * view * transjk;

		unsigned int transformLoc4 = glGetUniformLocation(programID4, "transform");
		glUniformMatrix4fv(transformLoc4, 1, GL_FALSE, glm::value_ptr(mvpjk));

		unsigned int transformLoc24 = glGetUniformLocation(programID4, "color");
		glUniform4fv(transformLoc24, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));

		glBindVertexArray(0);
		glBindVertexArray(vao4);

		glDrawElements(GL_TRIANGLES, 2000, GL_UNSIGNED_INT, 0);
		//checks if all the balls have been launched
		if (k > 5 && !won) {
			//calculates the score for each team
			scoreRed = sqrt(pow(transjk[3][0] - trans2[0][3][0], 2) + pow(transjk[3][2] - trans2[0][3][2], 2)) + sqrt(pow(transjk[3][0] - trans2[2][3][0], 2) + pow(transjk[3][2] - trans2[2][3][2], 2)) + sqrt(pow(transjk[3][0] - trans2[4][3][0], 2) + pow(transjk[3][2] - trans2[4][3][2], 2));
			scoreBlue = sqrt(pow(transjk[3][0] - trans2[1][3][0], 2) + pow(transjk[3][2] - trans2[1][3][2], 2)) + sqrt(pow(transjk[3][0] - trans2[3][3][0], 2) + pow(transjk[3][2] - trans2[3][3][2], 2)) + sqrt(pow(transjk[3][0] - trans2[5][3][0], 2) + pow(transjk[3][2] - trans2[5][3][2], 2));

			if (scoreRed < scoreBlue) {
				std::cout << "Red team has won!!" << "\n";
			}
			else {
				std::cout << "Blue team has won!!" << "\n";
			}
			//tells us the game is done
			won = 1;
		}


	}

	// Cleanup VBO

	glDeleteBuffers(1, &vbo2);
	glDeleteBuffers(1, &vbo3);
	glDeleteBuffers(1, &vbo4);
	glDeleteBuffers(1, &ibo2);
	glDeleteBuffers(1, &ibo3);
	glDeleteBuffers(1, &ibo4);
	glDeleteVertexArrays(1, &vao2);
	glDeleteVertexArrays(1, &vao3);
	glDeleteVertexArrays(1, &vao4);
	glDeleteProgram(programID2);
	glDeleteProgram(programID3);
	glDeleteProgram(programID4);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}