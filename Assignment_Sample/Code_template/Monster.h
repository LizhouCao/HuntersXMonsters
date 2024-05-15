#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>

#include <vector>

#include "Bullet.h"
#include "Hunter.h"

using namespace std;
using namespace glm;

class Hunter;
class Bullet;

class Monster
{
public:
	vec2 position;
	float radius;
	float speed = 15.0f;
	int life;
	bool isActived = true;
	vec2 targetPosition;

	static int g_difficultyLevel;
private:
	float rotation = 0.0f;
	float rotateSpeed = 90.0f;
	int maxLife;
	Hunter* target = NULL;
public:
	Monster() {
		float angle = glm::radians((float)(rand() % 360));
		float range = rand() % 50;
		position = vec2(range * cos(angle), range * sin(angle));
		int size = rand() % 3 + 8;
		radius = size;

		if (g_difficultyLevel > 0)
			maxLife = g_difficultyLevel;
		else
			maxLife = 1;
		life = maxLife;
	}
	void update(float _deltaTime, vector<Hunter*> players);
	void collisionDetection(vector<Bullet*> bullets);
	void draw();
	void attackPlayer(int _playerID);

private:
	void drawEye();
	void drawMouth();
	void drawLeg();
	void drawLifeBar();
};

