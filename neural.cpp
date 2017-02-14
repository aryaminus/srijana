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
}