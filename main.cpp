#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

struct Question {
    string text;
    vector<string> keywords;
    string tip;
};

struct Role {
    string name;
    vector<Question> questions;
};

string lowerText(string s) {
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return s;
}

int evaluateAnswer(const string& answer, const vector<string>& keywords,
                   vector<string>& matched) {
    string a = lowerText(answer);
    matched.clear();

    if (a.find_first_not_of(" \t\n\r") == string::npos) return 0;

    for (const auto& word : keywords) {
        if (a.find(lowerText(word)) != string::npos)
            matched.push_back(word);
    }

    int score = 2; // A non-empty, relevant attempt earns a small baseline.
    score += static_cast<int>(matched.size()) * 2;
    if (answer.size() >= 80) score += 2;
    if (answer.size() >= 180) score += 1;
    return min(score, 10);
}

string timestamp() {
    time_t now = time(nullptr);
    tm local{};
#ifdef _WIN32
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif
    ostringstream out;
    out << put_time(&local, "%Y%m%d_%H%M%S");
    return out.str();
}

vector<Role> makeRoles() {
    return {
        {"C++ Developer", {
            {"Tell me about yourself and why you are interested in C++ development.",
             {"C++", "programming", "problem solving", "project"}, "Connect your skills to a project and explain what you want to learn."},
            {"What is the difference between a class and an object in C++?",
             {"class", "blueprint", "object", "instance"}, "Explain that a class defines a structure and an object is an instance of it."},
            {"What is the difference between a pointer and a reference?",
             {"address", "pointer", "reference", "null", "alias"}, "Mention null pointers, reassignment, and how references act as aliases."},
            {"What is a constructor? Name two types of constructors.",
             {"constructor", "initialize", "default", "parameterized", "copy"}, "Describe when constructors run and give examples of constructor types."},
            {"Explain inheritance and one situation where it is useful.",
             {"inheritance", "base", "derived", "reuse", "class"}, "Give a simple base-class and derived-class example."},
            {"What is polymorphism in C++?",
             {"polymorphism", "overloading", "overriding", "virtual", "runtime"}, "Differentiate compile-time and runtime polymorphism."},
            {"What is the purpose of a virtual function?",
             {"virtual", "override", "runtime", "base", "derived"}, "Explain runtime method selection through a base-class pointer or reference."},
            {"What is the difference between stack and heap memory?",
             {"stack", "heap", "automatic", "dynamic", "allocation"}, "Discuss lifetime, allocation, and who manages the memory."},
            {"What is a destructor and when is it called?",
             {"destructor", "cleanup", "release", "object", "scope"}, "Mention resource cleanup when an object is destroyed."},
            {"How do you handle errors or exceptions in C++?",
             {"try", "catch", "throw", "exception", "error"}, "Give a small example using try, throw, and catch."}
        }},
        {"General Fresher", {
            {"Tell me about yourself.",
             {"education", "skills", "project", "goal", "interest"}, "Keep it structured: education, skills, project, and career goal."},
            {"What are your strengths?",
             {"communication", "teamwork", "learning", "problem solving", "adaptable"}, "Support each strength with a short real example."},
            {"What is one skill you are currently improving?",
             {"learning", "practice", "improve", "feedback", "goal"}, "Show a growth mindset and explain the steps you are taking."},
            {"Describe a project you have worked on.",
             {"project", "problem", "solution", "role", "result"}, "Explain the problem, your contribution, tools, and outcome."},
            {"How do you handle a difficult task?",
             {"plan", "break", "research", "ask", "solution"}, "Describe how you divide the task and check progress."},
            {"How do you work in a team?",
             {"teamwork", "communicate", "listen", "responsibility", "support"}, "Include an example of collaboration or resolving a disagreement."},
            {"Why should we select you?",
             {"skills", "learn", "contribute", "dedicated", "team"}, "Connect your current abilities with your willingness to learn."},
            {"Where do you see yourself in five years?",
             {"career", "skills", "experience", "growth", "goal"}, "Give a realistic answer focused on learning and responsibility."},
            {"How do you manage deadlines?",
             {"prioritize", "plan", "time", "deadline", "progress"}, "Mention prioritization, milestones, and communicating early."},
            {"Do you have any questions for the interviewer?",
             {"role", "team", "expectations", "learning", "company"}, "Ask about the role, team, learning opportunities, or expectations."}
        }},
        {"Python Developer", {
            {"What are the main features of Python?",
             {"readable", "interpreted", "dynamic", "library", "high level"}, "Mention readability, interpreted execution, and its ecosystem."},
            {"What is the difference between a list and a tuple?",
             {"list", "tuple", "mutable", "immutable"}, "Focus on whether elements can be changed after creation."},
            {"What is a dictionary in Python?",
             {"key", "value", "mapping", "unique"}, "Explain key-value pairs and show a simple use case."},
            {"What is the purpose of a function?",
             {"def", "reuse", "parameter", "return", "task"}, "Explain reusable blocks of code, inputs, and return values."},
            {"What is object-oriented programming?",
             {"class", "object", "encapsulation", "inheritance", "polymorphism"}, "Describe classes and objects, then mention core OOP concepts."},
            {"What is exception handling in Python?",
             {"try", "except", "finally", "exception", "error"}, "Explain how try and except prevent a program from stopping unexpectedly."},
            {"What is the difference between == and is?",
             {"value", "identity", "equal", "same object"}, "Explain value equality versus object identity."},
            {"What is a module?",
             {"module", "file", "import", "reuse", "function"}, "Describe a Python file that can be imported."},
            {"What is a virtual environment?",
             {"environment", "dependencies", "packages", "isolated"}, "Explain isolated project dependencies."},
            {"How would you debug a Python program?",
             {"debug", "error", "print", "breakpoint", "traceback"}, "Mention reading tracebacks, reproducing bugs, and using breakpoints."}
        }}
    };
}

