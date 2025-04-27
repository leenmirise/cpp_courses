#pragma once
#include <memory>
#include "document.h"

class Model {
public:
    Model();

    void createNewDocument();

    Document* getCurrentDocument();

    bool importDocument(const std::string& filename);

    bool exportDocument(const std::string& filename) const;

private:
    std::unique_ptr<Document> currentDocument;
};
