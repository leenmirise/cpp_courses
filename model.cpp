#include "model.h"

Model::Model(){}

void Model::createNewDocument(){}

Document* Model::getCurrentDocument() {return nullptr;}

bool Model::importDocument(const std::string& filename) {return true;}

bool Model::exportDocument(const std::string& filename) const {return true;}