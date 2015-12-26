#pragma once

namespace JsonParser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  przycisk;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->przycisk = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// przycisk
			// 
			this->przycisk->Location = System::Drawing::Point(238, 157);
			this->przycisk->Name = L"przycisk";
			this->przycisk->Size = System::Drawing::Size(75, 23);
			this->przycisk->TabIndex = 0;
			this->przycisk->Text = L"przycisk";
			this->przycisk->UseVisualStyleBackColor = true;
			this->przycisk->Click += gcnew System::EventHandler(this, &GUI::button1_Click);
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(561, 330);
			this->Controls->Add(this->przycisk);
			this->Name = L"GUI";
			this->Text = L"Nie zmyœlam";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
	}
	};
}
