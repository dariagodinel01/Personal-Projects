#include "camera.h"

Camera::Camera(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

Camera::Camera()
{
	this->cameraPosition = glm::vec3(0.0f, 0.0f, 100.0f);
	this->cameraViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = cameraViewDirection;
	this->cameraUp = cameraUp;
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

Camera::~Camera()
{
}

void Camera::rotateOx(float angle)
{
	//TODO
	cameraViewDirection=
	glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, cameraRight) *
		glm::vec4(cameraViewDirection, 1)));
	cameraUp = 
		glm::normalize(glm::cross(cameraRight, cameraViewDirection));

}

void Camera::rotateOy (float angle)
{
	//TODO
	cameraViewDirection =
		glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, cameraUp) *
			glm::vec4(cameraViewDirection, 1)));
	cameraRight =
		glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, cameraUp) *
			glm::vec4(cameraRight, 1)));
}

void Camera::translateUp(float speed) //R
{
	cameraPosition += speed * cameraUp;
}

void Camera::translateDown(float speed) //F
{
	//TODO
	cameraPosition -= speed* cameraUp;
}

void Camera::translateFront(float speed) //W
{
	//TODO
	cameraPosition += speed * cameraViewDirection;
}

void Camera::translateBack(float speed) //S
{
	//TODO
	cameraPosition -= speed * cameraViewDirection;
}


glm::vec3 Camera::getCameraPosition()
{
	return cameraPosition;
}

glm::vec3 Camera::getCameraViewDirection()
{
	return cameraViewDirection;
}

glm::vec3 Camera::getCameraUp()
{
	return cameraUp;
}

void Camera::setCameraPosition(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
}

void Camera::setCameraUp(glm::vec3 cameraUp)
{
	this->cameraUp = cameraUp;
}

void Camera::setCameraViewDirection(glm::vec3 cameraViewDirection)
{
	this->cameraViewDirection = cameraViewDirection;
}

