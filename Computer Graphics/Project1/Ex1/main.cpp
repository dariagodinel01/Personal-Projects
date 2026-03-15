// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include "dependente\glew\glew.h"

// Include GLFW
#include "dependente\glfw\glfw3.h"

// Include GLM
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"

//variables
GLFWwindow* window;
const int width = 900, height = 900;
glm::mat4 trans(1.0f); //used to translate the spaceship and to get its current position
GLuint programID, programID2, programID3;
GLuint vbo, vao, ibo, vbo2, ibo2, vao2, vbo3, vao3, ibo3;
glm::mat4 trans2(1.0f);//used to translate the bullet and to get its current position
glm::mat4 trans3(1.0f);
glm::mat4 trans4(1.0f);
glm::mat4 transitions[24];//used to translate each asteroid and to know its position
glm::mat4 model4(1.0f);//used for the rotation of the asteroids
double time1, time2, time3, time4;//time1->gets the time the user clicked the right button, time2,time3,time4 count the time for each level for spawning the asteroids
int score = 0;//keeps the score
int health = 1000;//starts at 1000 and gets lower every time the spaceship crashes into an asteroid
int level1 = 1, level2 = 1, level3 = 1, game = 1;//level->used to know the level the user is at, game->if health is bigger than 0 then it is 1 otherwise it is 0 and the game stops
int i = 0, count = 0, ok = 0, ok2 = 0;//count->counts how many times the user clicked right
//ok->if the user clicks left then it is 1 and we shot the bullet
//ok2->if the user clicks right then it is 1 and we start to spawn the asteroids
float x, y, xc, yc;//coordonates of the cursor position
int a[24];//used to know if the asteroid at index i has been destroied
int index1, index2, index3;//index->counts how many asteroids have been destroied at each level to know if
int countBullets2[8];//counts how many bullets have been shot at the level2 asteroids
int countBullets3[8];//counts how many bullets have been shot at the level3 asteroids

//vertices for the spaceship
float vertices[] = {
		0.09f,  0.0f, 0.0f,
		-0.09f, 0.0f, 0.0f,
		0.0f, 0.09f, 0.0f,


};
//indices for the spaceship
unsigned int indices[] = {
	0, 2, 1,

};
//the positions at which the asteroids are spawned at first
glm::vec3 positions[] = {
	//level 1
	//first wave
	glm::vec3(0.0f,  1.25f,  0),
	glm::vec3(0.0f,  -1.25f, 0),
	glm::vec3(1.5f, 0.0f, 0),
	glm::vec3(-1.5f, 0.0f, 0),
	//second wave
	glm::vec3(1.25f, 1.25f, 0),
	glm::vec3(-1.25f, -1.25f, 0),
	glm::vec3(-1.25f, 1.25f, 0),
	glm::vec3(1.25f,  -1.25f, 0),

	//level 2
	//first wave
	glm::vec3(0.5f,  1.25f,  0),
	glm::vec3(-0.5f,  -1.25f, 0),
	glm::vec3(1.5f, -0.5f, 0),
	glm::vec3(-1.5f, 0.5f, 0),
	//second wave
	glm::vec3(1.25f, 0.5f, 0),
	glm::vec3(-1.25f, -1.5f, 0),
	glm::vec3(-1.25f, 1.5f, 0),
	glm::vec3(1.5f,  -1.25f, 0),

	//level 3
	//first wave
	glm::vec3(0.15f,  1.4f,  0),
	glm::vec3(0.15f,  -1.4f, 0),
	glm::vec3(1.7f, 0.15f, 0),
	glm::vec3(-1.7f, 0.15f, 0),
	//second wave
	glm::vec3(1.4f, 1.3f, 0),
	glm::vec3(-1.3f, -1.4f, 0),
	glm::vec3(-1.4f, 1.3f, 0),
	glm::vec3(1.3f,  -1.4f, 0),
};


