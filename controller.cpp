#include "controller.h"

Controller::Controller(std::shared_ptr<Model> model, std::shared_ptr<View> view){}

void Controller::onCreateNewDocument(){}

void Controller::onImportDocument(const std::string& filename){}

void Controller::onExportDocument(const std::string& filename) const{}

template <typename T, typename... Args>
void Controller::onCreatePrimitive(Args&&... args){}

void Controller::onRemovePrimitive(size_t index){}