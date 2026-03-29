# Tutor Availability Platform

A console-based **Object Oriented Programming** project written in **C++** that connects students with tutors in an efficient and structured manner.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [OOP Concepts Used](#oop-concepts-used)
- [Class Structure](#class-structure)
- [How to Compile and Run](#how-to-compile-and-run)
- [Test Cases](#test-cases)
- [Sample Output](#sample-output)
- [Project Structure](#project-structure)

---

## Overview

The Tutor Availability Platform allows tutors to create profiles, define subject expertise, manage available time slots, and handle session requests. Students can browse tutor profiles, search tutors by subject, request sessions, and track their scheduled tutoring sessions.

The system goes beyond a basic management system by incorporating smart features such as tutor recommendation and ranking, waitlist management, and automatic slot reassignment after cancellations.

---

## Features

| Feature | Description |
|---|---|
| Add Tutor | Register a tutor with name, contact, subjects, rating, and time slots |
| Add Student | Register a student with name and contact details |
| Search by Subject | Find all tutors who teach a specific subject |
| Recommend Tutors | Rank tutors based on subject match, rating, and slot availability |
| Book Session | Book an available tutor slot for a student |
| Conflict Detection | Prevents double booking of the same tutor slot |
| Waitlist Management | Adds student to a waitlist if the slot is already booked |
| Auto Slot Reassignment | When a session is cancelled, the slot is automatically assigned to the next waitlisted student |
| Cancel Session | Cancel an existing session and trigger waitlist reassignment |
| Show All Sessions | Display all scheduled and cancelled sessions |

---

## OOP Concepts Used

### Encapsulation
All class attributes are declared `private`. Public getter and setter methods are used to control access. For example, `TimeSlot::isBooked` can only be changed through `bookSlot()` and `freeSlot()`.

### Inheritance
`Tutor` and `Student` both inherit from the base class `User`, which holds common attributes like `userId`, `name`, and `contactInfo`. This avoids code duplication.

```
User  (base class)
├── Tutor
└── Student
```

### Polymorphism
`viewProfile()` is declared as a pure virtual function in `User` and overridden in both `Tutor` and `Student` to display different profile information at runtime.

### Abstraction
The `User` class is abstract (cannot be instantiated directly). The `Platform` class exposes simple public methods like `bookSession()` and `cancelSession()` that hide complex internal logic from the caller.

### Exception Handling
`try/catch` blocks are used in `bookSession()` and `cancelSession()` to handle invalid tutor names, student names, and slot IDs without crashing the program.

---

## Class Structure

```
Platform
├── vector<Tutor>
├── vector<Student>
├── vector<Session>
├── vector<WaitlistEntry>
└── RecommendationEngine

User (abstract)
├── Tutor
│   ├── vector<string> subjects
│   ├── float rating
│   └── vector<TimeSlot> availableSlots
└── Student
    └── vector<Session> sessionHistory

Session
├── tutorName
├── studentName
├── subject
├── slotInfo
└── status

TimeSlot
├── slotId
├── date
├── time
└── isBooked

Waitlist
└── queue<string> waitingStudents

RecommendationEngine
├── calculateScore()
└── recommendTutors()
```

---

## How to Compile and Run

### Requirements
- A C++ compiler supporting C++17 (g++, clang++, MSVC)

### Compile

```bash
g++ -std=c++17 tutor_platform.cpp -o tutor_platform
```

### Run

```bash
./tutor_platform
```

On Windows:

```bash
tutor_platform.exe
```

---

## Test Cases

| TC | Feature | Input | Expected Output |
|---|---|---|---|
| TC-01 | Add Tutor | Tutor name, contact, subject, rating, availability | Tutor profile created successfully |
| TC-02 | Add Student | Student name and contact details | Student profile created successfully |
| TC-03 | Search by Subject | Subject = Mathematics | Matching tutors displayed |
| TC-04 | Recommend Tutors | Subject = Physics, preferred slot = 4 PM | Tutors ranked by subject, rating, availability |
| TC-05 | Book Session | Student selects tutor and available slot | Session created, slot marked as Booked |
| TC-06 | Conflict Detection | Another student requests the same booked slot | Student added to waitlist |

---

## Sample Output

```
+==========================================+
|   TUTOR AVAILABILITY PLATFORM v1.0       |
|   OOP Project -- Test Cases              |
+==========================================+

--------------------------------------------------
TC-01: Add Tutor
--------------------------------------------------
  Tutor "Dr. Ali Raza" added successfully.
  Tutor "Ms. Sara Khan" added successfully.
  Tutor "Mr. Usman Tariq" added successfully.

--------------------------------------------------
TC-05: Book Session
--------------------------------------------------
  Session booked successfully!
  +-----------------------------------------+
  Session ID   : 1
  Tutor        : Dr. Ali Raza
  Student      : Ahmed Malik
  Subject      : Mathematics
  Slot         : 2025-06-10 10:00 AM
  Status       : Scheduled
  +-----------------------------------------+

--------------------------------------------------
TC-06: Conflict Detection
--------------------------------------------------
  Slot is already booked. Adding "Zara Noor" to waitlist...
  [Waitlist] Student "Zara Noor" added to waitlist.
```

---

## Project Structure

```
tutor-availability-platform/
├── tutor_platform.cpp      # Full source code (single file)
└── README.md               # Project documentation
```

---

## Authors

OOP Project — Milestone 2  
Department of Computer Science
