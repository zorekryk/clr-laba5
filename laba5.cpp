#include "pch.h"
using namespace System;
int ReadInt(String^ prompt) {
	while (true) {
		Console::WriteLine(L"{0}", prompt);
		String^ line = Console::ReadLine();
		int value;
		if (Int32::TryParse(line, value)) {
			return value;
		}
		Console::WriteLine(L"Некоректне число, спробуйте знову.");
	}
}
int main(array<System::String^>^ args)
{
	int N = 0, M = 0;
	while (N <= 0) N = ReadInt(L"Введіть кільк. рядків (>0): ");
	while (M <= 0) M = ReadInt(L"Введіть кільк. стовпців (>0): ");
	Console::WriteLine(L"Введіть матрицю {0}*{1}: ", N, M);
	int count = N * M;
	array<int>^ all = gcnew array<int>(count);
	int filled = 0;
	while (filled < count) {
		array<String^>^ parts = Console::ReadLine()
			->Split(gcnew array<wchar_t>{' ', '\t'}, StringSplitOptions::RemoveEmptyEntries);
		for each(String ^ p in parts) {
			if (filled < count) {
				all[filled++] = Convert::ToInt32(p);
			}
		}
	}
	array<array<int>^>^ A = gcnew array<array<int>^>(N);
	for (int i = 0; i < N; i++) {
		A[i] = gcnew array<int>(M);
		for (int j = 0; j < M; j++)
			A[i][j] = all[i * M + j];
	}
	array<int>^ rowSum = gcnew array<int>(N);
	for (int i = 0; i < N; i++) {
		int s = 0;
		for (int j = 0; j < M; j++) {
			s += A[i][j];
		}
		rowSum[i] = s;
	}
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (rowSum[j] < rowSum[j + 1]) {
				int tempSum = rowSum[j];
				rowSum[j] = rowSum[j + 1];
				rowSum[j + 1] = tempSum;
				array<int>^ tempRow = A[j];
				A[j] = A[j + 1];
				A[j + 1] = tempRow;
			}
		}
	}
	Console::WriteLine(L"\nРезультат: ");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Console::Write(L"{0,5}", A[i][j]);
		}
		Console::WriteLine();
	}
	return 0;
}