int main() {
    cout << "============================================\n";
    cout << "          MOCK INTERVIEW CHATBOT\n";
    cout << "                 C++ Edition\n";
    cout << "============================================\n";

    while (true) {
        cout << "\n1. Start a new interview\n2. About this app\n3. Exit\n";
        cout << "Choose an option: ";
        string choice;
        getline(cin, choice);

        if (choice == "3") {
            cout << "\nThanks for practising. Keep learning and good luck!\n";
            break;
        }
        if (choice == "2") {
            cout << "\nThis is an offline, rule-based mock interview practice app.\n"
                 << "It asks 10 questions, checks for topic keywords, gives tips,\n"
                 << "calculates a practice score, and saves a text report.\n"
                 << "It does not use AI or send your answers online.\n";
            continue;
        }
        if (choice != "1") {
            cout << "Please enter 1, 2, or 3.\n";
            continue;
        }

        auto roles = makeRoles();
        cout << "\nSelect your interview category:\n";
        for (size_t i = 0; i < roles.size(); ++i)
            cout << i + 1 << ". " << roles[i].name << "\n";
        cout << "Enter category number: ";

        string roleChoice;
        getline(cin, roleChoice);
        int selected = 0;
        try { selected = stoi(roleChoice) - 1; } catch (...) { selected = -1; }
        if (selected < 0 || selected >= static_cast<int>(roles.size())) {
            cout << "Invalid category. Returning to menu.\n";
            continue;
        }

        cout << "\nEnter your name: ";
        string candidate;
        getline(cin, candidate);
        if (candidate.empty()) candidate = "Candidate";

        cout << "\nWelcome, " << candidate << "!\n";
        cout << "Category: " << roles[selected].name << "\n";
        cout << "There are 10 questions. Type your answer and press Enter.\n";
        cout << "Tip: Give clear answers with examples. Type /skip to skip a question.\n\n";

        int total = 0;
        vector<string> report;
        report.push_back("MOCK INTERVIEW REPORT");
        report.push_back("=====================");
        report.push_back("Candidate: " + candidate);
        report.push_back("Category: " + roles[selected].name);
        report.push_back("");

        for (size_t i = 0; i < roles[selected].questions.size(); ++i) {
            const auto& q = roles[selected].questions[i];
            cout << "Interviewer [" << i + 1 << "/10]: " << q.text << "\n";
            cout << "You: ";
            string answer;
            getline(cin, answer);

            if (lowerText(answer) == "/skip") {
                cout << "Interviewer: No problem. Let's move to the next question.\n\n";
                report.push_back("Q" + to_string(i + 1) + ": " + q.text);
                report.push_back("Answer: [Skipped]");
                report.push_back("Score: 0/10");
                report.push_back("");
                continue;
            }

            vector<string> matched;
            int score = evaluateAnswer(answer, q.keywords, matched);
            total += score;

            cout << "Interviewer: ";
            if (score >= 8) cout << "Good response! You covered several important points.\n";
            else if (score >= 5) cout << "Nice attempt. Add more relevant details and an example.\n";
            else cout << "Keep practising. Try to include key concepts and a clear example.\n";

            cout << "Practice score: " << score << "/10\n";
            cout << "Suggestion: " << q.tip << "\n\n";

            report.push_back("Q" + to_string(i + 1) + ": " + q.text);
            report.push_back("Answer: " + answer);
            report.push_back("Matched concepts: " +
                (matched.empty() ? string("None detected") : [&]() {
                    string s;
                    for (size_t j = 0; j < matched.size(); ++j) {
                        if (j) s += ", ";
                        s += matched[j];
                    }
                    return s;
                }()));
            report.push_back("Score: " + to_string(score) + "/10");
            report.push_back("Suggestion: " + q.tip);
            report.push_back("");
        }

        int maxScore = static_cast<int>(roles[selected].questions.size()) * 10;
        int percent = total * 100 / maxScore;
        cout << "============================================\n";
        cout << "              INTERVIEW RESULT\n";
        cout << "============================================\n";
        cout << "Candidate: " << candidate << "\n";
        cout << "Total score: " << total << "/" << maxScore << "\n";
        cout << "Overall: " << percent << "%\n";
        if (percent >= 80) cout << "Feedback: Excellent practice performance!\n";
        else if (percent >= 60) cout << "Feedback: Good progress. Keep refining your answers.\n";
        else if (percent >= 40) cout << "Feedback: Fair attempt. Review the suggestions and practise again.\n";
        else cout << "Feedback: Keep practising the fundamentals. Improvement comes with practice.\n";

        report.push_back("TOTAL SCORE: " + to_string(total) + "/" + to_string(maxScore));
        report.push_back("PERCENTAGE: " + to_string(percent) + "%");
        report.push_back("Note: Scores are keyword-based practice estimates, not an AI assessment.");

        string filename = "reports/interview_report_" + timestamp() + ".txt";
        ofstream file(filename);
        if (file) {
            for (const auto& line : report) file << line << "\n";
            cout << "\nYour report was saved to: " << filename << "\n";
        } else {
            cout << "\nCould not save report. Make sure the reports folder exists.\n";
        }
        cout << "============================================\n";
    }
    return 0;
}
