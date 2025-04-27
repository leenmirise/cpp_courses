#pragma once
#include <vector>
#include <memory>
#include <string>
#include "primitive.h"

class Document {
public:
    Document() = default;

    void addPrimitive(std::unique_ptr<Primitive> primitive);

    [[maybe_unused]] void removePrimitive(size_t index);

    const Primitive* getPrimitive(size_t index) const;

    // Очистка документа
    void clear();

    bool importFromFile(const std::string& filename);

    bool exportToFile(const std::string& filename) const;

private:
    std::vector<std::unique_ptr<Primitive>> primitives;
};
