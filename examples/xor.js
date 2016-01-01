import neuralnet from '../../index'

console.log('////////////////// RUNNING XOR OPERATION EXAMPLE //////////////////');

let nTrainingData = 200;
let nTestData = 100;

let input = [
    [ 0, 0 ],
    [ 0, 1 ],
    [ 1, 0 ],
    [ 1, 1 ]
];

let results = [
    [ 0 ],
    [ 1 ],
    [ 1 ],
    [ 0 ]
];

var i;
var trainingData = [];
var testData = [];

for (i = 0; i < nTrainingData; i++) {
    let index = Math.floor((Math.random() * input.length));

    trainingData.push({
        input : input[index],
        output : results[index]
    });
}

for (i = 0; i < nTestData; i++) {
    let index = Math.floor((Math.random() * input.length));

    testData.push({
        input : input[index],
        output : results[index]
    });
}

let handle = neuralnet.create([2,4,1]);

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
            error += Math.abs(output[z] -  testData[i].output[z]);
            cnt++;
        }
    }

    error = error / cnt;

    console.log('Epoch ' + (epoch++) + ', Error: ' + error);

    if (error < 0.05)
        break;
}

var printResult = input => {
    neuralnet.setInputValues(handle, input);
    let result = neuralnet.getOutputValues(handle);

    console.log('Result for ' + input[0] + ' XOR ' + input[1] + ' is ' + result[0]);
};

for (i = 0; i < input.length; i++) {
    printResult(input[i]);
}

neuralnet.clear(handle);