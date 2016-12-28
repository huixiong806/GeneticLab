#ifndef CHUNK_H
#define CHUNK_H
#include <memory>
#include <unordered_set>
#include "Food.h"
#include "Bloop.h"
class Bloop;
class Food;
class Chunk
{
public:
	void addBloop(std::shared_ptr<Bloop> bloop_);
	void removeBloop(std::shared_ptr<Bloop> bloop_);
	void addFood(std::shared_ptr<Food> food_);
	void removeFood(std::shared_ptr<Food> food_);
	std::unordered_set<std::shared_ptr<Bloop>>& bloopSet();
	std::unordered_set<std::shared_ptr<Food>>& foodSet();
private:
	std::unordered_set<std::shared_ptr<Bloop>> bloop;
	std::unordered_set<std::shared_ptr<Food>> food;
};
#endif