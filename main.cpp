#include <iostream>
#include <memory>
#include "model.h"
#include "view.h"
#include "controller.h"

template <typename T, typename... Args>
void Controller::onCreatePrimitive(Args&&... args) {
    auto primitive = std::make_unique<T>(std::forward<Args>(args)...);
    model->getCurrentDocument()->addPrimitive(std::move(primitive));
    view->update();
}

int main() {
    auto model = std::make_shared<Model>();
    auto view = std::make_shared<View>(model);
    auto controller = std::make_shared<Controller>(model, view);

    controller->onCreateNewDocument();
    controller->onCreatePrimitive<Circle>(10.0, 10.0, 5.0);

    return 0;
}