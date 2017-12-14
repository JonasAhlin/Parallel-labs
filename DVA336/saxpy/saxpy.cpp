
void seq_SAXPY(float a, float * x, int n, float * y) {
	for (int i = 0; i < n; i++) {
		y[i] = a * x[i] + y[i];
	}
}

void computeSAXPY_Ref(float a, float * x, int n, float * y) {
	seq_SAXPY(a, x, n, y);	
}
