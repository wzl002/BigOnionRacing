#include "RigidBodyComponent.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/ECS/GameWorld.h"

RigidBodyComponent::RigidBodyComponent(btRigidBody* _body)
	: rigidBody(_body)
{
}


void RigidBodyComponent::fixedUpdate(float deltaTime)
{
	// position
	glm::mat4 model = glm::mat4(1.0f);
	btTransform bTransform;
	rigidBody->getMotionState()->getWorldTransform(bTransform);
	bTransform.getOpenGLMatrix(glm::value_ptr(model));
	
	gameObject->transform.matrix = model;
	/*gameObject->transform.position = Vector3f(bTransform.getOrigin().x(), bTransform.getOrigin().y(), bTransform.getOrigin().z());

	// rotation
	btMatrix3x3 rotMatrix = btMatrix3x3(bTransform.getRotation());
	float z, y, x;
	rotMatrix.getEulerZYX(z, y, x);
	gameObject->transform.rotation = Vector3f(x, y, z);*/
}

void RigidBodyComponent::onAddToGameWorld()
{
	// position
	/*btTransform bTransform;
	rigidBody->getMotionState()->getWorldTransform(bTransform);
	gameObject->transform.position = Vector3f(bTransform.getOrigin().x(), bTransform.getOrigin().y(), bTransform.getOrigin().z());

	// rotation
	btMatrix3x3 rotMatrix = btMatrix3x3(bTransform.getRotation());
	float z, y, x;
	rotMatrix.getEulerZYX(z, y, x);
	gameObject->transform.rotation = Vector3f(x, y, z);

	//TODO: ABSOLUTELY FIX THIS
	/*
	Vector3f pos = gameObject->transform.position;
	trans.setOrigin(btVector3(gameObject->transform.position.x, pos.y, pos.z));
	rigidBody->setWorldTransform(trans);
	*/

	gameObject->world->physicsWorld->addRigidBody(rigidBody);
}
