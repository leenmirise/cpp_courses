#include "document.h"

void Document::addPrimitive(std::unique_ptr<Primitive> primitive){}

void Document::removePrimitive(size_t index){}

const Primitive* Document::getPrimitive(size_t index) const {return nullptr;}

void Document::clear(){}

bool Document::importFromFile(const std::string& filename) {return true;}

bool Document::exportToFile(const std::string& filename) const {return true;}