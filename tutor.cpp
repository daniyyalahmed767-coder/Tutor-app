#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// =====================================================================
// Forward Declarations
// =====================================================================
class TimeSlot;
class Session;
class Tutor;
class Student;

// =====================================================================
// CLASS: TimeSlot
// =====================================================================
class TimeSlot {
private:
    int slotId;
    string date;
    string time;
    bool isBooked;

public:
    TimeSlot() : slotId(0), date(""), time(""), isBooked(false) {}

    TimeSlot(int id, string d, string t)
        : slotId(id), date(d), time(t), isBooked(false) {}

    // Getters
    int getSlotId() const { return slotId; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    bool getIsBooked() const { return isBooked; }

    // Setters
    void setSlotId(int id) { slotId = id; }
    void setDate(string d) { date = d; }
    void setTime(string t) { time = t; }

    void bookSlot() { isBooked = true; }
    void freeSlot() { isBooked = false; }

    void displaySlot() const {
        cout << "  Slot ID: " << slotId
             << " | Date: " << date
             << " | Time: " << time
             << " | Status: " << (isBooked ? "Booked" : "Available") << endl;
    }
};

// =====================================================================
// CLASS: Waitlist
// =====================================================================
class Waitlist {
private:
    queue<string> waitingStudents; // stores student names

public:
    void addStudent(string studentName) {
        waitingStudents.push(studentName);
        cout << "  [Waitlist] Student \"" << studentName << "\" added to waitlist.\n";
    }

    string getNextStudent() {
        if (!waitingStudents.empty()) {
            string next = waitingStudents.front();
            waitingStudents.pop();
            return next;
        }
        return "";
    }

    bool isEmpty() const {
        return waitingStudents.empty();
    }

    void displayWaitlist() const {
        if (waitingStudents.empty()) {
            cout << "  Waitlist is empty.\n";
            return;
        }
        queue<string> temp = waitingStudents;
        int pos = 1;
        cout << "  Waitlist:\n";
        while (!temp.empty()) {
            cout << "    " << pos++ << ". " << temp.front() << endl;
            temp.pop();
        }
    }
};

// =====================================================================
// CLASS: Session
// =====================================================================
class Session {
private:
    int sessionId;
    string tutorName;
    string studentName;
    string subject;
    string slotInfo;
    string status;  // "Scheduled", "Cancelled", "Completed"

public:
    Session() : sessionId(0), status("Scheduled") {}

    Session(int id, string tName, string sName, string subj, string slot, string stat = "Scheduled")
        : sessionId(id), tutorName(tName), studentName(sName),
          subject(subj), slotInfo(slot), status(stat) {}

    // Getters
    int getSessionId() const { return sessionId; }
    string getTutorName() const { return tutorName; }
    string getStudentName() const { return studentName; }
    string getSubject() const { return subject; }
    string getSlotInfo() const { return slotInfo; }
    string getStatus() const { return status; }

    // Setters
    void setStatus(string s) { status = s; }
    void setStudentName(string s) { studentName = s; }

    void cancelSession() {
        status = "Cancelled";
        cout << "  Session ID " << sessionId << " has been cancelled.\n";
    }

    void displaySession() const {
        cout << "  +-----------------------------------------+\n";
        cout << "  Session ID   : " << sessionId << endl;
        cout << "  Tutor        : " << tutorName << endl;
        cout << "  Student      : " << studentName << endl;
        cout << "  Subject      : " << subject << endl;
        cout << "  Slot         : " << slotInfo << endl;
        cout << "  Status       : " << status << endl;
        cout << "  +-----------------------------------------+\n";
    }
};

// =====================================================================
// CLASS: User (Base Class)
// =====================================================================
class User {
protected:
    int userId;
    string name;
    string contactInfo;

public:
    User() : userId(0), name(""), contactInfo("") {}

    User(int id, string n, string contact)
        : userId(id), name(n), contactInfo(contact) {}

    virtual ~User() {}

