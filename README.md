# Recipe Management System

Welcome to the Recipe Management System! This system allows you to manage your recipes by adding ingredients, displaying recipes, and saving them to a file. Below is an overview of the classes and functions in the system, along with instructions on how to use it.

## Table of Contents

1. [Overview](#overview)
2. [Classes](#classes)
3. [Functions](#functions)
4. [Usage](#usage)
5. [File Structure](#file-structure)
6. [Error Handling](#error-handling)

## Overview

The Recipe Management System consists of the following main components:

- **Ingredient**: Represents an ingredient with a name and quantity.
- **Recipe**: Represents a recipe with a name, description, and a list of ingredients.
- **RecipeManager**: Manages a collection of recipes, allowing you to add new recipes, display all recipes, save them to a file, and load them from a file.

## Classes

### Ingredient

The `Ingredient` class represents an ingredient in a recipe.

#### Methods

- **Ingredient(const string& name, double quantity)**: Constructor to initialize the ingredient with a name and quantity.
- **string getName() const**: Returns the name of the ingredient.
- **double getQuantity() const**: Returns the quantity of the ingredient.
- **string toString() const**: Returns a string representation of the ingredient.

### Recipe

The `Recipe` class represents a recipe with a name, description, and a list of ingredients.

#### Methods

- **Recipe(const string& name, const string& description)**: Constructor to initialize the recipe with a name and description.
- **void addItem(RecipeItem* item)**: Adds an ingredient to the recipe.
- **void display() const**: Displays the recipe details.
- **string getName() const**: Returns the name of the recipe.
- **string getDescription() const**: Returns the description of the recipe.
- **~Recipe()**: Destructor to clean up dynamically allocated ingredients.

### RecipeManager

The `RecipeManager` class manages a collection of recipes.

#### Methods

- **RecipeManager()**: Constructor to initialize the recipe manager.
- **~RecipeManager()**: Destructor to clean up dynamically allocated recipes.
- **void addRecipe()**: Adds a new recipe.
- **void displayRecipes() const**: Displays all recipes.
- **void saveRecipesToFile()**: Saves all recipes to a file.
- **void loadRecipesFromFile()**: Loads recipes from a file.
- **void run()**: Runs the main program loop.

## Functions

### addIngredient

Adds an ingredient to a recipe, ensuring no duplicates within the recipe or across recipes.

### addExtraIngredientsToRecipe

Allows adding extra ingredients to a recipe.

### addIngredientsToRecipe

Adds a specified number of ingredients to a recipe.

### addRecipe

Prompts the user to enter recipe details and ingredients, and adds the recipe to the manager.

### displayRecipes

Displays all recipes in a structured format.

### saveRecipesToFile

Saves all recipes to a file named "recipes.txt".

### loadRecipesFromFile

Loads recipes from a file named "recipes.txt".

### run

Runs the main program loop, presenting a menu to the user for various operations.

## Usage

1. **Compile the Program**: Compile the program using a C++ compiler.
    ```sh
    g++ -o RecipeManager Recipe.cpp
    ```

2. **Run the Program**: Execute the compiled program.
    ```sh
    ./RecipeManager
    ```

3. **Main Menu**: The main menu offers the following options:
    - Add Recipe
    - Display Recipes
    - Save Recipes to File
    - Exit

## File Structure

- **Recipe.h**: Header file containing the declarations of classes and functions.
- **Recipe.cpp**: Implementation file containing the definitions of classes and functions.
- **recipes.txt**: File used to save and load recipes.

## Error Handling

- Input validation is performed for ingredient names and quantities.
- Errors in file operations are caught and handled gracefully.

Enjoy managing your recipes with the Recipe Management System!
