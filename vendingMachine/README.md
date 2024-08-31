# Vending Machine Low-Level Design (LLD)

## Overview

This project implements a vending machine simulation using the State design pattern in C++. The vending machine is designed to handle multiple products, manage cash transactions, and ensure a smooth flow of operations by transitioning between different states. The system is built with extensibility in mind, allowing easy addition of new products and states.

## Design Pattern: State

The **State design pattern** is used to encapsulate the various states a vending machine can be in. In this implementation, the machine can be in one of the following states:

- **SelectProduct**: The machine waits for the user to select a product.
- **CollectCash**: The machine collects cash from the user.
- **DispenseItem**: The machine dispenses the selected item.
- **CancelTransaction**: The machine handles transaction cancellation.

### Why State Pattern?

The State pattern is particularly well-suited for this project because it allows the vending machine to change its behavior based on its current state. Instead of having complex conditional logic to handle different states, the machine delegates the behavior to the current state object. This makes the code easier to maintain, extend, and understand.

## Class Structure

### 1. **State (Interface)**
- **Purpose**: An abstract class that defines the interface for various states of the vending machine. It contains pure virtual methods that each concrete state class must implement.
- **Methods**:
  - `void selectProduct() = 0;`
  - `void collectCash() = 0;`
  - `void dispenseItem() = 0;`
  - `void cancelTransaction() = 0;`

### 2. **VendingMachine (Main Class)**
- **Purpose**: Manages product registration, cash collection, state transitions, and interactions between different states.
- **Attributes**:
  - `unsigned int collectedCash`: Tracks the cash collected from the user.
  - `string selectedProduct`: Stores the ID of the selected product.
  - `map<string, Product*> products`: A map of registered products.
  - `map<string, unsigned int> productQuantity`: Tracks the quantity of each product.
  - `State* currentState`: Points to the current state of the vending machine.
- **Methods**:
  - `void registerProduct(Product* newProduct);`
  - `void addProduct(string productId, unsigned int quantity);`
  - `bool isProductRegistered(string productId);`
  - `void setState(State* newState);`
  - `void buyProduct(string productId, unsigned int collectedCash);`
  - `void selectProduct();`
  - `void collectCash();`
  - `void dispenseItem();`
  - `void cancelTransaction();`

### 3. **Product**
- **Purpose**: Represents the products available in the vending machine.
- **Attributes**:
  - `string productId`: A unique ID for the product.
  - `string productName`: The name of the product.
  - `unsigned int price`: The price of the product.
- **Methods**:
  - `string getProductId();`
  - `string getProductName();`
  - `unsigned int getPrice();`

### 4. **ProductCodeGenerator**
- **Purpose**: Generates unique product IDs for each product.
- **Methods**:
  - `static string generate(size_t length);`

### 5. **SelectProduct (State Implementation)**
- **Purpose**: Handles the product selection process.
- **Inherits**: Inherits from the `State` interface.
- **Attributes**:
  - `VendingMachine* vendingMachine`: Pointer to the vending machine instance.
- **Methods**:
  - `void selectProduct() override`: Validates the selected product and transitions to the `CollectCash` state.
  - `void collectCash() override`: Displays a message indicating that the product selection is required first.
  - `void dispenseItem() override`: Displays a message indicating that the product selection is required first.
  - `void cancelTransaction() override`: Cancels the transaction and resets the machine to the initial state.

### 6. **CollectCash (State Implementation)**
- **Purpose**: Manages the cash collection process after a product is selected.
- **Inherits**: Inherits from the `State` interface.
- **Attributes**:
  - `VendingMachine* vendingMachine`: Pointer to the vending machine instance.
- **Methods**:
  - `void selectProduct() override`: Displays a message that cash is being collected and the user should wait.
  - `void collectCash() override`: Checks if the collected cash is sufficient and transitions to the `DispenseItem` state; otherwise, transitions to the `CancelTransaction` state.
  - `void dispenseItem() override`: Displays a message that cash is being collected.
  - `void cancelTransaction() override`: Cancels the transaction and transitions to the `CancelTransaction` state.