    // Getters
    int getUserId() const { return userId; }
    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }

    // Setters
    void setUserId(int id) { userId = id; }
    void setName(string n) { name = n; }
    void setContactInfo(string c) { contactInfo = c; }

    virtual void viewProfile() const = 0;
};

// =====================================================================
// CLASS: Tutor (Derived from User)
// =====================================================================
class Tutor : public User {
private:
    vector<string> subjects;
    int experienceYears;
    float rating;
    vector<TimeSlot> availableSlots;

public:
    Tutor() : User(), experienceYears(0), rating(0.0f) {}

    Tutor(int id, string n, string contact, int exp, float rate)
        : User(id, n, contact), experienceYears(exp), rating(rate) {}

    // Getters
    float getRating() const { return rating; }
    int getExperienceYears() const { return experienceYears; }
    vector<string> getSubjects() const { return subjects; }
    vector<TimeSlot>& getAvailableSlots() { return availableSlots; }
    const vector<TimeSlot>& getAvailableSlots() const { return availableSlots; }

    void addSubject(string subject) {
        subjects.push_back(subject);
    }

    void addAvailability(TimeSlot slot) {
        availableSlots.push_back(slot);
    }

    bool isAvailable(int slotId) const {
        for (const auto& slot : availableSlots) {
            if (slot.getSlotId() == slotId && !slot.getIsBooked())
                return true;
        }
        return false;
    }

    bool teachesSubject(const string& subj) const {
        for (const auto& s : subjects) {
            if (s == subj) return true;
        }
        return false;
    }

    TimeSlot* findSlot(int slotId) {
        for (auto& slot : availableSlots) {
            if (slot.getSlotId() == slotId)
                return &slot;
        }
        return nullptr;
    }

    void viewProfile() const override {
        cout << "\n  ========== TUTOR PROFILE ==========\n";
        cout << "  ID          : " << userId << endl;
        cout << "  Name        : " << name << endl;
        cout << "  Contact     : " << contactInfo << endl;
        cout << "  Experience  : " << experienceYears << " years\n";
        cout << "  Rating      : " << rating << " / 5.0\n";
        cout << "  Subjects    : ";
        for (int i = 0; i < (int)subjects.size(); i++) {
            cout << subjects[i];
            if (i < (int)subjects.size() - 1) cout << ", ";
        }
        cout << "\n  Available Slots:\n";
        if (availableSlots.empty()) {
            cout << "    No slots available.\n";
        } else {
            for (const auto& slot : availableSlots)
                slot.displaySlot();
        }
        cout << "  ====================================\n";
    }
};

// =====================================================================
// CLASS: Student (Derived from User)
// =====================================================================
class Student : public User {
private:
    vector<Session> sessionHistory;

public:
    Student() : User() {}

    Student(int id, string n, string contact)
        : User(id, n, contact) {}

    void addToHistory(Session s) {
        sessionHistory.push_back(s);
    }

    void requestSession() {
        cout << "  Student \"" << name << "\" is requesting a session.\n";
    }

    void viewProfile() const override {
        cout << "\n  ========== STUDENT PROFILE ==========\n";
        cout << "  ID          : " << userId << endl;
        cout << "  Name        : " << name << endl;
        cout << "  Contact     : " << contactInfo << endl;
        cout << "  Sessions    : " << sessionHistory.size() << " session(s) in history\n";
        cout << "  =====================================\n";
    }

    void viewSessionHistory() const {
        if (sessionHistory.empty()) {
            cout << "  No session history found.\n";
            return;
        }
        cout << "\n  === Session History for " << name << " ===\n";
        for (const auto& s : sessionHistory)
            s.displaySession();
    }
};

