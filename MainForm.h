#pragma once
#include "Ball.h" 
#include <stdlib.h> 
#include <cmath>

namespace PopBallv3 {

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
	private:
		Ball* ballObj;
		int x1, y1, x2, y2;
		float nt = 0;
		float speedUp = 1.1f;
		float speedDown = 0.9f;

	public:
		MainForm(void)
		{
			InitializeComponent();
			MouseWheel += gcnew MouseEventHandler(this, &MainForm::Form_MouseWheel);
			//
			//TODO: Add the constructor code here
			//
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
	public: System::Windows::Forms::PictureBox^ frame;
	private: System::Windows::Forms::Timer^ moveTimer;
	public:
	private: System::Windows::Forms::Timer^ drawTimer;
	private: System::ComponentModel::IContainer^ components;
	protected:

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
			this->components = (gcnew System::ComponentModel::Container());
			this->frame = (gcnew System::Windows::Forms::PictureBox());
			this->moveTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->drawTimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->frame))->BeginInit();
			this->SuspendLayout();
			// 
			// frame
			// 
			this->frame->Location = System::Drawing::Point(13, 13);
			this->frame->Name = L"frame";
			this->frame->Size = System::Drawing::Size(755, 532);
			this->frame->TabIndex = 0;
			this->frame->TabStop = false;
			this->frame->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::frame_Paint);
			this->frame->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::frame_MouseDown);
			this->frame->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::frame_MouseUp);
			// 
			// moveTimer
			// 
			this->moveTimer->Enabled = true;
			this->moveTimer->Interval = 10;
			this->moveTimer->Tick += gcnew System::EventHandler(this, &MainForm::moveTimer_Tick);
			// 
			// drawTimer
			// 
			this->drawTimer->Enabled = true;
			this->drawTimer->Interval = 10;
			this->drawTimer->Tick += gcnew System::EventHandler(this, &MainForm::drawTimer_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(780, 557);
			this->Controls->Add(this->frame);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Pop Balls V3";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->frame))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void frame_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ grp = e->Graphics;
		manager->drawFrame(grp);
	}

	private: System::Void frame_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			PopObject* popBallObj = manager->search(e->X, e->Y);
			if (popBallObj == nullptr) {
				x1 = e->X;
				y1 = e->Y;
			}
			nt = 0;
		}
	}

	private: System::Void frame_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			PopObject* popBallObj = manager->search(e->X, e->Y);
			if (popBallObj == nullptr) {
				ballObj = new Ball(frame->Width, frame->Height, e->X, e->Y);
				x2 = e->X;
				y2 = e->Y;
				if (x2 - x1 != 0 && y2 - y1 != 0) {
					if (nt == 0) {
						nt = 1;
					}
					float dX = (x2 - x1) / nt;
					float dY = (y2 - y1) / nt;
					ballObj->setSpeed(dX, dY);
				}
				manager->add(ballObj);
			}
			else {
				manager->remove(popBallObj);
			}
		}
	}

	private: void Form_MouseWheel(Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (e->Delta < 0) {
			manager->setSpeedAll(speedDown);
		}
		else {
			manager->setSpeedAll(speedUp);
		}
	}

	private: System::Void moveTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		nt++;
		manager->move();
	}
	private: System::Void drawTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		frame->Invalidate();
	}

	private: System::Void MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::ControlKey) { moveTimer->Enabled = false; }
	}
	private: System::Void MainForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::ControlKey) { moveTimer->Enabled = true; }
	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
