#ifndef GRAPH_H
#define GRAPH_H
#include "json/types/types.h"
#include <string>
#include <stack>

namespace Graph {
struct ItemStackEntry {
	std::string name;
	const types::json::ItemType* itemType;
	int level; // Track the depth level
};

void dfs(const types::json::RunewordItemTypesHierarchy& hierarchy,
				 const std::function<void(const ItemStackEntry&)>& callback,
				 const std::optional<std::string>& startingElement = std::nullopt);
}; // namespace Graph

#endif // GRAPH_H