### 7. **DispenseItem (State Implementation)**
- **Purpose**: Handles the dispensing of the selected item once sufficient cash is collected.
- **Inherits**: Inherits from the `State` interface.
- **Attributes**:
  - `VendingMachine* vendingMachine`: Pointer to the vending machine instance.
- **Methods**:
  - `void selectProduct() override`: Displays a message that the item is being dispensed.
  - `void collectCash() override`: Displays a message that the item is being dispensed.
  - `void dispenseItem() override`: Dispenses the selected item and transitions back to the `SelectProduct` state.
  - `void cancelTransaction() override`: Cancels the transaction and transitions to the `CancelTransaction` state.

### 8. **CancelTransaction (State Implementation)**
- **Purpose**: Manages the cancellation of a transaction at any stage.
- **Inherits**: Inherits from the `State` interface.
- **Attributes**:
  - `VendingMachine* vendingMachine`: Pointer to the vending machine instance.
- **Methods**:
  - `void selectProduct() override`: Displays a message that the transaction is being canceled.
  - `void collectCash() override`: Displays a message that the transaction is being canceled.
  - `void dispenseItem() override`: Displays a message that the transaction is being canceled.
  - `void cancelTransaction() override`: Cancels the transaction, resets the machine, and transitions back to the `SelectProduct` state.

## Interaction Between Classes

The `VendingMachine` class interacts with the various state classes to manage the flow of the vending process. Here’s how the states change during a typical transaction:

1. **Initial State (SelectProduct)**: 
   - The vending machine is initialized in the `SelectProduct` state.
   - The user selects a product, and the machine checks if the product is available.
   - If available, the machine transitions to the `CollectCash` state.

2. **CollectCash State**:
   - The machine collects cash for the selected product.
   - If the collected cash is sufficient, the machine transitions to the `DispenseItem` state.
   - If not, it transitions to the `CancelTransaction` state.

3. **DispenseItem State**:
   - The machine dispenses the selected item and returns any change.
   - The machine then resets to the `SelectProduct` state for the next transaction.

4. **CancelTransaction State**:
   - If at any point the transaction is canceled, the machine enters the `CancelTransaction` state.
   - The transaction is canceled, and the machine resets to the `SelectProduct` state.

## Directory Structure

The project is organized as follows:

```
/vending-machine-project
├── /Headers.h
├── /State/
│   ├── State.h
├── /SelectProduct/
│   ├── SelectProduct.h
│   ├── SelectProduct.cpp
├── /CollectCash/
│   ├── CollectCash.h
│   ├── CollectCash.cpp
├── /DispenseItem/
│   ├── DispenseItem.h
│   ├── DispenseItem.cpp
├── /CancelTransaction/
│   ├── CancelTransaction.h
│   ├── CancelTransaction.cpp
├── /Product/
│   ├── Product.h
│   ├── Product.cpp
├── /ProductCodeGenerator/
│   ├── ProductCodeGenerator.h
│   ├── ProductCodeGenerator.cpp
├── /VendingMachine/
│   ├── VendingMachine.h
│   ├── VendingMachine.cpp
└── /main.cpp
```

### Explanation:
- **Headers.h**: Contains common includes and declarations used across the project.
- **State/**: Contains the `State` interface, which defines the methods that each state must implement.
- **SelectProduct/**, **CollectCash/**, **DispenseItem/**, **CancelTransaction/**: These directories contain the header and implementation files for each state of the vending machine.
- **Product/**: Contains the `Product` class, which handles the details of each product.
- **ProductCodeGenerator/**: Contains the `ProductCodeGenerator` class, responsible for generating unique product IDs.
- **VendingMachine/**: Contains the `VendingMachine` class, which manages the overall functioning and state transitions of the machine.
- **main.cpp**: The entry point of the application, where the vending machine is instantiated and transactions are simulated.
