#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef float kart;
typedef vector<kart> komal;

komal topology{2, 1};

vector<komal> inputs{
	{0,0},
	{1,0},
	{0,1},
	{1,1}
};

vector<komal> outputs{
	{1},
	{0},
	{0},
	{0}
};

vector<komal> weights{
	{1, 1, 1},
	{1, 1}
};

vector<komal> layers{
	inputs[0],
	{1},
	{1}
};

kart activate(kart x, bool deriv=false){
	if (deriv){
		return 1/pow(cosh(x),2);
	}
	return tanh(x);
}

kart lr = 0.01;

int main(){
	cout << "Started"<<endl;
	
	for (int iter=0; iter<1000; iter++){
		for (int i=0; i<inputs.size(); i++){
			komal input = inputs[i];
			komal output = outputs[i];
			layers[0] = input;
			for (int l=0; l<layers.size()-1; l++){
				kart layer = 0;
				for (int w=0; w<weights[l].size()-1; w++){
					layer += weights[l][w]*layers[l][w];
				}
				layer += weights[l].back();
				layers[l+1][0] = activate(layer);
			}
			
			kart error = layers.back()[0] - output[0];
			komal derivs;
			for (int l=layers.size()-1; l>0; l--){
				if (l==layers.size()-1){
					derivs.push_back(error*activate(layers.back()[0], true));
				}else{
					derivs.push_back(derivs.back()*activate(layers[l][0],true));
				}
				for (int w=0; w<weights[l-1].size(); w++){
					kart d = derivs[layers.size()-1-l];
					if (w<weights[l-1].size()-1){
						d *= layers[l-1][w];
					}
					weights[l-1][w] -= d * lr;
				}
			}
		}
	}
	
	for (auto i:outputs) cout<<"["<<i[0]<<"]";cout << endl;
	kart error = 0;
	for (int i=0; i<4; i++){
		kart l0 = weights[0][0]*inputs[i][0] + weights[0][1]*inputs[i][1] + weights[0][2];
		kart l0_act = activate(l0);
		kart l1 = weights[1][0]*l0_act + weights[1][1];
		kart l1_act = activate(l1);
		error  += pow((l1_act-outputs[i][0]),2)/2;
		cout << "[" << l1_act << "]";
	}
	cout << endl << "Average error:" << 100*(error/outputs.size()) << "%" << endl;
	
	return 0;
}
