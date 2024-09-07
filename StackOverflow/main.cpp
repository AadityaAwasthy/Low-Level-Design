#include<bits/stdc++.h>
using namespace std;

class User;

class Vote {
    private:
        static unsigned int id_generator;
        unsigned int id;
        unsigned int userId;
        int value;

    public:
        Vote(unsigned int userId, int value) {
            this -> userId = userId;
            this -> value = value;
            this -> id = getNextId();
        }

        unsigned int getUserid() {return userId;}
        unsigned int getId() {return id;}
        unsigned int getNextId() {return ++id_generator;}
        int getValue() {return value;}
};

class Votable {
    public:
        virtual void postVote(Vote *) = 0;
};

class Comment : public Votable {
    private:
        static unsigned int id_generator;
        unsigned int id;
        unsigned int userId;
        string comment;
        map<unsigned int , Vote *> idToVote;

    public:
        Comment(unsigned int userId,  string comment) {
            this -> comment = comment;
            this -> id = getNextId();
            this ->userId = userId;
        }

        void postVote(Vote *vote) {
            unsigned int voteId = vote -> getId();
            idToVote[voteId] = vote;
        }

        void print() {
            cout << "(" << id << ")" << "C: " << comment << endl;
        }


        //Getter Methods
        string getComment() {return comment;}
        unsigned int getUserid() {return userId;}
        unsigned int getId() {return id;}
        unsigned int getNextId() {return ++id_generator;}
};

class Commentable {
    public:
        virtual void postComment(Comment *) = 0;
};

class Answer : public Commentable, public Votable{
    private:
        static unsigned int id_generator;
        unsigned int id;
        unsigned int userId;
        string answer;
        map<unsigned int, Comment *> idToComment;
        map<unsigned int, Vote *> idToVote;

    public:
        Answer(unsigned int userId,  string answer) {
            this -> answer = answer;
            this -> id = getNextId();
            this ->userId = userId;
        }

        void postComment(Comment *comment) {
            unsigned int commentId = comment -> getId();
            idToComment[commentId] = comment;
        }

        void postVote(Vote *vote) {
            unsigned int voteId = vote -> getId();
            idToVote[voteId] = vote;
        }

        //Helper Methods
        void print() {
            cout << "(" << id << ")" << "A: " << answer << endl;
            
            for(auto &comment: idToComment) {
                comment.second -> print();
            }
        }


        //Getter methods
        string getAnswer() {return answer;}
        unsigned int getUserid() {return userId;}
        unsigned int getId() {return id;}
        // unsigned int getUpVotes() {return voteBank.getUpVotes();}
        // unsigned int getDownVotes() {return voteBank.getDownVotes();}
        unsigned int getNextId() {return ++id_generator;}
};

class Question : public Commentable, public Votable {
    private:
        static unsigned int id_generator;
        unsigned int id;
        unsigned int userId;
        string question;
        map<unsigned int, Answer *> idToAnswer;
        map<unsigned int, Comment *> idToComment;
        map<unsigned int, Vote *> idToVote;

    public:
        Question(unsigned int userId,  string question) {
            this -> question = question;
            this -> id = getNextId();
            this ->userId = userId;
        }

        void postAnswer(Answer *answer) {
            unsigned int answerId = answer -> getId();
            idToAnswer[answerId] = answer;
        }

        void postComment(Comment *comment) {
            unsigned int commentId = comment -> getId();
            idToComment[commentId] = comment;
        }

        void postVote(Vote *vote) {
            unsigned int voteId = vote -> getId();
            idToVote[voteId] = vote;
        }

        void print() {
            cout << "(" << id << ")" << "Q. " << question << endl;

            for(auto &comment: idToComment) {
                comment.second -> print();
            }

            for(auto &answer: idToAnswer) {
                answer.second -> print();
            }

            return;
        }


        //Getter methods
        string getQuestion() {return question;}
        unsigned int getUserid() {return userId;}
        unsigned int getId() {return id;}
        unsigned int getNextId() {return ++id_generator;}
        Answer * getAnswer(int id) {return idToAnswer[id];}
};


