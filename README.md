# Annadatu – Surplus Food Donation Platform

Annadatu is a C++17 console application connecting surplus-food donors with NGOs, shelters and community kitchens.

## Features
- Donor and acceptor accounts with separate workflows.
- Food donation listings with quantity, servings, dietary type, preparation type and safe-consumption window.
- Manually entered addresses displayed for pickup coordination. No GPS or distance-based matching.
- Urgency-aware donation ranking, including portion fit.
- Request, approval and handover confirmation workflow.
- Environmental impact estimates: 2.5 kg CO2e and 800 litres of virtual water per kg of food rescued.
- File-based persistence in `data/`.

## Requirements
- Windows
- MinGW-w64 / g++ with C++17 support

## Build and run
Open Command Prompt or PowerShell in this directory:

```bat
build.bat
run.bat
```

The executable is created at `build/annadatu.exe`. The application creates missing data files automatically.

## Demo accounts
- Donor: `DONOR-DEMO`
- Donor: `DONOR-MESS`
- Acceptor: `ACCEPTOR-DEMO`

Choose the corresponding role, select the existing-account option, and enter the ID. No password is configured in this demonstration build.

## Data files
- `data/users.txt` – accounts
- `data/donations.txt` – food listings
- `data/requests.txt` – donation requests, food requirements and their statuses

Records are stored as pipe-separated text. Avoid entering the `|` character; it is sanitized automatically.

## Notes
- Addresses are entered manually and displayed to users; they are not used to calculate distance.
- The environmental figures are estimates and should be treated as illustrative project metrics, not verified lifecycle assessments.
- A food requirement raised through the current menu is displayed during the session only; donation requests are persisted.
