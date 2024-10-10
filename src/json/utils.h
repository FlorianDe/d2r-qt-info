#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <QString>
#include <nlohmann/json.hpp>

namespace JsonUtils {

// Function to read JSON from a file path and return a nlohmann::json object
nlohmann::ordered_json readJsonFile(const QString& resourcePath);

} // namespace JsonUtils

#endif // JSONUTILS_H