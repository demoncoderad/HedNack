//
// Created by minley on 11/02/22.
//

#ifndef HEDNACK_EXPRESSION_VISITOR_PRINT
#define HEDNACK_EXPRESSION_VISITOR_PRINT

#include "Expressions/Expression.h"
namespace HedNack {
    class ExpressionVisitorPrint : public ExpressionVisitor<std::string> {
    private:
        std::string VisitExpressionUnary(const Unary<std::string> *unary) override;
        std::string VisitExpressionBinary(const Binary<std::string> *binary) override;
        std::string VisitExpressionGrouping(const Grouping<std::string> *grouping) override;
        std::string VisitExpressionLiteral(const Literal<std::string> *literal) override;
    public:
        std::string Print(Expression<std::string> &expr);
    };
}

#endif