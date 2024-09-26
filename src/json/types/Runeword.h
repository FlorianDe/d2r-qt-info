#ifndef RUNEWORD_H
#define RUNEWORD_H

#include <nlohmann/json.hpp>

namespace types::json {
struct Runeword {
	std::string title;															// NOLINT(*-identifier-naming)
	bool ladder = false;														// NOLINT(*-identifier-naming)
	int level = 0;																	// NOLINT(*-identifier-naming)
	std::vector<std::string> runes;									// NOLINT(*-identifier-naming)
	std::optional<std::string> tinfos;							// NOLINT(*-identifier-naming)
	std::optional<std::vector<std::string>> ttypes; // NOLINT(*-identifier-naming)
	std::optional<std::string> version;							// NOLINT(*-identifier-naming)
	std::vector<std::string> description;						// NOLINT(*-identifier-naming)
};

inline void from_json(const nlohmann::json& j, Runeword& rw) {
	// Mandatory fields
	j.at("title").get_to(rw.title);
	j.at("runes").get_to(rw.runes);
	j.at("description").get_to(rw.description);

	// Optional fields with defaults or std::optional
	if (j.contains("ladder") && !j["ladder"].is_null()) {
		rw.ladder = j["ladder"].get<bool>();
	} else {
		rw.ladder = false; // Default to false if not present
	}

	if (j.contains("level") && !j["level"].is_null()) {
		rw.level = j["level"].get<int>();
	} else {
		rw.level = 99; // Default to 0 if not present
	}

	if (j.contains("tinfos") && !j["tinfos"].is_null()) {
		rw.tinfos = j["tinfos"].get<std::string>();
	} else {
		rw.tinfos = std::nullopt; // Set to nullopt if not present
	}

	if (j.contains("ttypes") && !j["ttypes"].is_null()) {
		rw.ttypes = j["ttypes"].get<std::vector<std::string>>();
	} else {
		rw.ttypes = std::nullopt; // Set to nullopt if not present
	}

	if (j.contains("version") && !j["version"].is_null()) {
		rw.version = j["version"].get<std::string>();
	} else {
		rw.version = std::nullopt; // Set to nullopt if not present
	}
}

// inline void to_json(nlohmann::json& j, const RuneWord& rw) {
//     j = nlohmann::json{{"name", rw.name}, {"level", rw.level}, {"attributes",
//     rw.attributes}};
// }
} // namespace types::json

#endif // RUNEWORD_H
