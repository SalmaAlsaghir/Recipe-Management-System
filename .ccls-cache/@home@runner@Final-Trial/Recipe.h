#ifndef RECIPE_H
#define RECIPE_H
#pragma once  // Include guard to prevent double inclusion

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <exception>
#include <set>
#include <map>

using namespace std;

class RecipeItem {
public:
    virtual string getName() const = 0;
    virtual double getQuantity() const = 0;
    virtual string toString() const = 0;
};

class Ingredient : public RecipeItem {
private:
    string name;
    double quantity;

public:
    Ingredient(const std::string& name, double quantity);
    string getName() const override;
    double getQuantity() const override;
    string toString() const override;
};

class Recipe {
public:
    string name;
    string description;
    vector<RecipeItem*> items;

    Recipe(const string& name, const string& description);
    void addItem(RecipeItem* item);
    void display() const;
    string getName() const;
    string getDescription() const;
    ~Recipe();
};

class RecipeManager {
private:
    vector<Recipe*> recipes;
    const string filename = "recipes.txt";

public:
    RecipeManager();
    ~RecipeManager();
    bool addIngredient(Recipe* recipe, set<string>& addedIngredients);
    void addExtraIngredientsToRecipe(Recipe* recipe);
    void addIngredientsToRecipe(Recipe* recipe, int numIngredients);
    void addRecipe();
    void displayRecipes() const;
    void saveRecipesToFile();
    void loadRecipesFromFile();
    void run();
};

#endif
