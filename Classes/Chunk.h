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
	bloopPool& bloopSet();
	foodPool& foodSet();
private:
	bloopPool bloop;
	foodPool food;
};
#endif