// =====================================================================
// CLASS: RecommendationEngine
// =====================================================================
class RecommendationEngine {
public:
    float calculateScore(const Tutor& tutor, string subject, string date, string time) const {
        float score = 0.0f;

        // Subject match: +50 points
        if (tutor.teachesSubject(subject))
            score += 50.0f;

        // Rating: up to 30 points (rating * 6)
        score += tutor.getRating() * 6.0f;

        // Availability: +20 points if any free slot on that date/time
        for (const auto& slot : tutor.getAvailableSlots()) {
            if (slot.getDate() == date && slot.getTime() == time && !slot.getIsBooked()) {
                score += 20.0f;
                break;
            }
        }

        return score;
    }

    vector<Tutor*> recommendTutors(vector<Tutor>& tutors, string subject, string date, string time) const {
        vector<pair<float, Tutor*>> scored;

        for (auto& tutor : tutors) {
            float s = calculateScore(tutor, subject, date, time);
            if (s > 0)
                scored.push_back({s, &tutor});
        }

        // Sort descending by score
        sort(scored.begin(), scored.end(), [](const pair<float, Tutor*>& a, const pair<float, Tutor*>& b) {
            return a.first > b.first;
        });

        vector<Tutor*> result;
        for (auto& p : scored)
            result.push_back(p.second);

        return result;
    }
};

// =====================================================================
// CLASS: Platform (Main Controller)
// =====================================================================
class Platform {
private:
    vector<Tutor> tutors;
    vector<Student> students;
    vector<Session> sessions;
    // Simple waitlist storage without map
    struct WaitlistEntry {
        string key;
        Waitlist wl;
    };
    vector<WaitlistEntry> waitlists;
    RecommendationEngine recommender;
    int nextSessionId;

    // Helper: get or create waitlist for a key
    Waitlist& getWaitlist(const string& key) {
        for (auto& entry : waitlists) {
            if (entry.key == key)
                return entry.wl;
        }
        WaitlistEntry e;
        e.key = key;
        waitlists.push_back(e);
        return waitlists.back().wl;
    }

public:
    Platform() : nextSessionId(1) {}

    // ------------------------------------------------------------------
    void addTutor(Tutor t) {
        tutors.push_back(t);
        cout << "  Tutor \"" << t.getName() << "\" added successfully.\n";
    }

    void addStudent(Student s) {
        students.push_back(s);
        cout << "  Student \"" << s.getName() << "\" added successfully.\n";
    }

    // ------------------------------------------------------------------
    void showAllTutors() const {
        if (tutors.empty()) {
            cout << "  No tutors registered.\n";
            return;
        }
        cout << "\n  ============ ALL TUTORS ============\n";
        for (const auto& t : tutors)
            t.viewProfile();
    }

    void showAllStudents() const {
        if (students.empty()) {
            cout << "  No students registered.\n";
            return;
        }
        cout << "\n  ============ ALL STUDENTS ============\n";
        for (const auto& s : students)
            s.viewProfile();
    }

    // ------------------------------------------------------------------
    void searchTutorsBySubject(string subject) const {
        cout << "\n  === Tutors teaching \"" << subject << "\" ===\n";
        bool found = false;
        for (const auto& t : tutors) {
            if (t.teachesSubject(subject)) {
                t.viewProfile();
                found = true;
            }
        }
        if (!found)
            cout << "  No tutors found for subject: " << subject << endl;
    }

    // ------------------------------------------------------------------
    void recommendTutors(string subject, string date, string time) {
        cout << "\n  === Recommended Tutors for \"" << subject
             << "\" on " << date << " at " << time << " ===\n";

        vector<Tutor*> recs = recommender.recommendTutors(tutors, subject, date, time);

        if (recs.empty()) {
            cout << "  No recommendations available.\n";
            return;
        }
        int rank = 1;
        for (auto* t : recs) {
            float score = recommender.calculateScore(*t, subject, date, time);
            cout << "\n  Rank #" << rank++ << " (Score: " << score << ")";
            t->viewProfile();
        }
    }

