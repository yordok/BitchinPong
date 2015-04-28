/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Ball.h"

/* Constructor */
Ball::Ball(String ballName, matrix4 pos, vector3 vel) :
	GameObject(ballName, pos, vel, 0.1, 0.1) {
}

/* Destructor */
Ball::~Ball() {
}

/* Init */
void Ball::Init() {
	GameObject::Init();
	meshManager->LoadModelUnthreaded("Minecraft\\CubePrimitive.obj", name, position);
	boundingBox->GenerateBoundingBox();
}

/* Update */
void Ball::Update() {
	GameObject::Update();
	InBounds();
}

/* Draw */
void Ball::Draw() {
	GameObject::Draw();
}

/* Move */
void Ball::Move() {
	position *= glm::translate(velocity);
}

/* SwitchDirection */
void Ball::SwitchDirection(String ballName, String collisName)
{
	//Setting the velocity's x value to negative one, reversing it
	velocity.x *= -1;
	
	//Calculating the center points for both the ball and collision target in the global positioning
	vector3 ballCenter = vector3(meshManager->GetModelMatrix(ballName) * vector4(getCenterPoint(ballName), 1.0f));
	vector3 collisCenter = vector3(meshManager->GetModelMatrix(collisName) * vector4(getCenterPoint(collisName), 1.0f));
	//std::cout << ballCenter.y << ", " << collisCenter.y << std::endl;
	//The difference between the two points is calculated as the velocity's y value
	velocity.y = (ballCenter.y - collisCenter.y)/10.0f;
	//std::cout << velocity.y << std::endl;
	
}

// checks if the ball went passed a player
bool Ball::InBounds(){
	//X Value: Will move back into center position 
	if(position[3][0] > 10 || position[3][0] < -10) {
		velocity = vector3(0.01,0,0);
		position[3][0] = 0;
		position[3][1] = 0;
		return true;
	}

	//Y Value: Will bounce by reversing y value of the velocity
	if(position[3][1] > 3.5 || position[3][1] < -5.5) {
		velocity.y *= -1;
		return true;
	}

	return false;
}

//The function to calculate the center point of a specific matrix (used in the switch direction function
vector3 Ball::getCenterPoint(String targetMatName){
	//The functionality is the same as in the BoundingBox class
	//Getting the proper matrix  and setting up vector3s for the centroid and max/min vertex values
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	std::vector<vector3> vertices = meshManager->GetVertices(targetMatName);
	vector3 centroid;
	vector3 minVertices;
	vector3 maxVertices;
	//Calculating the maximum and minimum values
	for(int i = 0; i < vertices.size(); i++) {
		vector2 vertex = vector2(vertices[i].x, vertices[i].y);

		if(vertex.x < minVertices.x)
			minVertices.x = vertex.x;
		else if(vertex.x > maxVertices.x)
			maxVertices.x = vertex.x;

		if(vertex.y < minVertices.y)
			minVertices.y = vertex.y;
		else if(vertex.y > maxVertices.y)
			maxVertices.y = vertex.y;

		//Getting the centroid to be returned below
		centroid = (minVertices + maxVertices) / 2.0f;
	}
	return centroid;
}
