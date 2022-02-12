//
// Created by minley on 11/02/22.
//

#ifndef HEDNACK_EXPRESSION_H
#define HEDNACK_EXPRESSION_H

#include "Token.h"

namespace HedNack {

    template<typename T>
    class Expression;
    template<typename T>
    class ExpressionVisitor;
    template<typename T>
    class Unary;
    template<typename T>
    class Binary;
    template<typename T>
    class Grouping;
    template<typename T>
    class Literal;

    template<typename T>
    class ExpressionVisitor {
    private:
    public:
        virtual T VisitExpressionUnary(const Unary<T> *unary)          = 0;

        virtual T VisitExpressionBinary(const Binary<T> *binary)       = 0;

        virtual T VisitExpressionGrouping(const Grouping<T> *grouping) = 0;

        virtual T VisitExpressionLiteral(const Literal<T> *literal)    = 0;
    };


    template<typename T>
    class Expression {
    private:
    public:
        virtual T Accept(ExpressionVisitor<T>*) const {}
        virtual void PrintName() const {
            std::cout << "Expression" << std::endl;
        }
    };

    template<typename T>
    class Unary : public Expression<T> {
    private:
    public:
        const Token m_Oper;
        const Expression<T>& m_Right;

        Unary(Token Oper, Expression<T>& right)
            : m_Oper(Oper), m_Right(right) {}

        T Accept(ExpressionVisitor<T>* Visitor) const override {
            return Visitor->VisitExpressionUnary(this);
        }
        virtual void PrintName() const override {
            std::cout << "Unary" << std::endl;
        }
    };

    template<typename T>
    class Binary : public Expression<T> {
    private:
    public:
        const Expression<T>& m_Left;
        const Token m_Oper;
        const Expression<T>& m_Right;

        Binary(Expression<T>& left, Token Oper, Expression<T>& right)
        : m_Left(left), m_Oper(Oper), m_Right(right) {
        }

        virtual T Accept(ExpressionVisitor<T>* Visitor) const override {
            return Visitor->VisitExpressionBinary(this);
        }
        virtual void PrintName() const {
            std::cout << "Binary" << std::endl;
        }
    };

    template<typename T>
    class Grouping : public Expression<T> {
    private:
    public:
        const Expression<T>& m_Middle;

        Grouping(Expression<T>& middle)
        : m_Middle(middle){}

        T Accept(ExpressionVisitor<T>* Visitor) const override {
            return Visitor->VisitExpressionGrouping(this);
        }
        virtual void PrintName() const {
            std::cout << "Grouping" << std::endl;
        }
    };

    template<typename T>
    class Literal : public Expression<T> {
    private:
    public:
        const literalval m_Literal;

        Literal(literalval Literal)
        : m_Literal(Literal){}

        T Accept(ExpressionVisitor<T>* Visitor) const override {
            return Visitor->VisitExpressionLiteral(this);
        }
        virtual void PrintName() const {
            std::cout << "Literal" << std::endl;
        }
    };
}

#endif //HEDNACK_EXPRESSION_H
