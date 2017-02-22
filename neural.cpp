#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cstdlib>

typedef struct node{
	int num_inputs;
	float *weights;
	float *inputs;
	float *errors;
	float output;
} node;

typedef struct layer{
	int num_nodes;
	node *chr;
} layer;

using namespace std;

class neural{
	private:
		int num_inputs;
		int num_outputs;
		int num_layers;
		int num_weights;
		int num_hid_nodes;
		float leaning_rate;
		layer *layers;
		float *weights;
		
	public:
        neural();
        neural(int in, int out, int num, int hn, float lrate);
        void init();
        void put_weights(float *weights); 
};

neural :: neural(){
}

neural :: neural(int in, int out, int num, int hn, float lrate){
    num_inputs = in;
	num_outputs = out;
	num_layers = num;
	num_hid_nodes = hn;
	num_weights = 0;
	leaning_rate = lrate;
    
    layers = (layer *)malloc(sizeof(layer) * num); //Memory Allocation for layers struct
	layers[0].num_nodes = in; //num_modes takes num_input value
	layers[0].chr = (node *)malloc(sizeof(node) * in); //chr node memory allocation
    
    for(int i = 0; i < in; i++){
		(layers[0].chr[i]).num_inputs = 1; //put 1 as num_inputs of each chr of lay0
		num_weights += 1; //increment num_weight by 1
		(layers[0].chr[i]).weights = (float *)malloc(sizeof(float) * (1)); //Memory Allocation for weights
		(layers[0].chr[i]).inputs = (float *)malloc(sizeof(float) * (1)); //Memory Allocation for inputs
		(layers[0].chr[i]).errors = (float *)malloc(sizeof(float) * (1)); //Memory Allocation for errors
		for(int e = 0; e < 1; e++) (layers[0].chr[i]).errors[e] = 0.0; // set 0.0 error initially
	}

    for(int i = 1; i < num - 1; i++){
		layers[i].chr = (node *)malloc(sizeof(node) * hn); //Memory Allocation for chr node of lay_i with hn value
		layers[i].num_nodes = hn; //Set hn to num_nodes for each layer
		int nd = layers[i - 1].num_nodes; // set nd as previous layers num_nodes value
		for(int j = 0; j < hn; j++){
			(layers[i].chr[j]).num_inputs = nd + 1; //set num_inputs of node chr_j of lay_i to nd+1
			num_weights += nd + 1; //Increase num_weight with nd + 1
			(layers[i].chr[j]).weights = (float *)malloc(sizeof(float) * (nd + 1));
			(layers[i].chr[j]).inputs = (float *)malloc(sizeof(float) * (nd + 1));
			(layers[i].chr[j]).errors = (float *)malloc(sizeof(float) * (nd + 1));
            /*
                Memory allocation of chr_j of lay_i to nd+1 vlaue for weights,inputs and errors
            */
			for(int e = 0; e < nd + 1; e++) (layers[i].chr[j]).errors[e] = 0.0;
		}
	}

	int nd = layers[num - 2].num_nodes; //set nd to num_nodes of lay_num-2
	layers[num - 1].num_nodes = out; //set num_nodes of lay_num-1 to out
	layers[num - 1].chr = (node *)malloc(sizeof(node) * out); // set char of lay_num-1 for memory allocation to out

    for(int i = 0; i < out; i++){
		(layers[num - 1].chr[i]).num_inputs = nd + 1; //set num_inputs of chr_i of lay_num-1 to nd+1
		num_weights += nd + 1; //increment of num_weights to nd +1
		(layers[num - 1].chr[i]).weights = (float *)malloc(sizeof(float) * (nd + 1));
		(layers[num - 1].chr[i]).inputs = (float *)malloc(sizeof(float) * (nd + 1));
		(layers[num - 1].chr[i]).errors = (float *)malloc(sizeof(float) * (nd + 1));
        /*
            Memory Allocation of weights,inputs and errors of chr_i of lay_num-1 to nd + 1 
        */
		for(int e = 0; e < nd + 1; e++) (layers[num - 1].chr[i]).errors[e] = 0.0; //Set error to 0.0 of chr_i of lay_num-1
	}

    weights = (float *)malloc(sizeof(float) * num_weights); //Memory Allocation of weights to num_weights

}

void neural :: init(){
	float weights[num_weights];
	for(int i = 0; i < num_weights; i++){
		 weights[i] = (float)rand() / (float)RAND_MAX - 0.5; //Setup weight_i to rand variable by rand_max
	}
	put_weights(weights);
	for(int i = num_layers - 2; i >= 0; i--){
		for(int j = 0; j < layers[i].num_nodes ; j++){
			for(int k = 0; k < (layers[i].chr[j]).num_inputs; k++){	
				(layers[i].chr[j]).weights[k] = 1; //set weight_k ie num_inputs range for chr_j of layers_i to 1
			}
		}
	}
}

void neural :: put_weights(float *weights){
	int n = 0;
	for(int i = 0; i < num_layers; i++){
		for(int j = 0; j < layers[i].num_nodes; j++){

			for(int k = 0; k < (layers[i].chr[j]).num_inputs; k++){
				(layers[i].chr[j]).weights[k] = weights[n]; //set weight_k ie num_inputs range for chr_j of layers_i to 1 to weight_n
				n++; //N increment
			}
		}
	}
}