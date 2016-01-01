import neuralnet from '../../index'

console.log('////////////////// RUNNING SINUS APPROXIMATION EXAMPLE //////////////////');

let nTrainingData = 200;
let nTestData = 10;

var i;
var trainingData = [];
var testData = [];

for (i = 0; i < nTrainingData; i++) {
    let index = (Math.PI / nTrainingData) * i;

    trainingData.push({
        input: [index + 0.01],
        output: [Math.sin(index)]
    });
}

for (i = 0; i < nTestData; i++) {
    let index = (Math.PI / nTestData) * i;

    testData.push({
        input: [index],
        output: [Math.sin(index)]
    });
}

let handle = neuralnet.create([1, 10, 1]);

var epoch = 0;
while (true) {
    for (i = 0; i < trainingData.length; i++) {

        neuralnet.setInputValues(handle, trainingData[i].input);

        neuralnet.getOutputValues(handle);

        neuralnet.backPropagate(handle, trainingData[i].output);
    }

    let error = 0.0;
    let cnt = 0;

    for (i = 0; i < testData.length; i++) {

        neuralnet.setInputValues(handle, testData[i].input);

        var output = neuralnet.getOutputValues(handle);

        for (var z = 0; z < output.length; z++) {
            error += Math.abs(output[z] - testData[i].output[z]);
            cnt++;
        }
    }

    error = error / cnt;

    console.log('Epoch ' + (epoch++) + ', Error: ' + error);

    if (error < 0.04)
        break;
}


neuralnet.setInputValues(handle, [Math.PI / 2]);
var r = neuralnet.getOutputValues(handle, [Math.PI / 2]);
console.log('Result for sin(PI / 2) is ' + r[0]);

neuralnet.setInputValues(handle, [Math.PI]);
var r1 = neuralnet.getOutputValues(handle, [Math.PI]);
console.log('Result for sin(PI) is ' + r1[0]);

neuralnet.setInputValues(handle, [0]);
var r2 = neuralnet.getOutputValues(handle, [0]);
console.log('Result for sin(0) is ' + r2[0]);

neuralnet.setInputValues(handle, [0.5]);
var r2 = neuralnet.getOutputValues(handle, [0]);
console.log('Result for sin(0.5) is ' + r2[0]);

neuralnet.clear(handle);