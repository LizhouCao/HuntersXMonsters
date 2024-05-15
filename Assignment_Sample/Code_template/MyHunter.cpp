#include "MyHunter.h"

MyHunter::MyHunter(vec2 _position, int _ID)
{
	this->ID = _ID;

	/****************************/
	// write your code below
	// customize your player

	// customize the name of your player
	playerName = "hunter" + to_string(ID);

	// upgrade your player by calling the upgrade(armor, speed, weapon, bullet) function
	// armor + speed + weapon + bullet need to be <= 10, otherwise your player won't be upgraded
	upgrade(0, 0, 0, 0);

	// customize the color of your player
	bodyColor = vec3(1.0f, 0.0f, 0.0f);
	headColor = vec3(0.7f, 0.1f, 0.1f);
	weaponColor = vec3(0.0f, 0.0f, 0.0f);
	bulletColor = vec3(0.0f, 0.0f, 0.0f);
	// write your code above
	/******************************/

	this->position = _position;
	reloadTimer = reloadDuration * (1.0f + rand() % 10 / 20.0f);
	life = maxLife;
}

void MyHunter::update(float _deltaTime, const vector<Monster*> _monsters, const vector<Hunter*> _players)
{
	if (isActived == true) {
		reloadTimer -= _deltaTime;
		if (reloadTimer < 0.0f) {
			fire();
			reloadTimer = reloadDuration * (1.0f + rand() % 10 / 20.0f);
		}

		/*********************************************/
		// write your code below
		// update hunter's position based on speed and deltaTime
		// update hunter's rotation


		// write your code above
		/************************************************************/
		if (this->position.x < -300.0f + radius)
			this->position.x = -300.0f + radius;
		if (this->position.y < -300.0f + radius)
			this->position.y = -300.0f + radius;
		if (this->position.x > 300.0f - radius)
			this->position.x = 300.0f - radius;
		if (this->position.y > 300.0f - radius)
			this->position.y = 300.0f - radius;
	}
}

void MyHunter::collisionDetection(vector<Monster*> _monsters)
{
	if (isActived == true) {
		for (int i = 0; i < _monsters.size(); i++) {
			if (_monsters[i]->isActived) {
				if (circleBoundingVolume(this->position, _monsters[i]->position, this->radius, _monsters[i]->radius)) {
					this->life--;
					if (this->life <= 0) {
						bodyColor = 0.5f * bodyColor;
						headColor = 0.5f * headColor;
						weaponColor = 0.5f * weaponColor;
						isActived = false;
						return;
					}
					_monsters[i]->attackPlayer(this->ID);
				}
			}
		}
	}
}

void MyHunter::draw()
{
	glPushMatrix();

	glTranslatef(position.x, position.y, 0);
	drawLifeBar();

	glRotatef(rotation, 0, 0, 1);

	glColor3f(bodyColor.x, bodyColor.y, bodyColor.z);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 30; i++) {
		float angle = 2 * pi<float>() * i / 30;
		glVertex2f(radius * cos(angle), radius * sin(angle));
	}
	glEnd();

	glColor3f(weaponColor.x, weaponColor.y, weaponColor.z);
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(radius * 1.5f, -1.0f);
	glVertex2f(radius * 1.5f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();

	glColor3f(headColor.x, headColor.y, headColor.z);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 30; i++) {
		float angle = 2 * pi<float>() * i / 30;
		glVertex2f(0.5f * radius * cos(angle), 0.5f * radius * sin(angle));
	}
	glEnd();

	glPopMatrix();
}

void MyHunter::drawLifeBar()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-1.0f * radius, 1.2f * radius);
	glVertex2f((-1.0f + 2.0f * life / maxLife) * radius, 1.2f * radius);
	glVertex2f((-1.0f + 2.0f * life / maxLife) * radius, 1.5f * radius);
	glVertex2f(-1.0f * radius, 1.5f * radius);
	glEnd();
}


void MyHunter::fire()
{
	Bullet::bullets.push_back(new Bullet(this->position, this->rotation, this, this->bulletSpeed, this->bulletColor));
}

void MyHunter::getDPS(int _dps)
{
	dps += _dps;
}

void MyHunter::getScore(int _score)
{
	score += _score;
}

bool MyHunter::circleBoundingVolume(vec2 c1, vec2 c2, float r1, float r2)
{
	/***************************************/
	// return if two circle bounding volumes are overlapping or not
	return false;
	/***************************************/
}

void MyHunter::upgrade(unsigned int _armor, unsigned int _speed, unsigned int _weapon, unsigned int _bullet)
{
	if (_armor + _speed + _weapon + _bullet > 10)
		return;
	maxLife += _armor;
	speed *= 1.0f + _speed / 10.0f;
	reloadDuration *= 1.0f - _weapon / 15.0f;
	bulletSpeed *= 1.0f + _bullet / 10.0f;
}
