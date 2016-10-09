#pragma once
#include "Graphics.h"
#include <cmath> 

namespace task1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	enum WorkMode { COOL_LINE, COOL_CIRCLE, ELIPSE};

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			brush = Brushes::Red;
			bm = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
			pictureBox1->Image = bm;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  lineButton;
	private: Brush^ brush;
	private: Color^ color;
	private: System::Windows::Forms::Button^  drawCircule_button;
			 Bitmap^ bm;
	private: WorkMode mode;
	private: bool isFirstClick = true;
	private: Point^ firstClickPoint = gcnew Point();
	private: Point^ secondClickPoint = gcnew Point();
	private: System::Windows::Forms::Button^  drawElipse_button;




	protected:

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->lineButton = (gcnew System::Windows::Forms::Button());
			this->drawCircule_button = (gcnew System::Windows::Forms::Button());
			this->drawElipse_button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(243, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(661, 369);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox1_MouseClick);
			// 
			// lineButton
			// 
			this->lineButton->Location = System::Drawing::Point(13, 13);
			this->lineButton->Name = L"lineButton";
			this->lineButton->Size = System::Drawing::Size(224, 33);
			this->lineButton->TabIndex = 2;
			this->lineButton->Text = L"draw line";
			this->lineButton->UseVisualStyleBackColor = true;
			this->lineButton->Click += gcnew System::EventHandler(this, &MainForm::lineButton_Click);
			// 
			// drawCircule_button
			// 
			this->drawCircule_button->Location = System::Drawing::Point(12, 52);
			this->drawCircule_button->Name = L"drawCircule_button";
			this->drawCircule_button->Size = System::Drawing::Size(224, 40);
			this->drawCircule_button->TabIndex = 3;
			this->drawCircule_button->Text = L"draw circule";
			this->drawCircule_button->UseVisualStyleBackColor = true;
			this->drawCircule_button->Click += gcnew System::EventHandler(this, &MainForm::drawCircule_button_Click);
			// 
			// drawElipse_button
			// 
			this->drawElipse_button->Location = System::Drawing::Point(13, 98);
			this->drawElipse_button->Name = L"drawElipse_button";
			this->drawElipse_button->Size = System::Drawing::Size(224, 40);
			this->drawElipse_button->TabIndex = 5;
			this->drawElipse_button->Text = L"draw ordinal line";
			this->drawElipse_button->UseVisualStyleBackColor = true;
			this->drawElipse_button->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(916, 393);
			this->Controls->Add(this->drawElipse_button);
			this->Controls->Add(this->drawCircule_button);
			this->Controls->Add(this->lineButton);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void lineButton_Click(System::Object^  sender, System::EventArgs^  e) {
		mode = COOL_LINE;
	}


	private: System::Void drawCircule_button_Click(System::Object^  sender, System::EventArgs^  e) {
		mode = COOL_CIRCLE;
	}

	private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	activePixel(Brushes::Blue, bm, e->X, e->Y);
	if (isFirstClick) {
		firstClickPoint->X = e->X;
		firstClickPoint->Y = e->Y;
		isFirstClick = false;
	}
	else {
		secondClickPoint->X = e->X;
		secondClickPoint->Y = e->Y;
		draw();
		isFirstClick = true;
	}
}

	private: void draw() {	
		switch (mode)
		{
		case COOL_LINE:
			drawLineWithBrezenhem(brush, bm, firstClickPoint->X, firstClickPoint->Y,
				secondClickPoint->X, secondClickPoint->Y);
			break;
		case COOL_CIRCLE:
			drawCircule(brush, bm, firstClickPoint->X, firstClickPoint->Y, calcRadius());
			break;
		case ELIPSE:
			int center_x = firstClickPoint->X + (secondClickPoint->X - firstClickPoint->X ) / 2;
			int center_y = firstClickPoint->Y + (secondClickPoint->Y - firstClickPoint->Y) / 2;
			int a = secondClickPoint->X - center_x;
			int b = center_y - firstClickPoint->Y;
			drawElipse(brush, bm, center_x, center_y, a, b);
			break;
		}
		pictureBox1->Refresh();
	}

	

	private: int calcRadius() {
		 return (int)Math::Sqrt(Math::Pow((secondClickPoint->X - firstClickPoint->X),2) +
			Math::Pow((secondClickPoint->Y - firstClickPoint->Y),2));
		}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	mode = WorkMode::ELIPSE;
}
};


}
