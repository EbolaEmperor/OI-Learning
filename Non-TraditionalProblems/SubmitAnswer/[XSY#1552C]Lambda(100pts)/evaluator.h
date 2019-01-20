#pragma once

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#ifndef ERR
#define ERR cerr
#endif

constexpr char SPACE = ' ';
constexpr char TAB = '\t';

constexpr char ASSIGN = '=';
constexpr char PRINT = '?';

constexpr char SLASH = '\\';
constexpr char DOT = '.';
constexpr char LPAREN = '(';
constexpr char RPAREN = ')';

inline vector<string> tokenize(string s, ostream &err = ERR) {
    vector<string> parts;

    string::iterator it = s.begin();
    while (true) {
        while (it != s.end() && (*it == SPACE || *it == TAB)) ++it;
        if (it == s.end()) break;

        if (*it == ASSIGN || *it == PRINT || *it == SLASH || *it == DOT ||
            *it == LPAREN || *it == RPAREN) {
            parts.emplace_back(1, *it++);
        } else if (isalpha(*it)) {
            string token;
            while (isalpha(*it)) token.push_back(*it++);
            parts.push_back(std::move(token));
        } else {
            err << "Unexpected character '" << *it << "\'\n";
            return {};
        }
    }

    return parts;
}

typedef vector<string>::iterator Iter;

enum NodeType { NAME, FUNC, APPLY, OBJ };

struct Node;

typedef shared_ptr<Node> PNode;

struct Node {
    string name;
    NodeType type, obj_type;
    PNode left, right;
};

inline bool is_object_terminal(PNode obj) { return !obj->left; }

inline PNode obj() {
    static int counter = 0;
    PNode result(new Node);
    result->type = OBJ;
    result->name = to_string(counter++);
    return result;
}

inline PNode obj(PNode left, PNode right) {
    PNode result(new Node);
    result->type = OBJ;
    result->left = left;
    result->right = right;
    return result;
}

inline void print_node(PNode node, ostream &err = ERR, ostream &out = cout) {
    if (node->type == NAME) {
        out << node->name;
    } else if (node->type == FUNC) {
        out << LPAREN << SLASH << node->name << ' ' << DOT << ' ';
        print_node(node->right, err, out);
        out << RPAREN;
    } else if (node->type == APPLY) {
        out << LPAREN;
        print_node(node->left, err, out);
        out << ' ';
        print_node(node->right, err, out);
        out << RPAREN;
    } else if (node->type == OBJ) {
        if (is_object_terminal(node)) {
            out << node->name;
        } else {
            out << '[';
            print_node(node->left, err, out);
            out << ' ';
            print_node(node->right, err, out);
            out << ']';
        }
    } else {
        err << "Unknown node\n";
    }
}

inline PNode make_name(string name) {
    PNode result(new Node);
    result->type = NAME;
    result->name = std::move(name);
    return result;
}

inline PNode make_func(string name, PNode right) {
    PNode result(new Node);
    result->type = FUNC;
    result->name = std::move(name);
    result->right = right;
    return result;
}

inline PNode make_apply(PNode left, PNode right) {
    PNode result(new Node);
    result->type = APPLY;
    result->left = left;
    result->right = right;
    return result;
}

inline PNode read_name(Iter &begin, Iter end, ostream &err) {
    if (begin == end) {
        err << "Expect a name, found nothing\n";
        return nullptr;
    } else if (!isalpha(begin->front())) {
        err << "Expect a name, found " << *begin << '\n';
        return nullptr;
    }
    return make_name(*begin++);
}

PNode read_expr(Iter &begin, Iter end, ostream &err);

inline PNode read_term(Iter &begin, Iter end, ostream &err) {
    if (begin == end) {
        err << "Expect a term, found nothing\n";
        return nullptr;
    }
    if (begin->front() == LPAREN) {
        auto expr = read_expr(++begin, end, err);
        if (begin == end) {
            err << "Expect ), found nothing\n";
            return nullptr;
        } else if (begin->front() != RPAREN) {
            err << "Expect ), found " << *begin << '\n';
            return nullptr;
        }
        ++begin;
        return expr;
    } else if (isalpha(begin->front())) {
        return read_name(begin, end, err);
    } else {
        err << "Expect a term, found " << *begin << '\n';
        return nullptr;
    }
}

inline PNode read_expr(Iter &begin, Iter end, ostream &err) {
    if (begin == end) {
        err << "Expect an expression, found nothing\n";
        return nullptr;
    }
    if (begin->front() == SLASH) {
        ++begin;
        if (begin == end) {
            err << "Expect a name, found nothing\n";
            return nullptr;
        } else if (!isalpha(begin->front())) {
            err << "Expect a name, found " << *begin << '\n';
            return nullptr;
        }
        auto &param = *begin++;
        if (begin == end) {
            err << "Expected . , found nothing\n";
            return nullptr;
        } else if (begin->front() != DOT) {
            err << "Expected . , found " << *begin << '\n';
            return nullptr;
        }
        auto body = read_expr(++begin, end, err);
        if (!body) return nullptr;
        return make_func(std::move(param), body);
    }
    auto result = read_term(begin, end, err);
    if (!result) return nullptr;
    while (begin != end && begin->front() != RPAREN) {
        if (begin->front() == SLASH) {
            auto func = read_expr(begin, end, err);
            if (!func) return nullptr;
            return make_apply(result, func);
            break;
        }
        auto term = read_term(begin, end, err);
        if (!term) return nullptr;
        result = make_apply(result, term);
    }
    return result;
}

inline PNode parse(Iter begin, Iter end, ostream &err = ERR) {
    return read_expr(begin, end, err);
}

typedef unordered_map<string, PNode> Env;

Env global_env;

inline void set_name(string name, PNode value) {
    global_env.insert(make_pair(std::move(name), value));
}

inline void unset_name(string name) { global_env.erase(std::move(name)); }

inline PNode get_name(string name) {
    auto it = global_env.find(std::move(name));
    if (it == global_env.end()) return nullptr;
    return it->second;
}

inline PNode check(PNode expr, ostream &err = ERR) {
    static unordered_set<string> covered;
    if (expr->type == NAME) {
        if (covered.count(expr->name)) return expr;
        auto it = global_env.find(expr->name);
        if (it != global_env.end()) return it->second;

        err << "Unknown name " << expr->name << '\n';
        return nullptr;
    } else if (expr->type == FUNC) {
        bool already_covered = covered.count(expr->name);
        if (!already_covered) {
            covered.insert(expr->name);
        }
        auto check_right = check(expr->right, err);
        if (!check_right) return nullptr;
        auto result = make_func(expr->name, check_right);
        if (!already_covered) {
            covered.erase(expr->name);
        }
        return result;
    } else if (expr->type == APPLY) {
        auto check_left = check(expr->left, err);
        if (!check_left) return nullptr;
        auto check_right = check(expr->right, err);
        if (!check_right) return nullptr;
        return make_apply(check_left, check_right);
    } else {
        err << "Unknown node type\n";
        return nullptr;
    }
}

inline PNode apply_func_impl(PNode func, PNode arg, PNode expr) {
    if (expr->type == NAME) {
        if (expr->name == func->name) return arg;
        return expr;
    } else if (expr->type == FUNC) {
        if (expr->name == func->name) return expr;
        return make_func(expr->name, apply_func_impl(func, arg, expr->right));
    } else if (expr->type == APPLY) {
        return make_apply(apply_func_impl(func, arg, expr->left),
                          apply_func_impl(func, arg, expr->right));
    } else if (expr->type == OBJ) {
        return expr;
    } else {
        return nullptr;
    }
}

inline PNode apply_func(PNode func, PNode arg) {
    return apply_func_impl(func, arg, func->right);
}

PNode super_eval(PNode expr);

inline pair<bool, PNode> evaluate(PNode expr) {
    if (expr->type == NAME) {
        return make_pair(false, expr);
    } else if (expr->type == FUNC) {
        return make_pair(false, expr);
        // auto pr = evaluate(expr->right);
        // if (!pr.second) return make_pair(false, nullptr);
        // if (!pr.first) return make_pair(false, expr);
        // return make_pair(true, make_func(expr->name, pr.second));
    } else if (expr->type == APPLY) {
        if (expr->left->type == APPLY) {
            auto pr = evaluate(expr->left);
            if (!pr.second) return make_pair(false, nullptr);
            if (!pr.first) return make_pair(false, expr);
            return make_pair(true, make_apply(pr.second, expr->right));
        } else if (expr->left->type == FUNC) {
            return make_pair(true, apply_func(expr->left, expr->right));
        } else if (expr->left->type == OBJ) {
            auto arg = super_eval(expr->right);
            if (!arg) return make_pair(false, nullptr);
            if (arg->type != OBJ) return make_pair(false, nullptr);
            return make_pair(true, obj(expr->left, arg));
        } else if (expr->left->type == NAME) {
            return make_pair(false, expr);
            // auto pr = evaluate(expr->right);
            // if (!pr.second) return make_pair(false, nullptr);
            // if (!pr.first) return make_pair(false, expr);
            // return make_pair(true, make_apply(expr->left, pr.second));
        } else {
            return make_pair(false, nullptr);
        }
    } else if (expr->type == OBJ) {
        return make_pair(false, expr);
    } else {
        return make_pair(false, nullptr);
    }
}

inline PNode super_eval(PNode expr) {
    auto pr = evaluate(expr);
    while (pr.first && pr.second) {
        pr = evaluate(pr.second);
    }
    return pr.second;
}

#endif /* EVALUATOR_H_ */
