#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
// CLASS: TimeSlot
class TimeSlot {
private:
    int slotId;
    string date;
    string time;
    bool isBooked;

public:
    TimeSlot() {
        slotId = 0;
        date = "";
        time = "";
        isBooked = false;
    }

    TimeSlot(int id, string d, string t) {
        slotId = id;
        date = d;
        time = t;
        isBooked = false;
    }

    int getSlotId() { return slotId; }
    string getDate() { return date; }
    string getTime() { return time; }
    bool getIsBooked() { return isBooked; }

    void bookSlot() { isBooked = true; }
    void freeSlot() { isBooked = false; }

    void displaySlot() {
        cout << "  Slot ID: " << slotId;
        cout << " | Date: " << date;
        cout << " | Time: " << time;
        if (isBooked)
            cout << " | Status: Booked" << endl;
        else
            cout << " | Status: Available" << endl;
    }
};
// CLASS: Waitlist
class Waitlist {
private:
    queue<string> waitingStudents;

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

    bool isEmpty() {
        return waitingStudents.empty();
    }

    void displayWaitlist() {
        if (waitingStudents.empty()) {
            cout << "  Waitlist is empty.\n";
            return;
        }
        queue<string> temp = waitingStudents;
        int pos = 1;
        cout << "  Waitlist:\n";
        while (!temp.empty()) {
            cout << "    " << pos << ". " << temp.front() << endl;
            pos++;
            temp.pop();
        }
    }
};
// CLASS: Session
class Session {
private:
    int sessionId;
    string tutorName;
    string studentName;
    string subject;
    string slotInfo;
    string status;

public:
    Session() {
        sessionId = 0;
        status = "Scheduled";
    }

    Session(int id, string tName, string sName, string subj, string slot) {
        sessionId = id;
        tutorName = tName;
        studentName = sName;
        subject = subj;
        slotInfo = slot;
        status = "Scheduled";
    }

    int getSessionId() { return sessionId; }
    string getTutorName() { return tutorName; }
    string getStudentName() { return studentName; }
    string getSubject() { return subject; }
    string getSlotInfo() { return slotInfo; }
    string getStatus() { return status; }

    void setStatus(string s) { status = s; }
    void setStudentName(string s) { studentName = s; }

    void cancelSession() {
        status = "Cancelled";
        cout << "  Session ID " << sessionId << " has been cancelled.\n";
    }

