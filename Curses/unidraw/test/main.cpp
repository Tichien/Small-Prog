#include "Vector2.h"
#include "Rect.h"

using namespace std;

template <typename T>
bool testVector2(Vector2<T> v){
	cout << v << endl;
	return true;
}

template <typename T>
bool testRect(Rect<T> r){
	cout << r << endl;
	return true;
}

int main(){

	Vector2<Vector2i> vi(Vector2i::up, Vector2i::right);
	Vector2u vu(1);
	Vector2f vf(2.88);

	testVector2(vi);
	testVector2(vu);
	testVector2(vf);

	IntRect ir(2);
	FloatRect fr(3.897);

	testRect(ir);
	testRect(fr);

	return 0;
}