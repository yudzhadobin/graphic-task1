#pragma once
#include <cmath> 
namespace task1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	


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
			Color ^col = gcnew Color();
			pen = gcnew SolidBrush(col->Red);
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
	private: Brush^ pen;
	private: System::Windows::Forms::Button^  drawCircule_button;
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
			this->drawCircule_button->Location = System::Drawing::Point(13, 62);
			this->drawCircule_button->Name = L"drawCircule_button";
			this->drawCircule_button->Size = System::Drawing::Size(224, 40);
			this->drawCircule_button->TabIndex = 3;
			this->drawCircule_button->Text = L"draw circule";
			this->drawCircule_button->UseVisualStyleBackColor = true;
			this->drawCircule_button->Click += gcnew System::EventHandler(this, &MainForm::drawCircule_button_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(916, 393);
			this->Controls->Add(this->drawCircule_button);
			this->Controls->Add(this->lineButton);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		void activePixel(Brush^ brush, int x, int y) {
			Graphics ^im = pictureBox1->CreateGraphics();

			im->FillRectangle(brush, x, y, 1, 1);
			
			
		}


	private: System::Void lineButton_Click(System::Object^  sender, System::EventArgs^  e) {
		drawLineWithBrezenhem(0, 0, 300, 200);
		//activePixel(pen);
		}

	private: void drawLineWithBrezenhem(int start_x, int start_y, int end_x, int end_y) {
		int cur_x = start_x;
		int cur_y = start_y;
		int delta_x = std::abs(end_x - start_x);
		int delta_y = std::abs(end_y - start_y);
		bool s1 = delta_x > 0;
		bool s2 = delta_y > 0;
		bool was_swap;
		if (was_swap = delta_y > delta_x) {
			int sub = delta_x;
			delta_x = delta_y;
			delta_y = sub;
		}

		int error = 2 * delta_y - delta_x;
		int i = 1;
		while (i <= delta_x)
		{
			activePixel(pen, cur_x, cur_y);
			
			if (error >= 0) {
				if (was_swap) {
					cur_x = cur_x + s1;
				}
				else {
					cur_y = cur_y + s2;
				}
				error = error - 2 * delta_x;
			}
			else {
				if (!was_swap) {
					cur_x = cur_x + s1;
				}
				else {
					cur_y = cur_y + s2;
				}
				error = error + 2 * delta_y;
				i += 1;
			}
		}
	}

		private: void drawCircule(int start_x, int start_y, int radius) {
			int cur_x = 0;
			int cur_y = radius;
			int delta = 2 * (1 - radius);
			int limit = 0;
			while(true){
				activePixel(pen, start_x + cur_x, start_y + cur_y);
				activePixel(pen, start_x + cur_x, start_y - cur_y);
				activePixel(pen, start_x - cur_x, start_y + cur_y);
				activePixel(pen, start_x - cur_x, start_y - cur_y);
				if (cur_y <= 0) break;
				
				if (delta >= 0) {
					if (delta > 0) {
						int gamma = 2 * delta - 2 * cur_x - 1;
						if (gamma <= 0) {
							cur_x += 1;
							cur_y -= 1;
							delta += 2 * cur_x - 2 * cur_y + 2;
						}
						else {
							cur_y -= 1;
							delta -= 2 * cur_y + 1;
						}

					}
					else {
						cur_x += 1;
						cur_y -= 1;
						delta += 2 * cur_x - 2 * cur_y + 2;
					}
				}
				else {
					int gamma = 2 * delta + 2 * cur_y - 1;
					if (gamma <= 0) {
						cur_x += 1;
						delta += 2 * cur_x + 1;
					}
					else {
						cur_x += 1;
						cur_y -= 1;
						delta += 2 * cur_x - 2 * cur_y + 2;
					}
				}
			}
		}
	
				 
private: System::Void drawCircule_button_Click(System::Object^  sender, System::EventArgs^  e) {
	drawCircule(250, 250, 30);
}
};


}
