# ATM Management System
The ATM System is a C++ console application that simulates basic banking operations, such as user authentication, balance inquiry, withdrawals, deposits, and secure logout. Users can interact with the system through a simple interface, with all account data managed through a file-based storage system. This project demonstrates core C++ concepts such as file handling, data validation, and control flow, while offering practical functionality for managing multiple client accounts in a safe and efficient manner. The program works by reading and writing client data from a text file (`clients.txt`), providing various menu options for easy interaction.

## Table of Contents
- [Project Information](#Project-Information)
- [Live Demo](#Live-Demo)
- [Features](#features)
- [How It Works](#How-It-Works) 
- [Project Flow](#Project-Flow)
- [File Structure](#File-Structure)

## Project Information
This C++ simple console-based Bank Management System project was created at the end of the [8th course](https://programmingadvices.com/p/08-algorithms-problem-solving-level-4) from the Roadmap for General Foundation in Programming @ [Programming Advices](https://programmingadvices.com/).

## Live Demo
https://github.com/user-attachments/assets/e77ff750-5fad-47ae-a9b4-e96ae5baec73

## Features
- **Login System**: Users can log in with their account number and PIN code.
- **Balance Inquiry**: Users can check their account balance.
- **Withdrawals**:
  - Quick withdrawal option for common amounts.
  - Custom withdrawal option for user-specified amounts.
- **Deposits**: Users can deposit money into their account.
- **Account Management**: User details are stored in a file system (clients.txt).
- **Logout**: Users can log out safely after transactions.

## How It Works
1. **Login Screen**: The system prompts the user to input their account number and PIN code. This information is validated from a file (`clients.txt`).
2. **Main Menu**: After login, the user is presented with options for withdrawal, deposit, balance inquiry, and logout.
3. **Withdrawal**: Users can withdraw a set amount or enter a custom amount to withdraw.
4. **Deposit**: Users can add funds to their account by entering a deposit amount.
5. **Balance Check**: Users can check their current account balance, which updates in real-time after each transaction.
6. **Logout**: Users can securely log out, ending their session.

## Project Flow
1. **Login Process**: Reads user account details from `clients.txt`. If the account number and PIN code match, the user gains access to the main menu.
2. **Main Menu Operations**: Users choose between:
   - Quick withdrawal (fixed amounts),
   - Custom withdrawal (user-defined amount),
   - Deposit funds,
   - Check balance.
3. **File Management**: The `clients.txt` file stores user data, which the program reads and writes to when processing transactions.
4. **Error Handling**: Input validation ensures users enter correct data within specified ranges (e.g., valid account number, sufficient funds for withdrawal).

## File Structure
### `project-2-ATM-system.cpp`: The main program file containing the source code for the Bank Management System.
### `clients.txt`: The data file where client information is stored. This file is created automatically when the program runs.
