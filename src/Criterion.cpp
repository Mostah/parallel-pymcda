#include "Criterion.h"
#include <iostream>
#include <string>

Criterion::Criterion(std::string id) {
  id_ = id;
  direction_ = 1;
  weight_ = 0.;
}

Criterion::Criterion(std::string id, int direction, float weight) {
  id_ = id;
  direction_ = direction;
  weight_ = weight;
}

Criterion::Criterion(const Criterion &crit) {
  id_ = crit.getId();
  direction_ = crit.getDirection();
  weight_ = crit.getWeight();
}

Criterion::Criterion(std::string id, float weight) {
  id_ = id;
  direction_ = 1;
  weight_ = weight;
}

std::string Criterion::getId() const { return id_; }

void Criterion::setId(std::string id) { id_ = id; }

int Criterion::getDirection() const { return direction_; }

void Criterion::setDirection(int direction) { direction_ = direction; }

float Criterion::getWeight() const { return weight_; }

void Criterion::setWeight(float weight) { weight_ = weight; }

std::ostream &operator<<(std::ostream &out, const Criterion &crit) {
  std::string dir = "";
  if (crit.direction_ == 1) {
    dir = "+";
  } else {
    dir = "-";
  }
  out << "Criterion(id : " << crit.id_ << ", direction : " << dir
      << ", weight : " << crit.weight_ << ")";
  return out;
}

Criterion::~Criterion() {}