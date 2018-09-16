#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

using namespace std;



double char_finder(double target, string input){
	double num_found = 0;
	for(double i = 0; i < input.size(); i++){
		double temp = input[i] - '0';
		if(target == temp){
			num_found++;
		}
	}
	return num_found;
}

void couple_finder(vector<string> &output, double low_bound, double high_bound){
	string to_add = "";
	for(int i = low_bound; i <= high_bound; i++){
		to_add = to_string(i);
		for(int j = low_bound; j <= high_bound; j++){
			to_add += to_string(j);
			//cout << "to_add is: " << to_add << endl;
			output.push_back(to_add);
			//cout << "size of output: " << output.size() << endl;
			to_add = to_string(i);
		}
	}
}

void triple_finder(vector<string> &output, double low_bound, double high_bound){
	string to_add = "";
	string temp = "";
	string temp2 = "";
	for(int i = low_bound; i <= high_bound; i++){
		to_add = to_string(i);
		for(int j = low_bound; j <= high_bound; j++){
			temp2 = to_add;
			to_add += to_string(j);
			for(int k = low_bound; k <= high_bound; k++){
				temp = to_add;
				to_add += to_string(k);
				output.push_back(to_add);
				to_add = temp;
			}
			to_add = temp2;
		}
	}
}

void quadriple_finder(vector<string> &output, double low_bound, double high_bound){
	string to_add = "";
	string temp = "";
	string temp2 = "";
	string temp3 = "";
	for(int i = low_bound; i <= high_bound; i++){
		to_add = to_string(i);
		for(int j = low_bound; j <= high_bound; j++){
			temp2 = to_add;
			to_add += to_string(j);
			for(int k = low_bound; k <= high_bound; k++){
				temp = to_add;
				to_add += to_string(k);
				for(int l = low_bound; l <= high_bound; l++){
					temp3 = to_add;
					to_add += to_string(l);
					output.push_back(to_add);
					to_add = temp3;
				}
				to_add = temp;
			}
			to_add = temp2;
		}
	}
}

void final_finder(vector<string> &output, double low_bound, double high_bound){
	string to_add = "";
	string temp = "";
	string temp2 = "";
	string temp3 = "";
	string temp4 = "";
	for(int i = low_bound; i <= high_bound; i++){
		to_add = to_string(i);
		for(int j = low_bound; j <= high_bound; j++){
			temp2 = to_add;
			to_add += to_string(j);
			for(int k = low_bound; k <= high_bound; k++){
				temp = to_add;
				to_add += to_string(k);
				for(int l = low_bound; l <= high_bound; l++){
					temp3 = to_add;
					to_add += to_string(l);
					for(int m = low_bound; m <= high_bound; m++){
						temp4 = to_add;
						to_add += to_string(m);
						output.push_back(to_add);
						to_add = temp4;
					}
					to_add = temp3;
				}
				to_add = temp;
			}
			to_add = temp2;
		}
	}
}

vector<string> combi_lister(double low_bound, double high_bound, double max_combi){
	vector<string> output;

/*
	output.push_back("11");
	output.push_back("12");
	output.push_back("21");
	output.push_back("22");
*/
	couple_finder(output, low_bound, high_bound);
	if(max_combi > 2){
		triple_finder(output, low_bound, high_bound);
		if(max_combi > 3){
			quadriple_finder(output, low_bound, high_bound);
			if(max_combi > 4){
				final_finder(output, low_bound, high_bound);
			}
		}
	}


	return output;
}

int main(){
	double perfect_score = 0;
	double total_score = 0;
	double seq_size;
	double low_bound;
	double high_bound;
	double max_combi = 0;
	double range;
	string sequence;

	cout << "Enter the inclusive range of numbers seperated by a space." << endl;
	cin >> low_bound;
	cin >> high_bound;
	range = high_bound - low_bound + 1;
	cout << "Enter the sequence." << endl;
	cin >> sequence;
	seq_size = sequence.size();
	double temp_chance = 1 / range;
	double chance = temp_chance;
	while(!((chance * seq_size) < 1)){
		max_combi++;
		chance *= temp_chance;
	}
	perfect_score += seq_size;
	for(double i = low_bound; i < high_bound + 1; i++){
		double num_found = char_finder(i, sequence);
		if(num_found > (seq_size / range)){
			total_score += (seq_size / range);
		}
		else{
			total_score += num_found;
		}
	}
	vector<string> poss_combi = combi_lister(low_bound, high_bound, max_combi);
	vector<double> positions;

	//cout << poss_combi.size() << endl;

	for(double i = 0; i < poss_combi.size(); i++){
		double num_found = 0;
		double pos = sequence.find(poss_combi[i], 0);
		double EV = (seq_size * pow((1.0/range), (double)poss_combi[i].size()));
		while(pos != string::npos){
			positions.push_back(pos);
			num_found++;
			pos = sequence.find(poss_combi[i], pos+1);
		}
		//cout << "combi is: " << poss_combi[i] << " and num_found is: " << num_found << endl;
		positions.clear();
		perfect_score += EV;
		if(num_found > EV){
			total_score += EV;
		}
		else{
			total_score += num_found;
		}
	}
	cout << "Given sequence scored " << total_score << " out of " << perfect_score << endl;
	double percent = (total_score / perfect_score) * 100;
	cout << "This results to matching " << percent << "% of expected value, and is thus determined ";
	if(percent > 50){
		cout << "RANDOM." << endl;
	}
	else{
		cout << "PSEUDORANDOM." << endl;
	}
	exit(0);
}