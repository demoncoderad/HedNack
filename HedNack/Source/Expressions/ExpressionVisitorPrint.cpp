//
// Created by minley on 11/02/22.
//

#include "Expressions/ExpressionVisitorPrint.h"

/*
int main() {
    auto printer = HedNack::ExpressionVisitorPrint();
    auto lit1 = HedNack::Literal<std::string>(123);
    auto lit2 = HedNack::Literal<std::string>(321);
    auto binary1 = HedNack::Binary<std::string>(
            lit1,
            HedNack::Token(HedNack::TokenType::PLUS, "+", nullptr, 1),
            lit2
    );
    auto binary = HedNack::Binary<std::string>(
            binary1,
            HedNack::Token(HedNack::TokenType::PLUS, "+", nullptr, 1),
            lit2
    );
    auto print_string = printer.Print(binary);
    std::cout << print_string << std::endl;
}
*/

std::string HedNack::ExpressionVisitorPrint::VisitExpressionUnary(const Unary<std::string> *unary) {
    return "(" + unary->m_Oper.GetLexeme() + " " + unary->m_Right.Accept(this) + ")";
}

std::string HedNack::ExpressionVisitorPrint::VisitExpressionLiteral(const Literal<std::string> *literal) {
    size_t ind = literal->m_Literal.index();
    switch (ind) {
        case 0: return std::to_string(std::get<int>(literal->m_Literal)); break;
        case 1: return std::get<std::string>(literal->m_Literal); break;
        case 2: return std::to_string(std::get<double>(literal->m_Literal)); break;
        case 3: return "nil";
    }
}

std::string HedNack::ExpressionVisitorPrint::Print(HedNack::Expression<std::string>& expr) {
    return expr.Accept(this);
}

std::string HedNack::ExpressionVisitorPrint::VisitExpressionBinary(const HedNack::Binary<std::string> *binary) {
    auto left = "(" + binary->m_Left.Accept(this) + " " + binary->m_Oper.GetLexeme() + " " + binary->m_Right.Accept(this) + ")";

    return left;
}

std::string HedNack::ExpressionVisitorPrint::VisitExpressionGrouping(const HedNack::Grouping<std::string> *grouping) {
    return "(" + grouping->m_Middle.Accept(this) + ")";
}
