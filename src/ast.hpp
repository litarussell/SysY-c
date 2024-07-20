#pragma once

#include <iostream>

// 所有 AST 的基类
class BaseAST {
public:
  virtual ~BaseAST() = default;
  virtual void Dump() const = 0;
  virtual void GenIR() const = 0;
};

// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
public:
  // 用智能指针管理对象
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override {
    std::cout << "CompUnitAST { ";

    func_def->Dump();

    std::cout << " }";
  }

  void GenIR() const override {
    func_def->GenIR();
    std::cout << std::endl;
  }
};

// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;

  void Dump() const override {
    std::cout << "FuncDefAST { ";

    func_type->Dump();
    std::cout << ", " << ident << ", ";
    block->Dump();

    std::cout << " }";
  }

  void GenIR() const override {
    std::cout << "fun @" << ident << "(): ";
    func_type->GenIR();
    std::cout << " {\n";
    block->GenIR();
    std::cout << "}\n";
  }
};

// FuncType
class FuncTypeAST : public BaseAST {
public:
  std::string ident;

  void Dump() const override {
    std::cout << "FuncTypeAST { ";

    std::cout << "Int";

    std::cout << " }";
  }

  void GenIR() const override {
    std::cout << "i32";
  }
};

// Block
class BlockAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> stmt;

  void Dump() const override {
    std::cout << "BlockAST { ";

    stmt->Dump();

    std::cout << " }";
  }

  void GenIR() const override {
    std::cout << "@entry: \n";
    stmt->GenIR();
  }
};

// Stmt
class StmtAST : public BaseAST {
public:
  int value;

  void Dump() const override {
    std::cout << "StmtAST { " << value << " }";
  }

  void GenIR() const override {
    std::cout << " ret " << value << "\n";
  }
};

// Number
class NumberAST : public BaseAST {
public:
  int value;

  void Dump() const override {
    std::cout << 0;
  }
};