    // ------------------------------------------------------------------
    void bookSession(string tutorName, string studentName, string subject, int slotId) {
        // Find tutor
        Tutor* tutor = nullptr;
        for (auto& t : tutors) {
            if (t.getName() == tutorName) {
                tutor = &t;
                break;
            }
        }
        if (!tutor) {
            cout << "  ERROR: Tutor \"" << tutorName << "\" not found.\n";
            return;
        }

        // Find student
        Student* student = nullptr;
        for (auto& s : students) {
            if (s.getName() == studentName) {
                student = &s;
                break;
            }
        }
        if (!student) {
            cout << "  ERROR: Student \"" << studentName << "\" not found.\n";
            return;
        }

        // Find slot
        TimeSlot* slot = tutor->findSlot(slotId);
        if (!slot) {
            cout << "  ERROR: Slot ID " << slotId << " not found for tutor \"" << tutorName << "\".\n";
            return;
        }

        string waitlistKey = tutorName + "_" + to_string(slotId);

        // Conflict detection
        if (slot->getIsBooked()) {
            cout << "  Slot is already booked. Adding \"" << studentName << "\" to waitlist...\n";
            getWaitlist(waitlistKey).addStudent(studentName);
            return;
        }

        // Book the slot
        slot->bookSlot();
        string slotInfo = slot->getDate() + " " + slot->getTime();

        Session newSession(nextSessionId++, tutorName, studentName, subject, slotInfo);
        sessions.push_back(newSession);
        student->addToHistory(newSession);

        cout << "  Session booked successfully!\n";
        newSession.displaySession();
    }

    // ------------------------------------------------------------------
    void cancelSession(int sessionId) {
        Session* sess = nullptr;
        for (auto& s : sessions) {
            if (s.getSessionId() == sessionId) {
                sess = &s;
                break;
            }
        }
        if (!sess) {
            cout << "  ERROR: Session ID " << sessionId << " not found.\n";
            return;
        }
        if (sess->getStatus() == "Cancelled") {
            cout << "  Session is already cancelled.\n";
            return;
        }

        string tutorName   = sess->getTutorName();
        string slotInfo    = sess->getSlotInfo();
        string subject     = sess->getSubject();

        sess->cancelSession();

        // Free the slot in the tutor's list
        Tutor* tutor = nullptr;
        for (auto& t : tutors) {
            if (t.getName() == tutorName) {
                tutor = &t;
                break;
            }
        }

        if (tutor) {
            for (auto& slot : tutor->getAvailableSlots()) {
                string info = slot.getDate() + " " + slot.getTime();
                if (info == slotInfo && slot.getIsBooked()) {
                    slot.freeSlot();

                    // Check waitlist
                    string waitlistKey = tutorName + "_" + to_string(slot.getSlotId());
                    if (!getWaitlist(waitlistKey).isEmpty()) {
                        string nextStudent = getWaitlist(waitlistKey).getNextStudent();
                        cout << "  Auto-assigning slot to waitlisted student: \"" << nextStudent << "\"\n";
                        slot.bookSlot();

                        Session newSession(nextSessionId++, tutorName, nextStudent, subject, slotInfo);
                        sessions.push_back(newSession);

                        // Add to student history
                        for (auto& s : students) {
                            if (s.getName() == nextStudent) {
                                s.addToHistory(newSession);
                                break;
                            }
                        }
                        cout << "  New session created for \"" << nextStudent << "\":\n";
                        newSession.displaySession();
                    }
                    break;
                }
            }
        }
    }

    // ------------------------------------------------------------------
    void showAllSessions() const {
        if (sessions.empty()) {
            cout << "  No sessions recorded.\n";
            return;
        }
        cout << "\n  ============ ALL SESSIONS ============\n";
        for (const auto& s : sessions)
            s.displaySession();
    }

    // ------------------------------------------------------------------
    void showWaitlist(string tutorName, int slotId) {
        string key = tutorName + "_" + to_string(slotId);
        cout << "\n  Waitlist for Tutor \"" << tutorName << "\", Slot " << slotId << ":\n";
        getWaitlist(key).displayWaitlist();
    }

