#include<bits/stdc++.h>
#include <cstdio>
using namespace std;

class Vote {
    private:
        unsigned int upVotes;
        unsigned int downVotes;

    public:
        Vote() {
            upVotes = 0;
            downVotes = 0;
        }

        void upVote() {
            (this -> upVotes)++;
        }

        void downVote() {
            (this -> downVotes)++;
        }


        unsigned int getUpVotes() {return upVotes;}
        unsigned int getDownVotes() {return downVotes;}
};

class Comment {
    private:
        static unsigned int id_generator;
        unsigned int id;
        unsigned int userId;
        string comment;
        Vote voteBank;

    public:
        Comment(unsigned int userId,  string comment) {
            this -> comment = comment;
            this -> id = getNextId();
            this ->userId = userId;
            this -> voteBank = Vote();
        }

        //Getter Methods
        string getComment() {return comment;}
        unsigned int getUserid() {return userId;}
        unsigned int getId() {return id;}
        unsigned int getUpVotes() {return voteBank.getUpVotes();}
        unsigned int getDownVotes() {return voteBank.getDownVotes();}
        unsigned int getNextId() {return ++id_generator;}
};

class Answer {
    private:
        static unsigned int id_generator;
        unsigned int id;
        unsigned int userId;
        string answer;
        Vote voteBank;

    public:
        Answer(unsigned int userId,  string answer) {
            this -> answer = answer;
            this -> id = getNextId();
            this ->userId = userId;
            this -> voteBank = Vote();
        }


        //Getter methods
        string getAnswer() {return answer;}
        unsigned int getUserid() {return userId;}
        unsigned int getId() {return id;}
        unsigned int getUpVotes() {return voteBank.getUpVotes();}
        unsigned int getDownVotes() {return voteBank.getDownVotes();}
        unsigned int getNextId() {return ++id_generator;}
};

class Question {
    private:
        static unsigned int id_generator;
        unsigned int id;
        unsigned int userId;
        string question;
        Vote voteBank;
        map<unsigned int, Answer *> idToAnswer;

    public:
        Question(unsigned int userId,  string question) {
            this -> question = question;
            this -> id = getNextId();
            this ->userId = userId;
            this -> voteBank = Vote();
        }

        void print() {
            printf("(%d) (%d, %d)\n", id, voteBank.getUpVotes(), voteBank.getDownVotes());
            cout << question << endl;

            return;
        }


        //Getter methods
        string getQuestion() {return question;}
        unsigned int getUserid() {return userId;}
        unsigned int getId() {return id;}
        unsigned int getUpVotes() {return voteBank.getUpVotes();}
        unsigned int getDownVotes() {return voteBank.getDownVotes();}
        unsigned int getNextId() {return ++id_generator;}
        Answer * getAnswer(int id) {return idToAnswer[id];}
};

class User;

class StackOverflow{
    private:
        mutex mtx;
        map<unsigned int, User *> idToUser;
        map<unsigned int, Question *> idToQuestion;

    public:
        // Singleton class
        static StackOverflow& getInstance() {
            static StackOverflow instance;

            return instance;
        }

        User * createUser(string name);
        void postQuestion(Question *question);

        //Helper methods
        void printQuestionsAndAnswers ();

        //Getter Methods
        User * getUser(int id); 
        Question * getQuestion(int id);
        Answer * getAnswer(int id);
};

class User {
    private:
        static unsigned int id_generator;
        unsigned int id;
        string name;
        int reputationScore;
        StackOverflow& system;

        map<unsigned int, Question *> idToQuestion;
        map<unsigned int, Answer *> idToAnswer;

    public:
        User(string name, StackOverflow& system) : system(system) {
            this -> id = getNextId();
            this -> name = name;
            this -> reputationScore = 0;
        }

        void postQuestion(string question) {
            Question *newQuestion = new Question(id, question);
            unsigned int newQuestionId = newQuestion->getId();

            idToQuestion[newQuestionId] = newQuestion;
            system.postQuestion(newQuestion);
        }

        // Helper methods
        void print() {
            cout << "User id: " << (this -> id) << endl;
            cout << "User name: " << (this -> name) << endl;
            cout << "User reputationScore: " << (this -> reputationScore) << endl;

            return;
        }

        //Getter Methods 
        unsigned int getId() {return this -> id;}
        string getName() {return this -> name;}
        int getRepuationScore() {return this -> reputationScore;}
        unsigned int getNextId() {return ++id_generator;}
};


//-------------------------------------------------------------------------------
// Singleton class
User * StackOverflow::createUser(string name) {
    User *newUser = new User(name, getInstance());
    unsigned int newUserId = newUser -> getId();

    idToUser[newUserId] = newUser;
    return newUser;
}

void StackOverflow::postQuestion(Question *question) {
    unsigned int questionId = question -> getId();
    idToQuestion[questionId] = question;

    return;
}

void StackOverflow::printQuestionsAndAnswers() {
    for(auto &question: idToQuestion) {
        Question *currentQuestion = question.second;

        currentQuestion -> print();
        cout << endl;
    }

    return;
}


//Getter Methods
User * StackOverflow::getUser(int id) {return idToUser[id];}
Question * StackOverflow::getQuestion(int id) {return idToQuestion[id];}

//-------------------------------------------------------------------------------------



//Initialize id generators for all classes that generate an id
unsigned int User::id_generator = 0;
unsigned int Question::id_generator = 0;
unsigned int Answer::id_generator = 0;
unsigned int Comment::id_generator = 0;


//Driver code
int main() {
    StackOverflow& system = StackOverflow::getInstance();

    User *user1 = system.createUser("Aaditya");
    user1 -> postQuestion("How do you work with classes in cpp?");
    user1 -> postQuestion("How to prepare for placements?");
    user1 -> postQuestion("How to learn DSA?");

    system.printQuestionsAndAnswers();

    return 0;
}
