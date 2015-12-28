#include <node.h>
#include <vector>
#include <map>
#include <time.h>
#include "network.h"

namespace neuralnet {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::Exception;
using v8::Array;
using v8::Integer;
using v8::Number;
using v8::Handle;

/**
* Contains all active neural networks
*/
std::map<unsigned, Network*> m;

unsigned generateUniqueInt()
{
  if (m.size() == 0) {
    srand((unsigned)time(NULL));
  }

  unsigned num;
  do num = rand(); while(m.count( num ) == 1);
  return num;
}

/**
* Creates a network based on an input topology
* Returns a numeric handle used for any subsequent operations
*/
void create(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  //The number of arguments has to be precisely one argument which will be the topology
  if (args.Length() < 1) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
  }

  //the  first argument has to be an array
  if (!args[0]->IsArray()) {
        isolate->ThrowException(Exception::TypeError(
            v8::String::NewFromUtf8(isolate, "Wrong type of arguments")));
        return;
    }

  //extract topology from passed parameter
  std::vector<unsigned> topology;

  Local<Array> input = Local<Array>::Cast(args[0]);
  unsigned num_locations = input->Length();

  for (unsigned i = 0; i < num_locations; i++) {

    //All members of an array have to be integers
    if (!input->Get(i)->IsInt32()) {
        isolate->ThrowException(Exception::TypeError(
            v8::String::Concat(v8::String::NewFromUtf8(isolate, "Wrong type of member in array on index: ") ,
                    Integer::New(isolate, i)->ToString())
                    ));
        return;
    }

    Local<Integer> neuronCount = Local<Integer>::Cast(input->Get(i));

    topology.push_back(neuronCount->Int32Value());
  }

   int handle = generateUniqueInt();

  Network* net = new Network(topology);

  m.insert ( std::pair<unsigned,Network*>(handle,net) );

  v8::Handle<Integer> h =
    Integer::New(isolate, handle);

  args.GetReturnValue().Set(h);
}

/**
* Inputs the set of values into the network
*/
void setInputValues(const FunctionCallbackInfo<Value>& args) {

    Isolate* isolate = args.GetIsolate();

    try{

  //The number of arguments has to be precisely one argument which will be the topology
  if (args.Length() < 2) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
  }

  //the first arguments has to be a number
  if (!args[0]->IsInt32()) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong type of argument 0")));
      return;
  }

  //the second argument has to be an array
  if (!args[1]->IsArray()) {
        isolate->ThrowException(Exception::TypeError(
            v8::String::NewFromUtf8(isolate, "Wrong type of argument 1")));
        return;
    }

  //extract topology from passed parameter
  std::vector<double> inputValues;

  Local<Array> input = Local<Array>::Cast(args[1]);
  unsigned num_values = input->Length();

  for (unsigned i = 0; i < num_values; i++) {

    //All members of an array have to be integers
    if (!input->Get(i)->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
            v8::String::Concat(v8::String::NewFromUtf8(isolate, "Wrong type of member in array on index: ") ,
                    Integer::New(isolate, i)->ToString())
                    ));
        return;
    }

    Local<Number> neuronCount = Local<Number>::Cast(input->Get(i));

    inputValues.push_back(neuronCount->NumberValue());
  }

   int handle = args[0]->Int32Value();

   if (m.find( handle ) == m.end()) {
          isolate->ThrowException(Exception::TypeError(
              v8::String::NewFromUtf8(isolate, "Network with this handle doesn't exist")));
          return;
   }

  Network* net = m[handle];

  net->setInputValues(inputValues);
  }
  catch(const char* exception) {
    isolate->ThrowException(Exception::TypeError(
                  v8::String::NewFromUtf8(isolate, exception)));
  }
}

void getOutputValues(const FunctionCallbackInfo<Value>& args) {

    Isolate* isolate = args.GetIsolate();

    try{

  //The number of arguments has to be precisely one argument which will be the topology
  if (args.Length() < 1) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
  }

  //the first arguments has to be a number
  if (!args[0]->IsInt32()) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong type of argument 0")));
      return;
  }

   int handle = args[0]->Int32Value();

   if (m.find( handle ) == m.end()) {
          isolate->ThrowException(Exception::TypeError(
              v8::String::NewFromUtf8(isolate, "Network with this handle doesn't exist")));
          return;
   }

  Network* net = m[handle];

    std::vector<double> outputValues;
   net->getOutputValues(outputValues);

  // Create a new empty array.
    Handle<Array> array = Array::New(isolate, (unsigned)outputValues.size());

    // Fill out the values

    for (unsigned i = 0; i < outputValues.size(); i++) {
        array->Set(i, Number::New(isolate, outputValues[i]));
    }

    args.GetReturnValue().Set(array);
  }
  catch(const char* exception) {
    isolate->ThrowException(Exception::TypeError(
                  v8::String::NewFromUtf8(isolate, exception)));
  }
}

