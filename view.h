#pragma once
#include <memory>
#include "model.h"

class View {
public:
    View(std::shared_ptr<Model> model);

    void update();

    void renderDocument() const;

private:
    std::shared_ptr<Model> model;
};
