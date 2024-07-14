#include "Recipe.h"

using namespace std;

Ingredient::Ingredient(const string& name, double quantity) : name(name), quantity(quantity) {
}

string Ingredient::getName() const {
    return name;
}

double Ingredient::getQuantity() const {
    return quantity;
}

string Ingredient::toString() const {
    return name + ": " + to_string(quantity) + " units";
}

Recipe::Recipe(const string& name, const string& description) : name(name), description(description) {
}

void Recipe::addItem(RecipeItem* item) {
    items.push_back(item);
}

void Recipe::display() const {
    // Implementation of display
      cout << "\n╭──── 🍽️ Recipe: " << name << " ────╮\n";
      cout << "│ 📝 Description: " << description << " │\n";
      cout << "│ 🥦 Ingredients:\n";
      for (const RecipeItem* item : items) {
          cout << "│ - " << item->toString() << endl;
      }
      cout << "╰───────────────────────╯\n";
  }


string Recipe::getName() const {
    return name;
}

string Recipe::getDescription() const {
    return description;
}

Recipe::~Recipe() {
    for (RecipeItem* item : items) {
        delete item;
    }
}
