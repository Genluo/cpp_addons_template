#include <algorithm>
#include <cstddef>
#include <napi.h>
#include <iostream>
#include <vector>

namespace demo {

static int seq = 0;

// 定义一个工具函数，生成seq
Napi::Value GenSeq(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  return Napi::Number::New(env, ++seq);
}

Napi::Value getArray(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  std::vector<int> numbers = {1, 2, 3};
  Napi::Array jsArray = Napi::Array::New(env, numbers.size());

  for (size_t i = 0; i < numbers.size(); i++) {
    jsArray.Set(i, Napi::Number::New(env, numbers[i]));
  }

  return jsArray;
}
// 定义一个加法函数
Napi::Value Add(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  int a = info[0].As<Napi::Number>().Int32Value();
  int b = info[1].As<Napi::Number>().Int32Value();
  return Napi::Number::New(env, a + b);
}

// 定义构造函数
Napi::Value ZayleeConstructor(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);

  // 设置实例属性
  obj.Set("instanceField", Napi::Number::New(env, 2));
  obj.Set("add", Napi::Function::New(env, Add));

  return obj;
}

Napi::Object Initialize(Napi::Env env, Napi::Object exports) {
  // 创建构造函数
  Napi::Function constructor = Napi::Function::New(env, ZayleeConstructor, "Demo");

  // 设置函数对象本身的属性
  constructor.Set("funcField", Napi::Number::New(env, 3));

  // 设置原型属性
  Napi::Object prototype = constructor.Get("prototype").As<Napi::Object>();
  prototype.Set("protoField", Napi::Number::New(env, 1));

  // 导出函数
  exports.Set("Demo", constructor);

  // 导出工具函数
  exports.Set("genSeq", Napi::Function::New(env, GenSeq));
  exports.Set("getArray", Napi::Function::New(env, getArray));

  return exports;
}

NODE_API_MODULE(test, Initialize)

} // namespace demo
