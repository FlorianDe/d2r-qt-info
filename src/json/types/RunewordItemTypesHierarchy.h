#ifndef RUNEWORDITEMTYPESHIERARCHY_HPP
#define RUNEWORDITEMTYPESHIERARCHY_HPP

#include <map>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace types::json {

// Define the JSON parsing library as json
using json = nlohmann::ordered_json;
using namespace std;

// Struct to handle translation for en, de
struct Translation {
	string en;
	string de;
};

// Recursive struct for ItemTypes, where subtypes are also of type ItemType
struct ItemType {
	Translation translation;
	optional<map<string, ItemType>> subtypes; // Recursive subtypes, now optional
};

// Struct for the entire hierarchy
struct RunewordItemTypesHierarchy {
	map<string, ItemType> itemTypes; // Top-level items like Weapons, Body Armors, etc.
};

// Serialization and Deserialization Functions

// to_json and from_json functions for Translation
inline void to_json(json& j, const Translation& t) { j = json{{"en", t.en}, {"de", t.de}}; }

inline void from_json(const json& j, Translation& t) {
	j.at("en").get_to(t.en);
	j.at("de").get_to(t.de);
}

// to_json and from_json functions for ItemType
inline void to_json(json& j, const ItemType& it) {
	j = json{{"translation", it.translation}};
	if (it.subtypes) {
		j["subtypes"] = it.subtypes.value();
	}
}

inline void from_json(const json& j, ItemType& it) {
	j.at("translation").get_to(it.translation);
	if (j.contains("subtypes")) {
		it.subtypes = j.at("subtypes").get<map<string, ItemType>>();
	} else {
		it.subtypes = nullopt; // No subtypes found
	}
}

// to_json and from_json functions for RunewordItemTypesHierarchy
inline void to_json(json& j, const RunewordItemTypesHierarchy& r) { j = r.itemTypes; }

inline void from_json(const json& j, RunewordItemTypesHierarchy& r) { r.itemTypes = j.get<map<string, ItemType>>(); }

} // namespace types::json

#endif // RUNEWORDITEMTYPESHIERARCHY_HPP