    void displaySession() {
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
// CLASS: User (Base Class)
class User {
private:
    int userId;
    string name;
    string contactInfo;

public:
    User() {
        userId = 0;
        name = "";
        contactInfo = "";
    }

    User(int id, string n, string contact) {
        userId = id;
        name = n;
        contactInfo = contact;
    }

    int getUserId() { return userId; }
    string getName() { return name; }
    string getContactInfo() { return contactInfo; }

    void setUserId(int id) { userId = id; }
    void setName(string n) { name = n; }
    void setContactInfo(string c) { contactInfo = c; }

    virtual void viewProfile() = 0;
};
// CLASS: Tutor (Derived from User)
class Tutor : public User {
private:
    vector<string> subjects;
    int experienceYears;
    float rating;
    vector<TimeSlot> availableSlots;

public:
    Tutor() : User() {
        experienceYears = 0;
        rating = 0.0;
    }

    Tutor(int id, string n, string contact, int exp, float rate) : User(id, n, contact) {
        experienceYears = exp;
        rating = rate;
    }

    float getRating() { return rating; }
    int getExperienceYears() { return experienceYears; }

    void addSubject(string subject) {
        subjects.push_back(subject);
    }

    void addAvailability(TimeSlot slot) {
        availableSlots.push_back(slot);
    }

    bool teachesSubject(string subj) {
        for (int i = 0; i < subjects.size(); i++) {
            if (subjects[i] == subj)
                return true;
        }
        return false;
    }

    bool isAvailable(int slotId) {
        for (int i = 0; i < availableSlots.size(); i++) {
            if (availableSlots[i].getSlotId() == slotId && !availableSlots[i].getIsBooked())
                return true;
        }
        return false;
    }

    TimeSlot* findSlot(int slotId) {
        for (int i = 0; i < availableSlots.size(); i++) {
            if (availableSlots[i].getSlotId() == slotId)
                return &availableSlots[i];
        }
        return NULL;
    }

    vector<TimeSlot>& getAvailableSlots() {
        return availableSlots;
    }

    void viewProfile() {
        cout << "\n  ========== TUTOR PROFILE ==========\n";
        cout << "  ID          : " << getUserId() << endl;
        cout << "  Name        : " << getName() << endl;
        cout << "  Contact     : " << getContactInfo() << endl;
        cout << "  Experience  : " << experienceYears << " years\n";
        cout << "  Rating      : " << rating << " / 5.0\n";
        cout << "  Subjects    : ";
        for (int i = 0; i < subjects.size(); i++) {
            cout << subjects[i];
            if (i < subjects.size() - 1)
                cout << ", ";
        }
        cout << "\n  Available Slots:\n";
        if (availableSlots.empty()) {
            cout << "    No slots available.\n";
        } else {
            for (int i = 0; i < availableSlots.size(); i++)
                availableSlots[i].displaySlot();
        }
        cout << "  ====================================\n";
    }
};
// CLASS: Student (Derived from User)
class Student : public User {
private:
    vector<Session> sessionHistory;

public:
    Student() : User() {}

    Student(int id, string n, string contact) : User(id, n, contact) {}

    void addToHistory(Session s) {
        sessionHistory.push_back(s);
    }

    void requestSession() {
        cout << "  Student \"" << getName() << "\" is requesting a session.\n";
    }

    void viewProfile() {
        cout << "\n  ========== STUDENT PROFILE ==========\n";
        cout << "  ID          : " << getUserId() << endl;
        cout << "  Name        : " << getName() << endl;
        cout << "  Contact     : " << getContactInfo() << endl;
        cout << "  Sessions    : " << sessionHistory.size() << " session(s) in history\n";
        cout << "  =====================================\n";
    }

    void viewSessionHistory() {
        if (sessionHistory.empty()) {
            cout << "  No session history found.\n";
            return;
        }
        cout << "\n  === Session History for " << getName() << " ===\n";
        for (int i = 0; i < sessionHistory.size(); i++)
            sessionHistory[i].displaySession();
    }
};
// CLASS: RecommendationEngine
class RecommendationEngine {
public:
    float calculateScore(Tutor& tutor, string subject, string date, string time) {
        float score = 0.0;

        if (tutor.teachesSubject(subject))
            score += 50.0;

        score += tutor.getRating() * 6.0;

        vector<TimeSlot>& slots = tutor.getAvailableSlots();
        for (int i = 0; i < slots.size(); i++) {
            if (slots[i].getDate() == date && slots[i].getTime() == time && !slots[i].getIsBooked()) {
                score += 20.0;
                break;
            }
        }

        return score;
    }

    vector<Tutor*> recommendTutors(vector<Tutor>& tutors, string subject, string date, string time) {
        vector<float> scores;
        vector<Tutor*> matched;

        for (int i = 0; i < tutors.size(); i++) {
            float s = calculateScore(tutors[i], subject, date, time);
            if (s > 0) {
                scores.push_back(s);
                matched.push_back(&tutors[i]);
            }
        }

        // bubble sort descending by score
        for (int i = 0; i < matched.size(); i++) {
            for (int j = i + 1; j < matched.size(); j++) {
                if (scores[j] > scores[i]) {
                    float tempScore = scores[i];
                    scores[i] = scores[j];
                    scores[j] = tempScore;

                    Tutor* tempTutor = matched[i];
                    matched[i] = matched[j];
                    matched[j] = tempTutor;
                }
            }
        }

        return matched;
    }
};
// CLASS: Platform (Main)
class Platform {
private:
    vector<Tutor> tutors;
    vector<Student> students;
    vector<Session> sessions;
    RecommendationEngine recommender;
    int nextSessionId;

    vector<string> waitlistKeys;
    vector<Waitlist> waitlists;

    Waitlist& getWaitlist(string key) {
        for (int i = 0; i < waitlistKeys.size(); i++) {
            if (waitlistKeys[i] == key)
                return waitlists[i];
        }
        waitlistKeys.push_back(key);
        waitlists.push_back(Waitlist());
        return waitlists[waitlists.size() - 1];
    }

public:
    Platform() {
        nextSessionId = 1;
    }

    void addTutor(Tutor t) {
        tutors.push_back(t);
        cout << "  Tutor \"" << t.getName() << "\" added successfully.\n";
    }

    void addStudent(Student s) {
        students.push_back(s);
        cout << "  Student \"" << s.getName() << "\" added successfully.\n";
    }

    void showAllTutors() {
        if (tutors.empty()) {
            cout << "  No tutors registered.\n";
            return;
        }
        cout << "\n  ============ ALL TUTORS ============\n";
        for (int i = 0; i < tutors.size(); i++)
            tutors[i].viewProfile();
    }

    void showAllStudents() {
        if (students.empty()) {
            cout << "  No students registered.\n";
            return;
        }
        cout << "\n  ============ ALL STUDENTS ============\n";
        for (int i = 0; i < students.size(); i++)
            students[i].viewProfile();
    }

    void searchTutorsBySubject(string subject) {
        cout << "\n  === Tutors teaching \"" << subject << "\" ===\n";
        bool found = false;
        for (int i = 0; i < tutors.size(); i++) {
            if (tutors[i].teachesSubject(subject)) {
                tutors[i].viewProfile();
                found = true;
            }
        }
        if (!found)
            cout << "  No tutors found for subject: " << subject << endl;
    }

    void recommendTutors(string subject, string date, string time) {
        cout << "\n  === Recommended Tutors for \"" << subject << "\" on " << date << " at " << time << " ===\n";

        vector<Tutor*> recs = recommender.recommendTutors(tutors, subject, date, time);

        if (recs.empty()) {
            cout << "  No recommendations available.\n";
            return;
        }

        for (int i = 0; i < recs.size(); i++) {
            float score = recommender.calculateScore(*recs[i], subject, date, time);
            cout << "\n  Rank #" << i + 1 << " (Score: " << score << ")";
            recs[i]->viewProfile();
        }
    }

    void bookSession(string tutorName, string studentName, string subject, int slotId) {
        Tutor* tutor = NULL;
        for (int i = 0; i < tutors.size(); i++) {
            if (tutors[i].getName() == tutorName) {
                tutor = &tutors[i];
                break;
            }
        }
        if (tutor == NULL) {
            cout << "  ERROR: Tutor \"" << tutorName << "\" not found.\n";
            return;
        }

        Student* student = NULL;
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getName() == studentName) {
                student = &students[i];
                break;
            }
        }
        if (student == NULL) {
            cout << "  ERROR: Student \"" << studentName << "\" not found.\n";
            return;
        }

        TimeSlot* slot = tutor->findSlot(slotId);
        if (slot == NULL) {
            cout << "  ERROR: Slot ID " << slotId << " not found.\n";
            return;
        }

        string waitlistKey = tutorName + "_" + to_string(slotId);

        if (slot->getIsBooked()) {
            cout << "  Slot is already booked. Adding \"" << studentName << "\" to waitlist...\n";
            getWaitlist(waitlistKey).addStudent(studentName);
            return;
        }

        slot->bookSlot();
        string slotInfo = slot->getDate() + " " + slot->getTime();

        Session newSession(nextSessionId, tutorName, studentName, subject, slotInfo);
        nextSessionId++;
        sessions.push_back(newSession);
        student->addToHistory(newSession);

        cout << "  Session booked successfully!\n";
        newSession.displaySession();
    }

