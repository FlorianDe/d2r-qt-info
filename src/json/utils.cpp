#include "utils.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <iostream>

namespace JsonUtils {

nlohmann::ordered_json readJsonFile(const QString& resourcePath) {
	// Open the resource file using QFile
	QFile file(resourcePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open JSON resource:" << resourcePath;
		return {}; // Return an empty JSON object in case of failure
	}

	// Read the content of the file into a QString
	QTextStream in(&file);
	const QString jsonContent = in.readAll();
	file.close();

	// Convert QString to std::string for nlohmann::json
	std::string jsonString = jsonContent.toStdString();

	// Parse the JSON data using nlohmann::json
	nlohmann::ordered_json jsonData;
	try {
		jsonData = nlohmann::ordered_json::parse(jsonString);
	} catch (nlohmann::json::parse_error& e) {
		std::cerr << "JSON parse error: " << e.what() << std::endl;
		return {}; // Return an empty JSON object in case of parse failure
	}

	// Example of accessing the JSON data (assuming an array of runes)
	// std::cout << "Loaded JSON data: " << jsonData.dump(4) << std::endl;

	return jsonData; // Return the parsed JSON data
}

} // namespace JsonUtils