class StackOverflow{
    private:
        mutex mtx;
        map<unsigned int, User *> idToUser;
        map<unsigned int, Question *> idToQuestion;
        map<unsigned int, Answer *> idToAnswer;
        map<unsigned int, Comment *> idToComment;

    public:
        // Singleton class
        static StackOverflow& getInstance() {
            static StackOverflow instance;

            return instance;
        }

        User * createUser(string name);
        Question * postQuestion(User *user, string question);
        Answer * postAnswer(User *user, Question *question, string answer);
        Comment *postComment(User *user, Commentable *subject, string comment);
        Vote *postVote(User *user, Votable *subject, int value);
        void upVote(User *user, Votable *subject);

        //Helper methods
        void printQuestionsAndAnswers ();

        //Getter Methods
        User * getUser(int id); 
        Question * getQuestion(int id);
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
        map<unsigned int, Comment *> idToComment;
        map<unsigned int, Vote *> idToVote;

    public:
        User(string name, StackOverflow& system) : system(system) {
            this -> id = getNextId();
            this -> name = name;
            this -> reputationScore = 0;
        }

        void postQuestion(Question *question) {
            unsigned int questionId = question -> getId();
            idToQuestion[questionId] = question;
        }

        void postAnswer(Answer *answer) {
            unsigned int answerId = answer -> getId();
            idToAnswer[answerId] = answer;
        }

        void postComment(Comment *comment) {
            unsigned int commentId = comment -> getId();
            idToComment[commentId] = comment;
        }

        void postVote(Vote *vote) {
            unsigned int voteId = vote -> getId();
            idToVote[voteId] = vote;
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

Question * StackOverflow::postQuestion(User *user, string question) {
    Question *newQuestion = new Question(user -> getId(), question);
    unsigned int newQuestionId = newQuestion -> getId();

    user -> postQuestion(newQuestion);
    idToQuestion[newQuestionId] = newQuestion;

    return newQuestion;
}

Answer * StackOverflow::postAnswer(User *user, Question *question, string answer){
    Answer *newAnswer = new Answer(user -> getId(), answer);
    unsigned int newAnswerId = newAnswer -> getId();

    user -> postAnswer(newAnswer);
    question -> postAnswer(newAnswer);

    idToAnswer[newAnswerId] = newAnswer;
    return newAnswer;
}

Comment * StackOverflow::postComment(User *user, Commentable *subject, string comment) {
    Comment *newComment = new Comment(user -> getId(), comment);
    unsigned int newCommentId = newComment -> getId();

    user -> postComment(newComment);
    subject -> postComment(newComment);

    idToComment[newCommentId] = newComment;

    return newComment;
}

Vote * StackOverflow::postVote(User *user, Votable *subject, int value) {
    Vote *newVote = new Vote(user ->getId(), value);
    unsigned int newVoteId = newVote -> getId();

    user -> postVote(newVote);
    subject -> postVote(newVote);

    return newVote;
}

void StackOverflow::printQuestionsAndAnswers() {
    for(auto &question: idToQuestion) {
        question.second -> print();
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
unsigned int Vote::id_generator = 0;


//Driver code
int main() {
    StackOverflow& system = StackOverflow::getInstance();

    User *user1 = system.createUser("Aaditya");
    User *user2 = system.createUser("Manas");
    User *user3 = system.createUser("Rana");

    Question *ques1 = system.postQuestion(user1, "What is polymorphism in cpp");
    Question *ques2 = system.postQuestion(user2, "What is encapsulation");

    Answer *ans1 = system.postAnswer(user2, ques1, "Ability of an object to take various forms");

    Answer *ans2 = system.postAnswer(user1, ques2, "Confing similar data and methods in a class");

    Comment *comment1 = system.postComment(user3, ques1, "Valid question");
    Comment *comment2 = system.postComment(user3, ans2, "Confining ki spelling galat hai chutiye");

    system.printQuestionsAndAnswers();

    return 0;
}
