#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_glfw.h"
#include "Imgui\imgui_impl_opengl3.h"

void processKeyboardInput();

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Winter Wonderland", 800, 800);
Camera camera;


glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos = glm::vec3(-180.0f, 100.0f, -200.0f);
glm::mat4 ModelMatrixp = glm::mat4(1.0);
Camera fps(glm::vec3(-190.0f, 12.0f, -200.0f));
int x;

int main()
{


	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool start = false;
	bool task1 = false;
	bool task2 = false;
	bool task3 = false;
	bool task4 = false;
	bool task5 = false;


	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);

	//building and compiling shader program
	Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
	Shader sunShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");
	Shader planeShader("Shaders/plane_vertex_shader.glsl", "Shaders/plane_fragment_shader.glsl");
	Shader playerShader("Shaders/player_vertex_shader.glsl", "Shaders/player_fragment_shader.glsl");
	Shader armyShader("Shaders/army_vertex_shader.glsl", "Shaders/army_fragment_shader.glsl");
	Shader snowShader("Shaders/snow_vertex_shader.glsl", "Shaders/snow_fragment_shader.glsl");


	//Textures
	GLuint tex = loadBMP("Resources/Textures/wood.bmp");
	GLuint tex2 = loadBMP("Resources/Textures/ice.bmp");
	GLuint tex3 = loadBMP("Resources/Textures/orange.bmp");
	GLuint tex4 = loadBMP("Resources/Textures/capybara_texture.bmp");
	GLuint tex5 = loadBMP("Resources/Textures/indianabones.bmp");
	GLuint tex6 = loadBMP("Resources/Textures/Cottage2.bmp");
	GLuint tex7 = loadBMP("Resources/Textures/candy.bmp");
	GLuint tex8 = loadBMP("Resources/Textures/snowman.bmp");
	GLuint tex9 = loadBMP("Resources/Textures/tree.bmp");
	GLuint tex10 = loadBMP("Resources/Textures/candywhite.bmp");
	GLuint tex11 = loadBMP("Resources/Textures/cottoncandy.bmp");
	GLuint tex12 = loadBMP("Resources/Textures/GingerbreadCookie.bmp");
	GLuint tex13 = loadBMP("Resources/Textures/treev2.bmp");
	GLuint tex14 = loadBMP("Resources/Textures/campfire.bmp");
	GLuint tex15 = loadBMP("Resources/Textures/barrel.bmp");
	GLuint tex16 = loadBMP("Resources/Textures/portal.bmp");
	GLuint tex17 = loadBMP("Resources/Textures/chtree.bmp");
	GLuint tex18 = loadBMP("Resources/Textures/Candies.bmp");
	GLuint tex19 = loadBMP("Resources/Textures/candyv2.bmp");
	GLuint tex20 = loadBMP("Resources/Textures/snowman.bmp");
	GLuint tex21 = loadBMP("Resources/Textures/white.bmp");
	GLuint tex22 = loadBMP("Resources/Textures/red.bmp");
	GLuint tex23 = loadBMP("Resources/Textures/key.bmp");
	GLuint tex24 = loadBMP("Resources/Textures/red.bmp");
	GLuint tex25 = loadBMP("Resources/Textures/brown.bmp");


	glEnable(GL_DEPTH_TEST);

	//Test custom mesh loading
	std::vector<Vertex> vert;
	vert.push_back(Vertex());
	vert[0].pos = glm::vec3(10.5f, 10.5f, 0.0f);
	vert[0].textureCoords = glm::vec2(1.0f, 1.0f);

	vert.push_back(Vertex());
	vert[1].pos = glm::vec3(10.5f, -10.5f, 0.0f);
	vert[1].textureCoords = glm::vec2(1.0f, 0.0f);

	vert.push_back(Vertex());
	vert[2].pos = glm::vec3(-10.5f, -10.5f, 0.0f);
	vert[2].textureCoords = glm::vec2(0.0f, 0.0f);

	vert.push_back(Vertex());
	vert[3].pos = glm::vec3(-10.5f, 10.5f, 0.0f);
	vert[3].textureCoords = glm::vec2(0.0f, 1.0f);

	vert[0].normals = glm::normalize(glm::cross(vert[1].pos - vert[0].pos, vert[3].pos - vert[0].pos));
	vert[1].normals = glm::normalize(glm::cross(vert[2].pos - vert[1].pos, vert[0].pos - vert[1].pos));
	vert[2].normals = glm::normalize(glm::cross(vert[3].pos - vert[2].pos, vert[1].pos - vert[2].pos));
	vert[3].normals = glm::normalize(glm::cross(vert[0].pos - vert[3].pos, vert[2].pos - vert[3].pos));

	std::vector<int> ind = { 0, 1, 3,
		1, 2, 3 };

	std::vector<Texture> textures;
	textures.push_back(Texture());
	textures[0].id = tex;
	textures[0].type = "texture_diffuse";

	std::vector<Texture> textures2;
	textures2.push_back(Texture());
	textures2[0].id = tex2;
	textures2[0].type = "texture_diffuse";

	std::vector<Texture> textures3;
	textures3.push_back(Texture());
	textures3[0].id = tex3;
	textures3[0].type = "texture_diffuse";

	std::vector<Texture> textures4;
	textures4.push_back(Texture());
	textures4[0].id = tex4;
	textures4[0].type = "texture_diffuse";

	std::vector<Texture> textures5;
	textures5.push_back(Texture());
	textures5[0].id = tex5;
	textures5[0].type = "texture_diffuse";

	std::vector<Texture> textures6;
	textures6.push_back(Texture());
	textures6[0].id = tex6;
	textures6[0].type = "texture_diffuse";

	std::vector<Texture> textures7;
	textures7.push_back(Texture());
	textures7[0].id = tex7;
	textures7[0].type = "texture_diffuse";

	std::vector<Texture> textures8;
	textures8.push_back(Texture());
	textures8[0].id = tex8;
	textures8[0].type = "texture_diffuse";

	std::vector<Texture> textures9;
	textures9.push_back(Texture());
	textures9[0].id = tex9;
	textures9[0].type = "texture_diffuse";

	std::vector<Texture> textures10;
	textures10.push_back(Texture());
	textures10[0].id = tex10;
	textures10[0].type = "texture_diffuse";

	std::vector<Texture> textures11;
	textures11.push_back(Texture());
	textures11[0].id = tex11;
	textures11[0].type = "texture_diffuse";

	std::vector<Texture> textures12;
	textures12.push_back(Texture());
	textures12[0].id = tex12;
	textures12[0].type = "texture_diffuse";

	std::vector<Texture> textures13;
	textures13.push_back(Texture());
	textures13[0].id = tex13;
	textures13[0].type = "texture_diffuse";

	std::vector<Texture> textures14;
	textures14.push_back(Texture());
	textures14[0].id = tex14;
	textures14[0].type = "texture_diffuse";

	std::vector<Texture> textures15;
	textures15.push_back(Texture());
	textures15[0].id = tex15;
	textures15[0].type = "texture_diffuse";


	std::vector<Texture> textures16;
	textures16.push_back(Texture());
	textures16[0].id = tex16;
	textures16[0].type = "texture_diffuse";

	std::vector<Texture> textures17;
	textures17.push_back(Texture());
	textures17[0].id = tex17;
	textures17[0].type = "texture_diffuse";

	std::vector<Texture> textures18;
	textures18.push_back(Texture());
	textures18[0].id = tex18;
	textures18[0].type = "texture_diffuse";

	std::vector<Texture> textures19;
	textures19.push_back(Texture());
	textures19[0].id = tex19;
	textures19[0].type = "texture_diffuse";
	std::vector<Texture> textures20;
	textures20.push_back(Texture());
	textures20[0].id = tex20;
	textures20[0].type = "texture_diffuse";

	std::vector<Texture> textures21;
	textures21.push_back(Texture());
	textures21[0].id = tex21;
	textures21[0].type = "texture_diffuse";

	std::vector<Texture> textures22;
	textures22.push_back(Texture());
	textures22[0].id = tex22;
	textures22[0].type = "texture_diffuse";

	std::vector<Texture> textures23;
	textures23.push_back(Texture());
	textures23[0].id = tex23;
	textures23[0].type = "texture_diffuse";

	std::vector<Texture> textures24;
	textures24.push_back(Texture());
	textures24[0].id = tex24;
	textures24[0].type = "texture_diffuse";

	std::vector<Texture> textures25;
	textures25.push_back(Texture());
	textures25[0].id = tex25;
	textures25[0].type = "texture_diffuse";


	Mesh mesh(vert, ind, textures3);


	// Create Obj files - easier :)
	// we can add here our textures :)
	MeshLoaderObj loader;
	Mesh sun = loader.loadObj("Resources/Models/sphere.obj");
	Mesh box = loader.loadObj("Resources/Models/cube.obj", textures);
	Mesh plane = loader.loadObj("Resources/Models/plane1.obj", textures2);
	Mesh capybara = loader.loadObj("Resources/Models/Capybara.obj", textures4);
	Mesh indianabones = loader.loadObj("Resources/Models/IndianaBones.obj", textures5);
	Mesh cottage = loader.loadObj("Resources/Models/Cottage.obj", textures6);
	Mesh candy = loader.loadObj("Resources/Models/CandyCycles.obj", textures7);
	Mesh candywhite = loader.loadObj("Resources/Models/CandyCycles.obj", textures10);
	Mesh snowman = loader.loadObj("Resources/Models/snowman.obj", textures8);
	Mesh tree = loader.loadObj("Resources/Models/tree.obj", textures9);
	Mesh treev2 = loader.loadObj("Resources/Models/tree.obj", textures13);
	Mesh lolipop = loader.loadObj("Resources/Models/lolipop.obj", textures7);
	Mesh cotton = loader.loadObj("Resources/Models/CottonCandy.obj", textures11);
	Mesh gingerbread = loader.loadObj("Resources/Models/Gingerbread.obj", textures12);
	Mesh campfire = loader.loadObj("Resources/Models/campfire.obj", textures14);
	Mesh barrel = loader.loadObj("Resources/Models/Barrel.obj", textures15);
	Mesh portal = loader.loadObj("Resources/Models/plane.obj", textures16);
	Mesh chtree = loader.loadObj("Resources/Models/tree.obj", textures17);
	Mesh candies = loader.loadObj("Resources/Models/Candies.obj", textures18);
	Mesh candyv2 = loader.loadObj("Resources/Models/candyv2.obj", textures19);
	Mesh snowflake = loader.loadObj("Resources/Models/Snowflake.obj", textures20);
	Mesh snowflake2 = loader.loadObj("Resources/Models/snow-flake.obj", textures21);
	Mesh xsign = loader.loadObj("Resources/Models/button.obj", textures22);
	Mesh key = loader.loadObj("Resources/Models/Key.obj", textures23);
	Mesh arrowcandy = loader.loadObj("Resources/Models/Arrowcandy.obj", textures24);
	Mesh arrowhome = loader.loadObj("Resources/Models/sign.obj", textures25);



	static int f = 40;
	bool ok = true;
	bool ok2[1225]{};
	bool ok3[1225]{};
	glm::mat4 ModelMatrixs[30];
	glm::mat4 ModelMatrixk;
	glm::mat4 ModelMatrixs2[1225];
	glm::mat4 ModelMatrixs3[1225];
	bool teleport = false;
	bool oki = true;
	bool okcandy = false;
	bool okcandy2 = false;
	float timeCandy = 150000000;
	bool okkey = false;
	int keyy = 0;

	for (int i = 0; i < 1225; i++) {
		ok3[i] == true;
		ok2[i] == true;
	}
	fps.rotateOy(180);

	//check if we close the window or press the escape button
	while (!window.isPressed(GLFW_KEY_ESCAPE) &&
		glfwWindowShouldClose(window.getWindow()) == 0)
	{
		window.clear();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static int counter = 0;

		ImGui::Begin("Info");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Help the little Capybara pass all the trials");               // Display some text (you can use a format strings too)             
		ImGui::Text("and enjoy her Christmas tree.");


		ImGui::SliderInt("int", &f, 0.0f, 40);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		if (!start) {
			if (ImGui::Button("START"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				start = true;
		}
		else {
			if (!task1) {
				ImGui::Text("Find the Christmas Tree!");
				ImGui::Text("HINT: Try in the house. ;)");
			}
			if (task1 && !task2) {
				ImGui::Text("Run from the enemy!");
			}
			if (task2 && !task3) {
				ImGui::Text("Take the candy back to the CandyLand.");
			}
			if (task3 && !task4) {
				ImGui::Text("Choose the lucky barrel near the forest.");
				ImGui::Text("HINT: Think of a lucky number. ;)");
			}
			if (task4 && !task5) {
				ImGui::Text("Here is the final task:");
				ImGui::Text("Use the key to go back home.");
			}
			if(task5) {
				ImGui::Text("Game over");
			}
		}


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processKeyboardInput();
		
		//// Code for the light ////

		sunShader.use();

		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(fps.getCameraPosition(), fps.getCameraPosition() + fps.getCameraViewDirection(), fps.getCameraUp());

		GLuint MatrixID = glGetUniformLocation(sunShader.getId(), "MVP");

		//Test for one Obj loading = light source

		glm::mat4 ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, lightPos);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


		sun.draw(sunShader);

		//// End code for the light ////

		shader.use();

		///// Test Obj files for box ////

		GLuint MatrixID2 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID = glGetUniformLocation(shader.getId(), "model");

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), fps.getCameraPosition().x, fps.getCameraPosition().y, fps.getCameraPosition().z);

		//box.draw(shader);

		///// Test plane Obj file //////
		planeShader.use();

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(planeShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(planeShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(planeShader.getId(), "viewPos"), fps.getCameraPosition().x, fps.getCameraPosition().y, fps.getCameraPosition().z);

		plane.draw(planeShader);

		playerShader.use();
		if (ok) {
			ModelMatrixp = glm::translate(ModelMatrixp, glm::vec3(-190.0f, 0.0f, -200.0f));
			ModelMatrixp = glm::scale(ModelMatrixp, glm::vec3(1.5f, 1.5f, 1.5f));
			ModelMatrixp = glm::rotate(ModelMatrixp, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (abs(ModelMatrixp[3][0] + 250.0f) < 10.0f && abs(ModelMatrixp[3][2] + 200.0f) < 10.0f) {
			ModelMatrixp = glm::mat4(1.0);
			ModelMatrixp = glm::translate(ModelMatrixp, glm::vec3(150.0f, 0, 240.0f));
			ModelMatrixp = glm::scale(ModelMatrixp, glm::vec3(1.5f, 1.5f, 1.5f));
			ModelMatrixp = glm::rotate(ModelMatrixp, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrixp = glm::rotate(ModelMatrixp, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			fps.setCameraPosition(glm::vec3(150.0f, 12.0f, 240.0f));
			fps.rotateOy(-90);
			teleport = true;
			task1 = true;
			//task2 = true;
		}
		if (abs(ModelMatrixp[3][0] + 210.0f) < 10.0f && abs(ModelMatrixp[3][2] - 240.0f) < 10.0f) {
			oki = false;
			task2 = true;
			okcandy = true;
			timeCandy = glfwGetTime();
		}
		if (abs(ModelMatrixp[3][0] - 151.0f) < 10.0f && abs(ModelMatrixp[3][2] - 57.0f) < 10.0f) {
			task3 = true;
			okcandy2 = true;

		}
		if (abs(ModelMatrixp[3][0] + 140.0f) < 10.0f && abs(ModelMatrixp[3][2] - 10.0f) < 10.0f) {
			task4 = true;
			okkey = true;

		}
		if (abs(ModelMatrixp[3][0] + 220.0f) < 10.0f && abs(ModelMatrixp[3][2] + 200.0f) < 20.0f && task4) {
			task5 = true;
		}
		

		
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrixp;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrixp[0][0]);
		glUniform3f(glGetUniformLocation(playerShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(playerShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(playerShader.getId(), "viewPos"), fps.getCameraPosition().x, fps.getCameraPosition().y, fps.getCameraPosition().z);

		//printf("heeeeeeeey: %f\n", ModelMatrix[3][0]);

		capybara.draw(playerShader);

		armyShader.use();
		GLuint MatrixID3 = glGetUniformLocation(armyShader.getId(), "MVP");
		GLuint ModelMatrixID3 = glGetUniformLocation(armyShader.getId(), "model");

		if (ok == true) {
			for (int k = 0; k < 30; k++) {
				ModelMatrixs[k] = glm::mat4(1.0);

			}
			//printf("START ");
		}
		int k = 0;
		//printf("START ");
		if (oki) {
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (ok) {
						float xval = 10.0f * i + 190.0f;
						float zval = 20.0f * j + 220.0f;

						ModelMatrixs[k] = glm::translate(ModelMatrixs[k], glm::vec3(xval, 0.0f, zval));
						ModelMatrixs[k] = glm::rotate(ModelMatrixs[k], -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));




					}
					if (teleport) {
						//printf("vvvvvvvvvvv: %f\n", ModelMatrixs[k][3][0]);
						ModelMatrixs[k] = glm::translate(ModelMatrixs[k], glm::vec3(0.0f, 0.0f, 0.5f));
						//printf("jmmmmmmmm: %f\n", ModelMatrixs[k][3][0]);

					}
					//printf("vvvvvvvvvvv: %f\n", ModelMatrixs[k][3][0]);

					glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrixs[k];
					glUniformMatrix4fv(MatrixID3, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID3, 1, GL_FALSE, &ModelMatrixs[k][0][0]);
					glUniform3f(glGetUniformLocation(armyShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
					glUniform3f(glGetUniformLocation(armyShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
					glUniform3f(glGetUniformLocation(armyShader.getId(), "viewPos"), fps.getCameraPosition().x, fps.getCameraPosition().y, fps.getCameraPosition().z);
					indianabones.draw(armyShader);
					k++;
				}

			}
		}
		







		shader.use();
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-240.0f, 0.0f, -200.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.7f, 0.7f, 0.7f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		cottage.draw(shader);

		//christmas tree
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-250.0f, 0.0f, -200.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		chtree.draw(shader);

		//candy arrow

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(160.0f, 30.0f, 30.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(0.0f, 1.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		arrowcandy.draw(shader);

		//candyland
		for (int i = 0; i <= 5; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(225.0f + 10 * i, -5.0f, 10.0f * i));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			candy.draw(shader);
		}

		for (int i = 0; i <= 1; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(150.0f + 10 * i, -5.0f, 10.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			candy.draw(shader);
		}
		for (int i = 0; i <= 5; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(200.0f + 10 * i, -5.0f, 10.0f * i));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			candywhite.draw(shader);
		}
		for (int i = 0; i <= 1; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(150.0f + 10 * i, -5.0f, 20.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			candywhite.draw(shader);
		}
		for (int i = 0; i <= 2; i++) {

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(240.0f + 10 * i, -5.0f * i, -30.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			lolipop.draw(shader);

		}
		for (int i = 0; i <= 2; i++) {

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(220.0f + 10 * i, -5.0f * i, 80.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			lolipop.draw(shader);

		}

		for (int i = 0; i <= 3; i++) {

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(160.0f + 20 * i, -5.0f, 80.0f + 30 * i));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			lolipop.draw(shader);

		}
		for (int i = 0; i <= 3; i++) {

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(170.0f + 20 * i, -5.0f, 60.0f + 30 * i));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			lolipop.draw(shader);

		}

		for (int i = 0; i <= 1; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(205.0f + 10 * i, 0.0f, 50.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.55f, 0.55f, 0.55f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			cotton.draw(shader);
		}
		for (int i = 0; i <= 1; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(205 + 10 * i, 0.0f, 55.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.55f, 0.55f, 0.55f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			cotton.draw(shader);
		}

		for (int i = 0; i <= 1; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(260.0f + 10 * i, 0.0f, -5.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.55f, 0.55f, 0.55f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			cotton.draw(shader);
		}
		for (int i = 0; i <= 1; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(260.0f + 10 * i, 0.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.55f, 0.55f, 0.55f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			cotton.draw(shader);
		}

		for (int i = 0; i <= 3; i++) {

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(210.0f + 20 * i, -5.0f, -50.0f - 30 * i));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.55f, 0.55f, 0.55f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			cotton.draw(shader);

		}
		for (int i = 0; i <= 3; i++) {

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(170.0f + 20 * i, -5.0f, -20.0f - 40 * i));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.55f, 0.55f, 0.55f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			cotton.draw(shader);

		}

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(190.0f, 0.0f, -40.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(200.0f, 200.0f, 200.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		gingerbread.draw(shader);

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(260.0f, 0.0f, 90.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(200.0f, 200.0f, 200.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -35.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		gingerbread.draw(shader);

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(150.0f, 0.0f, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		candies.draw(shader);
		for (int i = 0; i < 3; i++)
		{
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(260.0f, 0.0f, 130.0f + 10 * i));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			candyv2.draw(shader);
		}

		for (int i = 0; i < 3; i++)
		{
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(270.0f, 0.0f, -80.0f + 10 * i));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			candyv2.draw(shader);
		}


		//snowmen		
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				ModelMatrix = glm::mat4(1.0);
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-90.0f + 10 * i, -5.0f, -80.0f - 10 * j));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				snowman.draw(shader);
			}
		}





		//forest
		for (int i = 0; i < f / 4 + 1; i++)
			if (i < f / 4) {
				for (int j = 0; j < 4; j++)
				{
					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-250.0f + 10 * i, -10.0f, 0.0f + 30 * j));
					ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					tree.draw(shader);
				}
			}
			else {
				for (int j = 0; j < f - (f / 4) * 4; j++)
				{
					ModelMatrix = glm::mat4(1.0);
					ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-250.0f + 10 * i, -10.0f, 0.0f + 30 * j));
					ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
					ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
					MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

					tree.draw(shader);
				}
			}
		{

		}

		//random trees
		for (int i = 0; i < 2; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(250.0f + 10 * i, -10.0f, -200.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			tree.draw(shader);
		}
		for (int i = 0; i < 2; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(250.0f + 10 * i, -10.0f, -220.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			tree.draw(shader);
		}

		for (int i = 0; i < 2; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(100.0f + 10 * i, -10.0f, -90.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			tree.draw(shader);
		}
		for (int i = 0; i < 2; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(100.0f + 10 * i, -10.0f, -110.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			tree.draw(shader);
		}

		for (int i = 0; i < 2; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(100.0f + 10 * i, -10.0f, -110.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			tree.draw(shader);
		}

		for (int i = 0; i < 2; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-180.0f + 10 * i, -10.0f, -240.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			tree.draw(shader);
		}

		for (int i = 0; i < 2; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-260.0f + 10 * i, -10.0f, -155.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.10f, 0.10f, 0.10f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			tree.draw(shader);
		}

		for (int i = 0; i < 27; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-250.0f + 20 * i, -10.0f, -260.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.15f, 0.15f, 0.15f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			treev2.draw(shader);
		}
		//indiana tunnel trees
		for (int i = 0; i < 8; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(160.0f - 40 * i, -10.0f, 200.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.15f, 0.15f, 0.15f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			treev2.draw(shader);
		}
		for (int i = 0; i < 8; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(160.0f - 40 * i, -10.0f, 280.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.15f, 0.15f, 0.15f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			treev2.draw(shader);
		}
		//indina tunnel snowman
		for (int i = 0; i < 8; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(140.0f - 40 * i, -10.0f, 200.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			snowman.draw(shader);
		}
		for (int i = 0; i < 8; i++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(140.0f - 40 * i, -10.0f, 280.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4.0f, 4.0f, 4.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			snowman.draw(shader);
		}

		//camfire indina
		for (int i = 0; i < 3; i++)
		{
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(170.0f + 30 * i, 5.0f, 200.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(9.0f, 9.0f, 9.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			campfire.draw(shader);
		}
		for (int i = 0; i < 3; i++)
		{
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(170.0f + 30 * i, 5.0f, 290.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(9.0f, 9.0f, 9.0f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			campfire.draw(shader);
		}

		//arrow home

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-140.0f, -5.0f, -45.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(12.08f, 12.08f, 12.08f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		arrowhome.draw(shader);


		//barrel
		for (int i = 0; i < 3; i++)
		{
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-140.0f, -9.0f, 10.0f + 30 * i));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.08f, 0.08f, 0.08f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			barrel.draw(shader);
		}

		//key
		if (!okkey) {
			ModelMatrixk = glm::mat4(1.0);
			ModelMatrixk = glm::translate(ModelMatrixk, glm::vec3(-140.0f, 0.0f, 10.0f));
			ModelMatrixk = glm::rotate(ModelMatrixk, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrixk = glm::scale(ModelMatrixk, glm::vec3(2.0f, 2.0f, 2.0f));
		}
		if (okkey && keyy < 4) {
			ModelMatrixk = glm::translate(ModelMatrixk, glm::vec3(0, 3.0f, 0));
			keyy++;
		}
		glm :: mat4 MVPk = ProjectionMatrix * ViewMatrix * ModelMatrixk;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVPk[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrixk[0][0]);

		key.draw(shader);
		
		//portal
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(150.0f, -5.0f, 240.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.15f, 0.15f, 0.15f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			portal.draw(shader);
	

		//xsign

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-210.0f, -10.0f, 240.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(65.0f, 65.0f, 65.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		xsign.draw(shader);

		if (glfwGetTime() - timeCandy > 1.5 && okcandy)
		{
			okcandy = false;
		}
		//candytask
		if (okcandy) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-220.0f, -5.0f, 190.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.2f, 1.2f, 1.2f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			lolipop.draw(shader);
		}
		if (okcandy2) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(151.0f, -5.0f, 59.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.2f, 1.2f, 1.2f));
			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			lolipop.draw(shader);
		}


		

		snowShader.use();
		GLuint MatrixID4 = glGetUniformLocation(snowShader.getId(), "MVP");
		GLuint ModelMatrixID4 = glGetUniformLocation(snowShader.getId(), "model");
		int m = 0;
		for (int i = 0; i < 35; i++)
		{
			for (int j = 0; j < 35; j++)
			{
				x = rand() % 10;
				if (ok2[m]) {
					ModelMatrixs2[m] = glm::mat4(1.0);
					ModelMatrixs2[m] = glm::translate(ModelMatrixs2[m], glm::vec3(360.0f - 20.0f * i, 500.0f+2.0f*x, 360.0f - 20.0f * j));
					ModelMatrixs2[m] = glm::scale(ModelMatrixs2[m], glm::vec3(0.005f, 0.005f, 0.005f));


					ok2[m] = false;
				}
				else {
					if (ModelMatrixs2[m][3][1] > 0) {
						ModelMatrixs2[m] = glm::translate(ModelMatrixs2[m], glm::vec3(0, -100000.0f * deltaTime, 0));
						//printf("vvvvvvvvvvvvvvvvv: %f\n", ModelMatrixs2[m][3][1]);
					}
					else {
						ok2[m] = true;
					}
				}
				//printf("vvvvvvvvvvvvvvvvv: %f\n", ModelMatrixs2[m][3][1]);
				glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrixs2[m];
				glUniformMatrix4fv(MatrixID4, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID4, 1, GL_FALSE, &ModelMatrixs2[m][0][0]);
				glUniform3f(glGetUniformLocation(snowShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
				glUniform3f(glGetUniformLocation(snowShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
				glUniform3f(glGetUniformLocation(snowShader.getId(), "viewPos"), fps.getCameraPosition().x, fps.getCameraPosition().y, fps.getCameraPosition().z);
				snowflake.draw(snowShader);
				m++;

			}
		}
		m = 0;
		for (int i = 0; i < 35; i++)
		{
			for (int j = 0; j < 35; j++)
			{
				x = rand() % 10;
				if (ok3[m]) {
					ModelMatrixs3[m] = glm::mat4(1.0);
					ModelMatrixs3[m] = glm::translate(ModelMatrixs3[m], glm::vec3((360.0f - 20.0f * i), 350.0f - 2.0f * x, (360.0f - 20.0f * j)));
					ModelMatrixs3[m] = glm::scale(ModelMatrixs3[m], glm::vec3(10.0f, 10.0f, 10.0f));
					ModelMatrixs3[m] = glm::rotate(ModelMatrixs3[m], -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
					ok3[m] = false;

				}
				if (!ok3[m]) {
					if (ModelMatrixs3[m][3][1] > 0) {
						ModelMatrixs3[m] = glm::translate(ModelMatrixs3[m], glm::vec3(0, 0, -100.0f * deltaTime));
						//printf("m   %d\n", m);
						//printf("heeeeeeeey: %f\n", ModelMatrixs3[m][3][1]);
					}
					else {
						ok3[m] = true;
					}
				}
				//printf("vvvvvvvvvvvvvvvvv: %f              %f                 %f\n", ModelMatrixs3[m][3][0], ModelMatrixs3[m][3][1], ModelMatrixs3[m][3][2]);
				//printf("heeeeeeeey: %f\n", ModelMatrixs3[m][3][1]);
				glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrixs3[m];
				glUniformMatrix4fv(MatrixID4, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID4, 1, GL_FALSE, &ModelMatrixs3[m][0][0]);
				glUniform3f(glGetUniformLocation(snowShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
				glUniform3f(glGetUniformLocation(snowShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
				glUniform3f(glGetUniformLocation(snowShader.getId(), "viewPos"), fps.getCameraPosition().x, fps.getCameraPosition().y, fps.getCameraPosition().z);
				snowflake2.draw(snowShader);
				m++;


			}
		}


		ok = false;






		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		window.update();
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void processKeyboardInput()
{
	float cameraSpeed = 30 * deltaTime;
	float playerSpeed = 15 * deltaTime;

	//translation
	if (window.isPressed(GLFW_KEY_W))
		camera.keyboardMoveFront(cameraSpeed);
	if (window.isPressed(GLFW_KEY_S))
		camera.keyboardMoveBack(cameraSpeed);
	if (window.isPressed(GLFW_KEY_A))
		camera.keyboardMoveLeft(cameraSpeed);
	if (window.isPressed(GLFW_KEY_D))
		camera.keyboardMoveRight(cameraSpeed);
	if (window.isPressed(GLFW_KEY_R))
		camera.keyboardMoveUp(cameraSpeed);
	if (window.isPressed(GLFW_KEY_F))
		camera.keyboardMoveDown(cameraSpeed);

	//rotation
	/*if (window.isPressed(GLFW_KEY_LEFT))
		camera.rotateOy(cameraSpeed);
	if (window.isPressed(GLFW_KEY_RIGHT))
		camera.rotateOy(-cameraSpeed);
	if (window.isPressed(GLFW_KEY_UP))
		camera.rotateOx(cameraSpeed);
	if (window.isPressed(GLFW_KEY_DOWN))
		camera.rotateOx(-cameraSpeed);*/

	if (window.isPressed(GLFW_KEY_UP)) {
		ModelMatrixp = glm::translate(ModelMatrixp, glm::vec3(0, -playerSpeed/1.5, 0));
		fps.keyboardMoveFront(playerSpeed);
	}
		
	if (window.isPressed(GLFW_KEY_RIGHT)) {
		ModelMatrixp = glm::rotate(ModelMatrixp,  - 10 * playerSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		fps.rotateOy(-10 * playerSpeed);
	}
		
	if (window.isPressed(GLFW_KEY_LEFT)) {
		ModelMatrixp = glm::rotate(ModelMatrixp, 10 * playerSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		fps.rotateOy(10 * playerSpeed);
	}
		
	if (window.isPressed(GLFW_KEY_DOWN)) {
		ModelMatrixp = glm::translate(ModelMatrixp, glm::vec3(0, playerSpeed/1.5, 0));
		fps.keyboardMoveBack(playerSpeed);
	}
		
}