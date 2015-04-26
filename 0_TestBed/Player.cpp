/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Player.h"

/* Constructor */
Player::Player(String n, matrix4 pos) : 
	GameObject(n, pos, vector3(0), 0.05f, 0.005f) {
}

/* Destructor */
Player::~Player() {
}

/* Init */
void Player::Init() {
	GameObject::Init();
	meshManager->LoadModelUnthreaded("Minecraft\\MC_Creeper.obj", name, position);
	boundingBox->GenerateBoundingBox();
	position *= glm::translate(-boundingBox->GetScale()/2.0f);
	boundingBox->SetPosition(position);
}

/* Update */
void Player::Update() {
	GameObject::Update();
}

/* Draw */
void Player::Draw() {
	GameObject::Draw();
}

/* Move */
void Player::Move() {
	position *= glm::translate(velocity);
	velocity *= 0.95f;
}

/* MovePlayer */
void Player::MovePlayer(int dir) {
	if(velocity.y < maxSpeed && velocity.y > -maxSpeed)
		velocity.y +=  acceleration * dir;
}

/* InBounds */
bool Player::InBounds() {
<<<<<<< HEAD

=======
>>>>>>> 1cf397df2ba96eea93282c200d94953723db71e8
	return true;
}
