#include "Recipe.h"

RecipeManager::RecipeManager() {
}

RecipeManager::~RecipeManager() {
    for (Recipe* recipe : recipes) {
        delete recipe;
    }
}
map<Recipe*, set<string>> addedIngredientsPerRecipe;
bool RecipeManager::addIngredient(Recipe* recipe, set<string>& addedIngredients) {
    string ingredientName;
    double ingredientQuantity;

    cout << "│ 🥦 Enter ingredient name: ";
    cin.ignore();
    getline(cin, ingredientName);

    // Check if the user's input stream has encountered any errors
    if (cin.fail()) {
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any invalid input
        cout << "│ ❌ Invalid input. Please enter a valid ingredient name.\n";
        return false;
    }

    // Validate and prompt for the quantity of the ingredient.
    while (true) {
        cout << "│   - 📏 Quantity: ";
        if (cin >> ingredientQuantity && ingredientQuantity >= 0) {
            break; // If a valid quantity is entered, exit the loop.
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n│ ❌ Invalid input. Please enter a valid quantity (a non-negative number).\n";
        }
    }

    // Check if the ingredient is already added to this recipe
    if (addedIngredients.find(ingredientName) != addedIngredients.end()) {
        cout << "│ ❌ Ingredient '" << ingredientName << "' has already been added to the recipe.\n";
        return false;
    }

    // Check if the ingredient is already added to any recipe
    if (addedIngredientsPerRecipe[recipe].find(ingredientName) != addedIngredientsPerRecipe[recipe].end()) {
        cout << "│ ❌ Ingredient '" << ingredientName << "' has already been added to another recipe.\n";
        return false;
    }

    // Create a new ingredient object with the provided name and quantity.
    RecipeItem* ingredient = new Ingredient(ingredientName, ingredientQuantity);
    if (!ingredient) {
        cout << "│ ❌ Failed to create an ingredient object. Aborting.\n";
        // Handle any other exception-specific actions if needed
        return false;
    }

    // Add the ingredient to the recipe.
    recipe->addItem(ingredient);
    // Add the ingredient to the set of added ingredients for this recipe
    addedIngredients.insert(ingredientName);
    addedIngredientsPerRecipe[recipe].insert(ingredientName);

    return true;
}



// Function to add extra ingredients to a recipe
void RecipeManager::addExtraIngredientsToRecipe(Recipe* recipe) {
    // A set to keep track of added ingredients to avoid duplication
    set<string> addedIngredients;

    do {
        if (!addIngredient(recipe, addedIngredients)) {
            // If adding the ingredient fails, you can give the user another chance
            continue;
        }

        // Notify the user that an extra ingredient has been added to the recipe.
        cout << "│ ✨ Extra ingredient added to the recipe!\n";

        // Ask the user if they want to add more extra ingredients
        char addMore;
        cout << "│ 📝 Do you want to add more extra ingredients? (Y/N): ";
        cin >> addMore;

        if (addMore != 'Y' && addMore != 'y') {
            break; // Exit the loop if the user doesn't want to add more extra ingredients
        }
    } while (true); // Keep adding extra ingredients until the user decides to stop
}

// Function to add ingredients to a recipe
void RecipeManager::addIngredientsToRecipe(Recipe* recipe, int numIngredients) {
    // A set to keep track of added ingredients to avoid duplication
    set<string> addedIngredients;

    for (int i = 0; i < numIngredients; i++) {
        if (!addIngredient(recipe, addedIngredients)) {
            // If adding the ingredient fails, decrement i to re-enter the ingredient
            i--;
        }
    }

    // Notify the user that ingredients have been added to the recipe.
    cout << "│ ✨ Ingredients added to the recipe!\n";

    // Ask the user if they want to add extra ingredients
    char addExtra;
    cout << "│ 📝 Do you want to add extra ingredients? (Y/N): ";
    cin >> addExtra;

    if (addExtra == 'Y' || addExtra == 'y') {
        // Call the function to add extra ingredients
        addExtraIngredientsToRecipe(recipe);
    }
}

void RecipeManager::addRecipe() {
  string recipeName, description;

  // Display a header to start the recipe addition process.
  cout << "\n╭──── 🍽️ Add Recipe ────╮\n";

  // Prompt the user to enter the name of the recipe.
  cout << "│ 🍳 Enter recipe name: ";
  cin.ignore(); // Ignore any previous newline characters in the input buffer.
  getline(cin, recipeName); // Read the recipe name from the user.

  // Validate that the recipe name is not empty. Prompt until a valid name is provided.
  while (recipeName.empty()) {
      cout << "│ ❌ Recipe name cannot be empty. Please enter a valid name: ";
      getline(cin, recipeName);
  }

  // Prompt the user to enter the description of the recipe.
  cout << "│ 📝 Enter recipe description: ";
  getline(cin, description);

  // Validate that the description is not empty. Prompt until a valid description is provided.
  while (description.empty()) {
      cout << "│ ❌ Description cannot be empty. Please enter a valid description: ";
      getline(cin, description);
  }

  // Prompt the user to enter the number of ingredients they want to add.
 cout << "│ 🥦 Enter the number of ingredients you want to add: ";
int numIngredients;
cin >> numIngredients;

// Validate the number of ingredients entered by the user
while (cin.fail() || numIngredients <= 0) {
    cin.clear(); // Clear the error state
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining characters in the input buffer
    cout << "│ ❌ Invalid input. Please enter a positive integer for the number of ingredients: ";
    cin >> numIngredients;
}
  // Create a new Recipe object with the provided name and description.
  Recipe* newRecipe = new Recipe(recipeName, description);

  // Call the 'addIngredientsToRecipe' function to add ingredients to the new recipe.
  addIngredientsToRecipe(newRecipe, numIngredients);

  // Add the new recipe to the list of recipes.
  recipes.push_back(newRecipe);

  // Notify the user that the recipe has been added successfully.
  cout << "│ 👨‍🍳 Recipe added successfully!\n";
  cout << "╰────────────────────╯\n";
}