void getValuesFromLayer(const FunctionCallbackInfo<Value>& args) {

    Isolate* isolate = args.GetIsolate();

    try{

  //The number of arguments has to be precisely one argument which will be the topology
  if (args.Length() < 2) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
  }

  //the first arguments has to be a number
  if (!args[0]->IsInt32()) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong type of argument 0")));
      return;
  }

  //the second arguments has to be a number
    if (!args[1]->IsInt32()) {
        isolate->ThrowException(Exception::TypeError(
            v8::String::NewFromUtf8(isolate, "Wrong type of argument 1")));
        return;
    }

   int handle = args[0]->Int32Value();
   int layerNum = args[1]->Int32Value();

   if (m.find( handle ) == m.end()) {
          isolate->ThrowException(Exception::TypeError(
              v8::String::NewFromUtf8(isolate, "Network with this handle doesn't exist")));
          return;
   }

  Network* net = m[handle];

    std::vector<double> outputValues;
   net->getValuesFromLayer(outputValues, layerNum);

  // Create a new empty array.
    Handle<Array> array = Array::New(isolate, (unsigned)outputValues.size());

    // Fill out the values

    for (unsigned i = 0; i < outputValues.size(); i++) {
        array->Set(i, Number::New(isolate, outputValues[i]));
    }

    args.GetReturnValue().Set(array);
  }
  catch(const char* exception) {
    isolate->ThrowException(Exception::TypeError(
                  v8::String::NewFromUtf8(isolate, exception)));
  }
}

/**
* Clears the neural network and releases all reserved resources
*/
void clear(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  //The number of arguments has to be precisely one argument which will be the handle
    if (args.Length() < 1) {
        isolate->ThrowException(Exception::TypeError(
            v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    //the  first argument has to be an integer
    if (!args[0]->IsInt32()) {
          isolate->ThrowException(Exception::TypeError(
              v8::String::NewFromUtf8(isolate, "Wrong type of argument 0")));
          return;
     }

     int handle = args[0]->Int32Value();

    if (m.find( handle ) == m.end()) {
           isolate->ThrowException(Exception::TypeError(
               v8::String::NewFromUtf8(isolate, "Network with this handle doesn't exist")));
           return;
    }

    delete m[handle];
    m.erase (handle);
}

void backPropagate(const FunctionCallbackInfo<Value>& args) {

    Isolate* isolate = args.GetIsolate();

    try{

  //The number of arguments has to be precisely one argument which will be the topology
  if (args.Length() < 2) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
  }

  //the first arguments has to be a number
  if (!args[0]->IsInt32()) {
      isolate->ThrowException(Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Wrong type of argument 0")));
      return;
  }

  //the second argument has to be an array
  if (!args[1]->IsArray()) {
        isolate->ThrowException(Exception::TypeError(
            v8::String::NewFromUtf8(isolate, "Wrong type of argument 1")));
        return;
    }

  //extract topology from passed parameter
  std::vector<double> inputValues;

  Local<Array> input = Local<Array>::Cast(args[1]);
  unsigned num_values = input->Length();

  for (unsigned i = 0; i < num_values; i++) {

    //All members of an array have to be integers
    if (!input->Get(i)->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
            v8::String::Concat(v8::String::NewFromUtf8(isolate, "Wrong type of member in array on index: ") ,
                    Integer::New(isolate, i)->ToString())
                    ));
        return;
    }

    Local<Number> neuronCount = Local<Number>::Cast(input->Get(i));

    inputValues.push_back(neuronCount->NumberValue());
  }

   int handle = args[0]->Int32Value();

   if (m.find( handle ) == m.end()) {
          isolate->ThrowException(Exception::TypeError(
              v8::String::NewFromUtf8(isolate, "Network with this handle doesn't exist")));
          return;
   }

  Network* net = m[handle];

  net->backPropagation(inputValues);
  }
  catch(const char* exception) {
    isolate->ThrowException(Exception::TypeError(
                  v8::String::NewFromUtf8(isolate, exception)));
  }
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "create", create);
  NODE_SET_METHOD(exports, "clear", clear);
  NODE_SET_METHOD(exports, "setInputValues", setInputValues);
  NODE_SET_METHOD(exports, "getOutputValues", getOutputValues);
  NODE_SET_METHOD(exports, "getValuesFromLayer", getValuesFromLayer);
  NODE_SET_METHOD(exports, "backPropagate", backPropagate);
}

NODE_MODULE(addon, init)

}  // namespace demo