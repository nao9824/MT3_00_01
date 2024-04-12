#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>

const char kWindowTitle[] = "LD2B_08_ワタナベ_ナオ_タイトル";

struct Vector3 {
	float x;
	float y;
	float z;
};

Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(float scalar, const Vector3 v);
float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalize(const Vector3& v);

static const int kColumnwidth = 60;
static const int kRowHeight = 20;

void vectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 v1{ 1.0f,3.0f,-5.0f };
	Vector3 v2{ 4.0f,-1.0f,2.0f };
	float k = { 4.0f };

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Vector3 resultAdd = Add(v1, v2);
		Vector3 resultSubtract = Subtract(v1, v2);
		Vector3 resultMultiply = Multiply(k, v1);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormalize = Normalize(v2);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		vectorScreenPrintf(0, 0, resultAdd, " : Add");
		vectorScreenPrintf(0, kRowHeight, resultSubtract, " : Subtract");
		vectorScreenPrintf(0, kRowHeight * 2, resultMultiply, " : Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength);
		vectorScreenPrintf(0, kRowHeight * 5, resultNormalize, " : Normalize");


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}
//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}
//スカラー倍
Vector3 Multiply(float scalar, const Vector3 v) {
	Vector3 result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;

	return result;
}
//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	Vector3 v3;
	float result;

	v3.x = v1.x * v2.x;
	v3.y = v1.y * v2.y;
	v3.z = v1.z * v2.z;

	result = v3.x + v3.y + v3.z;

	return result;
}
//長さ（ノルム）
float Length(const Vector3& v) {
	float result;

	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	return result;
}
//正規化
Vector3 Normalize(const Vector3& v) {
	float length;
	Vector3 result;

	length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;

	return result;
}
//3次元ベクトルの数値表示
void vectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnwidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnwidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnwidth * 3, y, "%s", label);
}
