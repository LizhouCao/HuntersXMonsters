#pragma once
#include "Hunter.h"
#include "Bullet.h"
#include "Monster.h"

class MyHunter: public Hunter
{
public:

private:
	// status
	int life;
	float reloadTimer;
	
	// attributes
	int maxLife = 3;
	float speed = 15.0f;
	float bulletSpeed = 30.0f;
	float reloadDuration = 1.0f;
	float radius = 10.0f;

	// colors
	vec3 bulletColor;
	vec3 bodyColor;
	vec3 headColor;
	vec3 weaponColor;

	// define your variables
	Monster* targetMonster = nullptr;

/*****************************/
// functions you need to complete
public:
	MyHunter(vec2 _position, int _ID);
	void update(float _deltaTime, const vector<Monster*> _monsters, const vector<Hunter*> _players) override;
private:
	bool circleBoundingVolume(vec2 c1, vec2 c2, float r1, float r2);

/*****************************/

#pragma region ProvidedFuctions

public:
	void collisionDetection(vector<Monster*> _monsters) override;
	
	void draw() override;
	void getDPS(int _dps) override;
	void getScore(int _score) override;

private:
	void fire();
	void drawLifeBar();
	void upgrade(unsigned int _armor, unsigned int _speed, unsigned int _weapon, unsigned int _bullet);

#pragma endregion ProvidedFuctions
};


