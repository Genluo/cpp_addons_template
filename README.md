# Node.js C++ Addons Template

这是一个使用 N-API 和 node-addon-api 的 Node.js C++ 扩展模板项目，提供了从 C++ 代码创建 Node.js 模块的完整示例。

## 项目概述

本项目演示了如何：

- 使用 N-API 创建 Node.js 原生扩展
- 在 C++ 中定义函数并导出到 JavaScript
- 创建构造函数和对象实例
- 处理不同类型的数据（数字、数组等）
- 使用 cmake-js 进行构建管理

## 技术栈

- **C++ 17**：主要编程语言
- **N-API/node-addon-api**：Node.js 原生扩展 API
- **CMake**：构建系统
- **cmake-js**：Node.js CMake 构建工具

## 项目结构

```
.
├── CMakeLists.txt      # CMake 构建配置
├── package.json        # Node.js 项目配置
├── src/
│   ├── test.cpp        # C++ 源码实现
│   └── test.hpp        # C++ 头文件（当前为空）
├── test.js             # JavaScript 测试文件
└── README.md           # 项目说明文档
```

## 功能特性

### 1. 基础函数导出

- `genSeq()`: 生成递增序列号
- `getArray()`: 返回预定义数组

### 2. 构造函数和对象

- `Demo` 构造函数：创建具有实例方法的对象
- 实例方法 `add(a, b)`: 执行两数相加
- 原型属性和实例属性支持

### 3. 类型处理

- 数字类型处理和转换
- 数组创建和操作
- 错误处理和参数验证

## 快速开始

### 前置要求

- Node.js (建议版本 >= 16)
- CMake (>= 3.15)
- C++ 编译器 (支持 C++17)
- vs code + CMake插件

### 安装依赖

```bash
npm install
```

这会自动触发 CMake 构建过程，编译 C++ 代码为 Node.js 模块。

### 运行测试

```bash
node test.js
```

预期输出：

```
demo对象: Demo { instanceField: 2, add: [Function (anonymous)] }

原型属性: 1

执行add方法: 3

执行seq方法: 1 2

执行getArray方法: [ 1, 2, 3 ]
```

## API 参考

### genSeq()

生成递增的序列号。

**返回值**: `number` - 当前序列号

```javascript
const { genSeq } = require('./build/Release/genluo.node');
console.log(genSeq()); // 1
console.log(genSeq()); // 2
```

### getArray()

返回预定义的整数数组。

**返回值**: `Array<number>` - [1, 2, 3]

```javascript
const { getArray } = require('./build/Release/genluo.node');
console.log(getArray()); // [1, 2, 3]
```

### Demo 构造函数

创建 Demo 对象实例。

**属性**:

- `instanceField`: number - 实例属性，值为 2
- `protoField`: number - 原型属性，值为 1

**方法**:

- `add(a, b)`: 两数相加

```javascript
const { Demo } = require('./build/Release/genluo.node');
const demo = new Demo();
console.log(demo.instanceField); // 2
console.log(demo.protoField);    // 1
console.log(demo.add(5, 3));     // 8
```

## 开发说明

### 修改 C++ 代码

1. 编辑 `src/test.cpp` 文件
2. 重新运行 `npm install` 进行编译
3. 测试修改后的功能

### CMake 配置

`CMakeLists.txt` 包含了：

- C++17 标准设置
- N-API 版本配置
- node-addon-api 头文件包含
- 平台特定的链接配置

### 构建产物

编译后的模块位于：`./build/Release/genluo.node`

## 扩展开发

基于此模板，你可以：

1. **添加更多 C++ 函数**：在 `Initialize` 函数中注册新的导出函数
2. **创建复杂数据结构**：使用 Napi::Object 创建复杂的 JavaScript 对象
3. **异步操作**：集成 `Napi::AsyncWorker` 实现异步操作
4. **类封装**：使用 `Napi::ObjectWrap` 创建 JavaScript 类

## 常见问题

### 编译失败

- 确保安装了 C++ 编译器
- 检查 Node.js 和 CMake 版本
- 确认 node-addon-api 依赖安装正确

### 模块加载失败

- 检查 build/Release 目录下是否存在 .node 文件
- 确认文件路径是否正确

## 许可证

ISC

## 贡献

欢迎提交 Issue 和 Pull Request 来改进这个模板项目。
