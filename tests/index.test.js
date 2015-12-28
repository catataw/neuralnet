import neuralnet from '../../build/Release/neuralnet'
import chai from 'chai'

chai.should();

describe('Neuralnet', function() {
    describe('#create()', function () {

        it('Should throw an error when unsufficient number of arguments is passed', function () {

            var factory = () => { neuralnet.create(); };

            factory.should.Throw('Wrong number of arguments');
        });

        it('Should throw an error when we pass a non integer member in an array', function () {

            var factory = () => { neuralnet.create([1,2,3, 'fsdfsdf']); };

            factory.should.Throw('Wrong type of member in array on index: 3');
        });

        it('Should return a handle number pointing to a network', function () {

            //Creating a neural network with three layers
            //The first (input) layer will contain 3 neurons
            //The second (hidden) layer will contain 3 neurons
            //The third (output) layer will contain 2 neurons
            let handle = neuralnet.create([3,4,2]);

            handle.should.not.equal(null);
            handle.should.be.a('Number');
        });
    });

    describe('#clear()', function () {

        it('Should throw an error when unsufficient number of arguments is passed', function () {

            var factory = () => { neuralnet.clear(); };

            factory.should.Throw('Wrong number of arguments');
        });

        it('Should throw an error when we pass a non integer member in an array', function () {

            var factory = () => { neuralnet.clear('fdsfsd'); };

            factory.should.Throw('Wrong type of argument 0');
        });

        it('Should throw an error when given handle doesnt exist', function () {

            var factory = () => { neuralnet.clear(123); };

            factory.should.Throw('Network with this handle doesn\'t exist');
        });

        it('Should successfully clear the neural network using a handle', function () {

            //Creating a neural network with three layers
            //The first (input) layer will contain 3 neurons
            //The second (hidden) layer will contain 3 neurons
            //The third (output) layer will contain 2 neurons
            let handle = neuralnet.create([3,4,2]);

            var foo = () => neuralnet.clear(handle);

            foo.should.not.Throw(Error);
        });
    });

    describe('#setInputValues()', function () {

        it('Should throw an error when unsufficient number of arguments is passed', function () {

            let handle = neuralnet.create([3,4,2]);

            var factory = () => { neuralnet.setInputValues(); };
            var factory2 = () => { neuralnet.setInputValues(handle); };

            factory.should.Throw('Wrong number of arguments');
            factory2.should.Throw('Wrong number of arguments');
        });

        it('Should throw an error when we pass a non numeric member in an array', function () {

            let handle = neuralnet.create([3,4,2]);

            var factory = () => { neuralnet.setInputValues(handle, [1,2.5,3, 'fsdfsdf']); };

            factory.should.Throw('Wrong type of member in array on index: 3');
        });


        it('Should successfully pass the input values into the input layer', function () {

            //Creating a neural network with three layers
            //The first (input) layer will contain 3 neurons
            //The second (hidden) layer will contain 3 neurons
            //The third (output) layer will contain 2 neurons
            let handle = neuralnet.create([3,4,2]);

            var factory = () => { neuralnet.setInputValues(handle, [1,2.6,3]); };

            factory.should.not.Throw(Error);

            neuralnet.clear(handle);
        });
    });

    describe('#getOutputValues()', function () {

        it('Should throw an error when unsufficient number of arguments is passed', function () {

            let handle = neuralnet.create([3,4,2]);

            var factory = () => { neuralnet.getOutputValues(); };

            factory.should.Throw('Wrong number of arguments');
        });

        it('Should throw an error when we pass a non numeric parameter as a handle', function () {

            let handle = neuralnet.create([3,4,2]);

            var factory = () => { neuralnet.getOutputValues('fdfds'); };

            factory.should.Throw('Wrong type of argument 0');
        });


        it('Should successfully retrieve values from the output neurons', function () {

            //Creating a neural network with three layers
            //The first (input) layer will contain 3 neurons
            //The second (hidden) layer will contain 3 neurons
            //The third (output) layer will contain 2 neurons
            let handle = neuralnet.create([3,4,4]);

            neuralnet.setInputValues(handle, [1,2.6,3]);

            var values = [];
            var factory = () => { values = neuralnet.getOutputValues(handle); };

            factory.should.not.Throw(Error);

            values.length.should.equal(4);

            //console.log(neuralnet.getValuesFromLayer(handle, 0));
            //console.log(neuralnet.getValuesFromLayer(handle, 1));
            //console.log(neuralnet.getValuesFromLayer(handle, 2));

            values[0].should.not.equal(null);
            values[1].should.not.equal(null);
            values[2].should.not.equal(null);
            values[3].should.not.equal(null);

            neuralnet.clear(handle);
        });
    });

    describe('#backPropagate()', function () {

        it('Should successfully retrieve values from the output neurons', function () {

            //Creating a neural network with three layers
            //The first (input) layer will contain 3 neurons
            //The second (hidden) layer will contain 3 neurons
            //The third (output) layer will contain 2 neurons
            let handle = neuralnet.create([3,4,3]);

            neuralnet.setInputValues(handle, [1,2.6,3]);

            var values = neuralnet.getOutputValues(handle);
            console.log(values);
            var factory = () => {
                neuralnet.getOutputValues(handle);
                neuralnet.backPropagate(handle, [0.1, 0.1, 0.7]);
            };

            for(var i = 0;i < 5000; i++) {
                factory.should.not.Throw(Error);
            }

            values = neuralnet.getOutputValues(handle);
            console.log(values);

            neuralnet.clear(handle);
        });
    });
});