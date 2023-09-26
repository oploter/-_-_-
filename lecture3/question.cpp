#include "question.h"
#include <sstream>
#include <iostream>

void Question::setQuestionText(const std::string& q){
    questionText = q;
}
void Question::addAnswer(bool isRight, const std::string& ans){
    answers.push_back({isRight, ans});
}

Question Question::fromGift(const std::string& giftStr){
    Question question;
    auto questionTextEndInd = giftStr.find('{');
    question.setQuestionText(trimString(giftStr.substr(0, questionTextEndInd)));
    auto currAnswerStatusInd = giftStr.find_first_of("=~", questionTextEndInd + 1);
    while(currAnswerStatusInd != std::string::npos && giftStr[currAnswerStatusInd] != '}'){
        auto nextAnswerStatusInd = giftStr.find_first_of("=~}", currAnswerStatusInd + 1);
        question.addAnswer(
            giftStr[currAnswerStatusInd] == '=',
            trimString(giftStr.substr(currAnswerStatusInd + 1,
                            nextAnswerStatusInd - currAnswerStatusInd - 1)));
        currAnswerStatusInd = nextAnswerStatusInd;
    }
    return question;
}

Question Question::fromTxt(const std::string& txtStr){
    Question question;
    
    auto currAnswerStatusInd = txtStr.find_first_of("-+");
    question.setQuestionText(trimString(txtStr.substr(0, currAnswerStatusInd)));

    while(currAnswerStatusInd != std::string::npos){
        auto nextAnswerStatusInd = txtStr.find_first_of("-+", currAnswerStatusInd + 1);
        question.addAnswer(
            txtStr[currAnswerStatusInd] == '+',
            trimString(txtStr.substr(currAnswerStatusInd + 1,
                (nextAnswerStatusInd == std::string::npos ? txtStr.size(): nextAnswerStatusInd) - currAnswerStatusInd - 1)));
        currAnswerStatusInd = nextAnswerStatusInd; 
    }
    return question;
}

std::string Question::toGift() const {
    std::stringstream ss;
    ss << questionText << '{';
    for(const auto& [isTrue, ansStr] : answers){
        ss << (isTrue ? '=' : '~') << ansStr;
    }
    ss << "}\n";
    return ss.str();
}

std::string Question::toGiftPretty() const {
    std::stringstream ss;
    ss << questionText << " {\n";
    for(const auto& [isTrue, ansStr] : answers){
        ss << (isTrue ? '=' : '~')  << ' ' << ansStr << '\n';
    }
    ss << "}\n";
    return ss.str();
}

std::string Question::toTxt() const{
    std::stringstream ss;
    ss << questionText << ' ';
    for(const auto& [isTrue, ansStr] : answers){
        ss << (isTrue ? '+' : '-') << ansStr;
    }
    ss << "\n";
    return ss.str();
}

std::string Question::toTxtPretty() const{
    std::stringstream ss;
    ss << questionText << '\n';
    for(const auto& [isTrue, ansStr] : answers){
        ss << (isTrue ? '+' : '-') << ' ' << ansStr << '\n';
    }
    return ss.str();
}


std::string Question::trimString(const std::string& s){
    std::string ans;
    size_t start = s.find_first_not_of("\n\r\t\f\v");
    ans = (start == std::string::npos) ? "" : s.substr(start);
    size_t end = ans.find_last_not_of("\n\r\t\f\v");
    ans = (end == std::string::npos) ? "" : ans.substr(0, end + 1);
    return ans;
}