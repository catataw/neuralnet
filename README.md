Neural network native module for Node.js
==========

This library was created as self learning project to get into creating Node.js native modules and neural networks.

The Node.js version used is 5.3.0.

Running the source
---------------

First run the install npm command to download and install all dependencies

```
npm install
```

Then you need node-gyp to create and compile C++ sources

```
npm install -g node-gyp
```

Then use the configure command to create appropriate project build files for your platform

```
node-gyp configure
```

After that you're ready to build. You can do that by using the node-gyp build command.

```
node-gyp build
```

After the build succeeds run the test command to verify that everything is OK.

```
gulp test
```

You can run embedded examples which are located in the examples folder

```
npm run example-xor
```

```
npm run example-sinus
```

Installation
---------------

```
npm install mkmarek.neuralnet
```

Usage
---------------

Import the the module

```javascript
var neuralnet = require('mkmarek.neuralnet');
```

or with ES6 modules syntax

```javascript
import neuralnet from 'mkmarek.neuralnet'
```

The neuralnet module exposes several functions you can use.

For creating a neural network use:

```javascript
let handle = neuralnet.create([2,4,1]);
```

Where the first parameter is the topology of the network. It's an array of numbers. Each member of that array represents
one layer and each value in that array represents amount of neurons in that layer. The first number then represents how
many neurons are in input layer and the last number represents how many neurons are in the output layer. Anything
in between are hidden layers.

The handle that is returned is a number used for referencing the created network.

For setting up input values use:

```javascript
neuralnet.setInputValues(handle, [1,0]);
```

Where the first parameter is a handle number of a given neural network and the second parameter is an array with
numbers that shall go into the input layer.

For getting the output values use:

```javascript
let values = neuralnet.getOutputValues(handle);
```

Where the first and only parameter is the network handle. The returned object is an array of numbers representing
the values in the output layer after a feed forward mechanism is invoked for all defined layers.

For invoking back propagation use:

```javascript
neuralnet.backPropagate(handle, [1]);
```

The first parameter is as usual the network handle and the second one is the desired output that we expect from our
neural network. Use the back propagation in combination with getOutputValues function to refresh the data each time
before the back propagation is called.

After you're done with you network call the clear function to cleanup all resources that your neural network allocated.

```javascript
neuralnet.clear(handle);
```

The one and only parameter is the neural network handle.