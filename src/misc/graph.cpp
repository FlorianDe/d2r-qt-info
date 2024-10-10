
#include "graph.h"

namespace Graph {

void dfs(const types::json::RunewordItemTypesHierarchy& hierarchy,
				 const std::function<void(const ItemStackEntry&)>& callback,
				 const std::optional<std::string>& startingElement) {
	std::stack<ItemStackEntry> stack;

	for (const auto& [typeName, itemType] : hierarchy.itemTypes) {
		stack.push({typeName, &itemType, 0});
	}

	std::optional<std::string> breakPoint = std::nullopt;
	while (!stack.empty()) {
		auto entry = stack.top();
		stack.pop();

		if (breakPoint.has_value() && entry.name == breakPoint.value()) {
			break;
		}

		if (!breakPoint.has_value() && entry.name == startingElement) {
			if (!stack.empty()) {
				breakPoint = stack.top().name;
			} else {
				breakPoint = "";
			}
		}

		if (!startingElement.has_value() || (startingElement.has_value() && breakPoint.has_value())) {
			callback(entry);
		}

		if (entry.itemType->subtypes) {
			for (const auto& [subtypeName, subtypeItem] : entry.itemType->subtypes.value()) {
				stack.push({subtypeName, &subtypeItem, entry.level + 1});
			}
		}
	}
};

} // namespace Graph