#include "dnn.h"
//#include "ap_fixed.h"

int main() {
	float w1[IMAGE_SIZE][HIDDEN_LAYER], b1[HIDDEN_LAYER], w2[HIDDEN_LAYER][OUTPUT_CLASS], b2[OUTPUT_CLASS];
#ifdef PRINT_DEBUG
	cout << "=================== Read Weight ===================" << endl;
#endif

	ifstream fin1("C:/xup/hls/dnn/source/b1.txt");
	for(int i = 0; i < HIDDEN_LAYER; i++)
		fin1 >> b1[i];
	ifstream fin2("C:/xup/hls/dnn/source/bout.txt");
	for(int i = 0; i < OUTPUT_CLASS; i++)
		fin2 >> b2[i];
	ifstream fin3("C:/xup/hls/dnn/source/W1.txt");
	for(int i = 0; i < IMAGE_SIZE; i++)
		for(int j = 0; j < HIDDEN_LAYER; j++)
			fin3 >> w1[i][j];
	ifstream fin4("C:/xup/hls/dnn/source/Wout.txt");
	for(int i = 0; i < HIDDEN_LAYER; i++)
		for(int j = 0; j < OUTPUT_CLASS; j++)
			fin4 >> w2[i][j];

	if(!fin1 | !fin2 | !fin3 | !fin4) {
		cout << "Open txt error in read weights";
		return -1;
	}
	fin1.close();
	fin2.close();
	fin3.close();
	fin4.close();

	w1_t w1_fp[IMAGE_SIZE][HIDDEN_LAYER];
	b1_t b1_fp[HIDDEN_LAYER];
	w2_t w2_fp[HIDDEN_LAYER][OUTPUT_CLASS];
	b2_t b2_fp[OUTPUT_CLASS];

	for(int i = 0; i < HIDDEN_LAYER; i++)
		b1_fp[i] = b1_t(b1[i]);
	for(int i = 0; i < OUTPUT_CLASS; i++)
		b2_fp[i] = b2_t(b2[i]);
	for(int i = 0; i < IMAGE_SIZE; i++)
		for(int j = 0; j < HIDDEN_LAYER; j++)
			w1_fp[i][j] = w1_t(w1[i][j]);
	for(int i = 0; i < HIDDEN_LAYER; i++)
		for(int j = 0; j < OUTPUT_CLASS; j++)
			w2_fp[i][j] = w2_t(w2[i][j]);

#ifdef PRINT_DEBUG
	cout << "=================== Read Images ===================" << endl;
#endif	
	int predict_labels[IMAGE_NUMS];
	for(int i = 0; i < IMAGE_NUMS; i++) {
		float image[IMAGE_SIZE];
		ifstream fin;
	    stringstream ss;
	    ss << "C:/xup/hls/dnn/source/testImage/image" << i << ".txt";
		fin.open(ss.str().c_str());
		if(!fin) {
			cout << "Open txt error in read image";
			return -1;
		}
		for(int j = 0; j < IMAGE_SIZE; j++)
			fin >> image[j];

		image_t image_fp[IMAGE_SIZE];
		for(int j = 0; j < IMAGE_SIZE; j++)
			image_fp[j] = image_t(image[j]);

		predict_labels[i] = dnn(image_fp, w1_fp, b1_fp, w2_fp, b2_fp);
		fin.close();
	}
#ifdef PRINT_DEBUG
	cout << "=================== Calculate Accuracy ===================" << endl;
#endif	
	cout << "=================== Predict Labels ===================" << endl;
	for(int i = 0; i < IMAGE_NUMS; i++)
		cout << predict_labels[i] <<'\t';

	ifstream fin5("C:/xup/hls/dnn/source/testImage/label.txt");
	if(!fin5) {
		cout << "Open txt error in read label";
		return -1;
	}
	float correct_labels[IMAGE_NUMS];
	for(int i = 0; i < IMAGE_NUMS; i++) {
		fin5 >> correct_labels[i];
	}
	fin5.close();
	cout << endl << "=================== Correct Labels ===================" << endl;
	for(int i = 0; i < IMAGE_NUMS; i++)
		cout << correct_labels[i] <<'\t';

	int cnt = 0;
	for(int i = 0; i < IMAGE_NUMS; i++) {
		if(correct_labels[i] == predict_labels[i])
			cnt++;
	}
	cout << endl << "=================== Accuracy is " << (double)cnt/IMAGE_NUMS << " ===================" << endl;

	return 0;
}