void RecipeManager::displayRecipes() const {
       if (recipes.empty()) {
           // If there are no recipes in the manager, notify the user.
           cout << "\n❗ No recipes available.\n";
       } else {
           // If there are recipes, display them in a well-structured format.
           cout << "\n╭──── 📚 All Recipes ────╮\n";

           // Iterate through each recipe in the 'recipes' vector and call the 'display' method.
           for (const Recipe* recipe : recipes) {
               recipe->display();
           }

           // Provide a closing statement for the displayed recipes.
           cout << "╰─────────────────────╯\n";
       }
   }


void RecipeManager::saveRecipesToFile() {
      try {
          // Open an output file stream with the specified filename.
          ofstream outputFile(filename);

          // Check if the file stream is open. If not, display an error message and return.
          if (!outputFile.is_open()) {
              cout << "\n❌ Error: Unable to open " << filename << " for writing.\n";
              return;
          }

          // Iterate through each recipe in the 'recipes' vector and save its details to the file.
          for (const Recipe* recipe : recipes) {
              // Save recipe name and description to the file.
              outputFile << "Recipe Name: " << recipe->getName() << "\n";
              outputFile << "Description: " << recipe->getDescription() << "\n";
              outputFile << "Ingredients:\n";

              // Iterate through the ingredients of the recipe and save them to the file.
              for (const RecipeItem* item : recipe->items) {
                  outputFile << "- " << item->toString() << "\n";
              }

              // Add a newline to separate recipes.
              outputFile << "\n";
          }

          // Close the file stream after saving all recipes.
          outputFile.close();

          // Notify the user that the recipes were saved successfully.
          cout << "\n✔️ Recipes saved to " << filename << " successfully!\n";
      } catch (const std::exception& e) {
          // Handle any exceptions that occur during the file-saving process and notify the user of the error.
          cout << "\n❌ An error occurred while saving recipes: " << e.what() << "\n";
      }
  }

void RecipeManager::loadRecipesFromFile() {
      try {
          // Open an input file stream with the specified filename.
          ifstream inputFile(filename);

          // Check if the file stream is open. If not, display a message and return.
          if (!inputFile.is_open()) {
              cout << "\nℹ️ Note: " << filename << " not found. No recipes loaded.\n";
              return;
          }

          // Clear the 'recipes' vector to prepare for loading new recipes.
          recipes.clear();

          string line;
          Recipe* currentRecipe = nullptr;

          // Read each line from the input file and parse the recipe details.
          while (getline(inputFile, line)) {
              if (line.find("Recipe Name: ") == 0) {
                  // A new recipe begins. Create a new 'currentRecipe' object.
                  if (currentRecipe != nullptr) {
                      recipes.push_back(currentRecipe);
                  }
                  currentRecipe = new Recipe(line.substr(13), "");
              } else if (line.find("Description: ") == 0) {
                  // Set the description for the current recipe.
                  currentRecipe->description = line.substr(13);
              } else if (line.find("- ") == 0) {
                  // Parse ingredient details and add them to the current recipe.
                  string ingredientLine = line.substr(2);
                  size_t colonPos = ingredientLine.find(": ");
                  if (colonPos != string::npos) {
                      string ingredientName = ingredientLine.substr(0, colonPos);
                      double ingredientQuantity = stod(ingredientLine.substr(colonPos + 2));
                      RecipeItem* ingredient = new Ingredient(ingredientName, ingredientQuantity);
                      currentRecipe->addItem(ingredient);
                  }
              }
          }

          // Add the last 'currentRecipe' (if any) to the 'recipes' vector.
          if (currentRecipe != nullptr) {
              recipes.push_back(currentRecipe);
          }

          // Close the file stream after loading all recipes.
          inputFile.close();

          // Notify the user that the recipes were loaded successfully.
          cout << "\n✔️ Recipes loaded from " << filename << " successfully!\n";
      } catch (const std::exception& e) {
          // Handle any exceptions that occur during the file-loading process and notify the user of the error.
          cout << "\n❌ An error occurred while loading recipes: " << e.what() << "\n";
      }
  }


void RecipeManager::run() {
  // Load existing recipes from the file when the program starts.
  loadRecipesFromFile();

  // Continue running the program in a loop until the user chooses to exit.
  while (true) {
      cout << "\n🍽️ WELCOME TO YOUR AMAZING RECIPE MANAGEMENT PROGRAM!!!" << endl;
      cout << "\n╭──── 📋 Main Menu ────╮\n";
      cout << "│ 1. Add Recipe\n";
      cout << "│ 2. Display Recipes\n";
      cout << "│ 3. Save Recipes to File\n";
      cout << "│ 4. Exit\n";
      cout << "│\n";
      cout << "│ Enter your choice: ";

      int choice;
      cin >> choice;

      switch (choice) {
          case 1:
              // Allow the user to add a new recipe by calling the 'addRecipe' function.
              addRecipe();
              break;
          case 2:
              // Display all recipes using the 'displayRecipes' function.
              displayRecipes();
              break;
          case 3:
              // Save the recipes to a file using the 'saveRecipesToFile' function.
              saveRecipesToFile();
              break;
          case 4:
              // Exit the program and display a goodbye message.
              cout << "\n👋 Exiting the program. Goodbye!\n";
              return;
          default:
              // Handle invalid input by informing the user to enter a valid option.
              cout << "\n❌ Invalid choice. Please enter a valid option.\n";
              break;
      }
  }
};
