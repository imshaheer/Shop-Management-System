#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Product {
    std::string name;
    double price;
    int quantity;
};

void addProduct(const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cout << "Error opening file for writing.\n";
        return;
    }

    Product product;
    std::cout << "Enter product name: ";
    std::cin.ignore();
    std::getline(std::cin, product.name);

    std::cout << "Enter product price: ";
    std::cin >> product.price;

    std::cout << "Enter product quantity: ";
    std::cin >> product.quantity;

    file << product.name << ' ' << product.price << ' ' << product.quantity << '\n';
    std::cout << "Product added successfully.\n";

    file.close();
}

void displayProducts(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file for reading.\n";
        return;
    }

    Product product;
    while (file >> product.name >> product.price >> product.quantity) {
        std::cout << "Name: " << product.name << ", Price: $" << product.price
                  << ", Quantity: " << product.quantity << '\n';
    }

    file.close();
}

void updateProduct(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file for reading.\n";
        return;
    }

    Product product;
    while (file >> product.name >> product.price >> product.quantity) {
        products.push_back(product);
    }

    file.close();

    std::cout << "Enter the name of the product to update: ";
    std::string productName;
    std::cin.ignore();
    std::getline(std::cin, productName);

    bool found = false;
    for (auto& p : products) {
        if (p.name == productName) {
            found = true;

            std::cout << "Enter new price: ";
            std::cin >> p.price;

            std::cout << "Enter new quantity: ";
            std::cin >> p.quantity;

            break;
        }
    }

    if (!found) {
        std::cout << "Product not found.\n";
        return;
    }

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "Error opening file for writing.\n";
        return;
    }

    for (const auto& p : products) {
        outFile << p.name << ' ' << p.price << ' ' << p.quantity << '\n';
    }

    std::cout << "Product updated successfully.\n";
    outFile.close();
}

void deleteProduct(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file for reading.\n";
        return;
    }

    Product product;
    while (file >> product.name >> product.price >> product.quantity) {
        products.push_back(product);
    }

    file.close();

    std::cout << "Enter the name of the product to delete: ";
    std::string productName;
    std::cin.ignore();
    std::getline(std::cin, productName);

    bool found = false;
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->name == productName) {
            found = true;
            products.erase(it);
            break;
        }
    }

    if (!found) {
        std::cout << "Product not found.\n";
        return;
    }

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "Error opening file for writing.\n";
        return;
    }

    for (const auto& p : products) {
        outFile << p.name << ' ' << p.price << ' ' << p.quantity << '\n';
    }

    std::cout << "Product deleted successfully.\n";
    outFile.close();
}

int main() {
    std::string filename = "products.txt";
    int choice;

    while (true) {
        std::cout << "\n***** Shop Management System *****\n";
        std::cout << "1. Add Product\n";
        std::cout << "2. Display Products\n";
        std::cout << "3. Update Product\n";
        std::cout << "4. Delete Product\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addProduct(filename);
                break;
            case 2:
                displayProducts(filename);
                break;
            case 3:
                updateProduct(filename);
                break;
            case 4:
                deleteProduct(filename);
                break;
            case 5:
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
