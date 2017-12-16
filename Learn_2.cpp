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

vector<komal> weights{
	{1, 1, 1},
	{1, 1}
};

vector<komal> layers{
	{1},
	{1}
};

vector<komal> outputs{
	{1},
	{0},
	{0},
	{0}
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
			kart l0 = weights[0][0]*inputs[i][0] + weights[0][1]*inputs[i][1] + weights[0][2];
			kart l0_act = activate(l0);
			kart l1 = weights[1][0]*l0_act + weights[1][1];
			kart l1_act = activate(l1);
			
			kart error = l1_act - outputs[i][0];
			kart loss = pow(error,2)/2;
			//cout << "loss:" << loss << endl;
			
			kart derror_l1 = error * activate(l1_act, true);
			kart dl1_dl0 = derror_l1 * activate(l0_act, true);
			
			kart delta_w10 = derror_l1*l0_act;
			kart delta_w11 = derror_l1;
			
			kart delta_w00 = dl1_dl0*inputs[i][0];
			kart delta_w01 = dl1_dl0*inputs[i][1];
			kart delta_w02 = dl1_dl0;
			
			weights[1][0] -= delta_w10 * lr;
			weights[1][1] -= delta_w11 * lr;
			
			weights[0][0] -= delta_w00 * lr;
			weights[0][1] -= delta_w01 * lr;
			weights[0][2] -= delta_w02 * lr;
		}
	}
	
	
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
