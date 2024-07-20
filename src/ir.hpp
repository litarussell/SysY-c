#pragma once

#include <iostream>

/**
 * Program
 *    全局变量列表:
 *        Value1
 *        Value2
 *    函数列表:
 *        Function1
 *            基本块列表:
 *                BasicBlock1
 *                    指令列表:
 *                        Value1
 *                        Value2
 *                        ...
 *                BasicBlock2
 *                ...
 *        Function2
 *        ...
 */

/**
 * 1, Function, BasicBlock, Value 的名字必须以 @ 或者 % 开头, 前者表示这是一个 “具名符号”, 后者表示这是一个 “临时符号”.
 */

// 所有 AST 的基类
class BaseIR {
public:
  virtual ~BaseIR() = default;
  virtual void GenIR() const = 0;
};

class ProgramIR : public BaseIR {
public:
  // 用智能指针管理对象
  std::unique_ptr<BaseIR> global_variable_list;
  std::unique_ptr<BaseIR> func_list;

  void GenIR() const override {
    func_def->GenIR();
  }
};

class GlobalVariableListIR : public BaseIR {
public:
  // 列表长度
  int len;
  // 用智能指针管理对象
  unique_ptr<BaseIR> list;

  void GenIR() const override {
    func_def->GenIR();
  }
};