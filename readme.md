# Locus - High-Performance Resource Allocation Engine

**Locus** is a modular, object-oriented resource management system designed to simulate a multi-lane parking facility. It features a Write-Through caching strategy for state management and utilizes advanced data structures to optimize resource allocation latency.

---

## 🚀 Key Features

### 1. High-Speed Allocation ($O(1)$)
Traditional systems iterate through arrays to find free space ($O(N)$). Locus utilizes **Min-Heaps (Priority Queues)** to track available slots, allowing for **$O(1)$ allocation time** regardless of facility size.

### 2. Polymorphic Billing Engine
The system handles heterogeneous vehicle types (Cars, Bikes, EVs) using a unified **Polymorphic Interface**.
* **Base Class:** `vehicle` (Abstract)
* **Derived Classes:** `Car` ($50/hr), `Bike` ($20/hr), `EVCar` ($25/hr), `EVBike` ($5/hr).
* **Benefit:** New vehicle types can be added without modifying the core logic (Open/Closed Principle).

### 3. Spatial State Management
Uses a **2D-Vector Grid** (Capacity × Lanes) to manage 3 parallel "universes" of parking at every index, allowing for mixed-use categorization within a single logical slot.

### 4. Modular Architecture
The codebase follows strict separation of concerns:
* **`headers/`**: Pure interfaces and class definitions.
* **`modules/`**: Implementation logic.
* **`main.cpp`**: Driver code and User Interface.

---

## 🛠️ Tech Stack
* **Language:** C++ (Standard 17)
* **Core Concepts:** OOP (Inheritance, Polymorphism), STL (Vectors, Priority Queues), Memory Management.
* **Build System:** Custom VS Code Task Configuration (`g++` linkage).

---

## 📂 Project Structure
```text
Locus/
├── headers/           # Interface Definitions
│   ├── parkingLot.h   # Manager Class Definition
│   └── vehicles.h     # Vehicle Class Definitions
├── modules/           # Implementation Logic
│   ├── parkingLot.cpp # Slot & Heap Management Logic
│   └── vehicles.cpp   # Billing & Polymorphic Logic
├── main.cpp           # Entry Point & UI
└── .vscode/           # Build Configuration
    └── tasks.json     # Linker settings
