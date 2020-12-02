#include "questioncontainer.h"
#include "question.h"

#define ASSERT_INIT() if(!_init) throw std::runtime_error("Attempted to access unitialized QuestionContainer");

QuestionContainer::QuestionContainer() {
    _init = false;
}

template<class T>
QuestionContainer::QuestionContainer(T question) {
    init(question);
}

template<>
void QuestionContainer::init(TrueFalseQuestion question)
{
    type = true_false;
    container = question;
    _init = true;
}

template<>
void QuestionContainer::init(MultiChoiceQuestion question)
{
    type = multi_choice;
    container = question;
    _init = true;
}

template<>
void QuestionContainer::init(ShortAnswerQuestion question)
{
    type = short_answer;
    container = question;
    _init = true;
}

QuestionType QuestionContainer::getType() {
    ASSERT_INIT();
    return type;
}

QuestionContainer::operator TrueFalseQuestion() const {
    ASSERT_INIT();
    return std::get<TrueFalseQuestion>(container);
}

QuestionContainer::operator MultiChoiceQuestion() const {
    ASSERT_INIT();
    return std::get<MultiChoiceQuestion>(container);
}

QuestionContainer::operator ShortAnswerQuestion() const {
    ASSERT_INIT();
    return std::get<ShortAnswerQuestion>(container);
}