    void cancelSession(int sessionId) {
        Session* sess = NULL;
        for (int i = 0; i < sessions.size(); i++) {
            if (sessions[i].getSessionId() == sessionId) {
                sess = &sessions[i];
                break;
            }
        }
        if (sess == NULL) {
            cout << "  ERROR: Session ID " << sessionId << " not found.\n";
            return;
        }
        if (sess->getStatus() == "Cancelled") {
            cout << "  Session is already cancelled.\n";
            return;
        }

        string tutorName = sess->getTutorName();
        string slotInfo  = sess->getSlotInfo();
        string subject   = sess->getSubject();

        sess->cancelSession();

        Tutor* tutor = NULL;
        for (int i = 0; i < tutors.size(); i++) {
            if (tutors[i].getName() == tutorName) {
                tutor = &tutors[i];
                break;
            }
        }

        if (tutor != NULL) {
            vector<TimeSlot>& slots = tutor->getAvailableSlots();
            for (int i = 0; i < slots.size(); i++) {
                string info = slots[i].getDate() + " " + slots[i].getTime();
                if (info == slotInfo && slots[i].getIsBooked()) {
                    slots[i].freeSlot();

                    string waitlistKey = tutorName + "_" + to_string(slots[i].getSlotId());
                    if (!getWaitlist(waitlistKey).isEmpty()) {
                        string nextStudent = getWaitlist(waitlistKey).getNextStudent();
                        cout << "  Auto-assigning slot to waitlisted student: \"" << nextStudent << "\"\n";
                        slots[i].bookSlot();

                        Session newSession(nextSessionId, tutorName, nextStudent, subject, slotInfo);
                        nextSessionId++;
                        sessions.push_back(newSession);

                        for (int j = 0; j < students.size(); j++) {
                            if (students[j].getName() == nextStudent) {
                                students[j].addToHistory(newSession);
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

    void showAllSessions() {
        if (sessions.empty()) {
            cout << "  No sessions recorded.\n";
            return;
        }
        cout << "\n  ============ ALL SESSIONS ============\n";
        for (int i = 0; i < sessions.size(); i++)
            sessions[i].displaySession();
    }

    void showWaitlist(string tutorName, int slotId) {
        string key = tutorName + "_" + to_string(slotId);
        cout << "\n  Waitlist for Tutor \"" << tutorName << "\", Slot " << slotId << ":\n";
        getWaitlist(key).displayWaitlist();
    }

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
                    cout << "  Subject " << i + 1 << ": "; getline(cin, subj);
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
//Test Cases
int main() {
    Platform platform;

    cout << "\n+==========================================+\n";
    cout << "|   TUTOR AVAILABILITY PLATFORM      |\n";
    cout << "|   OOP Project -- Test Cases              |\n";
    cout << "+==========================================+\n";

    // ==================================================================
    // TC-01: Add Tutor
    // Feature : Add Tutor
    // Input   : Tutor name, contact, subject, rating, availability
    // Expected: Tutor profile is created successfully
    // ==================================================================
    cout << "\n--------------------------------------------------\n";
    cout << "TC-01: Add Tutor\n";
    cout << "--------------------------------------------------\n";

    Tutor t1(101, "Dr. Ali Raza", "ali@email.com", 8, 4.8);
    t1.addSubject("Mathematics");
    t1.addSubject("Physics");
    t1.addAvailability(TimeSlot(1, "2025-06-10", "10:00 AM"));
    t1.addAvailability(TimeSlot(2, "2025-06-11", "04:00 PM"));
    platform.addTutor(t1);

    Tutor t2(102, "Ms. Sara Khan", "sara@email.com", 5, 4.5);
    t2.addSubject("Computer Science");
    t2.addSubject("Mathematics");
    t2.addAvailability(TimeSlot(3, "2025-06-10", "10:00 AM"));
    t2.addAvailability(TimeSlot(4, "2025-06-12", "04:00 PM"));
    platform.addTutor(t2);

    Tutor t3(103, "Mr. Usman Tariq", "usman@email.com", 6, 4.2);
    t3.addSubject("Physics");
    t3.addSubject("Chemistry");
    t3.addAvailability(TimeSlot(5, "2025-06-13", "04:00 PM"));
    t3.addAvailability(TimeSlot(6, "2025-06-14", "02:00 PM"));
    platform.addTutor(t3);

    cout << "\n  [Result] Tutor profiles created. Displaying all tutors:\n";
    platform.showAllTutors();

    // ==================================================================
    // TC-02: Add Student
    // Feature : Add Student
    // Input   : Student name and contact details
    // Expected: Student profile is created successfully
    // ==================================================================
    cout << "\n--------------------------------------------------\n";
    cout << "TC-02: Add Student\n";
    cout << "--------------------------------------------------\n";

    Student s1(201, "Ahmed Malik",  "ahmed@email.com");
    Student s2(202, "Zara Noor",    "zara@email.com");
    Student s3(203, "Hassan Butt",  "hassan@email.com");

    platform.addStudent(s1);
    platform.addStudent(s2);
    platform.addStudent(s3);

    cout << "\n  [Result] Student profiles created. Displaying all students:\n";
    platform.showAllStudents();

    // ==================================================================
    // TC-03: Search Tutors by Subject
    // Feature : Search Tutors by Subject
    // Input   : Subject = Mathematics
    // Expected: Matching tutors are displayed
    // ==================================================================
    cout << "\n--------------------------------------------------\n";
    cout << "TC-03: Search Tutors by Subject\n";
    cout << "--------------------------------------------------\n";
    cout << "  Input: Subject = \"Mathematics\"\n";

    platform.searchTutorsBySubject("Mathematics");

    cout << "  [Result] All tutors teaching Mathematics are listed above.\n";

    // ==================================================================
    // TC-04: Recommend Tutors
    // Feature : Recommend Tutors
    // Input   : Subject = Physics, preferred slot = 04:00 PM
    // Expected: Tutors ranked by subject match, rating, availability
    // ==================================================================
    cout << "\n--------------------------------------------------\n";
    cout << "TC-04: Recommend Tutors\n";
    cout << "--------------------------------------------------\n";
    cout << "  Input: Subject = \"Physics\", Date = \"2025-06-13\", Time = \"04:00 PM\"\n";

    platform.recommendTutors("Physics", "2025-06-13", "04:00 PM");

    cout << "  [Result] Tutors ranked by subject match + rating + availability.\n";

    // ==================================================================
    // TC-05: Book Session
    // Feature : Book Session
    // Input   : Student selects a tutor and an available slot
    // Expected: Session is created and slot is marked booked
    // ==================================================================
    cout << "\n--------------------------------------------------\n";
    cout << "TC-05: Book Session\n";
    cout << "--------------------------------------------------\n";
    cout << "  Input: Ahmed Malik books Dr. Ali Raza for Mathematics, Slot 1\n";

    platform.bookSession("Dr. Ali Raza", "Ahmed Malik", "Mathematics", 1);

    cout << "\n  [Result] Session created and Slot 1 is now marked as Booked.\n";

    cout << "\n  Verifying slot status in Dr. Ali Raza's profile:\n";
    platform.searchTutorsBySubject("Mathematics");

    // ==================================================================
    // TC-06: Conflict Detection
    // Feature : Conflict Detection
    // Input   : Another student requests the same already-booked slot
    // Expected: Booking rejected and student added to waitlist
    // ==================================================================
    cout << "\n--------------------------------------------------\n";
    cout << "TC-06: Conflict Detection\n";
    cout << "--------------------------------------------------\n";
    cout << "  Slot 1 of Dr. Ali Raza is already booked by Ahmed Malik.\n";
    cout << "  Input: Zara Noor tries to book the same Slot 1.\n";

    platform.bookSession("Dr. Ali Raza", "Zara Noor", "Mathematics", 1);

    cout << "\n  Input: Hassan Butt also tries to book the same Slot 1.\n";
    platform.bookSession("Dr. Ali Raza", "Hassan Butt", "Mathematics", 1);

    cout << "\n  [Result] Both students rejected from booking and added to waitlist.\n";
    cout << "  Displaying waitlist for Dr. Ali Raza, Slot 1:\n";
    platform.showWaitlist("Dr. Ali Raza", 1);

    // ==================================================================
    // Final Summary
    // ==================================================================
    cout << "\n--------------------------------------------------\n";
    cout << "  ALL TEST CASES EXECUTED SUCCESSFULLY\n";
    cout << "--------------------------------------------------\n";
    cout << "  Final session list:\n";
    platform.showAllSessions();

    return 0;
}
