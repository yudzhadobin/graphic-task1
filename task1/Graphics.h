#pragma once
#include <cmath> 

using namespace System;
using namespace System::Drawing;

void activePixel(Brush^ brush,Bitmap^ bm, int x, int y);

void drawLineWithBrezenhem(Brush^ brush, Bitmap^ bm, int start_x, int start_y, int end_x, int end_y);

void drawCircule(Brush^ brush, Bitmap^ bm, int start_x, int start_y, int radius);
void drawElipse(Brush^ brush, Bitmap^ bm, int start_x, int start_y, int a, int b);