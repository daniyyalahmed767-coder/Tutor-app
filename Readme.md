# Tutor Availability Platform (Final Submission)

An Object-Oriented Programming (OOP) project written in C++ that connects students with tutors in an efficient, structured, and smart manner. This represents the **Milestone 3 (Final)** version of the platform.

## Table of Contents
* [Overview](#overview)
* [Features](#features)
* [OOP Concepts Used](#oop-concepts-used)
* [Class Structure](#class-structure)
* [How to Compile and Run](#how-to-compile-and-run)
* [Test Cases](#test-cases)
* [Project Structure](#project-structure)

## Overview
The Tutor Availability Platform allows tutors to create profiles, define subject expertise, manage available time slots, and handle session requests. Students can browse tutor profiles, search tutors by subject, request sessions, and track their scheduled tutoring sessions.

Building upon the initial console prototype, this final **Milestone 3** version introduces a complete suite of smart features including a **Raylib Graphical User Interface**, a student rating and review system, a priority-based waitlist driven by student reliability scores, authorised session cancellation, and zero-collision auto-assigned IDs.

## Features
| Feature | Description |
| :--- | :--- |
| **Raylib GUI** | A fully functional graphical user interface running alongside the standard console menu. |
| **Add Tutor / Student** | Register users with auto-assigned, collision-free IDs. |
| **Smart Search** | Find tutors by name, specific subjects, or both. |
| **Recommend Tutors** | Rank tutors based on a strict subject match (hard gate) and running average rating. |
| **Book Session** | Book an available tutor slot for a student with conflict detection. |
| **Priority Waitlist** | Adds student to a waitlist sorted by *Reliability Score* (completed vs. cancelled bookings). |
| **Auto Slot Reassignment** | When a session is cancelled, the slot is instantly assigned to the highest-priority waitlisted student. |
| **Authorised Cancel** | Cancel an existing session (validates that the cancelling student is the original booker). |
| **Rate Session** | Students can rate (0.0 - 5.0) and review tutors post-session. |
| **Live Session History** | Display all scheduled, completed, and cancelled sessions accurately. |

## OOP Concepts Used

**Encapsulation**
All class attributes are declared `private`. Public getter and setter methods are used to control access. For example, a tutor's rating cannot be manually set; it is updated automatically via the `addRating()` method when a session is completed.

**Inheritance**
`Tutor` and `Student` both inherit from the base class `User`, which holds common attributes like `userId`, `name`, and `contactInfo`.

**Polymorphism**
`viewProfile()` is declared as a pure virtual function in `User` and overridden in both `Tutor` and `Student` to display different profile information at runtime.

**Abstraction**
The `User` class is abstract (`viewProfile() = 0`). The `Platform` class acts as the central controller, hiding the complexity of waitlist queues and rating logic behind simple public methods.

**Exception Handling**
Custom exception classes (`TutorNotFoundException`, `AlreadyCancelledException`, `RatingException`, etc.) are thrown and caught to handle runtime errors gracefully without crashing.

**Generic & Functional Programming**
Templates and Lambdas are used in `Utilities.hpp` to implement generic search algorithms (`linearSearch`, `filterVec`). A Functor (`ScoreComparator`) is used to dynamically sort recommended tutors.

## Class Structure

```text
Platform
├── vector<Tutor>
├── vector<Student>
├── vector<Session>
├── vector<Waitlist>
└── RecommendationEngine

User (abstract)
├── Tutor
│   ├── vector<string> subjects
│   ├── float ratingSum / ratingCount
│   └── vector<TimeSlot> availableSlots
└── Student
    ├── int totalBooked / cancelledCount
    └── vector<Session> sessionHistory

Session
├── tutorName / studentName / subject
├── slotId / slotInfo
├── status (Scheduled, Completed, Cancelled)
└── studentRating / studentReview

TimeSlot
├── static int nextSlotId (Auto-assigned)
└── date / time / isBooked

Waitlist
└── vector<WaitlistEntry> (Sorted by Reliability Score)

RecommendationEngine
├── calculateScore()
└── recommendTutors()
How to Compile and RunRequirementsA C++ compiler supporting C++17 (g++, clang++)Raylib (for the GUI version)CMake (optional)Option A: Direct Compilation (g++)1. Console VersionBashg++ -std=c++17 TimeSlot.cpp Session.cpp Waitlist.cpp User.cpp Tutor.cpp \
    Student.cpp RecommendationEngine.cpp Platform.cpp main.cpp -o platform_console

./platform_console
2. GUI Version (Requires Raylib)(Note: Adjust -I/path/to/raylib/include if your Raylib headers are installed in a custom location).Bashg++ -std=c++17 -I/path/to/raylib/include \
    TimeSlot.cpp Session.cpp Waitlist.cpp User.cpp Tutor.cpp \
    Student.cpp RecommendationEngine.cpp Platform.cpp gui_main.cpp \
    -o platform_gui -lraylib -lm -ldl -lpthread -lGL -lX11

./platform_gui
Option B: Compilation via CMakeBash# 1. Create a build directory
mkdir build && cd build

# 2. Generate and compile
cmake ..
make

# 3. Run the applications
./platform_console    
./platform_gui        
Test CasesThe system includes 29 automated test cases covering all edge cases. Below is a sample:TC IDFeatureInputExpected OutputTC-03Conflict DetectionAhmed books the same already-booked slotAhmed added to priority waitlist, no crashTC-07Cancel + WaitlistCancel Zara's session; Ahmed is on waitlistSession cancelled, Ahmed auto-assigned, new session createdTC-09Unauthorised CancelStudent B tries to cancel Student A's sessionruntime_error: Authorization failedTC-11Recommend by SubjectSubject = "Math"Only tutors teaching Math returned, ranked by ratingTC-23Double RatingSara rates same session againRatingException: already rated; count stays 1Project StructurePlaintexttutor-availability-platform/
├── CMakeLists.txt          # Build configuration
├── main.cpp                # Console entry point & 29 Test Cases
├── gui_main.cpp            # Raylib graphical interface entry point
├── Platform.hpp/.cpp       # Central controller
├── User.hpp/.cpp           # Abstract base class
├── Tutor.hpp/.cpp          # Tutor implementation
├── Student.hpp/.cpp        # Student implementation
├── Session.hpp/.cpp        # Booking & Rating records
├── TimeSlot.hpp/.cpp       # Auto-assigned time windows
├── Waitlist.hpp/.cpp       # Priority queue logic
├── RecommendationEngine.hpp/.cpp # Ranking algorithms
├── Utilities.hpp           # Generic templates & search functions
├── Exceptions.hpp          # Custom error handling
├── README.md               # Project documentation
└── docs/                   # UML diagram and milestone reports
