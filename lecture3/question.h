#ifndef QUESTION_H
#define QUESTION_H
#include <string>
#include <vector>
#include <utility>

class Question{
    std::string questionText;
    std::vector<std::pair<bool, std::string>> answers;
    static std::string trimString(const std::string& s);
public:
    Question(){}
    void setQuestionText(const std::string& q);
    void addAnswer(bool isRight, const std::string& ans);
    static Question fromGift(const std::string& giftStr);
    static Question fromTxt(const std::string& txtStr);
    std::string toGift() const;
    std::string toGiftPretty() const;
    std::string toTxt() const;
    std::string toTxtPretty() const;
};

#endif