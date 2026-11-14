# Annadatu – Surplus Food Donation Platform

Annadatu is a C++17 console application that connects people and businesses with surplus food to NGOs, shelters, and community kitchens that can distribute it to people in need.

The platform helps donors list available food and helps acceptors discover suitable nearby donations before the food expires.

## Features

- **Donor and acceptor accounts:** Separate user roles and workflows.
- **Food donation listings:** Record food details, quantity, servings, dietary type, preparation type, and safe-consumption window.
- **Food requests:** Acceptors can request suitable donations and raise food requirements.
- **Manually entered addresses:** Donors and acceptors can enter their addresses, which are displayed to help coordinate food pickup and delivery.
- **Urgency-based matching:** Prioritizes food based on its remaining safe-consumption time and portion fit.
- **Donation confirmation:** Supports request, confirmation, and handover workflows.
- **Environmental impact metrics:** Tracks estimated CO₂e emissions averted and virtual water saved based on the amount of food rescued.
- **Data persistence:** Saves users, donations, and requests in text files so data can be retained between runs.

## Technology

- **Language:** C++
- **Standard:** C++17
- **Storage:** File-based text serialization
- **Build/run scripts:** Windows batch files (`build.bat` and `run.bat`)

## Project Structure

```text
oops project/
├── build.bat
├── run.bat
├── annadatu.exe
├── data/
│   ├── users.txt
│   ├── donations.txt
│   └── requests.txt
├── include/
│   ├── Common.hpp
│   ├── Location.hpp
│   ├── FoodItem.hpp
│   ├── User.hpp
│   ├── Donor.hpp
│   ├── Acceptor.hpp
│   ├── DonationListing.hpp
│   ├── FoodRequest.hpp
│   ├── MatchingEngine.hpp
│   ├── StorageManager.hpp
│   ├── UIHelper.hpp
│   └── AnnadatuApp.hpp
└── src/
    ├── Location.cpp
    ├── FoodItem.cpp
    ├── User.cpp
    ├── Donor.cpp
    ├── Acceptor.cpp
    ├── DonationListing.cpp
    ├── FoodRequest.cpp
    ├── MatchingEngine.cpp
    ├── StorageManager.cpp
    ├── UIHelper.cpp
    ├── AnnadatuApp.cpp
    └── main.cpp
```

## How to Run

These instructions are for Windows.

### Run the application

Open PowerShell or Command Prompt in the project directory and run:

```powershell
.\run.bat
```

Alternatively, run the executable directly:

```powershell
.\annadatu.exe
```

### Build the application

To compile the source code, run:

```powershell
.\build.bat
```

## Application Workflow

### Donor

1. Sign in and choose a donor category.
2. Add a food donation with its details and safe-consumption window.
3. Review requests from nearby acceptors.
4. Confirm the handover.

### Acceptor

1. Sign in and choose an acceptor category.
2. Browse nearby donations and filter by dietary preference.
3. Send a request for a suitable donation.
4. Pick up the food and confirm receipt.
5. Submit a food request when additional supplies are needed.

## Matching Logic

Annadatu prioritizes listings according to the time remaining in their safe-consumption window. The matching score also considers portion fit. Addresses are entered manually and displayed to help users coordinate the handover; the application does not calculate distance or use GPS-based matching.

## Object-Oriented Design

The project uses C++ object-oriented programming concepts, including:

- **Encapsulation:** Class data is protected and validated through class methods.
- **Inheritance:** `Donor` and `Acceptor` derive from the base `User` class.
- **Polymorphism:** The abstract `User` interface supports role-specific behavior.
- **Operator overloading:** Used for formatted output, comparisons, and quantity accumulation.
- **Strategy pattern:** Matching strategies can be selected through the matching engine.
- **Storage management:** `StorageManager` handles saving and loading application data.