    // ------------------------------------------------------------------
    void menu() {
        int choice;
        do {
            cout << "\n+======================================+\n";
            cout << "|   TUTOR AVAILABILITY PLATFORM MENU   |\n";
            cout << "+======================================+\n";
            cout << "|  1. Add Tutor                        |\n";
            cout << "|  2. Add Student                      |\n";
            cout << "|  3. Show All Tutors                  |\n";
            cout << "|  4. Show All Students                |\n";
            cout << "|  5. Search Tutors by Subject         |\n";
            cout << "|  6. Recommend Tutors                 |\n";
            cout << "|  7. Book Session                     |\n";
            cout << "|  8. Cancel Session                   |\n";
            cout << "|  9. Show All Sessions                |\n";
            cout << "| 10. Show Waitlist                    |\n";
            cout << "|  0. Exit                             |\n";
            cout << "+======================================+\n";
            cout << "  Enter choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                int id, exp;
                float rating;
                string name, contact;
                cout << "  Tutor ID: "; cin >> id; cin.ignore();
                cout << "  Name: "; getline(cin, name);
                cout << "  Contact: "; getline(cin, contact);
                cout << "  Experience (years): "; cin >> exp;
                cout << "  Rating (0-5): "; cin >> rating; cin.ignore();

                Tutor t(id, name, contact, exp, rating);

                int numSubjects;
                cout << "  Number of subjects: "; cin >> numSubjects; cin.ignore();
                for (int i = 0; i < numSubjects; i++) {
                    string subj;
                    cout << "  Subject " << i+1 << ": "; getline(cin, subj);
                    t.addSubject(subj);
                }

                int numSlots;
                cout << "  Number of time slots: "; cin >> numSlots; cin.ignore();
                for (int i = 0; i < numSlots; i++) {
                    int sid;
                    string date, time;
                    cout << "  Slot ID: "; cin >> sid; cin.ignore();
                    cout << "  Date (e.g. 2025-06-10): "; getline(cin, date);
                    cout << "  Time (e.g. 10:00 AM): "; getline(cin, time);
                    t.addAvailability(TimeSlot(sid, date, time));
                }

                addTutor(t);

            } else if (choice == 2) {
                int id;
                string name, contact;
                cout << "  Student ID: "; cin >> id; cin.ignore();
                cout << "  Name: "; getline(cin, name);
                cout << "  Contact: "; getline(cin, contact);
                addStudent(Student(id, name, contact));

            } else if (choice == 3) {
                showAllTutors();

            } else if (choice == 4) {
                showAllStudents();

            } else if (choice == 5) {
                string subj;
                cout << "  Enter subject: "; getline(cin, subj);
                searchTutorsBySubject(subj);

            } else if (choice == 6) {
                string subj, date, time;
                cout << "  Subject: "; getline(cin, subj);
                cout << "  Date: "; getline(cin, date);
                cout << "  Time: "; getline(cin, time);
                recommendTutors(subj, date, time);

            } else if (choice == 7) {
                string tName, sName, subj;
                int slotId;
                cout << "  Tutor name: "; getline(cin, tName);
                cout << "  Student name: "; getline(cin, sName);
                cout << "  Subject: "; getline(cin, subj);
                cout << "  Slot ID: "; cin >> slotId; cin.ignore();
                bookSession(tName, sName, subj, slotId);

            } else if (choice == 8) {
                int sid;
                cout << "  Session ID to cancel: "; cin >> sid; cin.ignore();
                cancelSession(sid);

            } else if (choice == 9) {
                showAllSessions();

            } else if (choice == 10) {
                string tName;
                int slotId;
                cout << "  Tutor name: "; getline(cin, tName);
                cout << "  Slot ID: "; cin >> slotId; cin.ignore();
                showWaitlist(tName, slotId);

            } else if (choice != 0) {
                cout << "  Invalid option. Try again.\n";
            }

        } while (choice != 0);

        cout << "\n  Goodbye!\n";
    }
};

