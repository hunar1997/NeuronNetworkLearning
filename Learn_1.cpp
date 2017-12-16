#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef float kart;

vector<vector<kart>> inputs{
	{0,0},
	{1,0},
	{0,1},
	{1,1}
};

vector<kart> weights{1, 1, 1};

vector<vector<kart>> outputs{
	{0},
	{0},
	{0},
	{1}
};

kart activate(kart x, bool deriv=false){
	if (deriv){
		return 1/pow(cosh(x),2);
	}
	return tanh(x);
}

kart lr = 0.1;

int main(){
	cout << "Started"<<endl;
	
	for (int iter=0; iter<1000; iter++){
		for (int i=0; i<inputs.size(); i++){
			kart y = inputs[i][0]*weights[0] + inputs[i][1]*weights[1] + weights[2];
			kart ya = activate(y);
			kart t = outputs[i][0];
			kart error = ya - t;
			
			kart loss = pow(error,2)/2;
			//cout << "loss:" << loss << endl;
			
			kart dloss_derror = error;
			kart derror_dya = 1;
			kart dya_dy = activate(ya,true);
			
			kart dloss_dy = dloss_derror*derror_dya*dya_dy;
			
			kart dloss_dw0 = inputs[i][0] * dloss_dy;
			kart dloss_dw1 = inputs[i][1] * dloss_dy;
			kart dloss_dw2 = 1 * dloss_dy;
			
			weights[0] -= dloss_dw0 * lr;
			weights[1] -= dloss_dw1 * lr;
			weights[2] -= dloss_dw2 * lr;
		}
	}
	
	for (auto i:outputs){
		cout << "[";
		cout << i[0];
		cout << "]";
	}
	cout << endl;
	
	kart error = 0;
	for (int i=0; i<4; i++){
		kart r = weights[0]*inputs[i][0] + weights[1]*inputs[i][1] + weights[2];
		cout << "[" << r  << "]";
		error  += pow((r - outputs[i][0]),2)/2;
	}
	cout << endl << "Average error: " << abs(100*error/inputs.size()) << "%" << endl;
	
	return 0;
}
