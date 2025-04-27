#include "view.h"

View::View(std::shared_ptr<Model> model) : model(model) {}

void View::update() {}

void View::renderDocument() const {}