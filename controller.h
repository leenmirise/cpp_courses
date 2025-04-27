#pragma once
#include <memory>
#include "model.h"
#include "view.h"

class Controller {
public:
    Controller(std::shared_ptr<Model> model, std::shared_ptr<View> view);

    void onCreateNewDocument();

    void onImportDocument(const std::string& filename);

    void onExportDocument(const std::string& filename) const;

    template <typename T, typename... Args>
    void onCreatePrimitive(Args&&... args);

    void onRemovePrimitive(size_t index);

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<View> view;
};
