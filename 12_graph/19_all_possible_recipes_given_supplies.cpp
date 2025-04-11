#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
	vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
		unordered_map<string, vector<string>> adj;
		unordered_map<string, int> indegree;//For topological sort using Kahn's algo

		unordered_set<string> supply(supplies.begin(), supplies.end());
		for (int i = 0;i < recipes.size();++i) {
			indegree[recipes[i]] = 0;//Initialize indegree to 0
			for (string& ingredient : ingredients[i]) {
				if (supply.count(ingredient) == 0) {
					//Current ingredient must be a recipe
					adj[ingredient].push_back(recipes[i]);
					indegree[recipes[i]]++;
				}
			}
		}
		//Push all the start points of topological sort
		queue<string> q;
		for (auto& [recipe, indeg] : indegree)
			if (indeg == 0)
				q.push(recipe);

		vector<string> res;
		//Apply Kahn's algo
		while (!q.empty()) {
			string curr_recipe = q.front();
			q.pop();
			res.push_back(curr_recipe);

			for (string& next_recipe : adj[curr_recipe]) {
				indegree[next_recipe]--;
				if (indegree[next_recipe] == 0)
					q.push(next_recipe);
			}
		}
		return res;
	}
};


class Solution {
public:
	vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
		unordered_set<string> availableIngredients(supplies.begin(), supplies.end());
		unordered_map<string, vector<string>> recipeDependencies;
		unordered_map<string, int> remainingIngredients;

		// Initialize remainingIngredients for all recipes
		for (int i = 0; i < recipes.size(); ++i) {
			remainingIngredients[recipes[i]] = ingredients[i].size();
			for (const string& ingredient : ingredients[i]) {
				recipeDependencies[ingredient].push_back(recipes[i]);
			}
		}

		queue<string> processQueue;
		vector<string> preparedRecipes;

		// Start with available supplies (ingredients)
		for (const string& supply : supplies) {
			processQueue.push(supply);
		}

		// Process recipes using BFS (Topological Sorting)
		while (!processQueue.empty()) {
			string currentIngredient = processQueue.front();
			processQueue.pop();

			// If it's a recipe, add to the list of prepared recipes
			if (remainingIngredients.find(currentIngredient) != remainingIngredients.end()) {
				preparedRecipes.push_back(currentIngredient);
			}

			// Reduce the remaining ingredient count for dependent recipes
			for (const string& dependentRecipe : recipeDependencies[currentIngredient]) {
				if (--remainingIngredients[dependentRecipe] == 0) { // All required ingredients are available
					processQueue.push(dependentRecipe);
				}
			}
		}

		return preparedRecipes;
	}
};

// Example usage
// int main() {
//     Solution sol;
//     vector<string> recipes = {"bread", "sandwich", "burger"};
//     vector<vector<string>> ingredients = {{"flour", "water"}, {"bread", "cheese"}, {"sandwich", "patty"}};
//     vector<string> supplies = {"flour", "water", "cheese", "patty"};

//     vector<string> result = sol.findAllRecipes(recipes, ingredients, supplies);

//     for (const string& recipe : result) {
//         cout << recipe << " ";
//     }
//     return 0;
// }
