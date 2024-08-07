#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ast.hpp"

// 声明 lexer 的输入, 以及 parser 函数
// 为什么不引用 sysy.tab.hpp 呢? 因为首先里面没有 yyin 的定义
// 其次, 因为这个文件不是我们自己写的, 而是被 Bison 生成出来的
// 你的代码编辑器/IDE 很可能找不到这个文件, 然后会给你报错 (虽然编译不会出错)
// 看起来会很烦人, 于是干脆采用这种看起来 dirty 但实际很有效的手段
extern FILE *yyin;
extern int yyparse(std::unique_ptr<BaseAST> &ast);

int main(int argc, const char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler 模式 输入文件 -o 输出文件
  assert(argc == 5);
  auto mode = argv[1];
  auto input = argv[2];
  auto output = argv[4];

  // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
  yyin = fopen(input, "r");
  assert(yyin);

  // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
  std::unique_ptr<BaseAST> ast;
  auto ret = yyparse(ast);
  assert(!ret);

  // dump AST
  ast->GenIR();

  if (strcmp(mode, "-koopa")==0){
    // 备份标准输出流缓冲区
    std::streambuf* stream_buffer_cout = std::cout.rdbuf();

    // 将标准输出流缓冲区重定向到 oss
    std::ostringstream oss;
    std::cout.rdbuf(oss.rdbuf());

    ast->GenIR();

    // 恢复标准输出流缓冲区
    std::cout.rdbuf(stream_buffer_cout);

    // 从 oss 获取字符串
    std::string ir_str = oss.str();
    const char* ir_cstr = ir_str.c_str();

    FILE* output_file = fopen(output, "w");
    fwrite(ir_cstr, sizeof(char), ir_str.size(), output_file);
    fclose(output_file);
    // fstream file;
    // file.open(output, ios::out);
    // // 获取文件的streambuffer
    // streambuf* stream_buffer_file = file.rdbuf();
    // // 将 cout 重定向到文件
	  // cout.rdbuf(stream_buffer_file);

    // ast->GenIR();
    // cout << endl;

    // // 将 cout 重定向回屏幕
    // cout.rdbuf(stream_buffer_cout);

    // file.close();
  }

  return 0;
}