//gets the cursor postions translated  into viewport coordonates
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec3 win(xpos, ypos, 0);
	glm::vec4 viewport(0, 0, width, height);

	glm::vec3 realpos = glm::unProject(win, glm::mat4(1.0f), glm::mat4(1.0f), viewport);

	x = realpos.x;
	y = -realpos.y;



}
//verifies if the either of the mouse buttons was clicked
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//std::cout << "The button was clicked" << std::endl;

		glUseProgram(programID2);
		//vertices for the bullet
		float vertices2[] = {

			//bullet
			//+x+y
			0.0f,0.0f,0.0f,
			0.0f,0.02f,0.0f,//
			0.015f, 0.015f, 0.0f,
			0.02f, 0.0f, 0.0f,//
			0.015f, -0.015f, 0.0f,
			0.0f, -0.02f, 0.0f,//
			-0.015f, -0.015f, 0.0f,
			-0.02f, 0.0f, 0.0f,//
			-0.015f, 0.015f, 0.0f
		};
		//indices for the bullet
		unsigned int indices2[] = {  // note that we start from 0!
			0,2,1,
			0,3,2,
			0,4,3,
			0,5,4,
			0,6,5,
			0,7,6,
			0,8,7,
			0,1,8

		};
		//the buffers for the bullet
		glGenVertexArrays(1, &vao2);
		glGenBuffers(1, &vbo2);
		glGenBuffers(1, &ibo2);

		glBindVertexArray(vao2);

		glBindBuffer(GL_ARRAY_BUFFER, vbo2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			3 * sizeof(float),
			(void*)0
		);
		glEnableVertexAttribArray(0);
		//the position where the bullet should be
		xc = x; yc = y;
		//variable that is 0 if the button was clicked and 1 if it was not clicked 
		ok = 0;




	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		//count how many times the right button was clicked so we know what level is
		count++;
		glUseProgram(programID3);
		//vertices of teh asteroid
		float vertices3[] = {

			//asteroid
			//+x+y
			0.0f,0.0f,0.0f,
			0.0f,0.2f,0.0f,//
			0.15f, 0.15f, 0.0f,
			0.2f, 0.0f, 0.0f,//
			0.15f, -0.15f, 0.0f,
			0.0f, -0.2f, 0.0f,//
			-0.15f, -0.15f, 0.0f,
			-0.2f, 0.0f, 0.0f,//
			-0.15f, 0.15f, 0.0f
		};
		//indices of the asteroid
		unsigned int indices3[] = {  // note that we start from 0!
			0,2,1,
			0,3,2,
			0,4,3,
			0,5,4,
			0,6,5,
			0,7,6,
			0,8,7,
			0,1,8,
			0,8,1

		};
		//the buffers for the asteroids
		glGenVertexArrays(1, &vao3);
		glGenBuffers(1, &vbo3);
		glGenBuffers(1, &ibo3);

		glBindVertexArray(vao3);

		glBindBuffer(GL_ARRAY_BUFFER, vbo3);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			3 * sizeof(float),
			(void*)0
		);
		glEnableVertexAttribArray(0);



		//for level 1 2 and 3 populates the array a with -1
		for (int i = 0; i < 8; i++) {
			a[i] = -1;
			//translates the level 1 asteroids back at the center of the screen
			transitions[i] = glm::translate(transitions[i], glm::vec3(-transitions[i][3][0], -transitions[i][3][1], 0.0));
			//translates the level 1 asteroids at the initial postion
			transitions[i] = glm::translate(transitions[i], glm::vec3(positions[i].x * 4, positions[i].y * 4, 0));
		}
		//index1 is set at 0 because none of the level1 asteroids were destroied
		index1 = 0;
		//checks the level
		if (count > 1) {
			//the level 2 asteroids start from index 8 until 16
			index2 = 8;
			for (int k = 0; k < 8; k++) {
				//sets the times the level2 asteroids have been shot at to 0
				countBullets2[k] = 0;
			}
			//the same as the level 1 asteroids, but this time for level 2 asteroids
			for (int i = 8; i < 16; i++) {
				a[i] = -1;
				transitions[i] = glm::translate(transitions[i], glm::vec3(-transitions[i][3][0], -transitions[i][3][1], 0.0));
				transitions[i] = glm::translate(transitions[i], glm::vec3(positions[i].x * 2, positions[i].y * 2, 0));
			}
		}
		//checks the level
		if (count > 2) {
			//the level 3 asteroids start from index 16 until 24
			index3 = 16;
			index2 = 8;
			for (int k = 0; k < 8; k++) {
				//sets the times the level3 asteroids have been shot at to 0
				countBullets3[k] = 0;
			}
			//the same as the level 1 and level2 asteroids, but this time for level 3 asteroids
			for (int i = 16; i < 24; i++) {
				a[i] = -1;
				transitions[i] = glm::translate(transitions[i], glm::vec3(-transitions[i][3][0], -transitions[i][3][1], 0.0));
				transitions[i] = glm::translate(transitions[i], glm::vec3(positions[i].x, positions[i].y, 0));
			}
		}
		//if the right button was clicked the it is 1, else it is 0
		ok2 = 1;
		//gets the time the button was clicked so we can count the seconds for spawning the asteroids
		time1 = glfwGetTime();




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
	window = glfwCreateWindow(width, height, "Ex1", NULL, NULL);
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




	// Create and compile our GLSL program from the shaders
	//shader for spaceship
	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	//shader for bullet
	programID2 = LoadShaders("BulletVertexShader.vertexshader", "BulletFragmentShader.fragmentshader");
	//shader for asteroids
	programID3 = LoadShaders("EnemyVertexShader.vertexshader", "EnemyFragmentShader.fragmentshader");

	//the buffers for the spaceship
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	//bind VAO
	glBindVertexArray(vao);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void*)0
	);
	glEnableVertexAttribArray(0);

	// Check if the window was closed

	while (!glfwWindowShouldClose(window))
	{
		//checks the level the user is at
		if (count == 0 || count == 1) {
			// background for level 1

			glClearColor(0.106, 0.212, 0.482, 1.0);

		}
		else {
			if (count == 2) {
				//background for level2

				glClearColor(0.075, 0.298, 0.094, 1.0);

			}
			if (count > 2) {
				//background for level3

				glClearColor(0.725, 0.318, 0.012, 1.0);

			}

			if (!game) {
				//background if the player loses
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			}



		}


		// Swap buffers
		glfwSwapBuffers(window);

		// Check for events
		glfwPollEvents();
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		//checks if the user has enough health to continue to play
		if (health > 0) {
			glUseProgram(programID);//spaceship

			//moves the spaceship down
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				//checks the boundary
				if (trans[3][1] - 0.0003f > -1) {
					trans = glm::translate(trans, glm::vec3(0.0f, -0.0003f, 0.0));
					if (ok)
						trans2 = glm::translate(trans2, glm::vec3(0.0f, -0.0003f, 0.0));
				}

			}
			//moves the spaceship up
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				if (trans[3][1] + 0.0003f + 0.09f < 1) {
					trans = glm::translate(trans, glm::vec3(0.0f, 0.0003f, 0.0));
					if (ok)
						trans2 = glm::translate(trans2, glm::vec3(0.0f, 0.0003f, 0.0));
				}

			}
			//moves the spaceship left
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				if (trans[3][0] - 0.0003f - 0.09f > -1) {
					trans = glm::translate(trans, glm::vec3(-0.0003f, 0.0f, 0.0));
					if (ok)
						trans2 = glm::translate(trans2, glm::vec3(-0.0003f, 0.0f, 0.0));
				}

			}
			//moves the spaceship right
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				if (trans[3][0] + 0.0003f + 0.09f < 1)
				{
					trans = glm::translate(trans, glm::vec3(0.0003f, 0.0f, 0.0));
					if (ok)
						trans2 = glm::translate(trans2, glm::vec3(0.0003f, 0.0f, 0.0));
				}

			}

			// send variables to shader
			unsigned int transformLoc = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			unsigned int coloTransf = glGetUniformLocation(programID, "color");
			//color of the spaceship
			glm::vec4 color = glm::vec4(0.533, 0.224, 0.725, 1.0);
			glUniform4fv(coloTransf, 1, glm::value_ptr(color));


			//bind VAO
			glBindVertexArray(vao);

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

			glUseProgram(programID2);//bullet
			//checks if it shots the bullet
			if (!ok) {
				//translates the bullet to the cursor position
				if (abs(trans2[3][0] - xc) > 0.006 || abs(trans2[3][1] - yc) > 0.006) {
					if (trans2[3][0] < xc) {
						trans2 = glm::translate(trans2, glm::vec3(0.006f, 0.0, 0.0));

					}
					else {
						trans2 = glm::translate(trans2, glm::vec3(-0.006f, 0.0, 0.0));

					}
					if (trans2[3][1] < yc) {
						trans2 = glm::translate(trans2, glm::vec3(0.0, 0.006f, 0.0));

					}
					else {
						trans2 = glm::translate(trans2, glm::vec3(0.0, -0.006f, 0.0));

					}

				}
				else {
					//when the bullet is at the final destination, it translates it back inside the spaceship
					if (trans2[3][0] != trans[3][0] || trans2[3][1] != trans[3][1]) {
						trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
						//the position where the bullet is now
						xc = trans[3][0]; yc = trans[3][1];
						//ok goes back to 1 as it doesnt have to shot a bullet at the moment
						ok = 1;
					}

				}
			}


			glm::mat4 model(1.0f);
			trans4 = glm::rotate(trans4, 45.0f, glm::vec3(0.0, 0.0, 1.0));
			//rotation and translation on the bullet
			model = trans2 * trans4;
			unsigned int transformLoc2 = glGetUniformLocation(programID2, "transform");
			glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(model));
			unsigned int coloTransf2 = glGetUniformLocation(programID2, "color");
			//color of the bullet
			glm::vec4 color2 = glm::vec4(1.0, 0.6, 0.0, 0.0);
			glUniform4fv(coloTransf2, 1, glm::value_ptr(color2));


			if (!ok) {
				//draws the bullet
				glBindVertexArray(vao2);
				glDrawArrays(GL_POLYGON, 1, 17);
			}
			else {
				//indices that dont exist so the bullet is not visible when are not shooting
				glBindVertexArray(vao2);
				glDrawArrays(GL_POLYGON, 18, 3);

			}


			glUseProgram(programID3);//asteroid
			//checks if the user clicked the right button
			if (ok2) {


				glm::mat4  model5(1.0f), sc1(1.0f), sc2(1.0f);
				//scaling for the level1 asteroids 
				sc1 = glm::scale(sc1, glm::vec3(0.25f, 0.25f, 0.0f));
				//scaling for the level2 asteroids
				sc2 = glm::scale(sc2, glm::vec3(0.5f, 0.5f, 0.0f));
				//level3 asteroids are not scaled
				//rotation for the asteroids
				model4 = glm::rotate(model4, 100.0f, glm::vec3(0.0, 0.0, 1.0));
				//checks if all the level 1 asteroids have been destroied
				if (index1 < 8) {

					for (int i = 0; i < 4; i++)
					{
						glm::mat4 model3(1.0f);
						int ok7 = 1;//assumes that the asteroid has not been destroied
						for (int j = 0; j < 4; j++) {
							if (a[j] == i) {
								ok7 = 0;//the asteroid has been destroied
							}
						}
						//if the asteroid is not destroied it slowly translates toward the spaceship
						if (ok7) {
							if (trans[3][0] < transitions[i][3][0] / 4) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(-0.0003f, 0.0, 0.0));
							}
							if (trans[3][0] > transitions[i][3][0] / 4) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.0003f, 0.0, 0.0));
							}
							if (trans[3][1] < transitions[i][3][1] / 4) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, -0.0003f, 0.0));
							}
							if (trans[3][1] > transitions[i][3][1] / 4) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, 0.0003f, 0.0));
							}
							//if the bullet hits the asteroid
							if (transitions[i][3][1] / 4 + 0.05f > trans2[3][1] && transitions[i][3][1] / 4 - 0.05f < trans2[3][1] && transitions[i][3][0] / 4 - 0.05f < trans2[3][0] && transitions[i][3][0] / 4 + 0.05f > trans2[3][0]) {
								score += 100;
								std::cout << "Damage 100. Score:" << score << "\n";
								trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
								xc = trans[3][0]; yc = trans[3][1];
								ok = 1;
								//adds the index of the asteroid that has been destroied to the array so we know not to have it inside the screen anymore
								a[index1++] = i;

							}
						}
						else {

							//translates the destroied asteroid very far away
							//it will be brought back in the callback for the next level
							transitions[i] = glm::translate(transitions[i], glm::vec3(100.0, 100.0, 0.0));
						}
						//checks if the asteroid hit the spaceship
						if (transitions[i][3][1] / 4 + 0.05f > trans[3][1] && transitions[i][3][1] / 4 - 0.05f < trans[3][1] + 0.09f && transitions[i][3][0] / 4 - 0.05f < trans[3][0] + 0.09f && transitions[i][3][0] / 4 + 0.05f > trans[3][0] - 0.09f) {
							health -= 100;
							std::cout << "You have been hit. Damage 100. Health:" << health << "\n";
							//both the asteroid and the spaceship are translated in oppsoite directions after the collision
							//also checks boundaries
							if (trans[3][0] + 0.09f + 0.5f < 1) {
								if (trans[3][1] + 0.09f + 0.5f < 1) {
									trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, -0.5f, 0.0));
								}
								else {
									trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, 0.5f, 0.0));
								}
							}
							else {
								if (trans[3][1] + 0.09f + 0.5f < 1) {
									trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, -0.5f, 0.0));
								}
								else {
									trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, 0.5f, 0.0));
								}
							}
						}



						model5 = sc1 * transitions[i] * model4;



						unsigned int transformLoc5 = glGetUniformLocation(programID3, "transform");
						glUniformMatrix4fv(transformLoc5, 1, GL_FALSE, glm::value_ptr(model5));
						//colors of the asteroids
						glm::vec4 color5 = glm::vec4(0.5f + i / 10.0f, 1 - i / 10.0f, 0.5f + i / 10.0f, 0.5f);

						unsigned int transformLoc6 = glGetUniformLocation(programID3, "color");
						glUniform4fv(transformLoc6, 1, glm::value_ptr(color5));




						//bind VAO
						glBindVertexArray(vao3);

						glDrawElements(GL_POLYGON, 30, GL_UNSIGNED_INT, 0);
					}
					//gets the time after the click and spawns the second wave after 15 second wave
					time2 = glfwGetTime() - time1;
					if (time2 > 15) {
						//same algorthm just for the second wave
						for (int i = 4; i < 8; i++)
						{
							glm::mat4 model3(1.0f);
							int ok7 = 1;
							for (int j = 4; j < 8; j++) {
								if (a[j] == i) {
									ok7 = 0;
								}
							}
							if (ok7) {
								if (trans[3][0] < transitions[i][3][0] / 4) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.0003f, 0.0, 0.0));
								}
								if (trans[3][0] > transitions[i][3][0] / 4) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.0003f, 0.0, 0.0));
								}
								if (trans[3][1] < transitions[i][3][1] / 4) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, -0.0003f, 0.0));
								}
								if (trans[3][1] > transitions[i][3][1] / 4) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, 0.0003f, 0.0));
								}

								if (transitions[i][3][1] / 4 + 0.05f > trans2[3][1] && transitions[i][3][1] / 4 - 0.05f < trans2[3][1] && transitions[i][3][0] / 4 - 0.05f < trans2[3][0] && transitions[i][3][0] / 4 + 0.05f > trans2[3][0]) {
									score += 100;
									std::cout << "Damage 100. Score:" << score << "\n";
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									ok = 1;
									a[index1++] = i;

								}
							}
							else {


								transitions[i] = glm::translate(transitions[i], glm::vec3(100.0, 100.0, 0.0));
							}
							if (transitions[i][3][1] / 4 + 0.05f > trans[3][1] && transitions[i][3][1] / 4 - 0.05f < trans[3][1] + 0.09f && transitions[i][3][0] / 4 - 0.05f < trans[3][0] + 0.09f && transitions[i][3][0] / 4 + 0.05f > trans[3][0] - 0.09f) {
								health -= 100;
								std::cout << "You have been hit. Damage 100. Health:" << health << "\n";
								if (trans[3][0] + 0.09f + 0.5f < 1) {
									if (trans[3][1] + 0.09f + 0.5f < 1) {
										trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, -0.5f, 0.0));
									}
									else {
										trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, 0.5f, 0.0));
									}
								}
								else {
									if (trans[3][1] + 0.09f + 0.5f < 1) {
										trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, -0.5f, 0.0));
									}
									else {
										trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, 0.5f, 0.0));
									}
								}
							}




							model5 = sc1 * transitions[i] * model4;



							unsigned int transformLoc20 = glGetUniformLocation(programID3, "transform");
							glUniformMatrix4fv(transformLoc20, 1, GL_FALSE, glm::value_ptr(model5));
							glm::vec4 color20 = glm::vec4(0.5f + i / 10.0f, 1 - i / 10.0f, 0.5f + i / 10.0f, 0.5f);

							unsigned int transformLoc21 = glGetUniformLocation(programID3, "color");
							glUniform4fv(transformLoc21, 1, glm::value_ptr(color20));




							//bind VAO
							glBindVertexArray(vao3);

							glDrawElements(GL_POLYGON, 30, GL_UNSIGNED_INT, 0);
						}
					}

				}
				//tells the user to go to level2
				if (index1 > 7 && count == 1 && level1) {
					std::cout << "Press right click for level 2" << "\n";
					level1 = 0;
				}
				//draws level2 asteroids
				if (index2 < 16 && index2 > 7) {

					for (int i = 8; i < 12; i++)
					{
						glm::mat4 model3(1.0f);
						int ok7 = 1;
						for (int j = 8; j < 16; j++) {
							if (a[j] == i) {
								ok7 = 0;
							}
						}
						if (ok7) {
							if (trans[3][0] < transitions[i][3][0] / 2) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(-0.0002f, 0.0, 0.0));
							}
							if (trans[3][0] > transitions[i][3][0] / 2) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.0002f, 0.0, 0.0));
							}
							if (trans[3][1] < transitions[i][3][1] / 2) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, -0.0002f, 0.0));
							}
							if (trans[3][1] > transitions[i][3][1] / 2) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, 0.0002f, 0.0));
							}

							if (transitions[i][3][1] / 2 + 0.1f > trans2[3][1] && transitions[i][3][1] / 2 - 0.1f < trans2[3][1] && transitions[i][3][0] / 2 - 0.1f < trans2[3][0] && transitions[i][3][0] / 2 + 0.1f > trans2[3][0]) {
								countBullets2[i - 8]++;
								trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
								xc = trans[3][0]; yc = trans[3][1];
								ok = 1;
								if (countBullets2[i - 8] == 2) {
									score += 200;
									std::cout << "Damage 200. Score:" << score << "\n";

									a[index2++] = i;
								}

							}
						}
						else {


							transitions[i] = glm::translate(transitions[i], glm::vec3(100.0, 100.0, 0.0));

						}
						if (transitions[i][3][1] / 2 + 0.1f > trans[3][1] && transitions[i][3][1] / 2 - 0.1f < trans[3][1] + 0.1f && transitions[i][3][0] / 2 - 0.1f < trans[3][0] + 0.09f && transitions[i][3][0] / 2 + 0.1f > trans[3][0] - 0.09f) {
							health -= 200;
							std::cout << "You have been hit. Damage 200. Health:" << health << "\n";
							if (trans[3][0] + 0.09f + 0.5f < 1) {
								if (trans[3][1] + 0.09f + 0.5f < 1) {
									trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, -0.5f, 0.0));
								}
								else {
									trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, 0.5f, 0.0));
								}
							}
							else {
								if (trans[3][1] + 0.09f + 0.5f < 1) {
									trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, -0.5f, 0.0));
								}
								else {
									trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, 0.5f, 0.0));
								}
							}
						}



						model5 = sc2 * transitions[i] * model4;



						unsigned int transformLoc7 = glGetUniformLocation(programID3, "transform");
						glUniformMatrix4fv(transformLoc7, 1, GL_FALSE, glm::value_ptr(model5));
						glm::vec4 color6 = glm::vec4(i / 20.0f, 1 - i / 20.0f, 0.5f + i / 20.0f, 1.0f);

						unsigned int transformLoc8 = glGetUniformLocation(programID3, "color");
						glUniform4fv(transformLoc8, 1, glm::value_ptr(color6));




						//bind VAO
						glBindVertexArray(vao3);

						glDrawElements(GL_POLYGON, 30, GL_UNSIGNED_INT, 0);
					}
					time3 = glfwGetTime() - time1;
					//spawns the second wave after 10 seconds
					if (time3 > 10) {
						for (int i = 12; i < 16; i++)
						{
							glm::mat4 model3(1.0f);
							int ok7 = 1;
							for (int j = 8; j < 16; j++) {
								if (a[j] == i) {
									ok7 = 0;
								}
							}
							if (ok7) {
								if (trans[3][0] < transitions[i][3][0] / 2) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.0002f, 0.0, 0.0));
								}
								if (trans[3][0] > transitions[i][3][0] / 2) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.0002f, 0.0, 0.0));
								}
								if (trans[3][1] < transitions[i][3][1] / 2) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, -0.0002f, 0.0));
								}
								if (trans[3][1] > transitions[i][3][1] / 2) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, 0.0002f, 0.0));
								}

								if (transitions[i][3][1] / 2 + 0.1f > trans2[3][1] && transitions[i][3][1] / 2 - 0.1f < trans2[3][1] && transitions[i][3][0] / 2 - 0.1f < trans2[3][0] && transitions[i][3][0] / 2 + 0.1f > trans2[3][0]) {
									countBullets2[i - 8]++;
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									ok = 1;
									if (countBullets2[i - 8] == 2) {
										score += 200;
										std::cout << "Damage 200. Score:" << score << "\n";

										a[index2++] = i;
									}

								}
							}
							else {


								transitions[i] = glm::translate(transitions[i], glm::vec3(100.0, 100.0, 0.0));

							}
							if (transitions[i][3][1] / 2 + 0.1f > trans[3][1] && transitions[i][3][1] / 2 - 0.1f < trans[3][1] + 0.1f && transitions[i][3][0] / 2 - 0.1f < trans[3][0] + 0.09f && transitions[i][3][0] / 2 + 0.1f > trans[3][0] - 0.09f) {
								health -= 200;
								std::cout << "You have been hit. Damage 200. Health:" << health << "\n";
								if (trans[3][0] + 0.09f + 0.5f < 1) {
									if (trans[3][1] + 0.09f + 0.5f < 1) {
										trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, -0.5f, 0.0));
									}
									else {
										trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, 0.5f, 0.0));
									}
								}
								else {
									if (trans[3][1] + 0.09f + 0.5f < 1) {
										trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, -0.5f, 0.0));
									}
									else {
										trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, 0.5f, 0.0));
									}
								}
							}


							model5 = sc2 * transitions[i] * model4;



							unsigned int transformLoc7 = glGetUniformLocation(programID3, "transform");
							glUniformMatrix4fv(transformLoc7, 1, GL_FALSE, glm::value_ptr(model5));
							glm::vec4 color6 = glm::vec4(i / 20.0f, 1 - i / 20.0f, 0.5f + i / 20.0f, 1.0f);

							unsigned int transformLoc8 = glGetUniformLocation(programID3, "color");
							glUniform4fv(transformLoc8, 1, glm::value_ptr(color6));




							//bind VAO
							glBindVertexArray(vao3);

							glDrawElements(GL_POLYGON, 30, GL_UNSIGNED_INT, 0);
						}
					}

				}
				//tells the user to go to level 3
				if (index2 > 15 && count == 2 && level2 && index1 > 7) {
					std::cout << "Press right click for level 3" << "\n";
					level2 = 0;
				}
				//draws level 3 asteroids
				if (index3 < 24 && index3>15) {

					for (int i = 16; i < 20; i++)
					{
						glm::mat4 model3(1.0f);
						int ok7 = 1;
						for (int j = 16; j < 24; j++) {
							if (a[j] == i) {
								ok7 = 0;
							}
						}
						if (ok7) {
							if (trans[3][0] < transitions[i][3][0]) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(-0.00005f, 0.0, 0.0));
							}
							if (trans[3][0] > transitions[i][3][0]) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.00005f, 0.0, 0.0));
							}
							if (trans[3][1] < transitions[i][3][1]) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, -0.00005f, 0.0));
							}
							if (trans[3][1] > transitions[i][3][1]) {
								transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, 0.00005f, 0.0));
							}

							if (transitions[i][3][1] + 0.2f > trans2[3][1] && transitions[i][3][1] - 0.2f < trans2[3][1] && transitions[i][3][0] - 0.2f < trans2[3][0] && transitions[i][3][0] + 0.2f > trans2[3][0]) {
								countBullets3[i - 16]++;
								trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
								xc = trans[3][0]; yc = trans[3][1];
								ok = 1;
								if (countBullets3[i - 16] == 3) {
									score += 300;
									std::cout << "Damage 300. Score:" << score << "\n";

									a[index3++] = i;
								}
							}
						}
						else {


							transitions[i] = glm::translate(transitions[i], glm::vec3(100.0, 100.0, 0.0));
						}

						if (transitions[i][3][1] + 0.2f > trans[3][1] && transitions[i][3][1] - 0.2f < trans[3][1] + 0.09f && transitions[i][3][0] - 0.2f < trans[3][0] + 0.09f && transitions[i][3][0] + 0.2f > trans[3][0] - 0.09f) {
							health -= 300;
							std::cout << "You have been hit. Damage 300. Health:" << health << "\n";
							if (trans[3][0] + 0.09f + 0.5f < 1) {
								if (trans[3][1] + 0.09f + 0.5f < 1) {
									trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, -0.5f, 0.0));
								}
								else {
									trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, 0.5f, 0.0));
								}
							}
							else {
								if (trans[3][1] + 0.09f + 0.5f < 1) {
									trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, -0.5f, 0.0));
								}
								else {
									trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0));
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, 0.5f, 0.0));
								}
							}
						}


						model5 = transitions[i] * model4;



						unsigned int transformLoc9 = glGetUniformLocation(programID3, "transform");
						glUniformMatrix4fv(transformLoc9, 1, GL_FALSE, glm::value_ptr(model5));
						glm::vec4 color7 = glm::vec4(0.5f + i / 30.0f, 1 - i / 30.0f, i / 30.0f, 1.0f);

						unsigned int transformLoc10 = glGetUniformLocation(programID3, "color");
						glUniform4fv(transformLoc10, 1, glm::value_ptr(color7));




						//bind VAO
						glBindVertexArray(vao3);

						glDrawElements(GL_POLYGON, 30, GL_UNSIGNED_INT, 0);
					}
					time4 = glfwGetTime() - time1;
					//spawns the second wave after 5 seconds
					if (time4 > 5) {
						for (int i = 20; i < 24; i++)
						{
							glm::mat4 model3(1.0f);
							int ok7 = 1;
							for (int j = 16; j < 24; j++) {
								if (a[j] == i) {
									ok7 = 0;
								}
							}
							if (ok7) {
								if (trans[3][0] < transitions[i][3][0]) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(-0.00005f, 0.0, 0.0));
								}
								if (trans[3][0] > transitions[i][3][0]) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.00005f, 0.0, 0.0));
								}
								if (trans[3][1] < transitions[i][3][1]) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, -0.00005f, 0.0));
								}
								if (trans[3][1] > transitions[i][3][1]) {
									transitions[i] = glm::translate(transitions[i], glm::vec3(0.0, 0.00005f, 0.0));
								}

								if (transitions[i][3][1] + 0.2f > trans2[3][1] && transitions[i][3][1] - 0.2f < trans2[3][1] && transitions[i][3][0] - 0.2f < trans2[3][0] && transitions[i][3][0] + 0.2f > trans2[3][0]) {
									countBullets3[i - 16]++;
									trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
									xc = trans[3][0]; yc = trans[3][1];
									ok = 1;
									if (countBullets3[i - 16] == 3) {
										score += 300;
										std::cout << "Damage 300. Score:" << score << "\n";

										a[index3++] = i;
									}
								}
							}
							else {


								transitions[i] = glm::translate(transitions[i], glm::vec3(100.0, 100.0, 0.0));
							}

							if (transitions[i][3][1] + 0.2f > trans[3][1] && transitions[i][3][1] - 0.2f < trans[3][1] + 0.09f && transitions[i][3][0] - 0.2f < trans[3][0] + 0.09f && transitions[i][3][0] + 0.2f > trans[3][0] - 0.09f) {
								health -= 300;
								std::cout << "You have been hit. Damage 300. Health:" << health << "\n";
								if (trans[3][0] + 0.09f + 0.5f < 1) {
									if (trans[3][1] + 0.09f + 0.5f < 1) {
										trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, -0.5f, 0.0));
									}
									else {
										trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(-0.5f, 0.5f, 0.0));
									}
								}
								else {
									if (trans[3][1] + 0.09f + 0.5f < 1) {
										trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, -0.5f, 0.0));
									}
									else {
										trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0));
										trans2 = glm::translate(trans2, glm::vec3(trans[3][0] - trans2[3][0], trans[3][1] - trans2[3][1], 0.0));
										xc = trans[3][0]; yc = trans[3][1];
										transitions[i] = glm::translate(transitions[i], glm::vec3(0.5f, 0.5f, 0.0));
									}
								}
							}

							model5 = transitions[i] * model4;



							unsigned int transformLoc9 = glGetUniformLocation(programID3, "transform");
							glUniformMatrix4fv(transformLoc9, 1, GL_FALSE, glm::value_ptr(model5));
							glm::vec4 color7 = glm::vec4(0.5f + i / 30.0f, 1 - i / 30.0f, i / 30.0f, 1.0f);

							unsigned int transformLoc10 = glGetUniformLocation(programID3, "color");
							glUniform4fv(transformLoc10, 1, glm::value_ptr(color7));




							//bind VAO
							glBindVertexArray(vao3);

							glDrawElements(GL_POLYGON, 30, GL_UNSIGNED_INT, 0);
						}
					}
				}
				//if the users passes all the 3 levels with health above 0 the they win the game
				if (index2 > 15 && count == 3 && level3 && index1 > 7 && index3 > 23) {
					std::cout << "Congratulations! You won the game!" << "\n";
					std::cout << "If you want to restart the game click the right button" << "\n";
					level1 = 1; level2 = 1;
					count = 0; health = 1000;
					score = 0;
				}
			}


		}
		else {
			//if health is <=0 the the game is over and we get a black screen
			if (game) {
				std::cout << "Game over";
				game = 0;

			}
		}

	}




	// Cleanup
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &vbo2);
	glDeleteBuffers(1, &ibo2);
	glDeleteVertexArrays(1, &vao2);
	glDeleteProgram(programID2);
	glDeleteBuffers(1, &vbo3);
	glDeleteBuffers(1, &ibo3);
	glDeleteVertexArrays(1, &vao3);
	glDeleteProgram(programID3);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}