#include "Chunk.h"
void Chunk::addBloop(std::shared_ptr<Bloop> bloop_)
{
	bloop.insert(bloop_);
}
void Chunk::removeBloop(std::shared_ptr<Bloop> bloop_)
{
	bloop.erase(bloop_);
}
void Chunk::addFood(std::shared_ptr<Food>food_)
{
	food.insert(food_);
}
void Chunk::removeFood(std::shared_ptr<Food>food_)
{
	food.erase(food_);
}
std::unordered_set<std::shared_ptr<Food>>& Chunk::foodSet()
{
	return food;
}
std::unordered_set<std::shared_ptr<Bloop>>& Chunk::bloopSet()
{
	return bloop;
}